#define INCL_DOS
#include <os2.h>
#include <uconv.h>
#include <string.h>
#include "unicode.h"


#ifdef __GNUC__
#define CALLCONV
#endif

/* Unicode�p���C�u����(UCONV.DLL)�̃��W���[���n���h���y�т`�o�h */
/*extern*/ HMODULE hmoduconv = 0;

typedef int CALLCONV API_UniCreateUconvObject(UniChar*,UconvObject*);
typedef int CALLCONV API_UniFreeUconvObject(UconvObject);
typedef int CALLCONV API_UniStrFromUcs(UconvObject,char*,UniChar*,int);
typedef int CALLCONV API_UniStrToUcs(UconvObject,UniChar*,char*,int);

static API_UniCreateUconvObject* _UniCreateUconvObject = 0;
static API_UniFreeUconvObject* _UniFreeUconvObject = 0;
static API_UniStrFromUcs* _UniStrFromUcs = 0;
static API_UniStrToUcs* _UniStrToUcs = 0;


/* UTF-7��UTF-16�ϊ��i���g���G���f�B�A���Œ�j */
static size_t UTF7ToUTF16LE( char* utf16buf ,size_t utf16max ,const char* utf7str ,int setb );

/* �u�܁`��񂿂����v�΍��p���[�`�� */
static void WinUTF8_to_OS2UTF8( char* str );
static void WinUTF16_to_OS2UTF16( char* str );


/* Unicode�p���W���[���̃��[�h */
/* �����F���� */
/* �߂�l�F���[�h����=TRUE�A���s=FALSE */
int LoadUconvModule(void)
{
	int rc = 0;
	char faildll[CCHMAXPATH];

	if( !DosLoadModule( (PSZ)faildll ,sizeof(faildll) ,(PSZ)"UCONV.DLL" ,&hmoduconv ) ){
		if( !DosQueryProcAddr( hmoduconv ,1/*UniCreateUconvObject*/ ,(PSZ)0 ,(PFN*)&_UniCreateUconvObject ) )
		if( !DosQueryProcAddr( hmoduconv ,4/*UniFreeUconvObject*/ ,(PSZ)0 ,(PFN*)&_UniFreeUconvObject ) )
		if( !DosQueryProcAddr( hmoduconv ,11/*UniStrFromUcs*/ ,(PSZ)0 ,(PFN*)&_UniStrFromUcs ) )
		if( !DosQueryProcAddr( hmoduconv ,12/*UniStrToUcs*/ ,(PSZ)0 ,(PFN*)&_UniStrToUcs ) )
		{
			rc = 1;
		}

		if(!rc){
			FreeUconvModule();
		}
	}
	return rc;
}


/* Unicode�p���W���[���̃A�����[�h */
/* �����F���� */
/* �߂�l�F���� */
void FreeUconvModule(void)
{
	DosFreeModule(hmoduconv); hmoduconv = 0;
	_UniCreateUconvObject = 0;
	_UniFreeUconvObject = 0;
	_UniStrFromUcs = 0;
	_UniStrToUcs = 0;
}


/* UTF-8��Ascii�ϊ� */
/* �����FAscii�p�̃o�b�t�@�A���̒����AUTF-8�̕����� */
/* �߂�l�F�ϊ���̕�����̒��� */
size_t UTF8ToAscii( char* ascbuf ,size_t ascmax ,const char* utf8str )
{
	size_t rc = 0;

	/* �o�C�g�I�[�_�[�}�[�N�͖��� */
	if( ((*(unsigned long*)utf8str)&0xFFFFFF)==0xBFBBEF ){
		utf8str += 3;
	}

	if( ascbuf && ascmax && utf8str){
		size_t winlen = strlen(utf8str)+1;
		char* wintmp = 0;
		size_t ucs2len = winlen*2;
		UniChar* ucs2tmp = 0;

		if( !DosAllocMem( (PPVOID)&wintmp ,winlen ,PAG_COMMIT|PAG_READ|PAG_WRITE )
		 && !DosAllocMem( (PPVOID)&ucs2tmp ,ucs2len ,PAG_COMMIT|PAG_READ|PAG_WRITE ) )
		{
			UconvObject uc;
			int ur;

			/* �u�܁`��񂿂����v�΍� */
			memcpy( wintmp ,utf8str ,winlen );
			WinUTF8_to_OS2UTF8( wintmp );

			/* UTF-8 �� UCS-2 �� Ascii �ϊ� */
			ur = _UniCreateUconvObject( UTF_8 ,&uc );
			if( ur==ULS_SUCCESS ){
				ur = _UniStrToUcs( uc ,ucs2tmp ,wintmp ,ucs2len );
				_UniFreeUconvObject( uc );

				if( ur==ULS_SUCCESS ){
					ur = _UniCreateUconvObject( (UniChar*)L"" ,&uc );
					if( ur==ULS_SUCCESS ){
						ur = _UniStrFromUcs( uc ,ascbuf ,ucs2tmp ,ascmax );
						_UniFreeUconvObject( uc );

						if( ur==ULS_SUCCESS ){
							rc = strlen(ascbuf);
						}
					}
				}
			}
		}

		DosFreeMem(wintmp);
		DosFreeMem(ucs2tmp);
	}
	return rc;
}


