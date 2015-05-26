 /*********************************************************************/
 /*  Charctor Code Translation                                        */
 /*                                                                   */
 /*  この文字コード変換プログラムは「日経ソフトウエア99年10月号」     */
 /*  のサンプルコードをもとに岡林が変更したコードが含まれています     */
 /*********************************************************************/
 #include <os2.h>
 #include "charcode.h"

 #define ESC  0x1b

USHORT AutoEstimateCharCode(PUCHAR puc_buff, ULONG ul_buffsize ,BOOL disablejp ,BOOL disableutf )
{
   USHORT us_flg_nogaiji=1, us_lang;

   UCHAR uc_max_sjis_lead = us_flg_nogaiji ? 0xef : 0xfc;
   BOOL  bl_sjis_lead = FALSE;
   BOOL  bl_euc_lead = FALSE;
   ULONG ul_hankakukana = 0, ul_latincount=0, ul_cyrilcount=0, ul_koi8count=0,
         ul_ptr_shift=0, ul_count;
   BOOL  bl_code_sjis = FALSE, bl_spacechar = FALSE;

   int chk_utf8 = 0; /* UTF-8 の文字チェックカウンタ */
   int bl_code_utf8 = 0; /* UTF-8 の文字チェックフラグ */
   int not_utf7 = 0; /* UTF-7 に相応しくない記述の検出フラグ */
   int alg_utf7 = 0; /* UTF-7 特有の +/- 記号の組み合わせの検出フラグ */

   switch( *((unsigned short*)puc_buff) ){
   case 0xFFFE:
   case 0xFEFF:
      /* 先頭がUTF-16用のバイトオーダーマーク → UTF-16 */
      return disableutf ? CODE_SJIS : CODE_UTF16;
   }

   if( ((*(unsigned long*)puc_buff)&0xFFFFFF)==0xBFBBEF ){
      /* 先頭がUTF-8用のバイトオーダーマーク → UTF-8 */
      return disableutf ? CODE_SJIS : CODE_UTF8;
   }
   
   for(ul_count=0; ul_count < ul_buffsize; ul_count++) {
      if(puc_buff[ul_count] == ESC) {
         /* 日本語環境でないなら、これ以降のチェックはしない */
         if(disablejp) continue;
         if(ul_count+2 < ul_buffsize) {
            if((puc_buff[ul_count+1] == '$') 
             &&((puc_buff[ul_count+2] == '@')||(puc_buff[ul_count+2] == 'B'))) {
               return CODE_JIS;
            }else if ((puc_buff[ul_count+1] == '(')  
                    &&((puc_buff[ul_count+2] == 'J')||(puc_buff[ul_count+2] == 'B'))) {
               return CODE_JIS;
            }
         }
      } else if (puc_buff[ul_count] > 0x7f) {
         not_utf7 = 1; /* ８ビット文字は、UTF-7 にあらず */

         if( bl_code_utf8!=-1 ){
            /* UTF-8 として正しい文字であるかチェック */
            if( chk_utf8 ){
               chk_utf8--;
            } else if( puc_buff[ul_count]<0xc0 ){
               /* 0xC0 未満 → 未定義 */
               bl_code_utf8 = -1;
            } else if( puc_buff[ul_count]<0xe0 ){
               /* 0xC0～0xDF → ２バイト文字 */
               bl_code_utf8 = puc_buff[ul_count+1]>=0x80 ? +1 : -1;
               chk_utf8 = 1;
            } else if( puc_buff[ul_count]<0xf0 ){
               /* 0xE0～0xEF → ３バイト文字 */
               bl_code_utf8 = puc_buff[ul_count+1]>=0x80 && puc_buff[ul_count+2]>=0x80 ? +1 : -1;
               chk_utf8 = 2;
            } else if( puc_buff[ul_count]<0xf8 ){
               /* 0xF0～0xF7 → ４バイト文字 */
               bl_code_utf8 = puc_buff[ul_count+1]>=0x80 && puc_buff[ul_count+2]>=0x80 
                               && puc_buff[ul_count+3]>=0x80 ? +1 : -1;
               chk_utf8 = 3;
            } else {
               /* 0xF8 以上 → 未定義 */
               bl_code_utf8 = -1;
            }
         }

         /* 日本語環境でないなら、これ以降のチェックはしない */
         if(disablejp) continue;

         if(puc_buff[ul_count] < 0xa1 || puc_buff[ul_count] == 0xff) {
            if( !bl_euc_lead && puc_buff[ul_count]==0x8E 
                             && puc_buff[ul_count+1]>=0xA0 
                             && puc_buff[ul_count+1]<=0xDF ) bl_euc_lead = TRUE;
            else
               bl_code_sjis = TRUE;
//          return CODE_SJIS;
         } else {
            bl_euc_lead = !bl_euc_lead;
            if(puc_buff[ul_count] > 0xfc 
              ||(puc_buff[ul_count] > uc_max_sjis_lead && bl_sjis_lead)) {
//              return CODE_EUC;
            }else if(puc_buff[ul_count] >= 0xe0) {
               bl_sjis_lead = !bl_sjis_lead;
            } else {
               if(!bl_sjis_lead) ul_hankakukana++;
               bl_sjis_lead = 0;   /* 半角カナ領域の場合は必ず０ */

               /* Latin の罫線文字に相当する半角カナが４文字並んでいる */
               if((ul_ptr_shift=LatinKeisenCheck(&puc_buff[ul_count])) > 3) { 
                  ul_count += ul_ptr_shift;
                  ul_latincount += (ul_ptr_shift/3);
                  if(ul_latincount > 10) return CODE_LATIN;
               }
            }
         }
      } else { /* ７ビット */
         if( !not_utf7 ){
            /* UTF-7 の文法を厳密に遵守しているかチェック */
            /* 本来は多少曖昧な表記も許されているのだが、それ（厳密である事）を */
            /* 前提にしないと、 只の Ascii テキストを UTF-7 であると誤認して */
            /* しまう恐れがある */
              switch( puc_buff[ul_count] ){
                 case '\\': case '~':   /* UTF-7 で使われない文字 */
                    not_utf7 = 1;
                    break;
                 case '+':             /* SetB の入口 */
                    alg_utf7 = +1;
                    break;
                 case '-':             /* SetB の出口 */
                    if(alg_utf7) alg_utf7 = -1;
                    break;
                 case '\r': case '\n':
                     /* +/- のアルゴリズムが行内で完結していない場合は、UTF-7 ではないと見なす */
                    if(alg_utf7==+1) not_utf7 = 1;
                    break;
                 default:
                    if(alg_utf7==+1){
                     /* +/- のアルゴリズムの範囲が、SetB 文字だけで占められているかチェック */
                       unsigned char lc = (puc_buff[ul_count]|0x20);
                       not_utf7 = ( (lc<'a' || lc>'z') && (lc<'0' || lc>'9') && lc!='+' && lc!='/' );
                    }
              }
         }

         /* 日本語環境でないなら、これ以降のチェックはしない */
         if(disablejp) continue;

         if(bl_euc_lead) {
            bl_code_sjis = TRUE;
//          return CODE_SJIS;
         }else if(bl_sjis_lead) {
            if(puc_buff[ul_count] < 0x40) {
               if(bl_code_sjis == FALSE) return CODE_EUC;
            } else {
               bl_sjis_lead=0;
            }
         }
      }
  
      if (puc_buff[ul_count] == ' ') {
         bl_spacechar = TRUE;
      } else {
         if(bl_spacechar == TRUE) {
            us_lang=CODE_SJIS;
            if((ul_ptr_shift=LatinWordCheck(&puc_buff[ul_count], &us_lang)) > 0) {
               ul_count += ul_ptr_shift;
               switch(us_lang) {
                  case CODE_LATIN:
                     ul_latincount++;
                     if(ul_latincount > 10) return CODE_LATIN;
                     break;
                  case CODE_CYRIL:
                     ul_cyrilcount++;
                     if(ul_cyrilcount > 10) return CODE_CYRIL;
                     break;
                  case CODE_KOI8:
                     ul_koi8count++;
                     if(ul_koi8count > 10) return CODE_KOI8;
                     break;
               }
            }
         }
         bl_spacechar = FALSE;
      }
  
  }

   if(!disableutf){
      if( bl_code_utf8==+1 ) return CODE_UTF8;
      if( !not_utf7 && alg_utf7!=0 ) return CODE_UTF7;
   }

   if(bl_code_sjis==TRUE) return CODE_SJIS;
   if(ul_hankakukana && us_flg_nogaiji) return CODE_EUC;
   return CODE_SJIS;
}
   

