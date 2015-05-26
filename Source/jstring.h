/*
   jstring.h
*/

void jstring_init(void);

VOID _jmakepath(PSZ, PSZ, PSZ, PSZ, PSZ);
void  *jmemcpy(void *, const void *, size_t);

VOID  _jstr__setkanjiflag(UCHAR, PBOOL, PBOOL);
ULONG _jstr_inc(PUCHAR, const PUCHAR);
ULONG _jstr_dec(PUCHAR, const PUCHAR);
ULONG _jstr_now(PUCHAR, const PUCHAR);

PUCHAR jstrchr(PSZ, USHORT);
PUCHAR jstrrchr(PSZ, USHORT);
PSZ    jstrupr(PSZ);
PSZ    jstrlwr(PSZ);

BOOL   iskanji(UCHAR);  
BOOL   iskanji12(PSZ); 
BOOL   iskanjiofs(PSZ,size_t); 
char* jmemstr( const char* ,const char* ,size_t ,int );
int jmemicmp( const char* ,const char* ,size_t );

