#define INCL_DOS
#include <os2.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#include "jstring.h"


static unsigned char DBCSEnv[16]; /* DBCS環境テーブル */
/* DBCS環境テーブル取得 */
void jstring_init(void)
{
	COUNTRYCODE cc ={ 0 ,0 };
	DosQueryDBCSEnv( sizeof(DBCSEnv) ,&cc ,DBCSEnv );
}


/*************************************************************/    
/* _jmakepath                                                */    
/*************************************************************/    
VOID _jmakepath(PSZ psz_fullfname, PSZ psz_drive, PSZ psz_path,
                PSZ psz_file, PSZ psz_ext)
{                                           
   ULONG  ul_jstringslen;

   ul_jstringslen=strlen(psz_path);

   if(ul_jstringslen >1) {
      if(*(psz_path+ul_jstringslen-1) == '\\') {
         if(iskanjiofs(psz_path,ul_jstringslen-2) == TRUE)
         {
            strcat(psz_path, "\\");
            _makepath(psz_fullfname, psz_drive, psz_path, psz_file, psz_ext);
            *(psz_path+ul_jstringslen) = '\0';
            return;
         }
      }
   }

   _makepath(psz_fullfname, psz_drive, psz_path, psz_file, psz_ext);
   return;
}

/*************************************************************/    
/* _jstr__setkanjiflag                                        */    
/*************************************************************/    
VOID  _jstr__setkanjiflag(UCHAR uc_char, PBOOL pbl_sjislead, PBOOL pbl_sjistail)
{                                           
   if(*pbl_sjislead==FALSE) {
      if(iskanji(uc_char)==TRUE) {
         *pbl_sjislead = TRUE;
      }
      *pbl_sjistail =FALSE;
   } else {
      if(uc_char!='\0') {
         *pbl_sjistail = TRUE;
      }
      *pbl_sjislead =FALSE;
   }

}    

/*************************************************************/    
/* _jstr_inc                                                 */    
/*************************************************************/    
ULONG  _jstr_inc(PUCHAR puc_str, const PUCHAR puc_char)
{                                           
   BOOL bl_sjislead=FALSE, bl_sjistail=FALSE;
   
   while(*puc_str){
      _jstr__setkanjiflag(*puc_str, &bl_sjislead, &bl_sjistail);

      if(puc_str > puc_char) {
         if(bl_sjislead == TRUE) return (puc_str-puc_char);
         if(bl_sjislead == FALSE && bl_sjistail == FALSE) return (puc_str-puc_char);
      }
      puc_str++;
   }
   return (puc_str-puc_char);
}    


/*************************************************************/    
/* _jstr_dec                                                 */    
/*************************************************************/    
ULONG  _jstr_dec(PUCHAR puc_str, const PUCHAR puc_char)
{                                           
   BOOL bl_sjislead=FALSE, bl_sjistail=FALSE;
   PUCHAR puc_prev=puc_str;
   
   while(*puc_str && puc_str < puc_char){
      _jstr__setkanjiflag(*puc_str, &bl_sjislead, &bl_sjistail);
     
      if(bl_sjislead == TRUE) puc_prev=puc_str;
      if(bl_sjislead == FALSE && bl_sjistail == FALSE) puc_prev=puc_str;
      puc_str++;
   }
   return (puc_str-puc_prev);
}    

/*************************************************************/    
/* _jstr_now                                                 */    
/*************************************************************/    
ULONG  _jstr_now(PUCHAR puc_str, const PUCHAR puc_char)
{                                           
   BOOL bl_sjislead=FALSE, bl_sjistail=FALSE;
   
   while(*puc_str){
      _jstr__setkanjiflag(*puc_str, &bl_sjislead, &bl_sjistail);

      if(puc_str == puc_char) {
         if(bl_sjislead == FALSE && bl_sjistail == TRUE) {
            return 1;
         } else {
            return 0;
         }
      }
      puc_str++;
   }
   return 0;
}    


/*************************************************************/    
/* jmemcpy                                                   */    
/*************************************************************/    
void  *jmemcpy(void *dest, const void *src, size_t count)
{                                           
   BOOL bl_sjislead=FALSE;
   char *destptr, *srcptr;
   
   destptr= (char *)dest;
   srcptr= (char *)src;

   while(count){
      if(bl_sjislead==FALSE) {
         if(iskanji(*srcptr)==TRUE) {
            if(count==1)  {
               return dest;
            } else {
               bl_sjislead =! bl_sjislead;
            }
         }
      } else {
         bl_sjislead =! bl_sjislead;
      }
      *destptr = *srcptr;
      destptr++;
      srcptr++;
      count--;
   }
   return dest;
}    

/*************************************************************/    
/* jstrchr                                                   */    
/*************************************************************/    
PUCHAR jstrchr(PSZ psz_jstring, USHORT us_jchar)
{                                           
   UCHAR  uc_DBCSchar[2];
   PUCHAR puc_matchptr;

   uc_DBCSchar[0]=(UCHAR)((UINT)us_jchar & 0x00ff);
   uc_DBCSchar[1]=(UCHAR)((UINT)us_jchar >> 8);

   if(uc_DBCSchar[1] != 0x00) {
      for(puc_matchptr=psz_jstring; *(puc_matchptr+1) != '\0'; ) {
        if(*puc_matchptr==uc_DBCSchar[0] && *(puc_matchptr+1)==uc_DBCSchar[1])
           return puc_matchptr;
        puc_matchptr++;
      }
   } else {
      for(puc_matchptr=psz_jstring; *puc_matchptr != '\0'; ) {
        if(*puc_matchptr == uc_DBCSchar[0]) {
           if(iskanjiofs(psz_jstring,puc_matchptr-psz_jstring)==FALSE) return puc_matchptr;
        }
        puc_matchptr++;
      }
   }
   return NULL;

}