VOID JisCharToSjisChar(PUCHAR puc_h, PUCHAR puc_l) 
{
   if((*puc_h >= 0x21) && (*puc_h <= 0x7e)
    &&(*puc_l >= 0x21) && (*puc_l <=0x7e)) {
      if(*puc_h & 0x01) {
         *puc_l += (*puc_l < 0x60) ? 0x1f : 0x20;
      } else {
         *puc_l += 0x7e;
      }
      *puc_h = (UCHAR)((*puc_h - 0x21) >> 1) + ((*puc_h < 0x5f) ? 0x81 : 0xc1);
   } else {
      /* 変換できない場合は"■"(Shift-JISの0x81a1)を出力 */
      *puc_h = 0x81;
      *puc_l = 0xa1;
   }
}


BOOL CheckJisCode_KanjiOut(PUCHAR puc_jis)
{
   if(puc_jis[0] == ESC) {  // エスケープが現れた
      if(puc_jis[1] == '(' && (puc_jis[2] == 'B' || puc_jis[2] == 'J')) {
           return TRUE;
      }
   }
   return FALSE;
}



BOOL CheckJisCode_KanjiIn(PUCHAR puc_jis)
{
   if(puc_jis[0] == ESC) {  // エスケープが現れた
      if(puc_jis[1] == '$' && (puc_jis[2] == '@' || puc_jis[2] == 'B')) {
           return TRUE;
      }
   }
   return FALSE;
}


