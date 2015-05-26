#define INCL_DOSFILEMGR        
#define INCL_DOSMEMMGR         
#define INCL_DOSERRORS         
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#ifdef __EMX__
  #define  _alloca   alloca
#endif

typedef struct _EAstruct {
   USHORT usEAflg;
   USHORT usEALen;
   CHAR   szEAValue[1];
} EASTRUCT;

/******************************************************************/
/*   APIRET GetEALongName(PSZ, PSZ)                               */
/******************************************************************/
APIRET GetEALongName(PSZ psz_fname, PSZ psz_longname) 
{
  char *ea_name = ".LONGNAME";

  APIRET apr_info;

  EASTRUCT *ea_buf;
  EAOP2 eaop;
  PGEA2LIST pgealist;
  PFEA2LIST pfealist;
  PGEA2 pgea;
  PFEA2 pfea;
  int len, size;

  len = strlen(ea_name);
  size = sizeof(GEA2LIST) + len;
  pgealist = _alloca(size);
  pgealist->cbList = size;
  pgea = &pgealist->list[0];
  pgea->oNextEntryOffset = 0;
  pgea->cbName = len;

  strcpy (pgea->szName, ea_name);
  size = sizeof(FEA2LIST) + _MAX_PATH;
  pfealist = _alloca(size);
  pfealist->cbList = size;
  eaop.fpGEA2List = pgealist;
  eaop.fpFEA2List = pfealist;
  eaop.oError = 0;

  apr_info = DosQueryPathInfo (psz_fname, FIL_QUERYEASFROMLIST, 
                               &eaop, sizeof(eaop));
  if (apr_info) return apr_info;

  pfea = &pfealist->list[0];
  if (pfea->cbValue) {
      ea_buf = (EASTRUCT *)(pfea->szName + pfea->cbName + 1);
      memcpy(psz_longname, ea_buf->szEAValue, ea_buf->usEALen);
      *(psz_longname+ea_buf->usEALen)='\0';
  }
  return NO_ERROR;
}

/******************************************************************/
/*   APIRET GetFileSystem (const PSZ, PUSHORT)                    */
/******************************************************************/
APIRET  GetFileSystem (const PSZ psz_drive, PUSHORT pus_filesystem)
{
    /* 戻りデータ・バッファーは FSQBUFFER2、および szName, szFSDName, および */
    /* rgFSAData 用の最大データが入る十分な大きさを持つ必要があります。 　　 */
    /* 一般的には、データはそれほど大きくありません。                        */

   BYTE         fsqBuffer[sizeof(FSQBUFFER2) + (3 * CCHMAXPATH)] = {0};
   ULONG        cbBuffer   = sizeof(fsqBuffer); 
   PFSQBUFFER2  pfsqBuffer = (PFSQBUFFER2) fsqBuffer;
   APIRET       rc         = NO_ERROR; 


   *pus_filesystem=0;
    rc = DosQueryFSAttach(psz_drive, 0, FSAIL_QUERYNAME, pfsqBuffer, &cbBuffer); 

    if (rc == NO_ERROR) {
       if(!strcmp("FAT", (pfsqBuffer->szName + pfsqBuffer->cbName + 1))) {
          *pus_filesystem=1;
       } 
    }
   return rc;
}