/*************************************************************/    
/* jstrrchr                                                  */    
/*************************************************************/    
PUCHAR jstrrchr(PSZ psz_jstring, USHORT us_jchar)
{                                           
   UCHAR  uc_DBCSchar[2];
   PUCHAR puc_matchptr, puc_saveptr=NULL;

   uc_DBCSchar[0]=(UCHAR)((UINT)us_jchar & 0x00ff);
   uc_DBCSchar[1]=(UCHAR)((UINT)us_jchar >> 8);

   if(uc_DBCSchar[1] != 0x00) {
      for(puc_matchptr=psz_jstring; *(puc_matchptr+1) != '\0'; ) {
        if(*puc_matchptr==uc_DBCSchar[0] && *(puc_matchptr+1)==uc_DBCSchar[1])
           puc_saveptr = puc_matchptr;
        puc_matchptr++;
      }
   } else {
      for(puc_matchptr=psz_jstring; *puc_matchptr != '\0'; ) {
        if(*puc_matchptr == uc_DBCSchar[0]) {
           if(iskanjiofs(psz_jstring,puc_matchptr-psz_jstring)==FALSE) puc_saveptr = puc_matchptr;
        }
        puc_matchptr++;
      }
   }
   return puc_saveptr;

}


/*************************************************************/    
/* jstrupr                                                   */    
/*************************************************************/    
PUCHAR jstrupr(PSZ psz_jstring)
{                                           
   PUCHAR  puc_char;

   for(puc_char=psz_jstring; *puc_char != '\0'; ) {
      if(iskanji12(puc_char)) { 
         puc_char +=2;
      } else {
         *puc_char=toupper(*puc_char);
         puc_char++;
      }
   }
   
   return psz_jstring;
}

/*************************************************************/    
/* jstrlwr                                                   */    
/*************************************************************/    
PUCHAR jstrlwr(PSZ psz_jstring)
{                                           
   PUCHAR  puc_char;

   for(puc_char=psz_jstring; *puc_char != '\0'; ) {
      if(iskanji12(puc_char)) {
         puc_char +=2;
      } else {
         *puc_char=tolower(*puc_char);
         puc_char++;
      }
   }
   
   return psz_jstring;
}


// 日本語（シフトJIS）以外のDBCS環境に対応
/*************************************************************/    
/* Shift-JIS code のDBCS１バイト目か                         */    
/*************************************************************/    
BOOL iskanji(UCHAR uc_char)
{
	const unsigned char* dp;
	for( dp = DBCSEnv ;*dp ;dp+=2 ){
		if( uc_char>=dp[0] && uc_char<=dp[1] ) return TRUE;
	}
	return FALSE;
}

/*************************************************************/    
/* Shift-JIS code のDBCS１バイト目＋２バイト目か             */    
/*************************************************************/    
BOOL iskanji12(PSZ strp)
{
	return iskanji(strp[0]) && strp[1]!='\0';
}

/*************************************************************/    
/* オフセット位置がDBCSか                                    */    
/*************************************************************/    
BOOL iskanjiofs( PSZ strp ,size_t ofs )
{
	PSZ ofp = strp + ofs;
	for( ;strp<ofp ;strp += 1+iskanji(*strp) ){}
	return strp>ofp ? TRUE : iskanji(*strp);
}


/*************************************************************/    
/* メモリ上の文字列検索(アルファベット大小文字同一視可、DBCS対応) */    
/*************************************************************/    
char* jmemstr( const char* mem ,const char* tgt ,size_t len ,int cas )
{
	const char* rc = 0;
	size_t tlen = strlen(tgt);
	const char* mbtm = mem + len - tlen + 1;

	while( mem<mbtm ){
		if( !(cas ? memcmp(mem,tgt,tlen) : jmemicmp(mem,tgt,tlen) ) ){
			rc = mem;
			break;
		}
		mem += 1 + iskanji( *mem );
	}

	return (char*)rc;
}


/*************************************************************/    
/* メモリの比較(アルファベット大小文字同一視、DBCS対応)      */    
/*************************************************************/    
int jmemicmp( const char* buf1 ,const char* buf2 ,size_t len )
{
	int rc = 0;

	while( len && !rc ){
		if( iskanji(*((const unsigned char*)buf1)) && len>=2 ){
			rc = *((const short*)buf1) - *((const short*)buf2);

			buf1 += 2;
			buf2 += 2;
			len -= 2;
		}
		else{
			unsigned char chr1 = (unsigned char)*buf1;
			unsigned char chr2 = (unsigned char)*buf2;

			if(chr1>='A'&&chr1<='Z') chr1 |= 0x20;
			if(chr2>='A'&&chr2<='Z') chr2 |= 0x20;

			rc = (int)chr1 - (int)chr2;

			buf1++;
			buf2++;
			len -= 1;
		}
	}

	return rc;
}

