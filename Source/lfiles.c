/* ------------------------------------ */
/* Large File (larger than 2GB) Support */
/* ------------------------------------ */

#define  INCL_DOS
#include <os2.h>
#include <string.h>

#include "lfsatype.h"
#include "lfiles.h"

BOOL         bl_g_LargeFileSupport = FALSE;
fnDosOpenL  *pfnDosOpenL = 0;

BOOL lfs_QueryLargeFileSupport(VOID) {
   HMODULE hDOSCALLS;

   bl_g_LargeFileSupport = FALSE;

   if(DosQueryModuleHandle((const PSZ)"DOSCALLS", &hDOSCALLS))
     return FALSE;

   /* Query Dos32OpenL address to check large file support.*/ 
   /* Dos32OpenL ord number is 981.                        */
   if(DosQueryProcAddr(hDOSCALLS, 981L, 0L, (PFN *)&pfnDosOpenL))
      return FALSE;

   bl_g_LargeFileSupport = TRUE;
   return TRUE;
}


APIRET lfs_DosQueryPathInfo(PSZ pszPathName, ULONG ulInfoLevel, 
                  PVOID pInfoBuf, ULONG cbInfoBuf)
{
   APIRET ul_apiret;

   if( (bl_g_LargeFileSupport) || 
       (ulInfoLevel < FIL_STANDARDL) || 
       (ulInfoLevel > FIL_QUERYEASFROMLISTL) )
      return DosQueryPathInfo(pszPathName, ulInfoLevel, pInfoBuf, cbInfoBuf);

   switch(ulInfoLevel) {
      case FIL_STANDARDL:
         {
          FILESTATUS3  fs3_PathInfo3;
          PFILESTATUS3L pfs3L = (PFILESTATUS3L)pInfoBuf;

          ul_apiret = DosQueryPathInfo(pszPathName, FIL_STANDARD, 
                &fs3_PathInfo3, sizeof(FILESTATUS3));

          if(!ul_apiret)
             {
              pfs3L->fdateCreation=  fs3_PathInfo3.fdateCreation;
              pfs3L->ftimeCreation=  fs3_PathInfo3.ftimeCreation;
              pfs3L->fdateLastAccess=fs3_PathInfo3.fdateLastAccess;
              pfs3L->ftimeLastAccess=fs3_PathInfo3.ftimeLastAccess;
              pfs3L->fdateLastWrite= fs3_PathInfo3.fdateLastWrite;
              pfs3L->ftimeLastWrite= fs3_PathInfo3.ftimeLastWrite;
              pfs3L->cbFile=     (LONGLONG)fs3_PathInfo3.cbFile;
              pfs3L->cbFileAlloc=(LONGLONG)fs3_PathInfo3.cbFileAlloc;
              pfs3L->attrFile=       fs3_PathInfo3.attrFile;
             }
          break;
         }

      case FIL_QUERYEASIZEL:
         {
          FILESTATUS4  fs4_PathInfo4;
          PFILESTATUS4L pfs4L = (PFILESTATUS4L)pInfoBuf;

          ul_apiret = DosQueryPathInfo(pszPathName, FIL_QUERYEASIZE, 
                  &fs4_PathInfo4, sizeof(FILESTATUS4));

          if(!ul_apiret)
             {
              pfs4L->fdateCreation=  fs4_PathInfo4.fdateCreation;
              pfs4L->ftimeCreation=  fs4_PathInfo4.ftimeCreation;
              pfs4L->fdateLastAccess=fs4_PathInfo4.fdateLastAccess;
              pfs4L->ftimeLastAccess=fs4_PathInfo4.ftimeLastAccess;
              pfs4L->fdateLastWrite= fs4_PathInfo4.fdateLastWrite;
              pfs4L->ftimeLastWrite= fs4_PathInfo4.ftimeLastWrite;
              pfs4L->cbFile=     (LONGLONG)fs4_PathInfo4.cbFile;
              pfs4L->cbFileAlloc=(LONGLONG)fs4_PathInfo4.cbFileAlloc;
              pfs4L->attrFile=       fs4_PathInfo4.attrFile;
              pfs4L->cbList=         fs4_PathInfo4.cbList;
              }
            break;
         }

      case FIL_QUERYEASFROMLISTL:
            ul_apiret = DosQueryPathInfo(pszPathName, ulInfoLevel-10, 
                  pInfoBuf, cbInfoBuf);
            break;
   }
   return ul_apiret;
}