BOOL JisToSjis(PUCHAR puc_sjis, PUCHAR puc_jis, BOOL bl_kanji) 
{
   UCHAR c, c2;
   
   while(c = *puc_jis++) {
      if(CheckJisCode_KanjiOut(puc_jis-1)==TRUE) {
         bl_kanji = FALSE;  // ASCIIモードへ切り換え
         puc_jis += 2;
         continue;
      } else if(CheckJisCode_KanjiIn(puc_jis-1)==TRUE) {
         bl_kanji = TRUE;  // 漢字モードへ切り換え
         puc_jis += 2;
         continue;
      }

      if(bl_kanji) {  // 漢字モードの時、文字コード変換
         if(c2 = *puc_jis++) {
            JisCharToSjisChar(&c, &c2);
            *puc_sjis++ = c;
            *puc_sjis++ = c2;
         } else {
            *puc_sjis = '\0';
            return FALSE;
         }
      } else {  // ASCIIモードの時、そのままコピー
         *puc_sjis++ = c;
      }
   }
   *puc_sjis = '\0';
   return TRUE;
}


BOOL EucToSjis(PUCHAR puc_sjis, PUCHAR puc_euc)
{
   UCHAR c, c2;
   
   while(c = *puc_euc++) {
      if(c < 0x80) { 
         *puc_sjis++ = c;
      } else if(c == 0x8e) { // 半角カナ
         *puc_sjis++ = *puc_euc++;
      } else {
         if(c2 = *puc_euc++) {
            c &= 0x7f;
            c2 &= 0x7f;
            JisCharToSjisChar(&c, &c2);
            *puc_sjis++ = c;
            *puc_sjis++ = c2;
         } else {
            *puc_sjis = '\0';
            return FALSE;
         }
      }
   }
   *puc_sjis = '\0';
   return TRUE;
}


#define LATINDIC 9

static UCHAR latinstring1[]={'d', 'a', 0xe1, '\0'};      // "dass" ドイツ語
static UCHAR latinstring2[]={'m', 'u', 0xe1, '\0'};      // "muss"
static UCHAR latinstring3[]={'f', 0x81, 'r', '\0'};      // "fur" 
static UCHAR latinstring4[]={0x81, 'b', 'e', 'r', '\0'}; // "uber"
static UCHAR latinstring5[]={0x85, '\0'};                // "a"    フランス語
static UCHAR latinstring6[]={0x88, 't', 'r', 'e', '\0'}; // "etre"
static UCHAR latinstring7[]={0x8a, '\0'};                // "e"    イタリア語
static UCHAR latinstring8[]={0xa2,'\0'};                 // "B"    ロシア語(CP866)
static UCHAR latinstring9[]={0xd7,'\0'};                // "B""   ロシア語(KOI-8r)