/* UTF-7��Ascii�ϊ� */
/* �����FAscii�p�̃o�b�t�@�A���̒����AUTF-7�̕�����ASetB�t���O */
/* �߂�l�F�ϊ���̕�����̒��� */
size_t UTF7ToAscii( char* ascbuf ,size_t ascmax ,const char* utf7str ,int setb )
{
	size_t rc = 0;
	char* utf16buf;
	size_t utf16max = (strlen(utf7str)+1)*2*8/3;

	if( !DosAllocMem( (PPVOID)&utf16buf ,utf16max ,PAG_COMMIT|PAG_READ|PAG_WRITE ) ){
		/* UTF-7 �� UTF-16 �� Ascii �ϊ� */
		UTF7ToUTF16LE( utf16buf ,utf16max ,utf7str ,setb );
		rc = UTF16ToAscii( ascbuf ,ascmax ,utf16buf ,TRUE );
		DosFreeMem(utf16buf);
	}

	return rc;
}


/* UTF-16��Ascii�ϊ� */
/* �����FAscii�p�̃o�b�t�@�A���̒����AUTF-16�̕�����A���g���G���f�B�A���t���O */
/* �߂�l�F�ϊ���̕�����̒��� */
size_t UTF16ToAscii( char* ascbuf ,size_t ascmax ,const char* utf16str ,int little )
{
	size_t rc = 0;
	UniChar* ucs2tmp = 0;
	const unsigned short* up;
	size_t ul;

	/* �o�C�g�I�[�_�[�}�[�N�͖��� */
	switch( *(unsigned short*)utf16str ){
		case 0xFFFE: case 0xFEFF: utf16str += 2;
	}

	/* UTF-16�̕����񒷂𒲂ׂ� */
	for( up = (const unsigned short*)utf16str; *up ;up++ ){}
	ul = (const char*)up - utf16str + 2;

	if( !DosAllocMem( (PPVOID)&ucs2tmp ,ul ,PAG_COMMIT|PAG_READ|PAG_WRITE ) ){
		int ur;
		UconvObject uc;

		if(little){
			/* ���g���G���f�B�A���� UTF-16 ������́AUCS-2 �Ƃ��Ă��̂܂� API �ɓn���� */
			memcpy( ucs2tmp ,utf16str ,ul );
		}
		else{
			/* �r�b�O�G���f�B�A���� UTF-16 ������́A���g���ɕϊ����Ă��� API �ɓn�� */
			/* �iAPI�̓r�b�O�ɂ��Ή����Ă��锤�Ȃ̂����A���̂��ϊ�����肭�s���Ȃ����� */
			/* ����̂ŁA���O�ōs���j */
			const char* sp;
			char* dp;
			for( sp = utf16str ,dp = (char*)ucs2tmp; *((unsigned short*)sp); sp+=2 ,dp+=2 ){
				dp[0] = sp[1];
				dp[1] = sp[0];
			}
			*((unsigned short*)dp) = 0;
		}

		/* �u�܁`��񂿂����v�΍� */
		WinUTF16_to_OS2UTF16( (char*)ucs2tmp );

		/* UCS-2 �� Ascii �ϊ� */
		ur = _UniCreateUconvObject( (UniChar*)L"" ,&uc );
		if( ur==ULS_SUCCESS ){
			ur = _UniStrFromUcs( uc ,ascbuf ,ucs2tmp ,ascmax );
			_UniFreeUconvObject( uc );

			if( ur==ULS_SUCCESS ){
				rc = strlen(ascbuf);
			}
		}

		DosFreeMem( ucs2tmp );
	}

	return rc;
}