APIRET lfs_DosSetPathInfo(PSZ pszPathName, ULONG ulInfoLevel, 
             PVOID pInfoBuf, ULONG cbInfoBuf, ULONG flOptions)
{
   APIRET ul_apiret;

   if( (bl_g_LargeFileSupport) || 
       (ulInfoLevel < FIL_STANDARDL) ||
//       (ulInfoLevel > FIL_QUERYEASFROMLISTL) )
       (ulInfoLevel > FIL_QUERYEASIZEL) )
         return DosSetPathInfo(pszPathName, ulInfoLevel, pInfoBuf, 
                   cbInfoBuf, flOptions);

   switch(ulInfoLevel) {
      case FIL_STANDARDL:
         {
          FILESTATUS3  fs3_PathInfo3;
          PFILESTATUS3L pfs3L = (PFILESTATUS3L)pInfoBuf;

          fs3_PathInfo3.fdateCreation    = pfs3L->fdateCreation;
          fs3_PathInfo3.ftimeCreation    = pfs3L->ftimeCreation;
          fs3_PathInfo3.fdateLastAccess  = pfs3L->fdateLastAccess;
          fs3_PathInfo3.ftimeLastAccess  = pfs3L->ftimeLastAccess;
          fs3_PathInfo3.fdateLastWrite   = pfs3L->fdateLastWrite;
          fs3_PathInfo3.ftimeLastWrite   = pfs3L->ftimeLastWrite;
          fs3_PathInfo3.cbFile    = (ULONG)pfs3L->cbFile;
          fs3_PathInfo3.cbFileAlloc=(ULONG)pfs3L->cbFileAlloc;
          fs3_PathInfo3.attrFile         = pfs3L->attrFile;

          ul_apiret = DosSetPathInfo(pszPathName, FIL_STANDARD, 
               &fs3_PathInfo3, sizeof(FILESTATUS3), flOptions);

          break;
         }

      case FIL_QUERYEASIZEL:
          ul_apiret = DosSetPathInfo(pszPathName, ulInfoLevel-10, 
                    pInfoBuf, cbInfoBuf, flOptions);
          break;
   }
   return ul_apiret;
}