static UCHAR *latinworddic[] = {
   latinstring1, 
   latinstring2, 
   latinstring3, 
   latinstring4, 
   latinstring5, 
   latinstring6, 
   latinstring7, 
   latinstring8,  
   latinstring9,  
};

USHORT latincode_flg[]={
   CODE_LATIN, 
   CODE_LATIN,
   CODE_LATIN,
   CODE_LATIN,
   CODE_LATIN,
   CODE_LATIN,
   CODE_LATIN,
   CODE_CYRIL,
   CODE_KOI8
};

ULONG LatinWordCheck(PUCHAR puc_checkchar, PUSHORT pus_lang) 
{
   USHORT us_count;
   ULONG  ul_len;
   PUCHAR puc_char, puc_dicchar;

   for(us_count=0; us_count<LATINDIC; us_count++) {
      ul_len=0;
      puc_char=puc_checkchar;
      puc_dicchar=latinworddic[us_count];

      while(*puc_dicchar && (*puc_char == *puc_dicchar)) {
         ul_len++;
         puc_char++;
         puc_dicchar++;
      }
      if(*puc_char==' ') { 
         *pus_lang = latincode_flg[us_count];
         return ul_len;
      }
   }   
   return 0;
}


ULONG LatinKeisenCheck(PUCHAR puc_char) 
{
   UCHAR c = *puc_char;

   if(c == (UCHAR)'ﾄ' || c == (UCHAR)'ﾍ' 
        || c == (UCHAR)'ﾛ' || c == (UCHAR)'ｱ' ) {
      ULONG ul_len=0;
      do{
         ul_len++;
         puc_char++;
      }while(*puc_char == c);
      return ul_len;
   }
   return 0;
}



static USHORT LatinCodeTable[256] = 
{ 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
//
  0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f,
//
  0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
//
  0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f,
//
  0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
//
  0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
//
  0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
//
  0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
//
  0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
//
  0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
//
  0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
//
  0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
//                                                             
  0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
//
  0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
//
  0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
//
  0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x007f,
//
  0x0043, 0x0075, 0x0065, 0x0061, 0x0061, 0x0061, 0x0061, 0x0063,
//    C       u       e       a       a       a       a       c
  0x0065, 0x0065, 0x0065, 0x0069, 0x0069, 0x0069, 0x0041, 0x81f0,
//    e       e       e       i       i       i       A      Å
  0x0045, 0x6165, 0x4145, 0x006f, 0x006f, 0x006f, 0x0075, 0x0075,
//    E      ae      AE       o       o       o       u       u
  0x0079, 0x004f, 0x0055, 0x8191, 0x8192, 0x005c, 0x5074, 0x0066,
//    y       O       U      ￠      ￡       \      Pt       f
  0x0061, 0x0069, 0x006f, 0x0075, 0x006e, 0x004e, 0x0061, 0x006f,
//    a       i       o       u       n       N       a       o
  0x003f, 0x0001, 0x0002, 0x2f32, 0x2f34, 0x0021, 0x8173, 0x8174,
//    ?      |~       ~|     /2      /4       !      《      》
  0x001a, 0x001a, 0x0014, 0x0005, 0x0017, 0x0017, 0x0017, 0x0002,
//                            |       -|      -|      -|      ~|
  0x0002, 0x0017, 0x0005, 0x0002, 0x0004, 0x0004, 0x0004, 0x0002,
//    ~|      -|      |       ~|      _|      _|      _|      ~|
  0x0003, 0x0015, 0x0016, 0x0019, 0x0006, 0x0010, 0x0019, 0x0019,
//    |_     _|_     ~|~      |-      -       +       |-      |-
  0x0003, 0x0001, 0x0015, 0x0016, 0x0019, 0x0006, 0x0010, 0x0015,
//    |_      |~     _|_     ~|~      |-      -       +      _|_
  0x0015, 0x0016, 0x0016, 0x0003, 0x0003, 0x0001, 0x0001, 0x0010,
//   _|_     ~|~     ~|~      |_      |_      |~      |~      +
  0x0010, 0x0004, 0x0001, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014,
//    +       _|      |~                              
  0x83bf, 0x83c0, 0x83a1, 0x83ce, 0x83b0, 0x83d0, 0x83ca, 0x83d1,
//   α      β      Γ      π      Σ      σ      μ      τ
  0x8455, 0x83c6, 0x83b6, 0x83c2, 0x8187, 0x83d3, 0x81b8, 0x81bf,
//   Ф      θ      Ω      δ      ∞      φ      ∈      ∩
  0x81df, 0x81d7, 0x8186, 0x8185, 0x81e7, 0x2020, 0x8180, 0x81e0,
//   ≡      ±      ≧      ≦      ∫     "  "     ÷      ≒
  0x00a5, 0x00a5, 0x00a5, 0x81e3, 0x006e, 0x0032, 0x000e, 0x00ff };
