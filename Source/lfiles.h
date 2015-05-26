/* ------------------------------------ */
/* Large File (larger than 2GB) Support */
/* ------------------------------------ */


/* function prototype */

/* DosOpenL entry point */
typedef APIRET (EXPENTRY fnDosOpenL)(PSZ, PHFILE, PULONG, LONGLONG,
                  ULONG, ULONG, ULONG, PEAOP2);

/* query large file support ability */
BOOL   lfs_QueryLargeFileSupport(VOID);

/* transform functions */
APIRET lfs_DosQueryPathInfo(PSZ, ULONG, PVOID, ULONG);
APIRET lfs_DosSetPathInfo(PSZ, ULONG, PVOID, ULONG, ULONG);
APIRET lfs_DosFindFirst(PSZ, PHDIR, ULONG, PVOID, ULONG, PULONG, ULONG);

   /* InfoLevel is required to transform findbuf */
APIRET lfs_DosFindNext(HDIR, PVOID, ULONG, PULONG, ULONG);
APIRET lfs_DosOpen(PSZ, PHFILE, PULONG, ULONG, ULONG, ULONG, ULONG, PEAOP2);