APIRET lfs_DosFindFirst(PSZ pszFileSpec, PHDIR phdir, ULONG flAttribute, 
         PVOID pfindbuf, ULONG cbBuf, PULONG pcFileNames, ULONG ulInfoLevel)
{
   if( (bl_g_LargeFileSupport) ||
       (ulInfoLevel < FIL_STANDARDL) ||
       (ulInfoLevel > FIL_QUERYEASFROMLISTL) )
      return DosFindFirst(pszFileSpec, phdir, flAttribute, 
               pfindbuf, cbBuf, pcFileNames, ulInfoLevel);

   {
   APIRET ul_apiret;
   
   switch(ulInfoLevel)
      {
      case FIL_STANDARDL:
         {
         FILEFINDBUF3 ffb3_FileInfo3;
         PFILEFINDBUF3L pffb3L = (PFILEFINDBUF3L)pfindbuf;

         ffb3_FileInfo3.oNextEntryOffset = pffb3L->oNextEntryOffset;

         ul_apiret=DosFindFirst(pszFileSpec, phdir, flAttribute, 
               &ffb3_FileInfo3, cbBuf, pcFileNames, FIL_STANDARD);
         if(!ul_apiret)
            {
            pffb3L->oNextEntryOffset = ffb3_FileInfo3.oNextEntryOffset;
            pffb3L->fdateCreation = ffb3_FileInfo3.fdateCreation;
            pffb3L->ftimeCreation = ffb3_FileInfo3.ftimeCreation;
            pffb3L->fdateLastAccess = ffb3_FileInfo3.fdateLastAccess;
            pffb3L->ftimeLastAccess = ffb3_FileInfo3.ftimeLastAccess;
            pffb3L->fdateLastWrite = ffb3_FileInfo3.fdateLastWrite;
            pffb3L->ftimeLastWrite = ffb3_FileInfo3.ftimeLastWrite;
            pffb3L->cbFile = (LONGLONG)ffb3_FileInfo3.cbFile;
            pffb3L->cbFileAlloc = (LONGLONG)ffb3_FileInfo3.cbFileAlloc;
            pffb3L->attrFile = ffb3_FileInfo3.attrFile;
            pffb3L->cchName = ffb3_FileInfo3.cchName;
            strcpy(pffb3L->achName, ffb3_FileInfo3.achName);
//            memcpy(&(pffb3L->achName), &(ffb3_FileInfo3.achName), CCHMAXPATHCOMP);
            }
         break;
         }
      case FIL_QUERYEASIZEL:
         {
         FILEFINDBUF4 ffb4_FileInfo4;
         PFILEFINDBUF4L pffb4L = (PFILEFINDBUF4L)pfindbuf;

         ffb4_FileInfo4.oNextEntryOffset = pffb4L->oNextEntryOffset;

         ul_apiret=DosFindFirst(pszFileSpec, phdir, flAttribute, 
               &ffb4_FileInfo4, cbBuf, pcFileNames, FIL_QUERYEASIZEL);
         if(!ul_apiret)
            {
            pffb4L->oNextEntryOffset = ffb4_FileInfo4.oNextEntryOffset;
            pffb4L->fdateCreation = ffb4_FileInfo4.fdateCreation;
            pffb4L->ftimeCreation = ffb4_FileInfo4.ftimeCreation;
            pffb4L->fdateLastAccess = ffb4_FileInfo4.fdateLastAccess;
            pffb4L->ftimeLastAccess = ffb4_FileInfo4.ftimeLastAccess;
            pffb4L->fdateLastWrite = ffb4_FileInfo4.fdateLastWrite;
            pffb4L->ftimeLastWrite = ffb4_FileInfo4.ftimeLastWrite;
            pffb4L->cbFile = (LONGLONG)ffb4_FileInfo4.cbFile;
            pffb4L->cbFileAlloc = (LONGLONG)ffb4_FileInfo4.cbFileAlloc;
            pffb4L->attrFile = ffb4_FileInfo4.attrFile;
            pffb4L->cbList = ffb4_FileInfo4.cbList;
            pffb4L->cchName = ffb4_FileInfo4.cchName;
            strcpy(pffb4L->achName, ffb4_FileInfo4.achName);
//            memcpy(&(pffb4L->achName), &(ffb4_FileInfo4.achName), CCHMAXPATHCOMP);
            }
         break;
         }
      case FIL_QUERYEASFROMLISTL:
      default:
         ul_apiret=DosFindFirst(pszFileSpec, phdir, flAttribute, 
               pfindbuf, cbBuf, pcFileNames, ulInfoLevel -10);
         break;
      }
   return ul_apiret;
   }
}

