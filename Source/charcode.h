#define CODE_AUTO   0
#define CODE_SJIS   1
#define CODE_JIS    2
#define CODE_EUC    3
#define CODE_LATIN  4
#define CODE_CYRIL  5
#define CODE_KOI8   6

#define CODE_UTF8   7
#define CODE_UTF7   8
#define CODE_UTF16  9
#define CODE_BINARY 10

USHORT AutoEstimateCharCode(PUCHAR, ULONG,BOOL,BOOL);

BOOL CheckJisCode_KanjiOut(PUCHAR);
BOOL CheckJisCode_KanjiIn(PUCHAR);

VOID JisCharToSjisChar(PUCHAR, PUCHAR);
BOOL JisToSjis(PUCHAR, PUCHAR, BOOL); 
BOOL EucToSjis(PUCHAR, PUCHAR);
ULONG LatinWordCheck(PUCHAR, PUSHORT);
ULONG LatinKeisenCheck(PUCHAR);
INT  LatinCharToSjisChar(PUCHAR, PUCHAR, USHORT);
BOOL LatinToSjis(PUCHAR, PUCHAR, USHORT);   