//   ･        ･       ･      √      n        2               


static USHORT CyrilCodeTable[256] = 
{ 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
//
  0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f,
//
  0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
//
  0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f,
//
  0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
//
  0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
//
  0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
//
  0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
//
  0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
//
  0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
//
  0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
//
  0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
//                                                             
  0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
//
  0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
//
  0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
//
  0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x007f,
//
  0x8440, 0x8441, 0x8442, 0x8443, 0x8444, 0x8445, 0x8447, 0x8448,
//   А      Б      В      Г      Д      Е      Ж     З
  0x8449, 0x844a, 0x844b, 0x844c, 0x844d, 0x844e, 0x844f, 0x8450,
//   И      Й      К      Л      М      Н      О     П
  0x8451, 0x8452, 0x8453, 0x8454, 0x8455, 0x8456, 0x8457, 0x8458,
//   Р      С      Т      У      Ф      Х      Ц     Ч   
  0x8459, 0x845a, 0x845b, 0x845c, 0x845d, 0x845e, 0x845f, 0x8460,
//   Ш      Щ      Ъ      Ы      Ь      Э      Ю     Я
  0x8470, 0x8471, 0x8472, 0x8473, 0x8474, 0x8475, 0x8477, 0x8478,
//   а      б      в      г      д      е      ж      з
  0x8479, 0x847a, 0x847b, 0x847c, 0x847d, 0x847e, 0x8480, 0x8481,
//   и      й      к      л      м      н      о      п  
  0x001a, 0x001a, 0x0014, 0x0005, 0x0017, 0x0017, 0x0017, 0x0002,
//                            |       -|      -|      -|      ~|
  0x0002, 0x0017, 0x0005, 0x0002, 0x0004, 0x0004, 0x0004, 0x0002,
//    ~|      -|      |       ~|      _|      _|      _|      ~|
  0x0003, 0x0015, 0x0016, 0x0019, 0x0006, 0x0010, 0x0019, 0x0019,
//    |_     _|_     ~|~      |-      -       +       |-      |-
  0x0003, 0x0001, 0x0015, 0x0016, 0x0019, 0x0006, 0x0010, 0x0015,
//    |_      |~     _|_     ~|~      |-      -       +      _|_
  0x0015, 0x0016, 0x0016, 0x0003, 0x0003, 0x0001, 0x0001, 0x0010,
//   _|_     ~|~     ~|~      |_      |_      |~      |~      +
  0x0010, 0x0004, 0x0001, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014,
//    +       _|      |~                              
  0x8482, 0x8483, 0x8484, 0x8485, 0x8486, 0x8487, 0x8488, 0x8489,
//   р      с      т      у      ф      х      ц     ч
  0x848a, 0x848b, 0x8a8c, 0x848d, 0x848e, 0x848f, 0x8490, 0x8491,
//   ш      щ      ъ      ы      ь      э      ю     я
  0x8446, 0x8476, 0x83c3, 0x83c3, 0x8268, 0x8289, 0x8485, 0x8485,
//   Ё      ё      ε      ε      Ｉ      ｉ      у     у
  0x00a5, 0x00a5, 0x00a5, 0x81e3, 0x006e, 0x0032, 0x000e, 0x00ff };
//   ･        ･       ･      √      n        2               