APIRET lfs_DosFindNext(HDIR hdir, PVOID pfindbuf, ULONG cbfindbuf, 
           PULONG pcFilenames, ULONG ulInfoLevel)
{
   if( (bl_g_LargeFileSupport) ||
       (ulInfoLevel < FIL_STANDARDL) ||
       (ulInfoLevel > FIL_QUERYEASFROMLISTL) )
      return DosFindNext(hdir, pfindbuf, cbfindbuf, pcFilenames);

   {
   APIRET ul_apiret;
   
   switch(ulInfoLevel)
      {
      case FIL_STANDARDL:
         {
         FILEFINDBUF3 ffb3_FileInfo3;
         PFILEFINDBUF3L pffb3L = (PFILEFINDBUF3L)pfindbuf;

         ffb3_FileInfo3.oNextEntryOffset = pffb3L->oNextEntryOffset;
         ul_apiret = DosFindNext(hdir, &ffb3_FileInfo3, 
               cbfindbuf, pcFilenames);
         if(!ul_apiret)
            {
            pffb3L->oNextEntryOffset = ffb3_FileInfo3.oNextEntryOffset;
            pffb3L->fdateCreation = ffb3_FileInfo3.fdateCreation;
            pffb3L->ftimeCreation = ffb3_FileInfo3.ftimeCreation;
            pffb3L->fdateLastAccess = ffb3_FileInfo3.fdateLastAccess;
            pffb3L->ftimeLastAccess = ffb3_FileInfo3.ftimeLastAccess;
            pffb3L->fdateLastWrite = ffb3_FileInfo3.fdateLastWrite;
            pffb3L->ftimeLastWrite = ffb3_FileInfo3.ftimeLastWrite;
            pffb3L->cbFile = (LONGLONG)ffb3_FileInfo3.cbFile;
            pffb3L->cbFileAlloc = (LONGLONG)ffb3_FileInfo3.cbFileAlloc;
            pffb3L->attrFile = ffb3_FileInfo3.attrFile;
            pffb3L->cchName = ffb3_FileInfo3.cchName;
            strcpy(pffb3L->achName, ffb3_FileInfo3.achName);
//            memcpy(&(pffb3L->achName), &(ffb3_FileInfo3.achName), CCHMAXPATHCOMP);
            }
         break;
         }
      case FIL_QUERYEASIZEL:
         {
         FILEFINDBUF4 ffb4_FileInfo4;
         PFILEFINDBUF4L pffb4L = (PFILEFINDBUF4L)pfindbuf;

         ffb4_FileInfo4.oNextEntryOffset = pffb4L->oNextEntryOffset;
         ul_apiret = DosFindNext(hdir, &ffb4_FileInfo4, 
               cbfindbuf, pcFilenames);
         if(!ul_apiret)
            {
            pffb4L->oNextEntryOffset = ffb4_FileInfo4.oNextEntryOffset;
            pffb4L->fdateCreation = ffb4_FileInfo4.fdateCreation;
            pffb4L->ftimeCreation = ffb4_FileInfo4.ftimeCreation;
            pffb4L->fdateLastAccess = ffb4_FileInfo4.fdateLastAccess;
            pffb4L->ftimeLastAccess = ffb4_FileInfo4.ftimeLastAccess;
            pffb4L->fdateLastWrite = ffb4_FileInfo4.fdateLastWrite;
            pffb4L->ftimeLastWrite = ffb4_FileInfo4.ftimeLastWrite;
            pffb4L->cbFile = (LONGLONG)ffb4_FileInfo4.cbFile;
            pffb4L->cbFileAlloc = (LONGLONG)ffb4_FileInfo4.cbFileAlloc;
            pffb4L->attrFile = ffb4_FileInfo4.attrFile;
            pffb4L->cbList = ffb4_FileInfo4.cbList;
            pffb4L->cchName = ffb4_FileInfo4.cchName;
            strcpy(pffb4L->achName, ffb4_FileInfo4.achName);
//            memcpy(&(pffb4L->achName), &(ffb4_FileInfo4.achName), CCHMAXPATHCOMP);
            }
         break;
         }
      case FIL_QUERYEASFROMLISTL:
      default:
         ul_apiret = DosFindNext(hdir, pfindbuf, cbfindbuf, pcFilenames);
         break;
      }
   return ul_apiret;
   }
}

APIRET lfs_DosOpen(PSZ pszFileName, PHFILE phf, PULONG pulAction, ULONG cbFile,
         ULONG ulAttribute, ULONG fsOpenFlags, ULONG fsOpenMode, PEAOP2 peaop2)
{
   if( bl_g_LargeFileSupport && pfnDosOpenL ) {
      return pfnDosOpenL(pszFileName, phf, pulAction, (LONGLONG)cbFile, 
            ulAttribute, fsOpenFlags, fsOpenMode, peaop2);
   } else {
      return DosOpen(pszFileName, phf, pulAction, cbFile, 
            ulAttribute, fsOpenFlags, fsOpenMode, peaop2);
   }
}