/* UTF-7��UTF-16�ϊ��i���g���G���f�B�A���Œ�j */
/* �����FUTF-16�p�̃o�b�t�@�A���̒����AUTF-7�̕�����ASetB�t���O */
/* �߂�l�F�ϊ���̕�����̒��� */
static size_t UTF7ToUTF16LE( char* utf16buf ,size_t utf16max ,const char* utf7str ,int setb )
{
	size_t rc = 0;
	const unsigned char* sp = utf7str;
	unsigned char* dp = utf16buf;
	unsigned char* bp = utf16buf+utf16max-2-1;

	/* UTF-7 �� API �ŃT�|�[�g����Ă��Ȃ��̂ŁA�S�����O�ŕϊ����� */
	while( *sp && dp<bp ){
		if( !setb && *sp!='+' ){
			/* ���ʂ̕���(SetD/SetO) */
			*(dp++) = *(sp++);
			*(dp++) = 0;
			continue;
		}
		else{
			/* SetB�̕��� */
			if( !setb && *(++sp)=='-' ){
				/* �u+-�v�̋L�q = '+' �̈ꎚ */
				*(dp++) = '+';
				*(dp++) = 0;
				sp++;
				continue;
			}
			else{
				/* Base64�ŃG���R�[�h���ꂽ���� */
				int sl = 0;
				unsigned char bk;
				unsigned char u16b[4];
				unsigned char* u16p = u16b;

				setb = 0;

				/* Base64�̃f�R�[�h���s�����[�v */
				while( *sp ){
					unsigned char ch = DCUTF7SETB(*sp);

					if( ch==0xFF ){
						/* SetB�I�� */
						sp += (*sp=='-');
						break;
					}

					switch(sl){
					case 0:
						bk = (ch << 2);
						sl++;
						break;
					case 1:
						*(u16p++) = ( bk | (unsigned char)(ch >> 4) );
						bk = ((ch&0x0F) << 4);
						sl++;
						break;
					case 2:
						*(u16p++) = ( bk | (unsigned char)(ch >> 2) );
						bk = ((ch&0x03) << 6);
						sl++;
						break;
					default: /*case 3:*/
						*(u16p++) = ( bk | ch );
						sl = 0;
						break;
					}

					if( u16p==u16b+2 && (*u16b<0xD8 || *u16b>=0xDC) ){
						if( dp+2>=bp ) break;
						*(dp++) = u16b[1];
						*(dp++) = u16b[0];
						u16p = u16b;
					}
					else
					if( u16p==u16b+4 ){
						if( dp+4>=bp ) break;
						*(dp++) = u16b[1];
						*(dp++) = u16b[0];
						*(dp++) = u16b[3];
						*(dp++) = u16b[2];
						u16p = u16b;
					}
					sp++;
				}
			}
		}
	}

	*((unsigned short*)dp) = 0;
	return rc;
}


#define UTF_WINOS2TABLE_MAX 3


/* UTF-8�pOS2����Windows�ϊ��e�[�u�� */
typedef struct{
	const char Win[3+1];
	const char OS2[3+1];
} UTF8_TABLE_T;

static const UTF8_TABLE_T UTF8_WinOS2Table[UTF_WINOS2TABLE_MAX] ={
  { { 0xEF ,0xBD ,0x9E ,0 /*U+FF5E*/ } ,{ 0xE3 ,0x80 ,0x9C ,0 /*U+301C*/ } } // �` 0x8160
 ,{ { 0xE2 ,0x88 ,0xA5 ,0 /*U+2225*/ } ,{ 0xE2 ,0x80 ,0x96 ,0 /*U+2016*/ } } // �a 0x8161
 ,{ { 0xEF ,0xBC ,0x8D ,0 /*U+FF0D*/ } ,{ 0xE2 ,0x88 ,0x92 ,0 /*U+2212*/ } } // �| 0x817C
};


/* Windows�pUTF-8��������AOS/2�p�ɕϊ�����i�u�܁`��񂿂����v�΍��p�j */
/* �����FWindows�pUTF-8������ */
/* �߂�l�F���� */
static void WinUTF8_to_OS2UTF8( char* str )
{
	const UTF8_TABLE_T* lp;
	for( lp = UTF8_WinOS2Table ;lp<UTF8_WinOS2Table+UTF_WINOS2TABLE_MAX ;lp++ ){
		char* sp = str;
		while( (sp=strstr(sp,lp->Win))!=0 ){
			memcpy(sp,lp->OS2,3);
			sp += 3;
		}
	}
}


/* UTF-16�pOS/2����Windows�ϊ��e�[�u�� */
typedef struct{
	const unsigned short Win;
	const unsigned short OS2;
} UTF16_TABLE_T;

static const UTF16_TABLE_T UTF16LE_WinOS2Table[UTF_WINOS2TABLE_MAX] ={
  { 0xFF5E /*U+FF5E*/ ,0x301C /*U+301C*/ } // �` 0x8160
 ,{ 0x2225 /*U+2225*/ ,0x2016 /*U+2016*/ } // �a 0x8161
 ,{ 0xFF0D /*U+FF0D*/ ,0x2212 /*U+2212*/ } // �| 0x817C
};


/* Windows�pUTF-16��������AOS2�p�ɕϊ�����i�u�܁`��񂿂����v�΍��p�j */
/* �����FWindows�pUTF-16������i���g����p�j */
/* �߂�l�F���� */
static void WinUTF16_to_OS2UTF16( char* str )
{
	const UTF16_TABLE_T* lp;
	for( lp = UTF16LE_WinOS2Table ;lp<UTF16LE_WinOS2Table+UTF_WINOS2TABLE_MAX ;lp++ ){
		unsigned short* sp;
		for( sp = (unsigned short*)str ;*sp ;sp++ ){
			if( *sp==lp->Win ) *sp = lp->OS2;
		}
	}
}

