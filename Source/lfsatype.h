/* ------------------------------------ */
/* Additional definition for EMX gcc    */
/* Large File (larger than 2GB) Support */
/* ------------------------------------ */

/* add into emxos2.h */

typedef long long LONGLONG;
typedef LONGLONG *PLONGLONG;
typedef unsigned long long ULONGLONG;
typedef ULONGLONG *PULONGLONG;


#define FIL_STANDARDL		11
#define FIL_QUERYEASIZEL	12
#define FIL_QUERYEASFROMLISTL	13


typedef struct _FILESTATUS3L
{
  FDATE    fdateCreation;
  FTIME    ftimeCreation;
  FDATE    fdateLastAccess;
  FTIME    ftimeLastAccess;
  FDATE    fdateLastWrite;
  FTIME    ftimeLastWrite;
  LONGLONG cbFile;
  LONGLONG cbFileAlloc;
  ULONG    attrFile;
} FILESTATUS3L;
typedef FILESTATUS3L *PFILESTATUS3L;

typedef struct _FILESTATUS4L
{
  FDATE fdateCreation;
  FTIME ftimeCreation;
  FDATE fdateLastAccess;
  FTIME ftimeLastAccess;
  FDATE fdateLastWrite;
  FTIME ftimeLastWrite;
  LONGLONG cbFile;
  LONGLONG cbFileAlloc;
  ULONG attrFile;
  ULONG cbList;
} FILESTATUS4L;
typedef FILESTATUS4L *PFILESTATUS4L;

typedef struct _FILEFINDBUF3L
{
  ULONG    oNextEntryOffset;
  FDATE    fdateCreation;
  FTIME    ftimeCreation;
  FDATE    fdateLastAccess;
  FTIME    ftimeLastAccess;
  FDATE    fdateLastWrite;
  FTIME    ftimeLastWrite;
  LONGLONG cbFile;
  LONGLONG cbFileAlloc;
  ULONG    attrFile;
  UCHAR    cchName;
  CHAR	   achName[CCHMAXPATHCOMP];
} FILEFINDBUF3L;
typedef FILEFINDBUF3L *PFILEFINDBUF3L;

typedef struct _FILEFINDBUF4L
{
  ULONG oNextEntryOffset;
  FDATE fdateCreation;
  FTIME ftimeCreation;
  FDATE fdateLastAccess;
  FTIME ftimeLastAccess;
  FDATE fdateLastWrite;
  FTIME ftimeLastWrite;
  LONGLONG cbFile;
  LONGLONG cbFileAlloc;
  ULONG attrFile;
  ULONG cbList;
  UCHAR cchName;
  CHAR	achName[CCHMAXPATHCOMP];
} FILEFINDBUF4L;
typedef FILEFINDBUF4L *PFILEFINDBUF4L;

