/* Unicode�p���C�u����(UCONV.DLL)�̃��W���[���n���h�� */
extern HMODULE hmoduconv;

/* Unicode�p���W���[���̃��[�h */
int LoadUconvModule(void);
/* Unicode�p���W���[���̃A�����[�h */
void FreeUconvModule(void);
/* UTF-8��Ascii�ϊ� */
size_t UTF8ToAscii( char* ascbuf ,size_t ascmax ,const char* utf8str );
/* UTF-7��Ascii�ϊ� */
size_t UTF7ToAscii( char* ascbuf ,size_t ascmax ,const char* utf7str ,int setb );
/* UTF-16��Ascii�ϊ� */
size_t UTF16ToAscii( char* ascbuf ,size_t ascmax ,const char* utf16str ,int little );

/* �L�����N�^���AUTF-7 �� SetB �����ɊY�����邩�`�F�b�N���� */
#define ISUTF7SETB(chr) (((chr)>='A'&&(chr)<='Z')||((chr)>='a'&&(chr)<='z')||((chr)>='0'&&(chr)<='9')||(chr)=='+'||(chr)=='/')

/* UTF-7 �� SetB �������A6bit�o�C�i���Ƀf�R�[�h����(�s���ȕ���=0xFF) */
#define DCUTF7SETB(chr) ( ((chr)>='A'&&(chr)<='Z') ? ((chr)-'A') \
						: ((chr)>='a'&&(chr)<='z') ? ((chr)-'a'+26) \
						: ((chr)>='0'&&(chr)<='9') ? ((chr)-'0'+52) \
						: (chr)=='+' ? 62 : (chr)=='/' ? 63 : 0xFF )

/* UTF-16 ������|�C���^��̕������AUCS-2(unsigned short) �Ƃ��Ď擾���� */
#define UTF16WORD(ptr,little) ( little \
 ? *((unsigned short*)(ptr)) \
 : ( (unsigned short)(((unsigned short)(((unsigned char*)(ptr))[0]))<<8) | (unsigned short)(((unsigned char*)(ptr))[1]) ) \
 )

