/* Unicode用ライブラリ(UCONV.DLL)のモジュールハンドル */
extern HMODULE hmoduconv;

/* Unicode用モジュールのロード */
int LoadUconvModule(void);
/* Unicode用モジュールのアンロード */
void FreeUconvModule(void);
/* UTF-8→Ascii変換 */
size_t UTF8ToAscii( char* ascbuf ,size_t ascmax ,const char* utf8str );
/* UTF-7→Ascii変換 */
size_t UTF7ToAscii( char* ascbuf ,size_t ascmax ,const char* utf7str ,int setb );
/* UTF-16→Ascii変換 */
size_t UTF16ToAscii( char* ascbuf ,size_t ascmax ,const char* utf16str ,int little );

/* キャラクタが、UTF-7 の SetB 文字に該当するかチェックする */
#define ISUTF7SETB(chr) (((chr)>='A'&&(chr)<='Z')||((chr)>='a'&&(chr)<='z')||((chr)>='0'&&(chr)<='9')||(chr)=='+'||(chr)=='/')

/* UTF-7 の SetB 文字を、6bitバイナリにデコードする(不正な文字=0xFF) */
#define DCUTF7SETB(chr) ( ((chr)>='A'&&(chr)<='Z') ? ((chr)-'A') \
						: ((chr)>='a'&&(chr)<='z') ? ((chr)-'a'+26) \
						: ((chr)>='0'&&(chr)<='9') ? ((chr)-'0'+52) \
						: (chr)=='+' ? 62 : (chr)=='/' ? 63 : 0xFF )

/* UTF-16 文字列ポインタ上の文字を、UCS-2(unsigned short) として取得する */
#define UTF16WORD(ptr,little) ( little \
 ? *((unsigned short*)(ptr)) \
 : ( (unsigned short)(((unsigned short)(((unsigned char*)(ptr))[0]))<<8) | (unsigned short)(((unsigned char*)(ptr))[1]) ) \
 )