static USHORT Koi8rCodeTable[256] = 
{ 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
//
  0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f,
//
  0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
//
  0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f,
//
  0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
//
  0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
//
  0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
//
  0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
//
  0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
//
  0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
//
  0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
//
  0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
//                                                             
  0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
//
  0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
//
  0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
//
  0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x007f,
//
  0x0006, 0x0005, 0x0001, 0x0002, 0x0003, 0x0004, 0x0019, 0x0017,
//    -       |      |~      ~|      |_      _|      |-     -|
  0x0016, 0x0015, 0x0010, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014,
//   ~|~     _|_      +                                       
  0x001a, 0x001a, 0x0014, 0x81e7, 0x000e, 0x00a5, 0x81e3, 0x81e0,
//                           ∫              ･      √      ≒  
  0x8185, 0x8186, 0x0020, 0x2020, 0x00df, 0x0032, 0x00a5, 0x8180,
//   ≦      ≧                       ﾟ       2       ･     ÷
  0x0006, 0x0005, 0x0001, 0x8476, 0x0001, 0x0001, 0x0002, 0x0002,
//    -       |      |~      ё      |~      |~      ~|      ~|
  0x0002, 0x0003, 0x0003, 0x0003, 0x0004, 0x0004, 0x0004, 0x0019,
//   ~|      |_      |_      |_      _|      _|      _|      |-  
  0x0019, 0x0019, 0x0017, 0x8446, 0x0017, 0x0017, 0x0016, 0x0016,
//   |-      |-      -|      Ё       -|      -|     ~|~     ~|~
  0x0016, 0x0015, 0x0015, 0x0015, 0x0010, 0x0010, 0x0010, 0x0043,
//   ~|~     _|_     _|_     _|_      +       +       +       C 
  0x8490, 0x8470, 0x8471, 0x8488, 0x8474, 0x8475, 0x8486, 0x8473,
//   ю     а       б      ц      д      е      ф      г  
  0x8487, 0x8479, 0x847a, 0x847b, 0x847c, 0x847d, 0x847e, 0x8480,
//   х      и      й      к      л      м      н      о  
  0x8481, 0x8491, 0x8482, 0x8483, 0x8484, 0x8485, 0x8477, 0x8472,
//   п      я      р      с      т      у      ж      в
  0x848c, 0x848d, 0x8478, 0x848a, 0x8478, 0x848b, 0x8489, 0x845d,
//   ь      ы      з      ш      з      щ      ч      Ь
  0x845f, 0x8440, 0x8441, 0x8457, 0x8444, 0x8445, 0x8455, 0x8443,
//   Ю      А      Б      Ц      Д      Е      Ф      Г  
  0x8456, 0x8449, 0x844a, 0x844b, 0x844c, 0x844d, 0x844e, 0x844f,
//   Х      И      Й      К      Л      М      Н     О  
  0x8450, 0x8460, 0x8451, 0x8452, 0x8453, 0x8454, 0x8447, 0x8442,
//   П      Я      Р      С      Т      У      Ж     В
  0x845b, 0x845c, 0x8448, 0x8459, 0x8448, 0x845a, 0x8458, 0x845d,
//   Ъ      Ы      З      Ш      Э      Щ      Ч     Ь
};


USHORT GetLatinCharRable(UCHAR uc_cyril, USHORT us_charcode)
 {
    switch(us_charcode) {
       case CODE_LATIN:
       default:
          return LatinCodeTable[uc_cyril];
       case CODE_CYRIL:
          return CyrilCodeTable[uc_cyril];
       case CODE_KOI8:
          return Koi8rCodeTable[uc_cyril];
    }
}


INT LatinCharToSjisChar(PUCHAR puc_sjis, PUCHAR puc_latin, USHORT us_charcode)
{
   USHORT us_code;
   
   if((us_code=GetLatinCharRable(*puc_latin, us_charcode)) > 0x00ff) {
      if(puc_sjis) {
         *puc_sjis++ = us_code >> 8;
         *puc_sjis++ = (us_code & 0x00ff);
      }
      return 2;
   } else {
      if(puc_sjis) {
         *puc_sjis++ = (us_code & 0x00ff);
      }
      return 1;
   }
}

BOOL LatinToSjis(PUCHAR puc_sjis, PUCHAR puc_latin, USHORT us_charcode)
{
   UCHAR c;
   
   while(c = *puc_latin++) {
      puc_sjis += LatinCharToSjisChar(puc_sjis, &c, us_charcode);
   }
   *puc_sjis = '\0';
   return TRUE;
}

