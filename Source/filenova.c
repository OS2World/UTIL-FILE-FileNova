 /*********************************************************************/
 /*  FileNova Version 3.10.00                   2008.04.22            */
 /*-------------------------------------------------------------------*/
 /*  �ȉ��̃\�[�X��Filestar Version 2.33 �����ƂɎ�Ƃ��āu���ї����v */
 /*  ���feorge(���c���L)���̋����󂯂ĉ��҂������̂ł��B���̃t�@�C  */
 /*  ���̈����́A�ȉ��Ɏ���FileStar�̒��쌠���̕\�L�ɏ�������̂Ƃ��A */
 /*  �feorge(���c���L)���̋��Ȃ����ҁE���J���s�Ȃ������ւ��܂��B    */
 /*                                                                   */
 /*  �Ȃ��A���̃\�[�X�ɂ͈ȉ��̕��X�̃R�[�h���܂܂�Ă��܂��i�h�̗��j */
 /*                                                                   */
 /*     �feorge(���c���L)    : ��{�I�ȃ��W�b�N�A�x�[�X�R�[�h   �@    */
 /*     ���ї���             : ���҃R�[�h�̑啔��                     */
 /*     �����Ⴂ��(���V�M�F) : �g���q�\�[�g���A�o�O�C��               */
 /*     A.Y.DAYO             : �t�@�C�����̖��������A�p��Ł@Unicode��*/
 /*     kenn(���򌤓�)       : emx�p�̕ύX                            */
 /*     chagrin (YANAGIHARA Nobuyuki)                                 */
 /*                          : �f�B�X�N�̑�e�ʉ��ɔ������������ύX�� */
/*********************************************************************/
 /*-----------------------------------------------------------------------*/
 /*  ________________________________________                             */
 /*  ��FileStar��  File List Utility for OS/2                             */
 /*  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                             */
 /*  Version 2.33                          CopyRight �feorge(���c���L)    */
 /*                                        KGG02311@niftyserve.or.jp      */
 /* �����쌠                               1996.09.30                     */
 /*                                                                       */
 /*   �|�e�������r�������̓t���[�E�G�A�Ƃ��āC�\�[�X�R�[�h���܂߂Č��J    */
 /*�@ �@���܂��D�Ĕz�z�E�ė��p�͎��R�ɍs���Č��\�ł��D                    */
 /*                                                                       */
 /* �@�|�������C��i�Ƃ��Ắu�e�������r�������v�̒��쌏�͂feorge(���c    */
 /*     ���L)���ێ����܂��D���u�e�������r�������v�̉��C���J�͂feorge      */
 /*     (���c���L)�ɂ���Ă̂ݗL���ł���C�\�[�X�R�[�h���ė��p���邱��    */
 /*     �͔F�߂܂����C������u�e�������r�������v�̕ʃo�[�V�����Ƃ���      */
 /*     �feorge(���c���L)�̋��Ȃ����J���邱�Ƃ��֎~�v���܂��D           */
 /*                                                                       */
 /*�@���Ɛӎ���                                                           */
 /*                                                                       */
 /* �@�|���u�e�������r�������v�̈�؂̗��p�́C�g�p�҂̐ӔC�ɂ����čs��    */
 /* �@�@���̂Ƃ��C���̎g�p�ɂ�蒼�ړI�ԐړI�ɐ����������Ȃ鑹�Q�ɂ�    */
 /* �@�@�Ă��C��҂ł���feorge(���c���L)�͈�ؐӔC�𕉂��܂���D         */
 /*                                                                       */
 /*-----------------------------------------------------------------------*/
 #define  INCL_PM       
 #define  INCL_DOS
 #define  INCL_VIO
 #define  INCL_KBD
 #define  INCL_DOSFILEMGR
 #define  INCL_DOSSESMGR
 #define  INCL_ERRORS
 #define  INCL_WINWORKPLACE
 #include <os2.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <signal.h>
 #include <ctype.h>

 #if !defined(IBMCSET) // ��e�ʃt�@�C���΍�����Ȃ�
   #include "lfsatype.h"
 #endif

 #include "filenova.h"
 #include "jstring.h"
 #include "getkeyif.h"
 #include "ea.h"
 #include "unicode.h"

 #ifndef IBMCSET  /* ��e�ʃt�@�C���΍�����Ȃ� */
    #include "lfiles.h"
 #endif
 
/*----------------------------------------*/
/* ��ʐF (�w�i�F <<4 | �����F) �Ŏw��    */
/*----------------------------------------*/
BYTE  bt_g_FilerTytleBarColor      = (VIO_DARKWHITE   <<4 | VIO_BRIGHTBLUE   );
BYTE  bt_g_FilerFunctionBarColor   = (VIO_DARKWHITE   <<4 | VIO_BRIGHTBLUE   );
BYTE  bt_g_FilerWallColor          = (VIO_BLACK       <<4 | VIO_DARKYELLOW   );
BYTE  bt_g_FilerBackGroundColor    = (VIO_BLACK       <<4 | VIO_BLACK        );

BYTE  bt_g_VolumLabelColor         = (VIO_BLACK       <<4 | VIO_BRIGHTRED    );
BYTE  bt_g_CurrentPathColor        = (VIO_BLACK       <<4 | VIO_BRIGHTWHITE  );
BYTE  bt_g_CurrentPathInfomColor   = (VIO_BLACK       <<4 | VIO_BRIGHTYELLOW );
BYTE  bt_g_FileMaskColor           = (VIO_BLACK       <<4 | VIO_DARKWHITE    );

BYTE  bt_g_NormalFileColor         = (VIO_BLACK       <<4 | VIO_BRIGHTWHITE  );
BYTE  bt_g_NormalFileCursorColor   = (VIO_DARKYELLOW  <<4 | VIO_BRIGHTWHITE  );
BYTE  bt_g_DirectryColor           = (VIO_BLACK       <<4 | VIO_BRIGHTCYAN   );
BYTE  bt_g_DirectryCursorColor     = (VIO_DARKYELLOW  <<4 | VIO_BRIGHTCYAN   );
BYTE  bt_g_ReadOnlyFileColor       = (VIO_BLACK       <<4 | VIO_BRIGHTGREEN  );
BYTE  bt_g_ReadOnlyFileCursorColor = (VIO_DARKYELLOW  <<4 | VIO_BRIGHTGREEN  );
BYTE  bt_g_SystemFileColor         = (VIO_BLACK       <<4 | VIO_BRIGHTMAGENTA);
BYTE  bt_g_SystemFileCursorColor   = (VIO_DARKYELLOW  <<4 | VIO_BRIGHTMAGENTA);
BYTE  bt_g_HiddenFileColor         = (VIO_BLACK       <<4 | VIO_BRIGHTBLUE   );
BYTE  bt_g_HiddenFileCursorColor   = (VIO_DARKYELLOW  <<4 | VIO_BRIGHTBLUE   );

BYTE  bt_g_NormalWindowColor       = (VIO_DARKBLUE    <<4 | VIO_BRIGHTCYAN   );
BYTE  bt_g_InformWindowColor       = (VIO_DARKBLUE    <<4 | VIO_BRIGHTGREEN  );
BYTE  bt_g_WarningWindowColor      = (VIO_DARKBLUE    <<4 | VIO_BRIGHTYELLOW );
BYTE  bt_g_HistryWindowColor       = (VIO_DARKBLUE    <<4 | VIO_BRIGHTWHITE  );
BYTE  bt_g_HistryWindowCursorColor = (VIO_DARKYELLOW  <<4 | VIO_BRIGHTWHITE  );
BYTE  bt_g_WindowKeyWordColor      = (VIO_BRIGHTRED   <<4 | VIO_BRIGHTWHITE  );
BYTE  bt_g_InputLineColor          = (VIO_DARKYELLOW  <<4 | VIO_BRIGHTWHITE  );

BYTE  bt_g_ViewerTytleBarColor     = (VIO_DARKWHITE   <<4 | VIO_BRIGHTBLUE   );
BYTE  bt_g_ViewerCharcterColor     = (VIO_BLACK       <<4 | VIO_BRIGHTWHITE  );
BYTE  bt_g_ViewerCRLFColor         = (VIO_BLACK       <<4 | VIO_BRIGHTYELLOW );
BYTE  bt_g_ViewerCRColor           = (VIO_BLACK       <<4 | VIO_BRIGHTGREEN  );
BYTE  bt_g_ViewerLFColor           = (VIO_BLACK       <<4 | VIO_BRIGHTCYAN   );
BYTE  bt_g_ViewerBackGroundColor   = (VIO_BLACK       <<4 | VIO_BLACK        );
BYTE  bt_g_ViewerSearchStrColor    = (VIO_BRIGHTRED   <<4 | VIO_BRIGHTWHITE  );


 /*---------------------------------------------------------------*/
 /* Working Data Section                                          */
 /*---------------------------------------------------------------*/
 /* �t�@�C���Ǘ�/�\���p�o�b�t�@���\���̂ňꊇ�Ǘ����� */
 struct _FlDis{
    UCHAR    Nm[FILE_DISPLEN];
    UCHAR    LongNm[_MAX_PATH];
    BYTE     Atr;
    USHORT   Mark;
    BYTE     DisAtr[2];
#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
    ULONG    cbFile;  /* �t�@�C���T�C�Y�� Nm ����t�˂��Ȃ� */
#else
    unsigned long long cbFile;
#endif
 };
 /* �t�@�C���R�s�[/�ړ�/�폜�p�o�b�t�@���\���̂ňꊇ�Ǘ����� */
 struct _SvDis{
    CHAR     Nm[CCHMAXPATH],Time[16];
    BYTE     Atr;
    USHORT   Mark;
 };
 struct _FlDis* FlDis = 0;
 struct _SvDis* SvDis = 0;


/* �O���v���O�����p�\���� */
EXTERNALPROG  MacroProg[36]     ={0};
EXTERNALPROG  PackerProg[PACKER_MAX]     ={0};
EXTERNALPROG  UnpackerProg[UNPACKER_MAX] ={0};
EXTERNALPROG  AssocProg[ASSOC_MAX]       ={0};

struct _ViewerCfg {
   USHORT usUseExtViewer;
   ULONG  ulTabSize;
   EXTERNALPROG ViewerProg;
   USHORT usDefaultCaseSensitive; // �e�L�X�g�r���[�A�ɂ����錟���̑召�������ꎋ���f�t�H���g�ɂ���I�v
};                                // 0=�召�������ꎋ 1=�召�������
struct _ViewerCfg  ViewerCfg = {0,4,{0},1};

struct _EditorCfg {
   USHORT usLineSetTop;
   EXTERNALPROG EditorProg;
};
struct _EditorCfg  EditorCfg = {0};


 UCHAR  FlstrDirFl[_MAX_PATH], FlstrHstFl[_MAX_PATH], FlstrPhsFl[_MAX_PATH],
        FlstrIniFl[_MAX_PATH], FlstrExeFl[_MAX_PATH]; 

 KBDKEYINFO  KeyInfo;

#define FILER_TITLE_ROW      0
#define FILER_VOL_PATH_ROW   1
#define FILER_PATHINFO_ROW   2
#define FILER_FILEINFO_ROW   3
#define FILER_TOP_MARGIN     5
#define FILER_BOTTOM_MARGIN  1
#define FILER_LISTWINSIZE    (RowMax-FILER_TOP_MARGIN-FILER_BOTTOM_MARGIN)
#define FILER_LISTFILENUM    (FILER_LISTWINSIZE*FileListType)


 ULONG       FlCnt, MarkCnt, StartFl, SelFl, PageNo, ul_g_maxfilenum=MAX_FILE,
             ul_g_initialCodePage;
             
 USHORT      RowMax=0, ColMax=0, FileRow=0, FileListType=2,
             BoxHigh, BoxWide, BoxTop, BoxLeft,
             OverWrite=0, FirstDisp=1, us_g_flg_readonly=0,
             us_g_flg_dosmode=FLAG_DOSMODE_DOSV; 

 UCHAR       Label[12]={0};
 CHAR        DriveDis[3]=" :";
 CHAR        PathDis[_MAX_PATH]="\\";
 CHAR        FreeDis[32];

 CHAR        FlCntDis[32]={0}, MarkCntDis[32]={0}; 
 CHAR        FlMask[_MAX_PATH]="*.*";
 UCHAR       MsgTxt[20][_MAX_PATH], InpLine[CMDSTR_MAX];

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
 ULONG       CurrentSize,      MarkSize;
#else
 unsigned long long   CurrentSize,      MarkSize;
#endif

 UCHAR   HistoryBufDir[HISTORY_MAX][_MAX_PATH] ={0},
         HistoryBufPhs[HISTORY_MAX][_MAX_PATH] ={0},
         HistoryBufHst[HISTORY_MAX][CMDSTR_MAX]={0};
         
 USHORT  ExecSession=1, AutoClose=1, AlwaysSort=0, CaseOfSort=0,  
         us_g_flg_8_3rule=0, us_g_flg_auto_AndF=1, us_g_filesystem=0,
         AssocCnt=0,
         UnpackerCnt=0, us_g_unpack_dir=0, us_g_flg_JumpToUnpackDir=0,
         PackerCnt=0 ; 

 UCHAR   KindOfSort='N',
         ShellName[_MAX_PATH]="CMD.EXE",
         StartupDir[_MAX_PATH]={0}, UnpackDir[_MAX_PATH]={0};


/*------------------------------------------------*/
/*  ��ʕ\��                                      */
/*------------------------------------------------*/
 UCHAR       ListTxt[HISTORY_MAX][CMDSTR_MAX]
                  = {"1 ","2 ","3 ","4 ","5 ","6 ","7 ","8 ","9 ","  ","  "};

 CHAR* Footer[2]={ " 1���� 2�ݒ� 3���� 4 ϸ�   5�ŐV 6�J�� 7**** 8****   9���� 10���� 11���g 12��� "
                  ," 1Help 2Cust 3Hist 4Macr   5Refr 6Open 7**** 8****   9Copy 10ChCp 11Dupl 12Info " };

 UCHAR* FILESTAR_VERSION[2] ={ " ������ FileNova Version 3.10.00 ������         "
                              ," OOoo.. FileNova Version 3.10.00 ..ooOO         " };
 UCHAR  FILESTAR_DATETIME[]=   "                            2008.04.22          ";


static ULONG CodePage[3]; // �R�[�h�y�[�W���i���ɁA���s�E��E���R�[�h�y�[�W�j
/*extern*/ USHORT English = FALSE; // TRUE�ŉp��\��
static BOOL DisableJapanFunc = FALSE; // TRUE�œ��{��łɈˑ������@�\���֎~
static USHORT ForceEnglish = FALSE; // TRUE�ŏ펞�p��\��

// �r���L�����i�f�t�H���g�����{��j
static char LineChar_V[2]     = { 0x05 ,0 }; // 
static char LineChar_H[2]     = { 0x06 ,0 }; // 
static char LineChar_UR[2]    = { 0x03 ,0 }; // 
//static char LineChar_HU[2]  = { 0x15 ,0 }; // 
static char LineChar_UL[2]    = { 0x04 ,0 }; // 
//static char LineChar_VR[2]  = { 0x19 ,0 }; // 
//static char LineChar_VH[2]  = { 0x10 ,0 }; // 
//static char LineChar_VL[2]  = { 0x17 ,0 }; // 
static char LineChar_DR[2]    = { 0x01 ,0 }; // 
static char LineChar_HD[2]    = { 0x16 ,0 }; // 
static char LineChar_DL[2]    = { 0x02 ,0 }; // 


/*-----------------------------------------------*/
/* ���[�N�v���[�X�E�I�u�W�F�N�g�A�N�Z�X�pDLL�֌W */
/*-----------------------------------------------*/
typedef HAPP (EXPENTRY FnStartApp)(HWND,PPROGDETAILS,PSZ,PVOID,ULONG);
typedef BOOL (EXPENTRY FnCreateObject)(PSZ,PSZ,PSZ,PSZ,ULONG);
typedef BOOL (EXPENTRY FnSetObjectData)(HOBJECT,PSZ);
typedef HOBJECT (EXPENTRY FnQueryObject)(PSZ);

HMODULE hModuleMerge = 0; // PMMERGE.DLL
HMODULE hModuleWp = 0;    // PMWP.DLL

FnStartApp*      pfnStartApp      = 0;
FnCreateObject*  pfnCreateObject  = 0;
FnSetObjectData* pfnSetObjectData = 0;
FnQueryObject*   pfnQueryObject   = 0;

typedef HOBJECT (EXPENTRY FnCopyObject)(HOBJECT,HOBJECT,ULONG);
FnCopyObject*    pfnCopyObject    = 0;

 /*****************************************************************/
 /**    FNovaDllLoad                                             **/
 /*****************************************************************/
 BOOL FNovaDllLoad(void)
 {
    char loaderr[_MAX_PATH];

    // WIN-API�p��DLL(PMMERGE.DLL,PMWP.DLL)�����[�h����
    if( DosLoadModule(loaderr, sizeof(loaderr), (PSZ)"PMMERGE", &hModuleMerge)
     || DosLoadModule(loaderr, sizeof(loaderr), (PSZ)"PMWP", &hModuleWp) )
       return FALSE;

    // DLL���[�h���� �� �eAPI�̃A�h���X���擾����
    DosQueryProcAddr(hModuleMerge, 0, (PSZ)"WIN32STARTAPP",      (PFN*)&pfnStartApp);
    if(!pfnStartApp){
        DosQueryProcAddr(hModuleWp, 0, (PSZ)"WINSTARTAPP",  (PFN*)&pfnStartApp);
    }
    // WorkplaceShell���݂�API�́AAPI���ŃA�h���X���擾�ł��Ȃ��̂ŁA�ԍ��Ŏ擾
    DosQueryProcAddr(hModuleWp, 281, (PSZ)0/*"WINCREATEOBJECT"*/,  (PFN*)&pfnCreateObject);
    if(!pfnCreateObject){
        DosQueryProcAddr(hModuleWp, 202, (PSZ)0/*"WINCREATEOBJECT"*/,  (PFN*)&pfnCreateObject);
    }
    DosQueryProcAddr(hModuleWp, 250, (PSZ)0/*"WINSETOBJECTDATA"*/, (PFN*)&pfnSetObjectData);
    DosQueryProcAddr(hModuleWp, 252, (PSZ)0/*"WINQUERYOBJECT"*/,   (PFN*)&pfnQueryObject);
    DosQueryProcAddr(hModuleWp, 288, (PSZ)0/*"WINCOPYOBJECT"*/,    (PFN*)&pfnCopyObject);

    return TRUE;
 }

 /*****************************************************************/
 /**    SigTerm                                                  **/
 /*****************************************************************/
 VOID SigTerm(INT sig) {

      DosFreeModule(hModuleMerge);     /* PMMERGE.DLL�J�� */
      DosFreeModule(hModuleWp);     /* PMWP.DLL�J�� */
      FreeUconvModule(); /* Unicode�p���W���[���̃A�����[�h */

      ChangeCodePageFunc(ul_g_initialCodePage);
      SaveHistoryFile_toDisk();
      DosExit(1,0);
 }
 
 /*****************************************************************/
 /**    Main                                                     **/
 /*****************************************************************/
 int main(INT argc, CHAR *argv[])
 {
    APIRET apr_StartParmDir_Err=NO_ERROR, apr_StartupDir_Err=NO_ERROR;

    signal(SIGINT,  SIG_IGN);
    signal(SIGTERM, SigTerm);
    DosError(FERR_DISABLEHARDERR);  // �G���[�|�b�v�A�b�v�֎~

    GetOriginDir();
    LoadUconvModule(); /* Unicode�p���W���[���̃��[�h */
    LoadHistoryFile_fromDisk();
    InitCustomize(FLAG_FIRST);

    /* �p�����[�^���w�肳��Ă���΂��̃f�B���N�g���Ɉړ� */
    if (argc>1) 
       apr_StartParmDir_Err = ChangeDriveDirFunc(argv[1]);
    
    /* �w�肳��ĂȂ����INI�t�@�C���Ŏw�肳�ꂽ�f�B���N�g���Ɉړ� */
    if(argc==1 || apr_StartParmDir_Err) {
       if(StartupDir[0] != '\0') 
          apr_StartupDir_Err=ChangeDriveDirFunc(StartupDir);
    }

    GetCodePage(FLAG_FIRST);
    GetMode();
    SetWallColor();
    ShowNewDrive();

    /* �f�B���N�g���̈ړ��Ɏ��s�������̃��b�Z�[�W */
    if (apr_StartParmDir_Err) ErrorMsgDisp(apr_StartParmDir_Err, argv[1]);
    if (apr_StartupDir_Err)   ErrorMsgDisp(apr_StartupDir_Err, StartupDir);

    for(;;){
       KbdEvent();
    }
    return 0;
 }

/****************************************************************/
/**  ColorSetup                                                 */
/****************************************************************/
VOID ColorSetup(PSZ psz_IniFileIn)
 {
   if(*psz_IniFileIn == ' ') return;

   bt_g_FilerTytleBarColor   =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Filer_Title_Bar=", bt_g_FilerTytleBarColor);
   bt_g_FilerTytleBarColor   =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "Filer_Title_Letter=", bt_g_FilerTytleBarColor);

   bt_g_FilerFunctionBarColor=ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "FKey_Bar=", bt_g_FilerFunctionBarColor);
   bt_g_FilerFunctionBarColor=ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "FKey_Letter=", bt_g_FilerFunctionBarColor);

   bt_g_FilerWallColor       =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Filer_BackGround=", bt_g_FilerWallColor);
   bt_g_FilerBackGroundColor =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Filer_BackGround=", bt_g_FilerBackGroundColor);
   bt_g_FilerBackGroundColor =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "Filer_BackGround=", bt_g_FilerBackGroundColor);
   bt_g_VolumLabelColor      =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Filer_BackGround=", bt_g_VolumLabelColor);
   bt_g_CurrentPathColor     =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Filer_BackGround=", bt_g_CurrentPathColor);
   bt_g_CurrentPathInfomColor=ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Filer_BackGround=", bt_g_CurrentPathInfomColor);
   bt_g_FileMaskColor        =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Filer_BackGround=", bt_g_FileMaskColor);
   bt_g_NormalFileColor      =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Filer_BackGround=", bt_g_NormalFileColor);
   bt_g_DirectryColor        =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Filer_BackGround=", bt_g_DirectryColor);
   bt_g_ReadOnlyFileColor    =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Filer_BackGround=", bt_g_ReadOnlyFileColor);
   bt_g_SystemFileColor      =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Filer_BackGround=", bt_g_SystemFileColor);
   bt_g_HiddenFileColor      =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Filer_BackGround=", bt_g_HiddenFileColor);

   bt_g_VolumLabelColor      =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "VolumeLabel_Letter=", bt_g_VolumLabelColor);
   bt_g_CurrentPathColor     =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "CurrentDir_Letter=", bt_g_CurrentPathColor);
   bt_g_CurrentPathInfomColor=ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "PathInformation_Letter=", bt_g_CurrentPathInfomColor);
   bt_g_FileMaskColor        =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "FileMask_Letter=", bt_g_FileMaskColor);
   bt_g_FilerWallColor       =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "Filer_Wall=", bt_g_FilerWallColor);

   bt_g_NormalFileColor      =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "NormalFile_Letter=", bt_g_NormalFileColor);
   bt_g_NormalFileCursorColor=ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "NormalFile_Cursor=", bt_g_NormalFileCursorColor);
   bt_g_NormalFileCursorColor=ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "NormalFile_SelectLetter=", bt_g_NormalFileCursorColor);
   bt_g_DirectryColor        =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "Dir_Letter=", bt_g_DirectryColor);
   bt_g_DirectryCursorColor  =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Dir_Cursor=", bt_g_DirectryCursorColor);
   bt_g_DirectryCursorColor  =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "Dir_SelectLetter=", bt_g_DirectryCursorColor);
   bt_g_ReadOnlyFileColor    =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "ReadOnlyFile_Letter=", bt_g_ReadOnlyFileColor);
   bt_g_ReadOnlyFileCursorColor=ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "ReadOnlyFile_Cursor=", bt_g_ReadOnlyFileCursorColor);
   bt_g_ReadOnlyFileCursorColor=ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "ReadOnlyFile_SelectLetter=", bt_g_ReadOnlyFileCursorColor);
   bt_g_SystemFileColor      =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "SystemFile_Letter=", bt_g_SystemFileColor);
   bt_g_SystemFileCursorColor=ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "SystemFile_Cursor=", bt_g_SystemFileCursorColor);
   bt_g_SystemFileCursorColor=ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "SystemFile_SelectLetter=", bt_g_SystemFileCursorColor);
   bt_g_HiddenFileColor      =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "HiddenFile_Letter=", bt_g_HiddenFileColor);
   bt_g_HiddenFileCursorColor=ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "HiddenFile_Cursor=", bt_g_HiddenFileCursorColor);
   bt_g_HiddenFileCursorColor=ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "HiddenFile_SelectLetter=", bt_g_HiddenFileCursorColor);

   bt_g_NormalWindowColor    =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Msw_BackGround=", bt_g_NormalWindowColor);
   bt_g_InformWindowColor    =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Msw_BackGround=", bt_g_InformWindowColor);
   bt_g_WarningWindowColor   =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Msw_BackGround=", bt_g_WarningWindowColor);
   bt_g_HistryWindowColor    =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Msw_BackGround=", bt_g_HistryWindowColor);

   bt_g_NormalWindowColor    =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "Msw_Standard_Letter=", bt_g_NormalWindowColor);
   bt_g_InformWindowColor    =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "Msw_Help_Letter=", bt_g_InformWindowColor);
   bt_g_WarningWindowColor   =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "Msw_Warning_Letter=", bt_g_WarningWindowColor);
   bt_g_HistryWindowColor    =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "Msw_History_Letter=", bt_g_HistryWindowColor);
   bt_g_HistryWindowCursorColor=ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Msw_History_Cursor=", bt_g_HistryWindowCursorColor);
   bt_g_HistryWindowCursorColor=ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "Msw_History_SelectLetter=", bt_g_HistryWindowCursorColor);
   bt_g_WindowKeyWordColor   =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Msw_KeyWord_BackGround=", bt_g_WindowKeyWordColor);
   bt_g_WindowKeyWordColor   =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "Msw_KeyWord_Letter=", bt_g_WindowKeyWordColor);
   bt_g_InputLineColor       =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "Msw_Input_Window=", bt_g_InputLineColor);
   bt_g_InputLineColor       =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "Msw_Input_Letter=", bt_g_InputLineColor);

   bt_g_ViewerTytleBarColor  =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "View_Title_Bar=", bt_g_ViewerTytleBarColor);
   bt_g_ViewerTytleBarColor  =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "View_Title_Letter=", bt_g_ViewerTytleBarColor);
   bt_g_ViewerCharcterColor  =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "View_Letter=", bt_g_ViewerCharcterColor);
   bt_g_ViewerCRLFColor      =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "View_CRLF=", bt_g_ViewerCRLFColor);
   bt_g_ViewerCRColor        =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "View_CR=", bt_g_ViewerCRColor);
   bt_g_ViewerLFColor        =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "View_LF=", bt_g_ViewerLFColor);

   bt_g_ViewerBackGroundColor=ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "View_BackGround=", bt_g_ViewerBackGroundColor);
   bt_g_ViewerBackGroundColor=ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "View_BackGround=", bt_g_ViewerBackGroundColor);
   bt_g_ViewerCharcterColor  =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "View_BackGround=", bt_g_ViewerCharcterColor);
   bt_g_ViewerCRLFColor      =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "View_BackGround=", bt_g_ViewerCRLFColor);
   bt_g_ViewerCRColor        =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "View_BackGround=", bt_g_ViewerCRColor);
   bt_g_ViewerLFColor        =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "View_BackGround=", bt_g_ViewerLFColor);

   bt_g_ViewerSearchStrColor =ColorSetup_ForeGroundChange(psz_IniFileIn, 
                                "View_FoundLetter=", bt_g_ViewerSearchStrColor);
   bt_g_ViewerSearchStrColor =ColorSetup_BackGroundChange(psz_IniFileIn, 
                                "View_FoundLine=",   bt_g_ViewerSearchStrColor);
                                
 }

/****************************************************************/
/**  ColorSetup_BackGroundChange                                */
/****************************************************************/
BYTE ColorSetup_BackGroundChange(PSZ psz_IniFileIn, PSZ psz_keyword, 
                                 BYTE bt_color)
 {
   BYTE  bt_inputcolor;

   bt_inputcolor=ColorSetup_GetColor(psz_IniFileIn, psz_keyword);
   if(bt_inputcolor<0x10) 
      bt_color = (bt_inputcolor << 4 | (bt_color & 0x0f));

   return bt_color;
 }
/****************************************************************/
/**  ColorSetup_ForeGroundChange                                 */
/****************************************************************/
BYTE ColorSetup_ForeGroundChange(PSZ psz_IniFileIn, PSZ psz_keyword, 
                                 BYTE bt_color)
 {
   BYTE  bt_inputcolor;

   bt_inputcolor=ColorSetup_GetColor(psz_IniFileIn, psz_keyword);
   if(bt_inputcolor<0x10) 
      bt_color = ((bt_color & 0xf0) | bt_inputcolor);

   return bt_color;
 }


/****************************************************************/
/**  ColorSetup_GetColor                                         */
/*--------------------------------------------------------------*/
/* �Ԃ�l  0xff(�G���[),  ����ȊO Vio color                    */
/****************************************************************/
BYTE ColorSetup_GetColor(PSZ psz_IniFileIn, PSZ psz_keyword)
 {
   ULONG ul_inputnum;
   BYTE  bt_inputcolor=0xff;
   
   if(SetupGlobalFlag_GetValueAsULONG(psz_IniFileIn, psz_keyword,
                                &ul_inputnum, 0x000000ff)) {
      bt_inputcolor=(BYTE)ul_inputnum;
   }
   return bt_inputcolor;
 }
 
/****************************************************************/
/**   Archive_Pack                                             **/
/****************************************************************/
 ULONG Archive_Pack(PSZ psz_filename, ULONG ul_MarkFileNum)
 {
    USHORT us_count;

    if(!FlCnt) return MYFUNC_NOT_EXEC;
    if(ul_MarkFileNum == 0) {
       if(!strcmp(psz_filename, ".")||!strcmp(psz_filename, "..")) 
          return MYFUNC_NOT_EXEC;
    }
    
    strcpy(MsgTxt[0],
           English ? "Pack to archive file.                         " :
                     "�t�@�C���̈��k���s�Ȃ��܂�                    ");
    strcpy(MsgTxt[1],"                                              ");
    strcpy(MsgTxt[2],"                                              ");
    strcpy(MsgTxt[3],"                                              ");
    strcpy(MsgTxt[4],"                                              ");
    strcpy(MsgTxt[5],"                                              ");
    strcpy(MsgTxt[6],
           English ? "       Enter:Execute    Esc:Cancel            " :
                     "        Enter:���s       Esc:���             ");

    if(ul_MarkFileNum ==0) {
       sprintf(MsgTxt[1],"  File: %s", psz_filename);
    } else {
       sprintf(MsgTxt[1],
               English ? "  File: Marked files( %lu )" :
                         "  File: �}�[�N�t�@�C��( %lu ��)", ul_MarkFileNum);
    }

    sprintf(MsgTxt[3],
            English ? "  Archive filename(Default extention = %s) " :
                      "  ���Ƀt�@�C�����i�g���q�ȗ��� %s �`���j", PackerProg[0].uszExtention);

    if(KbdLineIn(7, bt_g_NormalWindowColor, 4, NULL, 
                 FLAG_INPUTWIN_MSGBOXCLEAR)==ESC) return MYFUNC_EXEC;
    
    for (us_count=0; us_count<PackerCnt; us_count++) {
       if (CheckExtention(InpLine, PackerProg[us_count].uszExtention)) break;
    }
    if (us_count==PackerCnt) us_count=0; /* �ŏ��Ɏw�肳�ꂽPacker */

    /* ��œ��͂��������� InpLine �́��̊֐����Ŏg���� */
    ExecAssocProgram_MsgBox(psz_filename, 
                   PackerProg[us_count].uszProgName, 
                   PackerProg[us_count].uszParamList, 
                   PackerProg[us_count].usSilent = 1, 
                   PackerProg[us_count].usSession, 
                   AutoClose, FLAG_NO_MARK, ul_MarkFileNum, 
                   FLAG_EXECPROG_PACKER);

    /* ����Z�b�V�����Ńv���O���������s���ꂽ�\��������̂� */
    /* �t�@�C�����X�g�����łȂ���ʑS�̂�\��������           */
    QDriveSize();
    ShowFileList_PrevFile(FLAG_DRAW_SCREEN, FlDis[SelFl].Nm+DISP_FN);
    return MYFUNC_EXEC;
 }

/****************************************************************/
/**  Archive_Unpack                                             */
/****************************************************************/
VOID Archive_Unpack(PSZ psz_filename, ULONG ul_MarkFileNum)
 {
    APIRET apr_chdir;
    UCHAR  uc_inputchar;
    PUCHAR puc_inputwinstr=UnpackDir;
    UCHAR  usz_targetdir[_MAX_PATH]={0}, usz_fname_backup[_MAX_PATH]={0};
    USHORT us_count, us_unpack_dir=us_g_unpack_dir, 
           us_flg_jump_dir=us_g_flg_JumpToUnpackDir,
           us_flg_autoclose=AutoClose,
           us_flg_exe_file=0;
           


    if(!FlCnt) return;
    strcpy(usz_fname_backup, psz_filename);

    if(ul_MarkFileNum == 0) {
       if(!strcmp(psz_filename, ".") || !strcmp(psz_filename, "..")) return;
       for (us_count=0; us_count<UnpackerCnt; us_count++) {
          if (CheckExtention(psz_filename, UnpackerProg[us_count].uszExtention)) break;
       }
       if (us_count==UnpackerCnt) {
          if (!CheckExtention(psz_filename, ".exe")) return;
          us_count =0;
          us_flg_exe_file=1;
       }

       if(us_unpack_dir) {
          Archive_Unpack_GetSubDirName(usz_targetdir, UnpackDir, 
                       psz_filename, UnpackerProg[us_count].uszExtention);
          puc_inputwinstr=usz_targetdir;
       }
    }

    do {
       if(English){
          strcpy(MsgTxt[0],"Unpack archive file(s).                           ");
          strcpy(MsgTxt[1],"                                                  ");
          strcpy(MsgTxt[2],"                                                  ");
          strcpy(MsgTxt[3],"  - [F2]Jump to extracted directory automatically ");
          strcpy(MsgTxt[4],"  - [F3]No prompt after extract                   ");
          strcpy(MsgTxt[5],"                                                  ");
          strcpy(MsgTxt[6],"Enter destination directory(Up arrow key:history).");
          strcpy(MsgTxt[7],"                                                  ");
          strcpy(MsgTxt[8],"                                                  ");
          strcpy(MsgTxt[9],"           Enter:Execute      Esc:Cancel          ");
       }
       else{
          strcpy(MsgTxt[0],"���Ƀt�@�C���̉𓀂��s�Ȃ��܂�                    ");
          strcpy(MsgTxt[1],"                                                  ");
          strcpy(MsgTxt[2],"                                                  ");
          strcpy(MsgTxt[3],"  ��[F2]�𓀐�f�B���N�g���Ɏ����I�Ɉړ�          ");
          strcpy(MsgTxt[4],"  ��[F3]�𓀏I����Ƀ��b�Z�[�W���m�F���Ȃ�        ");
          strcpy(MsgTxt[5],"                                                  ");
          strcpy(MsgTxt[6],"�𓀐�̃f�B���N�g�����w�肵�ĉ�����(������˽�ذ) ");
          strcpy(MsgTxt[7],"                                                  ");
          strcpy(MsgTxt[8],"                                                  ");
          strcpy(MsgTxt[9],"           Enter:���s         Esc:���            ");
       }

       if(ul_MarkFileNum==0) {
          sprintf(MsgTxt[1], "  File    : %s", psz_filename);
          sprintf(MsgTxt[2], "  Unpacker: %s", UnpackerProg[us_count].uszProgName);
       } else {
          if(English){
             sprintf(MsgTxt[1], "  File    : Marked files( %lu )", ul_MarkFileNum);
             strcpy (MsgTxt[2], "  - [F1]Assign individual directory to each files ");
          }
          else{
             sprintf(MsgTxt[1], "  File    : �}�[�N�t�@�C��( %lu ��)", ul_MarkFileNum);
             strcpy (MsgTxt[2], "  ��[F1]���ɂ��ƂɌʂ̃T�u�f�B���N�g���ɉ�    ");
          }
          Change_FlagMark(us_unpack_dir,  2, 2);
       }

       Change_FlagMark(us_flg_jump_dir,  3, 2);
       Change_FlagMark(us_flg_autoclose, 4, 2);
       uc_inputchar= KbdLineIn(10, bt_g_NormalWindowColor, 7, puc_inputwinstr,
                               FLAG_INPUTWIN_HISTRY_ON|FLAG_INPUTWIN_NOSTRINGS_OK
                               |FLAG_INPUTWIN_MSGBOXCLEAR|FLAG_INPUTWIN_FUNCKEY_ON); 
       switch(uc_inputchar) {
          case ESC:
             return;
          case ENTER:
             break;
          case ARROW_UP:
             puc_inputwinstr=HistryBox(FLAG_HISTRY_PATH);
             break;
          case PF1:
             if(ul_MarkFileNum) {
                us_unpack_dir=!us_unpack_dir;
             }
             puc_inputwinstr=InpLine;
             break;
          case PF2:
             us_flg_jump_dir=!us_flg_jump_dir;
             puc_inputwinstr=InpLine;
             break;
          case PF3:
             us_flg_autoclose=!us_flg_autoclose;
             puc_inputwinstr=InpLine;
             break;
          case PF12:
             if(us_flg_exe_file==1) {
                us_count++;
                if(us_count==UnpackerCnt) us_count=0;
             }
             break;
          default:
             puc_inputwinstr=InpLine;
             break;
       }
    }while(uc_inputchar!=ENTER);
    
    if(strlen(InpLine)==0) {
        SetFullCurrentPathName(InpLine);
        us_flg_jump_dir=0;
    } else {
        FileCopy_ConverttoAbsolutePath(InpLine);
    }

    if(ul_MarkFileNum==0) {
       if(us_unpack_dir && !strcmp(usz_targetdir, InpLine)) {
          /* �f�t�H���g�̃T�u�f�B���N�g���ɓW�J���m�F�Ȃ� */
          apr_chdir=Archive_Unpack_CurrentFile(us_count, psz_filename, UnpackDir, 
                       us_unpack_dir, us_flg_autoclose);
       } else {
          /* �W�J�悪�ύX���ꂽ���m�F���� */
          apr_chdir=Archive_Unpack_CurrentFile(us_count, psz_filename, InpLine, 
                       us_unpack_dir=0, us_flg_autoclose);
       }
    } else {
       apr_chdir=Archive_Unpack_MarkFile(InpLine, us_unpack_dir, us_flg_autoclose);
    }
    if(!apr_chdir) {
       JumpHistInsert(FLAG_HISTRY_PATH, InpLine);
       if(us_flg_jump_dir && strcmp(InpLine, ".")) {
          ChangeDriveDirFunc(InpLine);
          GetMode();
          SetWallColor();
          ShowNewDrive();
          return;
       }
    }
    
    /* ����Z�b�V�����Ńv���O���������s���ꂽ�\��������̂� */
    /* �t�@�C�����X�g�����łȂ���ʑS�̂�\��������           */
    QDriveSize();
    ShowFileList_PrevFile(FLAG_DRAW_SCREEN, usz_fname_backup);
 }


/****************************************************************/
/**  Archive_Unpack_CurrentFile                                 */
/****************************************************************/
 APIRET Archive_Unpack_CurrentFile(USHORT us_unpackernum, PSZ psz_filename, 
                       PSZ psz_extractdir, USHORT us_flg_unpacksubdir,
                       USHORT us_flg_autoclose)
 {
    UCHAR uc_currentdir[_MAX_PATH], usz_targetdir[_MAX_PATH];
    APIRET apr_chdir;

    SetFullCurrentPathName(uc_currentdir);
    apr_chdir=ChangeDriveDirFunc(psz_extractdir);
    switch(apr_chdir) {
       case ERROR_INVALID_DRIVE:
       case ERROR_NOT_READY:
          ErrorMsgDisp(apr_chdir, "");
       case NO_ERROR:
          break;
       default:   
          /* �Ƃ肠�����ړI�f�B���N�g������邩�m�F */
          if(CreateDir_YesorNo(psz_extractdir, FLAG_GETYESORNO_MSGBOXCLEAR)==ENTER){
             apr_chdir=CreateAndEnterDir(psz_extractdir);
          } 
    }

    if(!apr_chdir) {
       if(us_flg_unpacksubdir) {
          /* �e���ɂ��ƂɃT�u�f�B���N�g������� */
          Archive_Unpack_GetSubDirName(usz_targetdir, psz_extractdir, 
                       psz_filename, UnpackerProg[us_unpackernum].uszExtention);
          apr_chdir=CreateAndEnterDir(usz_targetdir);
       }
    }
    
    if(!apr_chdir) {
       ExecAssocProgram_MsgBox(psz_filename, 
                 UnpackerProg[us_unpackernum].uszProgName, 
                 UnpackerProg[us_unpackernum].uszParamList, 
                 UnpackerProg[us_unpackernum].usSilent=1, 
                 UnpackerProg[us_unpackernum].usSession,
                 us_flg_autoclose, FLAG_MARK, 1, FLAG_EXECPROG_UNPACKER);
    }

    ChangeDriveDirFunc(uc_currentdir);
    return apr_chdir;
 }

/****************************************************************/
/**  Archive_Unpack_MarkFile                                    */
/****************************************************************/
 APIRET Archive_Unpack_MarkFile(PSZ psz_extractdir, USHORT us_flg_unpacksubdir,
                                USHORT us_flg_autoclose)
 {
    USHORT us_unpackernum;
    APIRET apr_chdir=0;
    ULONG  ul_count;

    for (ul_count=0; ul_count<FlCnt; ul_count++) {
       KbdCharIn(&KeyInfo, IO_NOWAIT, 0);
       if(KeyInfo.chChar==ESC) return apr_chdir;

       if (FlDis[ul_count].Mark) {
          for (us_unpackernum=0; us_unpackernum<UnpackerCnt; us_unpackernum++) {
             if (CheckExtention(FlDis[ul_count].Nm+DISP_FN, 
                                UnpackerProg[us_unpackernum].uszExtention)) break;
          }
          if (us_unpackernum!=UnpackerCnt) {
             apr_chdir=Archive_Unpack_CurrentFile(us_unpackernum,
                                    FlDis[ul_count].Nm+DISP_FN, psz_extractdir,
                                    us_flg_unpacksubdir, us_flg_autoclose);
             if(apr_chdir) return apr_chdir;
             DosSleep(500L);  /* �ʃZ�b�V�����ł͘A�����Ă͋N���ł��Ȃ��̂� */
                              /* �O�̂��ߋN�����I������܂ő҂�             */
          }
       }
    }
    return apr_chdir;
 }


/****************************************************************/
/**  Archive_Unpack_GetSubDirName                               */
/****************************************************************/
 VOID Archive_Unpack_GetSubDirName(PSZ psz_targetdir, PSZ psz_extractdir, 
                                   PSZ psz_arcname, PSZ psz_arcextention)
 {
    if(*psz_extractdir=='\0') {
       strcpy(psz_targetdir, psz_arcname); 
    } else {
       sprintf(psz_targetdir, "%s\\%s", psz_extractdir, psz_arcname);
    }
       
    *(psz_targetdir+(strlen(psz_targetdir)
                    -strlen(psz_arcextention)))='\0';
 }

/****************************************************************/
/**   CheckExtention                                           **/
/**------------------------------------------------------------**/
/**   �Ԃ�l�F�g���q����v������ 1, ����ȊO�� 0               **/
/****************************************************************/
 USHORT CheckExtention(PSZ psz_filename, PSZ psz_extention)
 {
    ULONG ul_len_filename, ul_len_extention;
    PUCHAR puc_ext_in_filename;
    
    ul_len_filename =strlen(psz_filename);
    ul_len_extention=strlen(psz_extention);

    if(!ul_len_filename||!ul_len_extention) return 0; /* ���� 0       */
    if(ul_len_filename <= ul_len_extention) return 0; /* �g���q������ */
    
    puc_ext_in_filename=psz_filename+(ul_len_filename-ul_len_extention+1);

    if(stricmp(puc_ext_in_filename, psz_extention+1))  return 0;   
       /* �������g���q�ƈ�v���Ȃ� */

    if(*(--puc_ext_in_filename) == '.') return 1; /* �擪�� '.' */

    if(strchr(psz_extention+1, '.') != NULL) {
       if(*puc_ext_in_filename == '_') return 1; 
          /* ������'.'������Ƃ��͐擪��'_'�ł��悢:VFAT�p */
    }
    return 0;
}

#ifdef BAKAYARO
/****************************************************************/
/**   CheckExtention                                           **/
/**------------------------------------------------------------**/
/**   �Ԃ�l�F�g���q����v������ 1, ����ȊO�� 0               **/
/****************************************************************/
 USHORT CheckExtention(PSZ psz_filename, PSZ psz_extention)
 {
    UCHAR usz_wildcardfname[_MAX_PATH]="*.",
          usz_estimatefname[_MAX_PATH]={0};
    PUCHAR puc_lastpriod, puc_searchpriod;
    INT i_priodnum=0;

    puc_searchpriod=strchr(psz_extention, '.');
    while(puc_searchpriod=strchr(puc_searchpriod+1, '.')) {
       i_priodnum++;
    }
    puc_searchpriod=strchr(psz_filename, '.');
    if(!puc_searchpriod) return 0; /* �g���q�������Ȃ� */

    while(puc_searchpriod=strchr(puc_searchpriod+1, '.')) {
       if(i_priodnum > 0) {
          i_priodnum --;
       } else {
          strcat(usz_wildcardfname, "*.");
       }
    }

    puc_lastpriod=strrchr(usz_wildcardfname, '.');
    strcat(usz_wildcardfname, psz_extention+1);

    switch(i_priodnum) {
       case 0:
          if(!DosEditName(1, psz_filename, usz_wildcardfname, usz_estimatefname,
                          sizeof(usz_estimatefname))) {
             if(!stricmp(psz_filename, usz_estimatefname)) return 1;
          }
       case 1:
          /* �g���q�ɕ�����'.'������Ƃ��͐擪��'_'�ł��悢:VFAT�p */
          *puc_lastpriod = '_';
 
          if(!DosEditName(1, psz_filename, usz_wildcardfname, usz_estimatefname,
                          sizeof(usz_estimatefname))) {
             if(!stricmp(psz_filename, usz_estimatefname)) return 1;
          }
          break;
       default:
          break;
    }

    return 0;
}
#endif

/****************************************************************/
/**   ChangeAttribute                                          **/
/****************************************************************/
 void ChangeAttribute(PSZ psz_filename, USHORT us_fileattr,
                                        ULONG  ul_MarkFileNum)
 {
    USHORT us_AttrSys=0, us_AttrHidden=0, us_AttrROnly=0;
    APIRET apr_ChangeAttr;
    ULONG  ul_count;
 
    if(!FlCnt) return ;
    if(ul_MarkFileNum ==0) {
       if(!strcmp(psz_filename, ".") || !strcmp(psz_filename, "..")) return;
    }
    
    if(English){
       strcpy(MsgTxt[0],"Change attribute of file(s).        ");
       strcpy(MsgTxt[1],"                                    ");
       strcpy(MsgTxt[2],"                                    ");
       strcpy(MsgTxt[3],"Push 1-3 key to set/reset attribute.");
       strcpy(MsgTxt[4],"  1.- System file                   ");
       strcpy(MsgTxt[5],"  2.- Hidden file                   ");
       strcpy(MsgTxt[6],"  3.- Read only file                ");
       strcpy(MsgTxt[7],"                                    ");
       strcpy(MsgTxt[8],"      Enter:OK      Esc:Cancel      ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C���̑�����ύX���܂�          ");
       strcpy(MsgTxt[1],"                                    ");
       strcpy(MsgTxt[2],"                                    ");
       strcpy(MsgTxt[3],"�ύX���鑮���̔ԍ��L�[�������ĉ�����");
       strcpy(MsgTxt[4],"  1.���V�X�e���E�t�@�C��            ");
       strcpy(MsgTxt[5],"  2.���B���t�@�C��                  ");
       strcpy(MsgTxt[6],"  3.�����[�h�E�I�����[              ");
       strcpy(MsgTxt[7],"                                    ");
       strcpy(MsgTxt[8],"     Enter:���s    Esc:���         ");
    }
    
    if(ul_MarkFileNum ==0) {
       sprintf(MsgTxt[1], " File: %s", psz_filename);
       us_AttrSys    = us_fileattr&FILE_SYSTEM ;
       us_AttrHidden = us_fileattr&FILE_HIDDEN;
       us_AttrROnly  = us_fileattr&FILE_READONLY;
    } else {
       if(English){
          sprintf(MsgTxt[1]," File: Marked files( %lu )", ul_MarkFileNum);
       }
       else{
          strcpy(MsgTxt[1]+6,"�}�[�N�t�@�C��");
          sprintf(MsgTxt[1]," File: �}�[�N�t�@�C��( %lu ��)", ul_MarkFileNum);
       }
    }
    
    do {
       Change_FlagMark(us_AttrSys,    4, 4);
       Change_FlagMark(us_AttrHidden, 5, 4);
       Change_FlagMark(us_AttrROnly,  6, 4);
    
       ShowMsgBox(9, bt_g_NormalWindowColor); 
       KbdCharIn(&KeyInfo,IO_WAIT,0);
       ChangeAttributeFlag(KeyInfo.chChar, &us_AttrSys, 
                           &us_AttrHidden, &us_AttrROnly);   
    }while((KeyInfo.chChar!=ESC)&&(KeyInfo.chChar!=ENTER));

    ShowFileList();
    if (KeyInfo.chChar==ESC) return;
    
    if(ul_MarkFileNum ==0) {
       ChangeAttributeFunc(psz_filename, us_AttrSys, us_AttrHidden, us_AttrROnly);
    } else {
       ChangeAttributeDisp(FLAG_FIRST, "");
       for (ul_count=0; ul_count<FlCnt&&KeyInfo.chChar!=ESC; ul_count++) {
          KbdCharIn(&KeyInfo,IO_NOWAIT,0);
          if (FlDis[ul_count].Mark){
             ChangeAttributeDisp(FLAG_NOT_FIRST, FlDis[ul_count].Nm+DISP_FN);
             apr_ChangeAttr=ChangeAttributeFunc(FlDis[ul_count].Nm+DISP_FN, 
                                 us_AttrSys, us_AttrHidden, us_AttrROnly);
             if(apr_ChangeAttr) 
                ChangeAttributeDisp(FLAG_FIRST, FlDis[ul_count].Nm+DISP_FN);

          }
       } 
    }
    ShowFileList_PrevFile(FLAG_DRAW_FILELIST, psz_filename);
 }

/****************************************************************/
/**   ChangeAttributeDisp                                      **/
/****************************************************************/
 void ChangeAttributeDisp(USHORT us_flg_firstdisp, PSZ FlNm)
 {
    strcpy(MsgTxt[0],
           English ? "Now changing attribute. " :
                     "�t�@�C�������̕ύX���ł�");
    strcpy(MsgTxt[1],"                        ");
    
    if (us_flg_firstdisp == FLAG_FIRST) {
       ShowMsgBox(2, bt_g_InformWindowColor);
    } else {
       strcpy(MsgTxt[1]+1, FlNm);
       ShowMsgBox_Line(1, bt_g_InformWindowColor);
    }
 }

/****************************************************************/
/**   ChangeAttributeFlag                                      **/
/****************************************************************/
 void ChangeAttributeFlag(UCHAR uc_inputchar, PUSHORT pus_AttrSys, 
                          PUSHORT pus_AttrHidden, PUSHORT pus_AttrROnly)
 {
    switch(uc_inputchar){
       case '1':
          *pus_AttrSys=!(*pus_AttrSys);
          break;
       case '2':
          *pus_AttrHidden=!(*pus_AttrHidden);
          break;
       case '3':
          *pus_AttrROnly=!(*pus_AttrROnly);
          break;
       default:;
    }
 }

/****************************************************************/
/**   ChangeAttributeFunc                                      **/
/****************************************************************/
 APIRET ChangeAttributeFunc(PUCHAR puc_filename, USHORT us_AttrSys, 
                          USHORT us_AttrHidden, USHORT us_AttrROnly)
 {
    APIRET apr_Pathinfo;
    FILESTATUS3 fs3_PathInfo3={{0}};

    
    apr_Pathinfo=DosQueryPathInfo(puc_filename, 1, &fs3_PathInfo3,
                                  sizeof(FILESTATUS3));
    if(apr_Pathinfo) {
       ErrorMsgDisp(apr_Pathinfo, puc_filename);
       return apr_Pathinfo;
    }

    fs3_PathInfo3.attrFile = ChangeAttributeFunc_BitSet(us_AttrSys, 
                                 fs3_PathInfo3.attrFile, FILE_SYSTEM);
    fs3_PathInfo3.attrFile = ChangeAttributeFunc_BitSet(us_AttrHidden, 
                                 fs3_PathInfo3.attrFile, FILE_HIDDEN);
    fs3_PathInfo3.attrFile = ChangeAttributeFunc_BitSet(us_AttrROnly, 
                                 fs3_PathInfo3.attrFile, FILE_READONLY);

    apr_Pathinfo=DosSetPathInfo(puc_filename, 1, &fs3_PathInfo3,
                                          sizeof(FILESTATUS3),0);
    if(apr_Pathinfo) ErrorMsgDisp(apr_Pathinfo, puc_filename);

    return apr_Pathinfo;
 }

/****************************************************************/
/**   ChangeAttributeFunc_BitSet                               **/
/****************************************************************/
 ULONG ChangeAttributeFunc_BitSet(USHORT us_Attr, ULONG ul_current_attr,
                                  ULONG ul_changeattr_bit)
 {
    if (us_Attr) {
       return  ul_current_attr | ul_changeattr_bit; 
    } else { 
       return  ul_current_attr & ~ul_changeattr_bit;
    }
    
 }

/****************************************************************/
/**   ChangeTimeStamp                                          **/
/****************************************************************/
 VOID ChangeTimeStamp(PSZ psz_filename, ULONG ul_markcnt)
 {
    CHAR c_time_write[32];
    PUCHAR puc_inputwinstr=c_time_write;
    APIRET apr_ChangeTime;
    ULONG ul_count=0;
    UCHAR uc_inputchar;

    if(!FlCnt) return;
    if(!strcmp(psz_filename, ".") || !strcmp(psz_filename, "..")) return;

    if(English){
       strcpy(MsgTxt[0]," Change time stamps.");
       strcpy(MsgTxt[1],"                    ");
       strcpy(MsgTxt[2],"                    ");
       strcpy(MsgTxt[3],"[F1]Set current time");
       strcpy(MsgTxt[4],"                    ");
       strcpy(MsgTxt[5],"                    ");
       strcpy(MsgTxt[6],"Enter:OK  Esc:Cancel");
    }
    else{
       strcpy(MsgTxt[0],"�^�C���X�^���v�̕ύX");
       strcpy(MsgTxt[1],"                    ");
       strcpy(MsgTxt[2],"                    ");
       strcpy(MsgTxt[3],"  [F1]���ݎ����w��  ");
       strcpy(MsgTxt[4],"                    ");
       strcpy(MsgTxt[5],"                    ");
       strcpy(MsgTxt[6],"Enter:���s  Esc:���");
    }

    if(!ul_markcnt) {
       strcpy(MsgTxt[1]+1, psz_filename);
       if(ChangeTimeStampGet(psz_filename, c_time_write)) return;
    }else{
       strcpy(MsgTxt[1]+1,
                English ? "Marked files" :
                          "�}�[�N�t�@�C��");
       if(ChangeTimeStampGetCurrentTime(c_time_write)) return;
    }

    for (;;){
       do {
          uc_inputchar=KbdLineIn(7, bt_g_NormalWindowColor, 4, puc_inputwinstr,
                       FLAG_INPUTWIN_OVERWRITE|FLAG_INPUTWIN_CURSORHEAD|
                       FLAG_INPUTWIN_FUNCKEY_ON);
          switch(uc_inputchar) {
             case ESC:
                ShowFileList();
                return;
             case ENTER:
                break;
             case PF1:
                if(ChangeTimeStampGetCurrentTime(c_time_write)) return;
                break;
             default:;
          }
       }while(uc_inputchar!=ENTER);

       if(CheckTimeStampStr(InpLine) == FALSE) {
          puc_inputwinstr = c_time_write;
       } else {
          strcpy(MsgTxt[4],InpLine);
          strcpy(MsgTxt[6],
                 English ? "End:Write Esc:Cancel" :
                           "End:������  Esc:���");
          ShowMsgBox(7, bt_g_NormalWindowColor);
          for (;;) {
             KbdCharIn(&KeyInfo,IO_WAIT,0);
             if(KeyInfo.chChar == ESC) {
                if(English){
                   strcpy(MsgTxt[4],"                    ");
                   strcpy(MsgTxt[6],"Enter:OK  Esc:Cancel");
                }
                else{
                   strcpy(MsgTxt[4],"                    ");
                   strcpy(MsgTxt[6],"Enter:���s  Esc:���");
                }
                puc_inputwinstr = InpLine;
                break;
             } 
             if(KeyInfo.chScan == END) {
                ShowFileList();
                if(!ul_markcnt) {
                   ChangeTimeStampSet(psz_filename, InpLine);
                }else{
                   ChangeAttributeDisp(FLAG_FIRST, "");
                   for (ul_count=0; ul_count<FlCnt&&KeyInfo.chChar!=ESC; ul_count++) {
                       KbdCharIn(&KeyInfo,IO_NOWAIT,0);
                   if (FlDis[ul_count].Mark){
                      ChangeAttributeDisp(FLAG_NOT_FIRST, FlDis[ul_count].Nm+DISP_FN);
                      apr_ChangeTime=ChangeTimeStampSet(FlDis[ul_count].Nm+DISP_FN, 
                                                        InpLine);
                      if(apr_ChangeTime) 
                          ChangeAttributeDisp(FLAG_FIRST, FlDis[ul_count].Nm+DISP_FN);
                      }
                   } 
                }
                ShowFileList_PrevFile(FLAG_DRAW_FILELIST, psz_filename);
                return;
             }
          }
       }
    } 
    
 }

/****************************************************************/
/**   ChangeTimeStampGet                                       **/
/****************************************************************/
 APIRET ChangeTimeStampGet(PSZ psz_filename, PSZ psz_time_write)
 {
    APIRET apr_PathInfo;
    FILESTATUS3 fs3_PathInfo3={{0}};
    
    apr_PathInfo=DosQueryPathInfo(psz_filename, FIL_STANDARD, 
                     (PVOID)&fs3_PathInfo3, sizeof(FILESTATUS3));
    if(apr_PathInfo) {
       ErrorMsgDisp(apr_PathInfo, psz_filename);
       return apr_PathInfo;
    }

    ChangeTimeStamp_MakeString(psz_time_write, &fs3_PathInfo3.fdateLastWrite,
                                               &fs3_PathInfo3.ftimeLastWrite);
    return apr_PathInfo;
 }

/****************************************************************/
/**   ChangeTimeStampGetCurrentTime                            **/
/****************************************************************/
 APIRET ChangeTimeStampGetCurrentTime(PSZ psz_time_write)
 {
    APIRET apr_datetime;
    DATETIME dt_datetime={0};
    
    
    apr_datetime=DosGetDateTime(&dt_datetime);
    if(apr_datetime) {
       ErrorMsgDisp(apr_datetime, "");
    }else{
       sprintf(psz_time_write,"%04.4d/%02.2d/%02.2d %02.2d:%02.2d:%02.2d\0",
             dt_datetime.year, dt_datetime.month, dt_datetime.day,
             dt_datetime.hours, dt_datetime.minutes, dt_datetime.seconds);
    }

    return apr_datetime;
 }

/****************************************************************/
/**   ChangeTimeStampSet                                       **/
/****************************************************************/
 APIRET ChangeTimeStampSet(PSZ psz_filename, PSZ psz_time_write)
 {
    APIRET apr_PathInfo;
    CHAR c_time_creat[32], c_time_access[32];

    FILESTATUS3 fs3_PathInfo3={{0}};
    FDATE fd_date ={0};
    FTIME ft_time ={0};

    ChangeTimeStamp_MakeStructure(psz_time_write, &fd_date, &ft_time); 

    apr_PathInfo=DosQueryPathInfo(psz_filename, FIL_STANDARD, 
                     (PVOID)&fs3_PathInfo3, sizeof(FILESTATUS3));
    if(apr_PathInfo) {
       ErrorMsgDisp(apr_PathInfo, psz_filename);
       return apr_PathInfo;
    }

    ChangeTimeStamp_MakeString(c_time_creat,  &fs3_PathInfo3.fdateCreation,
                                              &fs3_PathInfo3.ftimeCreation);
    ChangeTimeStamp_MakeString(c_time_access, &fs3_PathInfo3.fdateLastAccess,
                                              &fs3_PathInfo3.ftimeLastAccess);
    fs3_PathInfo3.fdateLastWrite=fd_date;
    fs3_PathInfo3.ftimeLastWrite=ft_time;

    if(strcmp(c_time_creat, psz_time_write) > 0) {
       fs3_PathInfo3.fdateCreation=fd_date;
       fs3_PathInfo3.ftimeCreation=ft_time;
    } else if(strcmp(c_time_access, psz_time_write) < 0) {
       fs3_PathInfo3.fdateLastAccess=fd_date;
       fs3_PathInfo3.ftimeLastAccess=ft_time;
    }

    apr_PathInfo=DosSetPathInfo(psz_filename, FIL_STANDARD, 
                     (PVOID)&fs3_PathInfo3, sizeof(FILESTATUS3), 
                     DSPI_WRTTHRU);
    if(apr_PathInfo) ErrorMsgDisp(apr_PathInfo, psz_filename);
    return apr_PathInfo;
 }

/****************************************************************/
/**   CheckTimeStampStr                                       **/
/****************************************************************/
 BOOL CheckTimeStampStr(PSZ psz_timestr)
 {
    FDATE fd_date ={0};
    FTIME ft_time ={0};
    BOOL  bl_timesetok;

    if((bl_timesetok = ChangeTimeStamp_MakeStructure
                       (psz_timestr, &fd_date, &ft_time)) == TRUE) { 
       memset(psz_timestr, 0, strlen(psz_timestr));
       ChangeTimeStamp_MakeString(psz_timestr, &fd_date, &ft_time);
    }
    
    return bl_timesetok;
 }

/****************************************************************/
/**   ChangeTimeStampGet_MakeString                            **/
/****************************************************************/
VOID ChangeTimeStamp_MakeString(PSZ psz_timestr, 
                     const PFDATE pfd_date, const PFTIME pft_time)
 {
    sprintf(psz_timestr,"%04.4d/%02.2d/%02.2d %02.2d:%02.2d:%02.2d\0",
             (pfd_date->year+1980), pfd_date->month, pfd_date->day,
             pft_time->hours, pft_time->minutes, (pft_time->twosecs*2));
 }

/****************************************************************/
/**   ChangeTimeStampGet_MakeStructure                         **/
/****************************************************************/
BOOL ChangeTimeStamp_MakeStructure(PSZ psz_timestr, PFDATE pfd_date, 
                                                    PFTIME pft_time)
 {
    PCHAR  pc_startptr;
    USHORT us_year, us_month, us_day, us_hours, us_minutes, us_seconds;
    
    pc_startptr = psz_timestr + strspn(psz_timestr, " "); /* ���̋󔒂��΂� */
    if(sscanf(pc_startptr, "%hu/%hu/%hu %hu:%hu:%hu", 
              &us_year, &us_month, &us_day, 
              &us_hours, &us_minutes, &us_seconds) != 6) return FALSE;

    if(us_year   > 2107 || us_year  <  1980) return FALSE;
    if(us_month  > 12   || us_month == 0   ) return FALSE;
    if(us_day    > 31   || us_day   == 0   ) return FALSE;
    if(us_hours  > 23                      ) return FALSE;
    if(us_minutes> 59                      ) return FALSE;
    if(us_seconds> 59                      ) return FALSE;

    pfd_date->year   = us_year-1980;
    pfd_date->month  = us_month;
    pfd_date->day    = us_day; 
    pft_time->hours  = us_hours; 
    pft_time->minutes= us_minutes;
    pft_time->twosecs= us_seconds/2;
    
    return TRUE;
 }


/****************************************************************/
/**   ChangeVolumeLable                                        **/
/****************************************************************/
 VOID ChangeVolumeLabel(VOID)
 {
    PUCHAR puc_inputwinstr=Label;

    if(English){
       strcpy(MsgTxt[0]," Enter new volume label");
       strcpy(MsgTxt[1],"  within 11 characters ");
       strcpy(MsgTxt[2],"                       ");
       strcpy(MsgTxt[3],"                       ");
       strcpy(MsgTxt[4]," Enter:OK   Esc:Cancel ");
    }
    else{
       strcpy(MsgTxt[0],"�{�����[�����x���̕ύX ");
       strcpy(MsgTxt[1],"�@�i�P�P�����ȓ��j     ");
       strcpy(MsgTxt[2],"                       ");
       strcpy(MsgTxt[3],"                       ");
       strcpy(MsgTxt[4]," Enter:���s   Esc:��� ");
    }
    
    for (;;){
       if(KbdLineIn(5, bt_g_NormalWindowColor, 2, puc_inputwinstr,
                    FLAG_INPUTWIN_NOSTRINGS_OK) == ESC) {
          ShowFileList();
          return;
       }
       puc_inputwinstr=InpLine;
       if(strlen(InpLine) < 12) {
          ShowFileList();
          if(!ChangeVolumeLabelSet(InpLine)) QDrive();
          return;
       }
    } 
    
 }

/*****************************************************************/
/**   ChangeVolumeLabelSet                                      **/
/*****************************************************************/
 APIRET ChangeVolumeLabelSet(PSZ psz_volumelabel)
 {
    VOLUMELABEL vl_volumelabel={0};
    APIRET apr_vlabelset;

    strcpy(vl_volumelabel.szVolLabel, psz_volumelabel);  
    vl_volumelabel.cch =(BYTE)strlen(vl_volumelabel.szVolLabel);

    apr_vlabelset=DosSetFSInfo(0L, FSIL_VOLSER, 
                               (PVOID)&vl_volumelabel, sizeof(VOLUMELABEL));
    if(apr_vlabelset) ErrorMsgDisp(apr_vlabelset, "");

    return apr_vlabelset;
 }


/****************************************************************/
/**   ChangeDrive                                              **/
/****************************************************************/
 void ChangeDrive(void)
 {
    if(English){
       strcpy(MsgTxt[0],"   Change current drive.  ");
       strcpy(MsgTxt[1],"  Push a key of drive id. ");
    }
    else{
       strcpy(MsgTxt[0],"  �ʂ̃h���C�u�ֈڂ�܂�  ");
       strcpy(MsgTxt[1],"�h���C�u�����������ĉ�����");
    }

    ShowMsgBox(2, bt_g_NormalWindowColor);
    for(;;) {
       KbdCharIn(&KeyInfo,IO_WAIT,0); 
       if (KeyInfo.chChar==ESC) {
          ShowFileList();
          return;
       }
       if(isalpha(KeyInfo.chChar)) {
          ShowFileList();
          ChangeDriveFunc(KeyInfo.chChar);
          return;
       }
    }

 }

/****************************************************************/
/**   ChangeDriveFunc                                          **/
/****************************************************************/
 VOID ChangeDriveFunc(UCHAR uc_DriveChar)
 {
    UCHAR  usz_currentdir[_MAX_PATH]={0};
    
    if(ChangeDriveFunc_API(uc_DriveChar)) {
       ShowMsgDriveErr();
    } else {
       ShowNewDrive(); 
    }
    SetFullCurrentPathName(usz_currentdir);
    JumpHistInsert(FLAG_HISTRY_PATH, usz_currentdir);

    return;
 }

/****************************************************************/
/**   ChangeDriveFunc_API                                      **/
/****************************************************************/
 APIRET ChangeDriveFunc_API(UCHAR uc_DriveChar)
 {
    if(isdigit(uc_DriveChar)) {
       uc_DriveChar-=0x30;
    } else if(isupper(uc_DriveChar)){
       uc_DriveChar-=0x40;
    } else if(islower(uc_DriveChar)){
       uc_DriveChar-=0x60;
    } 
    return DosSetDefaultDisk((ULONG)uc_DriveChar);
} 

/*****************************************************************/
/**   ChangeDriveDir                                            **/
/*****************************************************************/
 void ChangeDriveDir(USHORT us_flg_jumpdirorchdir)
 {
    APIRET apr_drivedir;
    UCHAR  uc_inputchar, usz_currentdir[_MAX_PATH]={0};
    PUCHAR puc_inputwinstr=NULL;

    if(us_flg_jumpdirorchdir!=FLAG_CHDIR_JUMP) {
       do {
          if(English){
             strcpy(MsgTxt[0],"Change current directory.                     ");
             strcpy(MsgTxt[1],"                                              ");
             strcpy(MsgTxt[2],"Enter target directory(Up arrow key:history). ");
             strcpy(MsgTxt[3],"                                              ");
             strcpy(MsgTxt[4],"                                              ");
             strcpy(MsgTxt[5],"            Enter:OK    Esc:Cancel            ");
          }
          else{
             strcpy(MsgTxt[0],"�J�����g�f�B���N�g���̕ύX                    ");
             strcpy(MsgTxt[1],"                                              ");
             strcpy(MsgTxt[2],"�ύX����w�肵�ĉ�����          (������˽�ذ) ");
             strcpy(MsgTxt[3],"                                              ");
             strcpy(MsgTxt[4],"                                              ");
             strcpy(MsgTxt[5],"          Enter:���s        Esc:���          ");
          }

          uc_inputchar = KbdLineIn(6, bt_g_NormalWindowColor, 3, puc_inputwinstr,
                              FLAG_INPUTWIN_HISTRY_ON|FLAG_INPUTWIN_MSGBOXCLEAR); 
          switch(uc_inputchar) {
             case ESC:
                return;
             case ENTER:
                break;
             default:
                puc_inputwinstr=HistryBox(FLAG_HISTRY_PATH);
          }
       }while(uc_inputchar!=ENTER);
    } else {
       puc_inputwinstr=HistryBox(FLAG_HISTRY_DIRECTRY);
       ShowFileList();
       if(KeyInfo.chChar == ESC) return;
       strcpy(InpLine, puc_inputwinstr);
    }
    
    apr_drivedir=ChangeDriveDirFunc(InpLine);
    if(apr_drivedir==ERROR_INVALID_DRIVE) {
       ErrorMsgDisp(apr_drivedir, InpLine);
       return;
    }
    ShowNewDrive();
    if(apr_drivedir) ErrorMsgDisp(apr_drivedir, InpLine);
    SetFullCurrentPathName(usz_currentdir);
    JumpHistInsert(FLAG_HISTRY_PATH, usz_currentdir);

    return;

 }

/****************************************************************/
/**   ChangeDriveDirFunc                                       **/
/****************************************************************/
 APIRET ChangeDriveDirFunc(PSZ psz_drivepath)
 {
    APIRET apr_DriveErr;
    
    psz_drivepath += strspn(psz_drivepath, " "); /* �擪�̋󔒂��΂� */
    
    if(*(psz_drivepath+1) == ':') {
       apr_DriveErr = ChangeDriveFunc_API(*psz_drivepath); 
       if(apr_DriveErr != NO_ERROR)  return apr_DriveErr;
       if(*(psz_drivepath+2) == '\0'||*(psz_drivepath+2) == ' ') 
          return NO_ERROR;
    }
    return DosSetCurrentDir(psz_drivepath);
 }

/****************************************************************/
/**   ChangeSetup                                              **/
/****************************************************************/
 void ChangeSetup(void)
 {
    UCHAR uc_inputchar;

    do{
       if(English){
          strcpy(MsgTxt[0], "Customize(Push 0-9 key to change)                         ");
          strcpy(MsgTxt[1], "  0.Reload FILENOVA.INI                                   ");
          strcpy(MsgTxt[2], "                                                          ");
          strcpy(MsgTxt[3], "  1.- Sort file list automatically                        ");
          strcpy(MsgTxt[4], "  2.- Case sensitive at sort                              ");
          strcpy(MsgTxt[5], "  3.- Create another session at execute program           ");
          strcpy(MsgTxt[6], "  4.- Close a program window automatically                ");
          strcpy(MsgTxt[7], DisableJapanFunc ? 
                            "                                                          " :
                            "  5.- Use DOS/V mode at create VDM session                ");
          strcpy(MsgTxt[8], "  6.Text editor:                                          ");
          strcpy(MsgTxt[9 ],"  7.- Create another session at text editor               ");
          strcpy(MsgTxt[10],"  8.- Use external viewer                                 ");
          strcpy(MsgTxt[11],"  9.- Assign an individual directory to each archive files");
          strcpy(MsgTxt[12],"                                   Enter/Esc:Back         ");
       }
       else{
          strcpy(MsgTxt[0], "�J�X�^�}�C�Y�ύX(�ύX�͔ԍ���)                    ");
          strcpy(MsgTxt[1], "  0.INI̧�ق̍ēǂݍ���                           ");
          strcpy(MsgTxt[2], "                                                  ");
          strcpy(MsgTxt[3], "  1.�����̧��ؽĂ�Ă���                        ");
          strcpy(MsgTxt[4], "  2.����Ď��ɑ啶��/����������ʂ���              ");
          strcpy(MsgTxt[5], "  3.����۸���/����ދN�����ɕʾ���݂𐶐�����      ");
          strcpy(MsgTxt[6], "  4.����۸���/����ޏI�����ɳ���޳�������۰�ނ���  ");
          strcpy(MsgTxt[7], "  5.��DOS��۸��ю��s����DOS/V���[�h���g�p����     ");
          strcpy(MsgTxt[8], "  6.�O����޲���:                                  ");
          strcpy(MsgTxt[9 ],"  7.���O����޲��N�����ɕʾ���݂𐶐�����          ");
          strcpy(MsgTxt[10],"  8.���O���ޭ�܂��g�p����                         ");
          strcpy(MsgTxt[11],"  9.�����ɉ𓀎��ɌʂɃf�B���N�g���𐶐�����    ");
          strcpy(MsgTxt[12],"                            Enter/Esc:�߂�        ");
       }
    
       Change_FlagMark(AlwaysSort,                     3, 4);
       Change_FlagMark(CaseOfSort,                     4, 4);
       Change_FlagMark(ExecSession,                    5, 4);
       Change_FlagMark(AutoClose,                      6, 4);
       
       if(!DisableJapanFunc) //��R�[�h�y�[�W�����{��̏ꍇ�̂�DOS/V���[�h�I����
          Change_FlagMark(us_g_flg_dosmode,               7, 4);
       
       Change_FlagMark(EditorCfg.EditorProg.usSession, 9, 4);
       Change_FlagMark(ViewerCfg.usUseExtViewer,      10, 4);
       Change_FlagMark(us_g_unpack_dir,               11, 4);
       strcpy(MsgTxt[8] +16, EditorCfg.EditorProg.uszProgName); 

       ShowMsgBox(13, bt_g_WarningWindowColor);  
       KbdCharIn(&KeyInfo,IO_WAIT,0);

       if(KeyInfo.chScan==PF2) {
          uc_inputchar=ESC;
       } else {
          uc_inputchar=KeyInfo.chChar;
       }

       switch(uc_inputchar){
          case '0': 
             if(ChangeSetupFuncIniRead()==TRUE) return; 
             break;
          case '1': 
             AlwaysSort=!AlwaysSort;
             break;
          case '2': 
             CaseOfSort=!CaseOfSort;
             break;
          case '3': 
             ExecSession=!ExecSession;
             break;
          case '4': 
             AutoClose=!AutoClose;
             break;
          case '5': 
             if(!DisableJapanFunc)    // ���{����ȊO�ł́ADOS/V�֘A�̋@�\�𖳌��ɂ���
               us_g_flg_dosmode=!us_g_flg_dosmode;
             break;
          case '6': 
             ChangeSetupFuncEditorName(); 
             break;
          case '7': 
             EditorCfg.EditorProg.usSession
                       =! EditorCfg.EditorProg.usSession;
             break;
          case '8': 
             ViewerCfg.usUseExtViewer=!ViewerCfg.usUseExtViewer;
             break;
          case '9': 
             us_g_unpack_dir= !us_g_unpack_dir;
             break;
       }
    } while((uc_inputchar!=ESC)&&(uc_inputchar!=ENTER));
    ShowFileList();
 }

/****************************************************************/
/**   Change_FlagMark                                          **/
/****************************************************************/
 VOID Change_FlagMark(USHORT setupflag, USHORT mark_row, USHORT mark_col)
 {
    if (setupflag)  memcpy(MsgTxt[mark_row]+mark_col,English ? "* " : "��",2);
    else            memcpy(MsgTxt[mark_row]+mark_col,English ? "- " : "��",2);
 }

/****************************************************************/
/**   ChangeSetupFuncEditorName                                **/
/****************************************************************/
 void ChangeSetupFuncEditorName(VOID)
 {
    ShowFileList();

    if(English){
       strcpy(MsgTxt[0],"Enter filename of text editor.   ");
       strcpy(MsgTxt[1],"                                 ");
       strcpy(MsgTxt[2],"                                 ");
       strcpy(MsgTxt[3],"     Enter:OK     Esc:Cancel     ");
    }
    else{
       strcpy(MsgTxt[0],"�O���G�f�B�^���̕ύX             ");
       strcpy(MsgTxt[1],"                                 ");
       strcpy(MsgTxt[2],"                                 ");
       strcpy(MsgTxt[3],"     Enter:���s   Esc:���       ");
    }
    
    if(KbdLineIn(4, bt_g_NormalWindowColor, 1, EditorCfg.EditorProg.uszProgName,
                 FLAG_INPUTWIN_MSGBOXCLEAR)!=ESC) {
         strcpy(EditorCfg.EditorProg.uszProgName, InpLine);
    }
 }

/****************************************************************/
/**   ChangeSetupFuncIniRead                                   **/
/****************************************************************/
 BOOL ChangeSetupFuncIniRead(void)
 {
    ShowFileList();

    if(English){
       strcpy(MsgTxt[0],"    Reload FILENOVA.INI.   ");
       strcpy(MsgTxt[1],"                           ");
       strcpy(MsgTxt[2],"   Enter:OK   Esc:Cancel   ");
    }
    else{
       strcpy(MsgTxt[0]," INI ̧�ق��ēǂݍ��݂��܂�");
       strcpy(MsgTxt[1],"                           ");
       strcpy(MsgTxt[2],"   Enter:���s   Esc:���   ");
    }

    ShowMsgBox(3, bt_g_NormalWindowColor);
    for(;;){
       KbdCharIn(&KeyInfo,IO_WAIT,0);
       switch(KeyInfo.chChar) {
          case ENTER:
             InitCustomize(FLAG_NOT_FIRST);
             ShowFileList_PrevFile(FLAG_DRAW_SCREEN, FlDis[SelFl].Nm+DISP_FN);
                                      /* �J���[�J�X�^�}�C�Y�ɑΉ����邽�� */
             return TRUE;
          case ESC:
             ShowFileList();
             return FALSE;
       }
    }
 }


/****************************************************************/
/**   ChangeCodePage                                           **/
/****************************************************************/
 void ChangeCodePage(void)
 {
    if (CodePage[0] == CodePage[1]) CodePage[0]=CodePage[2] ;
    else CodePage[0]=CodePage[1];

    ChangeCodePageFunc(CodePage[0]);  
    GetCodePage(FLAG_NOT_FIRST);

    FileMarkRefresh(); /* �}�[�N�t�@�C���\�������t���b�V�� */

    RedrawScreen();
 }

/****************************************************************/
/**   ChangeCodePageFunc                                      **/
/****************************************************************/
 void ChangeCodePageFunc(ULONG ul_codepage)
 {
    UCHAR  CmdParm[CMDSTR_MAX];

    DosSetProcessCp(CodePage[0]);  /* ����������Codepage��ς��� */

    sprintf(CmdParm, "chcp %d", ul_codepage);
    system(CmdParm);               /* �\����Codepage ��ς��� */
 }


/****************************************************************/
/**   ChangeWindowSize                                         **/
/****************************************************************/
 void ChangeWindowSize(void)
 {
    UCHAR  usz_inputwinstr[32]={0};
 
    if(English){
       strcpy(MsgTxt[0],"Change this window size.      ");
       strcpy(MsgTxt[1],"                              ");
       strcpy(MsgTxt[2],"Enter X,Y(no blank character).");
       strcpy(MsgTxt[3],"                              ");
       strcpy(MsgTxt[4],"                              ");
       strcpy(MsgTxt[5],"    Enter:OK    Esc:Cancel    ");
    }
    else{
       strcpy(MsgTxt[0],"�E�C���h�E�E�T�C�Y��ύX���܂�");
       strcpy(MsgTxt[1],"                              ");
       strcpy(MsgTxt[2],"����,�s��(���ݸ�Ȃ�)          ");
       strcpy(MsgTxt[3],"                              ");
       strcpy(MsgTxt[4],"                              ");
       strcpy(MsgTxt[5],"    Enter:���s  Esc:���      ");
    }

    sprintf(usz_inputwinstr,"%d,%d\0",ColMax,RowMax);
    if(KbdLineIn(6, bt_g_NormalWindowColor, 3, usz_inputwinstr, 
                 FLAG_INPUTWIN_NO_OPTION)==ESC) {
       ShowFileList();
    } else {
       ChangeWindowSizeFunc(InpLine);
       GetMode();
       RedrawScreen();
    }
 }

/****************************************************************/
/**   ChangeWindowSizeFunc                                     **/
/****************************************************************/
 void ChangeWindowSizeFunc(PSZ psz_windowsize)
 {
    UCHAR  CmdParm[CMDSTR_MAX];

    sprintf(CmdParm, "mode co%s", psz_windowsize);
    system(CmdParm);
 }

/**************************************************************/
/**   CommandProcess                                         **/
/**************************************************************/
 void CommandProcess(void)
 {
    UCHAR  usz_currdir[_MAX_PATH];
 
    if(English){
       strcpy(MsgTxt[0], "Execute a command processor.        ");
       strcpy(MsgTxt[1], "                                    ");
       strcpy(MsgTxt[2], "  0/Space : Execute on same session ");
       strcpy(MsgTxt[3], "  1/Enter : Create another session  ");
       strcpy(MsgTxt[4], "  2       : OS/2 Full screen        ");
       strcpy(MsgTxt[5], "  3       : PC-DOS Window           ");
       strcpy(MsgTxt[6], DisableJapanFunc ?
                         "                                    " :
                         "  4       : DOS/V Window            ");
       strcpy(MsgTxt[7], "  5       : PC-DOS Full screen      ");
       strcpy(MsgTxt[8], DisableJapanFunc ?
                         "                                    " :
                         "  6       : DOS/V Full screen       ");
       strcpy(MsgTxt[9], DisableJapanFunc ?
                         "  7       : Win-OS2 Window          " :
                         "  7       : Win-OS2J Window         ");
       strcpy(MsgTxt[10],DisableJapanFunc ?
                         "  8       : Win-OS2 Full screen     " :
                         "  8       : Win-OS2J Full screen    ");
       strcpy(MsgTxt[11],"                         Esc:Cancel ");
    }
    else{
       strcpy(MsgTxt[0], "�R�}���h�v���Z�b�T���N�����܂�      ");
       strcpy(MsgTxt[1], "                                    ");
       strcpy(MsgTxt[2], "  0/Space : ���̾���ݓ��ł̋N��     ");
       strcpy(MsgTxt[3], "  1/Enter : �ʾ���݂𐶐�����       ");
       strcpy(MsgTxt[4], "  2       : OS/2 �S���             ");
       strcpy(MsgTxt[5], "  3       : PC-DOS�E�B���h�E        ");
       strcpy(MsgTxt[6], "  4       : DOS/V �E�B���h�E        ");
       strcpy(MsgTxt[7], "  5       : PC-DOS�S���            ");
       strcpy(MsgTxt[8], "  6       : DOS/V �S���            ");
       strcpy(MsgTxt[9], "  7       : ���{��Win-OS2�E�C���h�E ");
       strcpy(MsgTxt[10],"  8       : ���{��Win-OS2�S���     ");
       strcpy(MsgTxt[11],"                          Esc:���  ");
    }

    ShowMsgBox(12, bt_g_NormalWindowColor);
    SetFullCurrentPathName(usz_currdir);

    for(;;){
       KbdCharIn(&KeyInfo,IO_WAIT,0);
       switch(KeyInfo.chChar){
          case '0': 
          case ' ':
             CmdExec_SameSession(FLAG_NO_MARK, ShellName, 1);
             QDriveSize();
             return;
          case '1': 
          case ENTER:
             ShowFileList();
             FileExecFunc_AnotherSession(FLAG_NO_MARK, 
                                         English ?  "OS/2 Window" : "OS/2�E�B���h�E", 
                                         ShellName, "", 1, SSF_TYPE_DEFAULT);
                                  /* "", 1 �̓p�����[�^�Ȃ�,us_AutoClose=1�̈� */
             return;
          case '2':
             FileExecFunc_AnotherSession(FLAG_NO_MARK,
                                         English ? "OS/2 Full screen" : "OS/2�S���", 
                                         ShellName, "", 1, SSF_TYPE_FULLSCREEN);
             return;
          case '3':
             ShowFileList();
             FileExecFunc_UseWinAPI(English ? "PC-DOS Window" : "PC-DOS�E�B���h�E", 
                                    "COMMAND.COM", "/K",  usz_currdir, 
                                    FLAG_DOSMODE_PCDOS, PROG_WINDOWEDVDM);
             return;
          case '4':   // ���{����ȊO�ł́ADOS/V�֘A�̋@�\�𖳌��ɂ���
             if(DisableJapanFunc) break;
             ShowFileList();
             FileExecFunc_UseWinAPI(English ? "DOS/V Window" : "DOS/V�E�B���h�E", 
                                    "COMMAND.COM", "/K", usz_currdir, 
                                    FLAG_DOSMODE_DOSV, PROG_WINDOWEDVDM);
             return;
          case '5':
             ShowFileList();
             FileExecFunc_UseWinAPI(English ? "PC-DOS Full screen" :"PC-DOS�S���", 
                                    "COMMAND.COM", "/K",  usz_currdir, 
                                    FLAG_DOSMODE_PCDOS, PROG_VDM);
             return;
          case '6':  // ���{����ȊO�ł́ADOS/V�֘A�̋@�\�𖳌��ɂ���
             if(DisableJapanFunc) break;
             ShowFileList();
             FileExecFunc_UseWinAPI(English ? "DOS/V Full screen" : "DOS/V�S���", 
                                    "COMMAND.COM", "/K", usz_currdir, 
                                    FLAG_DOSMODE_DOSV, PROG_VDM);
             return;
          case '7':
             ShowFileList();
             FileExecFunc_UseWinAPI(DisableJapanFunc ? "Win-OS2 Window" :
                                        English ? "Win-OS2J Window" :"���{��WIN-OS2�E�B���h�E", 
                                    "PROGMAN.EXE", "", usz_currdir,
                                    DisableJapanFunc ? FLAG_DOSMODE_PCDOS : FLAG_DOSMODE_DOSV,
                                    PROG_31_ENHSEAMLESSCOMMON);
             return;
          case '8':
             ShowFileList();
             FileExecFunc_UseWinAPI(DisableJapanFunc ? "Win-OS2 Full screen" :
                                        English ? "Win-OS2J Full screen" : "���{��WIN-OS2�S���",
                                    "PROGMAN.EXE", "", usz_currdir,
                                    DisableJapanFunc ? FLAG_DOSMODE_PCDOS : FLAG_DOSMODE_DOSV,
                                    PROG_31_ENH);

             return;
          case ESC:
             ShowFileList();
             return;
       }
    }
 }

/**************************************************************/
/**   CmdExec_SameSession                                    **/
/**************************************************************/
VOID CmdExec_SameSession(USHORT us_flg_markfile, PSZ psz_parm_strings,
                         USHORT us_AutoClose)
{
   puts(CLEAR); 
   Vio_CursorShape(FLAG_CURSOR_DISP);
   system(psz_parm_strings); 
   
   ChangeCodePageFunc(CodePage[0]);  /* �O�̂��� CodePage ��߂� */

   if(!us_AutoClose) {
      puts( English ? "\n\nPush any key." : "\n\n�����L�[�������ĉ�����" );
      KbdCharIn(&KeyInfo, IO_WAIT, 0);
   }

   if (us_flg_markfile == FLAG_NO_MARK) { /* �A�����s�łȂ��� */
      ShowFileList_PrevFile(FLAG_DRAW_SCREEN, FlDis[SelFl].Nm+DISP_FN);
   }
}

/**************************************************************/
/**   CopyDirContents                                        **/
/**************************************************************/
 APIRET CopyDirContents(PSZ SourceDir, PSZ TargetDir, PSZ NewDir,
                        USHORT us_flg_copydelmove)
 {
    APIRET rca; 
    ULONG  ia, ib, ul_dircount=0; 
    UCHAR  TargetNewDir[_MAX_PATH], uc_savesourcedir[_MAX_PATH]={0}; 
    
    FILESTATUS3 fs3_PathInfo3={{0}};

    /*------------------------------*/
    /*   �ړI�p�X�̗L���𒲂ׂ�     */
    /*------------------------------*/
    if(NewDir == NULL) {
       strcpy(TargetNewDir, TargetDir);
    } else { 
       _jmakepath(TargetNewDir, NULL, TargetDir, NewDir, NULL);
    }
    rca=DosQueryPathInfo(TargetNewDir, 1, &fs3_PathInfo3, sizeof(FILESTATUS3));

    if (!rca) { /* ����̃t�@�C���E�f�B���N�g�������� */
       if(!(fs3_PathInfo3.attrFile&FILE_DIRECTORY))
          return ERROR_PATH_NOT_FOUND;   /* ����̃t�@�C�����Ȃ��߂� */
    } else {    
       if(us_flg_copydelmove==FLAG_MOVE_SAMEDRIVE) { /*  ����h���C�u���Ȃ�܂邲�ƈړ�  */
          return DosMove(SourceDir, TargetNewDir);
       } else {  
          rca=DosCreateDir(TargetNewDir,0);    /* Dir���Ȃ��Ȃ�V���ɍ�� */
          if (rca) return rca;
       }
    }

    /*---------------------------------*/
    /*   Dir�����̃t�@�C���̌ʏ���   */
    /*---------------------------------*/
    rca=DosSetCurrentDir(SourceDir);     /* �\�[�XDir�̒��Ɉړ� */
    if (rca) return rca;

    FileCopyFuncDisp(" ", us_flg_copydelmove);
    QFile_LoadFileList(FLAG_LOADFILELIST_ANYFILE, "*.*");

    /*-----------------------------*/
    /*  �܂��̓t�@�C�����R�s�[     */
    /*-----------------------------*/
    for (ia=0; ia<FlCnt&&!rca&&KeyInfo.chChar!=ESC; ++ia) {
       KbdCharIn(&KeyInfo,IO_NOWAIT,0);
       FileCopyFuncDisp(FlDis[ia].Nm+DISP_FN, us_flg_copydelmove);

       if (FlDis[ia].Atr&FILE_DIRECTORY) {  /* ������SubDir�݂̂̃��X�g����� */
          FlDis[ul_dircount++]=FlDis[ia];
       } else {                       /*  �t�@�C���Ȃ�R�s�[ */
          rca=FileCopyFunc(FlDis[ia].Nm+DISP_FN, FlDis[ia].Nm+DISP_DT,
                           TargetNewDir, FlDis[ia].Nm+DISP_FN, us_flg_copydelmove);
       }
       if(us_flg_copydelmove!=FLAG_MOVE_SAMEDRIVE) QDriveSize();
    }
    /*-------------------------------------*/
    /*  ����SubDir�̓������ċA�I�ɃR�s�[   */
    /*-------------------------------------*/
    for (ia=ib=0; ia<ul_dircount&&!rca&&KeyInfo.chChar!=ESC; ++ia) {
       if (strcmp(FlDis[ib].Nm+DISP_FN, ".")&&strcmp(FlDis[ib].Nm+DISP_FN, "..")) {

          /* SAMEDRIVE�̂Ƃ�subdir���Ƃ��łɈړ�����Ă���΍�: ����*/
          if(us_flg_copydelmove==FLAG_MOVE_SAMEDRIVE)
             strcpy(uc_savesourcedir, FlDis[ib].Nm+DISP_FN); 

          rca=CopyDirContents(FlDis[ib].Nm+DISP_FN, TargetNewDir, FlDis[ib].Nm+DISP_FN,
                              us_flg_copydelmove);
          QFile_LoadFileList(FLAG_LOADFILELIST_DIRONLY, "*.*");

          /* SAMEDRIVE�̂Ƃ�subdir���Ƃ��łɈړ�����Ă���΍�F ����*/
          if(us_flg_copydelmove==FLAG_MOVE_SAMEDRIVE) {
             if (strcmp(uc_savesourcedir, FlDis[ib].Nm+DISP_FN) ) { /*���O���ς���Ă��� = SubDir �ړ��ς�*/
                strcpy(uc_savesourcedir, FlDis[ib].Nm+DISP_FN); 
                ib--; 
             } 
          }
       }
       ib++;
    }
    /*----------------------------*/
    /*  �ړ��Ȃ�SubDir���폜      */
    /*----------------------------*/
    if(us_flg_copydelmove==FLAG_MOVE_SAMEDRIVE
             ||us_flg_copydelmove==FLAG_COPY_DELETE) {
       for (ia=0; ia<ul_dircount&&!rca&&KeyInfo.chChar!=ESC; ++ia) {
          if (strcmp(FlDis[ia].Nm+DISP_FN, ".")
                  &&strcmp(FlDis[ia].Nm+DISP_FN, "..")) {
             KbdCharIn(&KeyInfo,IO_NOWAIT,0);
             DosDeleteDir(FlDis[ia].Nm+DISP_FN);
          }
       }
    }
    DosSetCurrentDir("..");
    return rca;
 }


/****************************************************************/
/**   CreateDir_YesorNo                                        **/
/****************************************************************/
 UCHAR CreateDir_YesorNo(PSZ psz_dirname, USHORT us_flg_msgboxclear)
 {
    UCHAR usz_fnamebuff[_MAX_PATH]={0};

    if(English){
       strcpy(MsgTxt[0],"The destination directory is not found.");
       strcpy(MsgTxt[1],"Create it?                             ");
       strcpy(MsgTxt[2]," Dir:                                  ");
       strcpy(MsgTxt[3],"                                       ");
       strcpy(MsgTxt[4],"     Y(Enter):OK     N(Esc):Cancel     ");
    }
    else{
       strcpy(MsgTxt[0],"�w�肳�ꂽ�f�B���N�g���͑��݂��܂���");
       strcpy(MsgTxt[1],"�V���Ƀf�B���N�g�����쐬���܂����H  ");
       strcpy(MsgTxt[2]," Dir:                               ");
       strcpy(MsgTxt[3],"                                    ");
       strcpy(MsgTxt[4],"    Y(Enter):���s    N(Esc):���    ");
    }


    strcpy(usz_fnamebuff, psz_dirname);
    FileCopyFuncOption_StringsAdjust(usz_fnamebuff, strlen(MsgTxt[0])-5);

    strcpy(MsgTxt[2]+5, usz_fnamebuff);

    return GetYesorNo_withMsgBox(ENTER, 5, bt_g_NormalWindowColor,
                                 us_flg_msgboxclear);
 }

/****************************************************************/
/**   CreateDir                                                **/
/****************************************************************/
 void CreateDir(void)
 {
    APIRET apr_CreateDir;
    FILESTATUS3 fs3_PathInfo3={{0}};


    if(English){
       strcpy(MsgTxt[0],"Make a directory.               ");
       strcpy(MsgTxt[1],"                                ");
       strcpy(MsgTxt[2],"Enter name of directory         ");
       strcpy(MsgTxt[3],"                                ");
       strcpy(MsgTxt[4],"                                ");
       strcpy(MsgTxt[5],"     Enter:OK    Esc:Cancel     ");
    }
    else{
       strcpy(MsgTxt[0],"�f�B���N�g�����쐬���܂��@�@�@�@");
       strcpy(MsgTxt[1],"                                ");
       strcpy(MsgTxt[2],"�f�B���N�g����                  ");
       strcpy(MsgTxt[3],"                                ");
       strcpy(MsgTxt[4],"                                ");
       strcpy(MsgTxt[5],"    Enter:���s    Esc:���      ");
    }

    if(KbdLineIn(6, bt_g_NormalWindowColor, 3, NULL, 
                 FLAG_INPUTWIN_MSGBOXCLEAR) ==ESC) return;
    
    FileCopy_ConverttoAbsolutePath(InpLine);

    if (!DosQueryPathInfo(InpLine,1,&fs3_PathInfo3,sizeof(FILESTATUS3))) {
       ShowMsgSameName();
       return;
    }

    apr_CreateDir = CreateDirFunc(InpLine);
    if(!apr_CreateDir) {
       JumpHistInsert(FLAG_HISTRY_PATH, InpLine);
    }
    CreateDirFuncRc(apr_CreateDir);
 }


/****************************************************************/
/**   CreateDirFunc                                            **/
/****************************************************************/
 APIRET CreateDirFunc(PSZ pDirName)
 {
    PUCHAR s1,s2;
    APIRET apr_CreatDir; 
    
    if (s1=strstr(pDirName,":\\")) {
       s1+=2;
    } else if (s1=jstrchr(pDirName,':')) {
       ++s1;
    } else {
       s1=pDirName;
    }
    
    do {
       s2=jstrchr(s1,'\\');
       if (s2) {
          *s2 = '\0';
          apr_CreatDir=CreateDirFunc_API(pDirName); 
          *s2 = '\\';
          s1=s2+1;
       } else {
          apr_CreatDir=CreateDirFunc_API(pDirName); 
       }
    }while(s2!=NULL && s2!=pDirName+strlen(pDirName)-1);
    return apr_CreatDir;
 }

/****************************************************************/
/**   CreateDirFunc_API                                        **/
/****************************************************************/
 APIRET CreateDirFunc_API(PSZ psz_dirname)
 {
    APIRET apr_CreatDir;
    FILESTATUS3 fs3_PathInfo3={{0}};

    apr_CreatDir=DosQueryPathInfo(psz_dirname, FIL_STANDARD, 
                                  &fs3_PathInfo3, sizeof(FILESTATUS3));
    switch(apr_CreatDir){
       case ERROR_FILE_NOT_FOUND:
       case ERROR_PATH_NOT_FOUND:
          apr_CreatDir=DosCreateDir(psz_dirname, 0);
          break;
    }
    return apr_CreatDir;
 }
 
/****************************************************************/
/**   CreateDirFuncRc                                          **/
/****************************************************************/
 void CreateDirFuncRc(APIRET apr_CreatDir)
 {
    switch(apr_CreatDir){
       case NO_ERROR: 
       case ERROR_FILE_NOT_FOUND:
          ShowFileList_PrevFile(FLAG_DRAW_FILELIST, FlDis[SelFl].Nm+DISP_FN);
          break;
       case ERROR_PATH_NOT_FOUND:
          ShowMsgNameNg(); 
          break;
       default: 
          ErrorMsgDisp(apr_CreatDir, "");
    }
 }

/****************************************************************/
/**   CreateAndEnterDir                                        **/
/****************************************************************/
 APIRET CreateAndEnterDir(PSZ psz_dirname)
 {
    APIRET apr_mkdir;
 
    apr_mkdir=CreateDirFunc(psz_dirname);
    if(apr_mkdir) {
       CreateDirFuncRc(apr_mkdir);
       return apr_mkdir;
    }
    return DosSetCurrentDir(psz_dirname);
 }

/****************************************************************/
/**   DeleteDirContents                                        **/
/****************************************************************/
 APIRET DeleteDirContents(PSZ DirName)
 {
    APIRET rca=0; 
    ULONG  ia, ul_dircount=0;
    

    rca=DosSetCurrentDir(DirName);
    if (rca) return rca;

    /*----------------------------------*/
    /*   �܂�Dir�ȊO�̃t�@�C�����폜    */
    /*----------------------------------*/
    QFile_LoadFileList(FLAG_LOADFILELIST_ANYFILE, "*.*"); 
    for (ia=0; ia<FlCnt&&!rca&&KeyInfo.chChar!=ESC; ++ia) {
       KbdCharIn(&KeyInfo,IO_NOWAIT,0);
       FileDeleteFuncDisp(FLAG_NOT_FIRST, FlDis[ia].Nm+DISP_FN);

       if (FlDis[ia].Atr&FILE_DIRECTORY) {   /* ������SubDir�݂̂̃��X�g����� */
          FlDis[ul_dircount++]=FlDis[ia];
       } else {                        /* �t�@�C���Ȃ�폜 */
          if (FlDis[ia].Atr&FILE_READONLY)
             ChangeAttributeFunc(FlDis[ia].Nm+DISP_FN, 0, 0, 0);  /* �S�Ă̑������N���A */
          rca=DosDelete(FlDis[ia].Nm+DISP_FN);
          if (rca) strcpy(InpLine, FlDis[ia].Nm+DISP_FN); /* �G���[�R�[�h�Ɏg���Ă��� */
       }
       QDriveSize();
    }

    /*---------------------------------*/
    /*   SubDir�̒����ċA�I�ɍ폜      */
    /*---------------------------------*/
    for (ia=0; ia<ul_dircount&&!rca&&KeyInfo.chChar!=ESC; ++ia) {
       if (strcmp(FlDis[ia].Nm+DISP_FN, ".")&&strcmp(FlDis[ia].Nm+DISP_FN, "..")){
          rca=DeleteDirContents(FlDis[ia].Nm+DISP_FN);
          QFile_LoadFileList(FLAG_LOADFILELIST_DIRONLY, "*.*"); /* ���X�g����蒼�� */
       }
    }
    /*---------------------------------*/
    /*   ��ɂȂ���SubDir���폜        */
    /*---------------------------------*/
    for (ia=0; ia<ul_dircount&&!rca&&KeyInfo.chChar!=ESC; ++ia) {
       KbdCharIn(&KeyInfo,IO_NOWAIT,0);
       if (strcmp(FlDis[ia].Nm+DISP_FN, ".")&&strcmp(FlDis[ia].Nm+DISP_FN, ".."))
          rca=DosDeleteDir(FlDis[ia].Nm+DISP_FN);
    }
    DosSetCurrentDir("..");
    return rca;
 }

/*****************************************************************/
/**   ExecCommand                                               **/
/*****************************************************************/
 void ExecCommand(void)
 {
    UCHAR   uc_inputchar;
    UCHAR   CmdParm[CMDSTR_MAX], usz_currfile[CMDSTR_MAX];
    PUCHAR  puc_inputwinstr;
    USHORT  us_AutoClose=AutoClose, us_ExecSession=ExecSession;
    
    ExecAssocProgramParm_NamewithSpace(FlDis[SelFl].Nm+DISP_FN, usz_currfile, FALSE); 
    puc_inputwinstr=usz_currfile;

    do {
       if(English){
          strcpy(MsgTxt[0],"Execute a command(Use CMD.EXE).             ");
          strcpy(MsgTxt[1],"  - [F1]Create another session              ");
          strcpy(MsgTxt[2],"  - [F2]Close a program window automatically");
          strcpy(MsgTxt[3],"                                            ");
          strcpy(MsgTxt[4],"Enter command(Up arrow key:history).        ");
          strcpy(MsgTxt[5],"                                            ");
          strcpy(MsgTxt[6],"                                            ");
          strcpy(MsgTxt[7],"        Enter:Execute    Esc:Cancel         ");
       }
       else{
          strcpy(MsgTxt[0],"�R�}���h�̎��s(CMD.EXE�Ăяo��)�����܂�     ");
          strcpy(MsgTxt[1],"  ��[F1]�ʾ���݂𐶐�����                   ");
          strcpy(MsgTxt[2],"  ��[F2]�I���������۰��                     ");
          strcpy(MsgTxt[3],"                                            ");
          strcpy(MsgTxt[4],"�R�}���h����͂��ĉ�����        (����˽�ذ) ");
          strcpy(MsgTxt[5],"                                            ");
          strcpy(MsgTxt[6],"                                            ");
          strcpy(MsgTxt[7],"        Enter:���s    Esc:���              ");
       }

       Change_FlagMark(us_ExecSession, 1, 2);
       Change_FlagMark(us_AutoClose,   2, 2);

       uc_inputchar=KbdLineIn(8, bt_g_NormalWindowColor, 5, puc_inputwinstr,
                              FLAG_INPUTWIN_HISTRY_ON|FLAG_INPUTWIN_FUNCKEY_ON
                              |FLAG_INPUTWIN_MSGBOXCLEAR); 
       switch(uc_inputchar) {
          case ESC:
             return;
          case ENTER:
             break;
          case ARROW_UP:
             puc_inputwinstr=HistryBox(FLAG_HISTRY_COMMAND);
             break;
          default:
             if(uc_inputchar==PF1) us_ExecSession = !us_ExecSession;
             if(uc_inputchar==PF2) us_AutoClose = !us_AutoClose;
             puc_inputwinstr=InpLine;
             break;
       }
    }while(uc_inputchar!=ENTER);

    sprintf(CmdParm, "/C \"%s\"", InpLine);
    ExecAssocProgramFunc(FLAG_NO_MARK, us_ExecSession, us_AutoClose, 
                         "CMD.EXE", InpLine, CmdParm);
    JumpHistInsert(FLAG_HISTRY_COMMAND, InpLine);
    QDriveSize();
 }


/****************************************************************/
/**   ExecAssocProgram                                         **/
/****************************************************************/
 ULONG ExecAssocProgram(USHORT us_flg_markfile, PSZ psz_filename)
 {
    USHORT us_count, us_silent=1;

    for (us_count=0; us_count<AssocCnt; us_count++)
       if (CheckExtention(psz_filename, AssocProg[us_count].uszExtention)) break;
    if (us_count==AssocCnt) return MYFUNC_NOT_EXEC;

    if(us_flg_markfile == FLAG_NO_MARK) {
       if(ExecAssocProgram_Select(&us_count)==ESC) return MYFUNC_EXEC;
       if(AssocProg[us_count].usSilent==0) us_silent=0;
    }
    ExecAssocProgram_MsgBox(psz_filename, 
                            AssocProg[us_count].uszProgName, 
                            AssocProg[us_count].uszParamList, 
                            us_silent, 
                            AssocProg[us_count].usSession,
                            AutoClose, us_flg_markfile, 1, 
                            FLAG_EXECPROG_EXTENTION);

    return MYFUNC_EXEC;

 }

/****************************************************************/
/**   ExecAssocProgram_Select                                  **/
/****************************************************************/
 UCHAR ExecAssocProgram_Select(PUSHORT pus_assoc_count)
 {
    UCHAR  uc_flg_operate;
    USHORT us_histry_number=0;  /* �ŏ��̗��� */
    USHORT us_count, us_listcount=0;
    USHORT us_assocnum_list[HISTORY_MAX]={0};


    for (us_count=*pus_assoc_count; us_count<AssocCnt; us_count++) {
       if (!stricmp(AssocProg[*pus_assoc_count].uszExtention, 
                    AssocProg[us_count].uszExtention)){
          us_assocnum_list[us_listcount++]=us_count;
       }   
       if(us_listcount==HISTORY_MAX) break;
    }    
    if(us_listcount==1) return ENTER;  /* �o�^�v���O�����͂P���� */

    for (us_count=0; us_count<us_listcount; us_count++){
       memset(ListTxt[us_count]+2, 0, sizeof(ListTxt[us_count])-2);
       sprintf(ListTxt[us_count]+2, "%s %s", 
                      AssocProg[us_assocnum_list[us_count]].uszProgName, 
                      AssocProg[us_assocnum_list[us_count]].uszParamList);
    }

    do {
       ShowMsgBox(HistryBox_Set(FLAG_HISTRY_ASSOCPROG, us_listcount), 
                  bt_g_NormalWindowColor);
       uc_flg_operate=HistryBoxDisp(&us_histry_number, us_listcount);
    }while(uc_flg_operate!=ESC && uc_flg_operate!=ENTER);
 
    if(uc_flg_operate==ENTER) {
       *pus_assoc_count=us_assocnum_list[us_histry_number];
    }
    ShowFileList();
    return uc_flg_operate;
 }


/****************************************************************/
/**   ExecAssocProgram_MsgBox                                  **/
/****************************************************************/
 APIRET ExecAssocProgram_MsgBox(PSZ psz_filename, PSZ psz_progname,
                   PSZ psz_parmlist, USHORT us_silent, USHORT us_session,
                   USHORT us_autoclose, USHORT us_flg_markfile, 
                   ULONG ul_markcnt, USHORT us_flg_macro)
 {
    UCHAR  ObjTitle[CMDSTR_MAX]={0}, ObjInputs[CMDSTR_MAX]={0};
    BOOL   bl_useinputwin;
    UCHAR  uc_inputchar=0;
    PUCHAR puc_inputwinstr=NULL;
    APIRET apr_execprog;
    BOOL   bl_success;

    bl_useinputwin=ExecAssocProgramParm(psz_filename, psz_parmlist,
                         ObjTitle, ObjInputs, ul_markcnt, strlen(psz_progname),
                         &bl_success);

    if(bl_success == FALSE) {
        ShowMsgTooLongStr();
        return ERROR_INVALID_FUNCTION;
    }


    if(us_silent==0) {
       switch(us_flg_macro) {
          case FLAG_EXECPROG_EXTENTION:
             strcpy(MsgTxt[0],
                    English ? "Execute program related to extension.        " :
                              "�g���q�Ɋ֘A�t����ꂽ�v���O���������s���܂� ");
             break;
          case FLAG_EXECPROG_KEYMACRO:
             strcpy(MsgTxt[0],
                    English ? "Execute program registered in macro.         " :
                              "�}�N���o�^���ꂽ�v���O���������s���܂�       ");
             break;
          default:
             strcpy(MsgTxt[0],
                    English ? "Execute a program.                           " :
                              "�v���O���������s���܂�                       ");
       }
       if(English){
          strcpy(MsgTxt[1],"  Pgm :                                      ");
          strcpy(MsgTxt[2],"  Parm:                                      ");
          strcpy(MsgTxt[3],"  - [F1]Create another session               ");
          strcpy(MsgTxt[4],"  - [F2]Close a program window automatically ");
          strcpy(MsgTxt[5],"                                             ");
          strcpy(MsgTxt[6],"                                             ");
          strcpy(MsgTxt[7],"         Enter:Execute    Esc:Cancel         ");
       }
       else{
          strcpy(MsgTxt[1],"  Pgm :                                      ");
          strcpy(MsgTxt[2],"  Parm:                                      ");
          strcpy(MsgTxt[3],"  ��[F1]�ʾ���݂𐶐�����                    ");
          strcpy(MsgTxt[4],"  ��[F2]�I���������۰��                      ");
          strcpy(MsgTxt[5],"                                             ");
          strcpy(MsgTxt[6],"                                             ");
          strcpy(MsgTxt[7],"         Enter:���s       Esc:���           ");
       }
    
       strcpy(MsgTxt[1]+8, psz_progname);
       strcpy(MsgTxt[2]+8, ObjTitle);   
    
       do {
          Change_FlagMark(us_session, 3, 2);
          Change_FlagMark(us_autoclose, 4, 2);

          if(bl_useinputwin==FALSE) {
             uc_inputchar=GetYesorNo_withMsgBox(ENTER, 8, bt_g_NormalWindowColor,
                            FLAG_GETYESORNO_FUNCKEY_ON|FLAG_GETYESORNO_MSGBOXCLEAR);
          } else {
             uc_inputchar=KbdLineIn(8, bt_g_NormalWindowColor, 6, puc_inputwinstr,
                            FLAG_INPUTWIN_NOSTRINGS_OK|FLAG_INPUTWIN_FUNCKEY_ON
                            |FLAG_INPUTWIN_MSGBOXCLEAR);
          }
       
          switch(uc_inputchar) {
             case ENTER:
                break;
             case ESC:
                return NO_ERROR;
             default:
                if(uc_inputchar== PF1) us_session = !us_session;
                if(uc_inputchar== PF2) us_autoclose = !us_autoclose;
                if(bl_useinputwin==TRUE) puc_inputwinstr=InpLine;
                break;
          }
       }while(uc_inputchar!=ENTER);
    }

    if(bl_useinputwin==TRUE) {
       bl_success=ExecAssocProgramParm_Restruct(InpLine, ObjTitle, ObjInputs, 
                                     strlen(psz_progname), bl_useinputwin);
       if(bl_success == FALSE) {
           ShowMsgTooLongStr();
           return ERROR_INVALID_FUNCTION;
       }
    }
    apr_execprog=ExecAssocProgram_IfProgExist(us_flg_markfile, us_session, 
                       us_autoclose, psz_progname, ObjTitle, ObjInputs);

    if (us_session && us_flg_macro==FLAG_EXECPROG_KEYMACRO){
       if(ul_markcnt) QFile();
       ShowFileList();
    }
    return apr_execprog;
 }


/****************************************************************/
/**   ExecAssocProgram_IfProgExist                             **/
/****************************************************************/
 APIRET ExecAssocProgram_IfProgExist(USHORT us_flg_markfile, USHORT us_session, 
                USHORT us_AutoClose, PSZ psz_progname, PSZ ObjTitle, PSZ ObjInputs )
 {
    APIRET apr_progexist;
    FILESTATUS3 fs3_PathInfo3={{0}};
    UCHAR  uc_fullfilename[_MAX_PATH]; /* dummy �Ƃ��Ďg���� */
    
    apr_progexist=DosQueryPathInfo(psz_progname, FIL_STANDARD,
                                   (PVOID)&fs3_PathInfo3, sizeof(FILESTATUS3));
    if (apr_progexist) {
       apr_progexist=FilePathSearch(psz_progname, uc_fullfilename,
                                    sizeof(uc_fullfilename));  
    }
    if (apr_progexist) {
       ShowMsgExecNotF(psz_progname);
    } else {
       ExecAssocProgramFunc(us_flg_markfile, us_session, us_AutoClose, psz_progname, 
                            ObjTitle, ObjInputs);
    }
    return apr_progexist;
 }

/****************************************************************/
/**   ExecAssocProgramFunc                                     **/
/****************************************************************/
 void ExecAssocProgramFunc(USHORT us_flg_markfile, USHORT session, USHORT us_AutoClose, 
                           PSZ pPgmName, PSZ ObjTitle, PSZ ObjInputs)
{
    UCHAR  CmdParm[CMDSTR_MAX], usz_currdir[_MAX_PATH];
    APIRET apr_apptype;
    ULONG  ul_apptype=0L;
    USHORT us_sessiontype;

    if (session){
       if (CheckExtention(pPgmName,".cmd")) { 
          sprintf(CmdParm, "/C %s %s", pPgmName, ObjInputs);
          FileExecFunc_AnotherSession(us_flg_markfile, pPgmName, 
                          "CMD.EXE", CmdParm, us_AutoClose, SSF_TYPE_DEFAULT);

       } else if (CheckExtention(pPgmName,".bat")) {
          sprintf(CmdParm, "/C %s %s", pPgmName, ObjInputs);
          FileExecFunc_AnotherSession(us_flg_markfile, pPgmName, 
                          "COMMAND.COM", CmdParm, us_AutoClose, SSF_TYPE_WINDOWEDVDM);
       } else {
          apr_apptype=DosQueryAppType(pPgmName, &ul_apptype);
          if(apr_apptype) {
             ErrorMsgDisp(apr_apptype, pPgmName);
             return;
          }

          if(ul_apptype&(FAPPTYP_WINDOWSREAL|FAPPTYP_WINDOWSPROT
                         |FAPPTYP_WINDOWSPROT31)) {
             SetFullCurrentPathName(usz_currdir);
             FileExecFunc_UseWinAPI(ObjTitle, pPgmName, ObjInputs, usz_currdir, 
                          DisableJapanFunc ? FLAG_DOSMODE_PCDOS : FLAG_DOSMODE_DOSV,
                          PROG_31_ENHSEAMLESSCOMMON);
                          // ���{����ȊO�ł́ADOS/V�֘A�̋@�\�𖳌��ɂ���

          } else {
             if(ul_apptype&FAPPTYP_DOS) 
                us_sessiontype=SSF_TYPE_WINDOWEDVDM;
             else 
                us_sessiontype=SSF_TYPE_DEFAULT;
             FileExecFunc_AnotherSession(us_flg_markfile, ObjTitle, 
                          pPgmName, ObjInputs, us_AutoClose, us_sessiontype);
          }
       }
    } else {

#if  defined(__GNUC__) 
       sprintf(CmdParm, "\"%s\" %s", pPgmName, ObjInputs);
#else
       sprintf(CmdParm, "\"\"%s\" %s\"", pPgmName, ObjInputs);
#endif
       CmdExec_SameSession(us_flg_markfile, CmdParm, us_AutoClose);
    }
    if(us_flg_markfile == FLAG_NO_MARK) QDriveSize();
 }

/****************************************************************/
/**   ExecAssocProgramParm                                     **/
/*--------------------------------------------------------------*/
/*      ExcecAssocProgFunc() �̂��߂Ƀp�����[�^���Z�b�g����     */
/*         ObjInputs[] :&F(̧�ٖ��͐�΃p�X��), &C(���΃p�X��)  */
/*         ObjTitle[]  :̧�ٖ��͑��΃p�X��                      */ 
/****************************************************************/
 BOOL ExecAssocProgramParm(PSZ psz_filename, PSZ pParm, 
                           PSZ ObjTitle, PSZ ObjInputs, 
                           USHORT us_parmfilenum, USHORT us_prognamelen,
                           BOOL *bl_success)
 {
    PUCHAR puc_AndF_ptr, puc_AndC_ptr, puc_AndN_ptr;
    UCHAR uc_fullfname[CMDSTR_MAX], uc_currentfname[CMDSTR_MAX],
          usz_fname_woext[_MAX_PATH];

    *bl_success = TRUE;

    if(us_parmfilenum < 2) {
       ExecAssocProgramParm_NamewithSpace(psz_filename, uc_fullfname, TRUE);
       ExecAssocProgramParm_NamewithSpace(psz_filename, uc_currentfname, FALSE);
    } else {
       ObjTitle[0]='\0'; /* �^�C�g����OS�ɔC���� */
       *bl_success=ExecAssocProgramParm_NameSet(uc_fullfname, 
                                    us_prognamelen+strlen(pParm), TRUE);
       if(*bl_success == FALSE) return FALSE;

       *bl_success=ExecAssocProgramParm_NameSet(uc_currentfname, 
                                    us_prognamelen+strlen(pParm), FALSE);
       if(*bl_success == FALSE) return FALSE;
    }

    /* �p�����[�^���� "&F/&C" ������΃t�@�C�����ɒu�������� */
    puc_AndF_ptr=strstr(pParm,"&F");
    if(!puc_AndF_ptr) puc_AndF_ptr=strstr(pParm,"&f");
    puc_AndC_ptr=strstr(pParm,"&C");
    if(!puc_AndC_ptr) puc_AndC_ptr=strstr(pParm,"&c");

    if (puc_AndF_ptr){
       *(puc_AndF_ptr)='\0'; 
       sprintf(ObjInputs,  "%s%s%s", pParm, uc_fullfname,    puc_AndF_ptr+2);
       if(us_parmfilenum < 2) {
          sprintf(ObjTitle,"%s%s%s", pParm, uc_currentfname, puc_AndF_ptr+2);
       }
       *(puc_AndF_ptr)='&'; 
    } else if (puc_AndC_ptr){
       *(puc_AndC_ptr)='\0'; 
       sprintf(ObjInputs,  "%s%s%s", pParm, uc_currentfname, puc_AndC_ptr+2);
       if(us_parmfilenum < 2) {
          sprintf(ObjTitle,"%s%s%s", pParm, uc_currentfname, puc_AndC_ptr+2);
       }
       *(puc_AndC_ptr)='&'; 
    } else { 
       strcpy(ObjInputs, pParm);
       if(us_parmfilenum < 2) strcpy(ObjTitle,  pParm);
    }

    puc_AndN_ptr=strstr(pParm,"&N");
    if(!puc_AndN_ptr) puc_AndN_ptr=strstr(pParm,"&n");

    if (puc_AndN_ptr){
       _splitpath(psz_filename, NULL, NULL, usz_fname_woext, NULL);   
       *bl_success=ExecAssocProgramParm_Restruct(usz_fname_woext, ObjTitle, ObjInputs, 
                                     us_prognamelen, FALSE);
       if(*bl_success == FALSE) return FALSE;
    }
    
    if(strstr(pParm, "&I") || strstr(pParm, "&i")) return TRUE;
    return FALSE;
 }


/****************************************************************/
/**   ExecAssocProgramParm_NameSet                             **/
/**------------------------------------------------------------**/
/**     �}�[�N���ꂽ�t�@�C��������̕����񒆂ɋ󔒂łȂ�   **/
/****************************************************************/
 BOOL ExecAssocProgramParm_NameSet(PSZ  psz_objinput, USHORT us_prognamelen, 
                                   BOOL bl_fullpath)
 {
    USHORT us_maxstrlen;
    UCHAR  uc_filedummy[_MAX_PATH];
    ULONG  ul_count;

    us_maxstrlen=CMDSTR_MAX-us_prognamelen-4;
    psz_objinput[0]='\0';

    for (ul_count=0; ul_count <FlCnt; ul_count++) {
       if (FlDis[ul_count].Mark) {
          ExecAssocProgramParm_NamewithSpace(FlDis[ul_count].Nm+DISP_FN, 
                                             uc_filedummy, bl_fullpath);
          if((strlen(psz_objinput)+strlen(uc_filedummy)) > us_maxstrlen-2) 
             return FALSE;
          sprintf(psz_objinput, "%s%s ", psz_objinput, uc_filedummy);
       }
    }
    return TRUE;
 }

/****************************************************************/
/**   ExecAssocProgramParm_NamewithSpace                       **/
/****************************************************************/
 void ExecAssocProgramParm_NamewithSpace(PSZ psz_filename, PSZ psz_filestr, 
                                         BOOL bl_fullpath)
 {
    UCHAR uc_filedummy[_MAX_PATH];

    if(bl_fullpath==TRUE) SetFullFileName(psz_filename, uc_filedummy);
    else                  strcpy(uc_filedummy, psz_filename);

    /* �S�p�^���p�̋󔒂����&���܂ރt�@�C�����΍� */
    if(strchr(uc_filedummy, ' ')||strstr(uc_filedummy, "�@")
     ||strchr(uc_filedummy, '&')) {
       sprintf(psz_filestr,"\"%s\"", uc_filedummy);
    } else {
       strcpy(psz_filestr, uc_filedummy);
    }

 }

/****************************************************************/
/**   ExecAssocProgramParm_Restruct                            **/
/****************************************************************/
BOOL ExecAssocProgramParm_Restruct(PSZ psz_inputstr, PSZ ObjTitle, PSZ ObjInputs, 
                                   USHORT us_prognamelen, BOOL bl_inputwin)
{
  BOOL bl_success = TRUE;

  bl_success = ExecAssocProgramParm_RestructString(psz_inputstr, ObjTitle, us_prognamelen, bl_inputwin);
  if(bl_success == FALSE) return FALSE;

  bl_success = ExecAssocProgramParm_RestructString(psz_inputstr, ObjInputs, us_prognamelen, bl_inputwin);
  if(bl_success == FALSE) return FALSE;

  return TRUE;
}

/****************************************************************/
/**   ExecAssocProgramParm_RestructString                      **/
/****************************************************************/
BOOL ExecAssocProgramParm_RestructString(PSZ psz_inputstr, PSZ psz_cmdstr, 
                                   USHORT us_prognamelen, BOOL bl_inputwin)
{

   PUCHAR puc_AndI_ptr;
   UCHAR  uc_cmdstrdummy[CMDSTR_MAX];
   BOOL   bl_stringlen_ok=TRUE;
   
   if(strlen(psz_inputstr)+strlen(psz_cmdstr)+us_prognamelen > CMDSTR_MAX-2 ) {
      bl_stringlen_ok=FALSE;
      return FALSE;
   }

   if(bl_inputwin == TRUE) {
      puc_AndI_ptr = strstr(psz_cmdstr, "&I" );
      if(!puc_AndI_ptr) puc_AndI_ptr=strstr(psz_cmdstr, "&i" );
   } else {
      puc_AndI_ptr = strstr(psz_cmdstr, "&N" );
      if(!puc_AndI_ptr) puc_AndI_ptr=strstr(psz_cmdstr, "&n" );
   }

   if (puc_AndI_ptr) {
      *(puc_AndI_ptr)='\0'; 
      strcpy(uc_cmdstrdummy, puc_AndI_ptr+2);
      if(bl_stringlen_ok == TRUE) 
         sprintf(psz_cmdstr,  "%s%s%s", psz_cmdstr, psz_inputstr, uc_cmdstrdummy);
      else 
         strcat(psz_cmdstr, uc_cmdstrdummy);
   }
   return TRUE;
}


/****************************************************************/
/**   ExecProgram                                              **/
/****************************************************************/
 void ExecProgram(void)
 {
    UCHAR  FulFlNm[_MAX_PATH];
    UCHAR  uc_inputchar;
    USHORT us_ExecSession=ExecSession, us_AutoClose=AutoClose;
    PUCHAR  puc_inputwinstr=NULL;


    if(English){
       strcpy(MsgTxt[0],"Execute a program.                          ");
       strcpy(MsgTxt[1],"                                            ");
       strcpy(MsgTxt[2],"  - [F1]Create another session              ");
       strcpy(MsgTxt[3],"  - [F2]Close a program window automatically");
       strcpy(MsgTxt[4],"                                            ");
       strcpy(MsgTxt[5],"  Input parameter if require it.            ");
       strcpy(MsgTxt[6],"                                            ");
       strcpy(MsgTxt[7],"                                            ");
       strcpy(MsgTxt[8],"        Enter:Execute    Esc:Cancel         ");
    }
    else{
       strcpy(MsgTxt[0],"�v���O���������s���܂�                ");
       strcpy(MsgTxt[1],"                                      ");
       strcpy(MsgTxt[2],"  ��[F1]�ʾ���݂𐶐�����             ");
       strcpy(MsgTxt[3],"  ��[F2]�I���������۰��               ");
       strcpy(MsgTxt[4],"                                      ");
       strcpy(MsgTxt[5],"  �p�����[�^���K�v�Ȃ���͂��ĉ�����  ");
       strcpy(MsgTxt[6],"                                      ");
       strcpy(MsgTxt[7],"                                      ");
       strcpy(MsgTxt[8],"      Enter:���s      Esc:���        ");
    }

    strcpy(MsgTxt[1]+2, FlDis[SelFl].Nm+DISP_FN);

    do {
       Change_FlagMark(us_ExecSession, 2, 2);
       Change_FlagMark(us_AutoClose,   3, 2);

       uc_inputchar=KbdLineIn(9, bt_g_NormalWindowColor, 6, puc_inputwinstr,
                       FLAG_INPUTWIN_NOSTRINGS_OK|FLAG_INPUTWIN_FUNCKEY_ON
                       |FLAG_INPUTWIN_MSGBOXCLEAR);

       switch(uc_inputchar) {
          case ESC:
             return;
          case ENTER:
             break;
          default:
             if(uc_inputchar==PF1) us_ExecSession = !us_ExecSession;
             if(uc_inputchar==PF2) us_AutoClose = !us_AutoClose;
             puc_inputwinstr=InpLine;
             break;
       }
    }while(uc_inputchar!=ENTER);

    SetFullFileName(FlDis[SelFl].Nm+DISP_FN, FulFlNm);
    ExecAssocProgramFunc(FLAG_NO_MARK, us_ExecSession, us_AutoClose, FulFlNm, 
                         FlDis[SelFl].Nm+DISP_FN, InpLine);
 }

/*****************************************************************/
/**   FileExecFunc_AnotherSession                               **/
/*****************************************************************/
VOID FileExecFunc_AnotherSession(USHORT us_flg_markfile, PSZ psz_PgmTitle, 
       PSZ psz_PgmName, PSZ psz_PgmInputs, USHORT us_AutoClose, 
       USHORT us_SessionType) 
{
    ULONG  ul_SessID;
    PID    pid_ProcID;
    APIRET apr_ExecProg;
    
    STARTDATA StartData ={0};
    UCHAR ObjBuf[256]={0};

    /*--------------------------------*/
    /* StartData �̏������i���ʕ����j */
    /*--------------------------------*/
    StartData.Length      = sizeof(STARTDATA);
    StartData.Related     = SSF_RELATED_INDEPENDENT;
    StartData.FgBg        = SSF_FGBG_FORE;
    StartData.TraceOpt    = SSF_TRACEOPT_NONE;
    StartData.TermQ       = 0;
    StartData.Environment = 0;
    StartData.InheritOpt  = SSF_INHERTOPT_PARENT;
    StartData.IconFile    = 0;
    StartData.PgmHandle   = 0;
    StartData.InitXPos    = 30;
    StartData.InitYPos    = 40;
    StartData.InitXSize   = 200;
    StartData.InitYSize   = 140;
    StartData.Reserved    = 0;
    StartData.ObjectBuffer  = ObjBuf;
    StartData.ObjectBuffLen = sizeof(ObjBuf);  

    /*--------------------------------*/
    /* StartData �ւ̑��             */
    /*--------------------------------*/
    StartData.PgmTitle    = psz_PgmTitle;   
    StartData.PgmName     = psz_PgmName;    
    StartData.PgmInputs   = psz_PgmInputs;  
    StartData.SessionType = us_SessionType; 
    if (us_AutoClose) 
       StartData.PgmControl = SSF_CONTROL_VISIBLE;
    else 
       StartData.PgmControl = SSF_CONTROL_VISIBLE|SSF_CONTROL_NOAUTOCLOSE;
    
    if(us_SessionType==SSF_TYPE_WINDOWEDVDM) {
       if(us_g_flg_dosmode==FLAG_DOSMODE_DOSV && !DisableJapanFunc)
                  // ���{����ȊO�ł́ADOS/V�֘A�̋@�\�𖳌��ɂ���
          StartData.Environment = STRING_DOSMODE_DOSV;
       else 
          StartData.Environment = STRING_DOSMODE_PCDOS;
    }
    
    apr_ExecProg = DosStartSession(&StartData, &ul_SessID, &pid_ProcID); 
    switch(apr_ExecProg){
       case NO_ERROR: 
       case ERROR_SMG_START_IN_BACKGROUND: /* BackGround�Ŏ��s���ꂽ */
          if (us_flg_markfile == FLAG_NO_MARK) ShowMsgExecOk(); 
          break;
       case ERROR_FILE_NOT_FOUND: 
          ShowMsgExecNotF(StartData.ObjectBuffer); 
          break;
       default: 
          ShowMsgExecErr(apr_ExecProg, StartData.ObjectBuffer); 
          break;
    }
    return;
}

/*****************************************************************/
/**   FileExecFunc_UseWinAPI                                    **/
/*****************************************************************/
VOID FileExecFunc_UseWinAPI(PSZ psz_PgmTitle, PSZ psz_PgmName, 
       PSZ psz_PgmInputs, PSZ psz_StartupDir, USHORT us_flg_dosmode, 
       ULONG ul_ProgType) 
{
   PROGDETAILS  pds_progdetails={0};

   /* DLL�̃��[�h�̃`�F�b�N */
   if(!pfnStartApp) return; 

   /*--------------------------------------*/
   /* pds_progdetails �̏������i���ʕ����j */
   /*--------------------------------------*/
   pds_progdetails.Length          = sizeof(PROGDETAILS);
   pds_progdetails.progt.fbVisible = SHE_VISIBLE;
   pds_progdetails.pszIcon         = "";
   pds_progdetails.swpInitial.fl   = SWP_ACTIVATE; /* �E�C���h�E�ʒu   */
   pds_progdetails.swpInitial.cy   = 0;            /* �E�B���h�E�̕�   */
   pds_progdetails.swpInitial.cx   = 0;            /* �E�B���h�E�̍��� */
   pds_progdetails.swpInitial.y    = 0;            /* �E�B���h�E�̒[   */
   pds_progdetails.swpInitial.x    = 0;            /* �E�B���h�E�̍��[ */
   pds_progdetails.swpInitial.hwndInsertBehind = HWND_TOP;
   pds_progdetails.swpInitial.hwnd             = 0;
   pds_progdetails.swpInitial.ulReserved1      = 0;
   pds_progdetails.swpInitial.ulReserved2      = 0;

   /*--------------------------------*/
   /* pds_progdetails �ւ̑��       */
   /*--------------------------------*/
   pds_progdetails.progt.progc     = ul_ProgType;
   pds_progdetails.pszExecutable   = psz_PgmName;
   pds_progdetails.pszTitle        = psz_PgmTitle;
   pds_progdetails.pszParameters   = psz_PgmInputs;
   pds_progdetails.pszStartupDir   = psz_StartupDir;

   switch(us_flg_dosmode) {
      case FLAG_DOSMODE_DOSV: 
         pds_progdetails.pszEnvironment = 
                DisableJapanFunc ? STRING_DOSMODE_PCDOS : STRING_DOSMODE_DOSV;
                       // ���{����ȊO�ł́ADOS/V�֘A�̋@�\�𖳌��ɂ���
         break;
      case FLAG_DOSMODE_PCDOS: 
         pds_progdetails.pszEnvironment = STRING_DOSMODE_PCDOS;
         break;
      default:
         pds_progdetails.pszEnvironment = 0;
         break;
   }

   pfnStartApp(NULLHANDLE, &pds_progdetails, NULL, NULL,
               SAF_INSTALLEDCMDLINE);
}

 
/*****************************************************************/
/**   FileCopy                                                  **/
/*****************************************************************/
 void FileCopy(void)
 {
    UCHAR uc_inputchar, usz_fnamesave[_MAX_PATH]={0}, usz_tstampsave[16]={0};
    APIRET apr_filecopy;
    USHORT us_dummy, us_flg_inthedir=0;
    PUCHAR puc_inputwinstr=NULL;
 
    if(!FlCnt) return;
    if(!strcmp(FlDis[SelFl].Nm+DISP_FN, ".") || 
       !strcmp(FlDis[SelFl].Nm+DISP_FN, "..")) return;


    do {
       if(FlDis[SelFl].Atr&FILE_DIRECTORY) {
           if(English){
              strcpy(MsgTxt[0],"Copy a directory.                                 ");
              strcpy(MsgTxt[1]," Dir:                                             ");
              strcpy(MsgTxt[2]," - [F1] Copy contents of a directory              ");
           }
           else{
              strcpy(MsgTxt[0],"�f�B���N�g�����R�s�[���܂�                        ");
              strcpy(MsgTxt[1]," Dir:                                             ");
              strcpy(MsgTxt[2]," ��[F1] �f�B���N�g���̒��g���R�s�[����            ");
           }
           Change_FlagMark(us_flg_inthedir, 2, 1);
       } else {
           if(English){
              strcpy(MsgTxt[0],"Copy a file.                                      ");
              strcpy(MsgTxt[1]," File:                                            ");
              strcpy(MsgTxt[2],"                                                  ");
           }
           else{
              strcpy(MsgTxt[0],"�t�@�C�����R�s�[���܂�                            ");
              strcpy(MsgTxt[1]," File:                                            ");
              strcpy(MsgTxt[2],"                                                  ");
           }
       }
       strcpy(MsgTxt[3],"                                                  ");

       if(English){
          strcpy(MsgTxt[4],"Enter destination directory(Up arrow key:history).");
          strcpy(MsgTxt[5],"                                                  ");
          strcpy(MsgTxt[6],"                                                  ");
          strcpy(MsgTxt[7],"            Enter:OK        Esc:Cancel            ");
       }
       else{
          strcpy(MsgTxt[4],"�R�s�[����w�肵�ĉ�����            (������˽�ذ) ");
          strcpy(MsgTxt[5],"                                                  ");
          strcpy(MsgTxt[6],"                                                  ");
          strcpy(MsgTxt[7],"           Enter:���s         Esc:���            ");
       }

       strcpy(MsgTxt[1]+6, FlDis[SelFl].Nm+DISP_FN);

       uc_inputchar=KbdLineIn(8, bt_g_NormalWindowColor, 5, puc_inputwinstr,
                              FLAG_INPUTWIN_HISTRY_ON|FLAG_INPUTWIN_MSGBOXCLEAR
                              |FLAG_INPUTWIN_TABKEY_ON|FLAG_INPUTWIN_FUNCKEY_ON);    
       switch(uc_inputchar) {
          case ESC:
             return;
          case ENTER:
             break;
          case PF1:                          
             if(FlDis[SelFl].Atr&FILE_DIRECTORY) {
                 us_flg_inthedir = !us_flg_inthedir;
                 puc_inputwinstr=InpLine;        
             }
             break;         
          default:
             puc_inputwinstr=HistryBox(FLAG_HISTRY_PATH);
       }
    }while(uc_inputchar!=ENTER);

    apr_filecopy=FileCopy_ConverttoAbsolutePath(InpLine);
    if(apr_filecopy) {    
       FileCopyRc(apr_filecopy);
       return;
    }

    if(SameDriveCheck(&us_dummy)) return; /* ���͕������s���̎� */
    if(SameDirCheck(FlDis[SelFl].Nm+DISP_FN)) return;

    OverWrite=RESET; 
    us_g_flg_readonly=READONLY_RESET;
    FirstDisp=1;


    strcpy(usz_fnamesave, FlDis[SelFl].Nm+DISP_FN);  
    memcpy(usz_tstampsave, FlDis[SelFl].Nm+DISP_DT, (DISP_MK-DISP_DT)); 
                        /* �t�@�C�����̑ޔ� [QFile()�΍�] */

    if (FlDis[SelFl].Atr&FILE_DIRECTORY) {
       apr_filecopy=FileCopyDir(usz_fnamesave, FLAG_COPY_ONLY, us_flg_inthedir);
       QFile();
    } else {
       apr_filecopy=FileCopyFl(usz_fnamesave, usz_tstampsave, 
                               FLAG_COPY_ONLY, 1);
    }
    ShowFileList();
    FileCopyRc(apr_filecopy);
    JumpHistInsert(FLAG_HISTRY_PATH, InpLine);
    QDriveSize();
 }

/******************************************************************/
/**   FileCopyDir                                                **/
/******************************************************************/
 APIRET FileCopyDir(PSZ DirNm, USHORT us_flg_copydelmove, USHORT us_flg_inthedir)
 {  

    PUCHAR puc_newDirname = DirNm;
    FILESTATUS3 fs3_PathInfo3={{0}};
    APIRET apr_creatdir, apr_pathexist;
    

    if(us_flg_inthedir == 1) puc_newDirname = NULL;
    
    apr_pathexist=DosQueryPathInfo(InpLine,1,&fs3_PathInfo3,sizeof(FILESTATUS3));
    switch(apr_pathexist){
       case NO_ERROR:
          return CopyDirContents(DirNm, InpLine, puc_newDirname, us_flg_copydelmove);
       case ERROR_FILE_NOT_FOUND: 
       case ERROR_PATH_NOT_FOUND: 
          break;
       default: 
          return apr_pathexist;
    }


    if(CreateDir_YesorNo(InpLine, FLAG_GETYESORNO_MSGBOXCLEAR) == ESC) {
       KeyInfo.chChar=ESC;
       return 0;
    }

    /* �V����dir�����   */
    apr_creatdir=CreateDirFunc(InpLine);
    CreateDirFuncRc(apr_creatdir); 
    if (apr_creatdir) return 1;

    return CopyDirContents(DirNm, InpLine, puc_newDirname, us_flg_copydelmove);
 }

/******************************************************************/
/**   FileCopyFl                                                 **/
/******************************************************************/
 APIRET FileCopyFl(PSZ FlNm, PSZ Time, USHORT us_flg_copydelmove, 
                   ULONG ul_copyfilenum)
 {
    FILESTATUS3 fs3_PathInfo3={{0}};
    APIRET apr_pathexist, apr_creatdir;
    PUCHAR puc_yenptr;
    UCHAR  uc_inputchar, usz_fulldirname[_MAX_PATH]={0};

    /*-------------------------------------------------*/
    /* ���͂��ꂽ������ɑ�������f�B���N�g�������邩  */
    /*-------------------------------------------------*/
    apr_pathexist=DosQueryPathInfo(InpLine,1,&fs3_PathInfo3,sizeof(FILESTATUS3));
    switch(apr_pathexist){
       case NO_ERROR:  /* ����I�@���̂܂܃R�s�[�� */
          if(ul_copyfilenum>1) {
             if(!(fs3_PathInfo3.attrFile&FILE_DIRECTORY)) {
                ShowMsgSameName();
                KeyInfo.chChar=ESC; 
                return 0;
             }   
          }
          return  FileCopyFunc(FlNm, Time, InpLine, FlNm, us_flg_copydelmove);

       case ERROR_FILE_NOT_FOUND: 
       case ERROR_PATH_NOT_FOUND: 
          break;
       default: 
          return apr_pathexist;
    }

    /*--------------------------------------*/
    /*  �ިڸ�ذ�Ȃ�                        */
    /*--------------------------------------*/
    strcpy(usz_fulldirname, InpLine);

    if(ul_copyfilenum > 1) {
        uc_inputchar=CreateDir_YesorNo(InpLine, FLAG_GETYESORNO_NO_OPTION);
    } else {
        if(English){
           strcpy(MsgTxt[0],"The destination directory is not found.   ");
           strcpy(MsgTxt[1],"                                          "); 
           strcpy(MsgTxt[2],"                                          ");
           strcpy(MsgTxt[3],"Select action.                            ");
           strcpy(MsgTxt[4]," Y(Enter). Make directory                 ");
           strcpy(MsgTxt[5]," F(Space). Copy file to here by other name");
           strcpy(MsgTxt[6],"                                          ");
           strcpy(MsgTxt[7],"                       N/Esc:Cancel       ");
        }
        else{
           strcpy(MsgTxt[0],"���ݑ��݂����ިڸ�؂ł͂���܂���.        ");
           strcpy(MsgTxt[1],"                                          "); 
           strcpy(MsgTxt[2],"                                          ");
           strcpy(MsgTxt[3],"�������@��I�����ĉ�����.                 ");
           strcpy(MsgTxt[4]," �x(Enter).�ިڸ�؂��쐬��̧�ق��߰����. ");
           strcpy(MsgTxt[5]," �e(Space).���ިڸ�؂ŕʖ��ɺ�߰����.     ");
           strcpy(MsgTxt[6],"                                          ");
           strcpy(MsgTxt[7],"                       �m/Esc:���        ");
        }

        FileCopyFuncOption_StringsAdjust(usz_fulldirname, strlen(MsgTxt[0])-2);
        strcpy(MsgTxt[1]+1, usz_fulldirname);
        if (us_flg_copydelmove==FLAG_COPY_DELETE
               ||us_flg_copydelmove==FLAG_MOVE_SAMEDRIVE) {
           if(English){
              memcpy(MsgTxt[5]+10,"Move",4);
           }
           else{
              memcpy(MsgTxt[4]+32,"�ړ�",4);
              memcpy(MsgTxt[5]+28,"�ړ�",4);
           }
        }
        ShowMsgBox(8, bt_g_NormalWindowColor);

        uc_inputchar=0;
        do {
           KbdCharIn(&KeyInfo,IO_WAIT,0);
           switch(KeyInfo.chChar){
              case 'Y': 
              case 'y': 
              case ENTER:
              case 'F': 
              case 'f':
              case ' ':
              case 'N': 
              case 'n':
              case ESC:
                 uc_inputchar=KeyInfo.chChar;
                 break;
              default:
                 uc_inputchar=0;
           }
        }while(uc_inputchar==0);
    }

    switch(uc_inputchar){
       case 'Y': 
       case 'y': 
       case ENTER:
          ShowFileList();
          apr_creatdir=CreateDirFunc(InpLine);
          if (apr_creatdir) {
             CreateDirFuncRc(apr_creatdir);
             return 1;
          }
          puc_yenptr=jstrrchr(InpLine, '\\');
          if (puc_yenptr == InpLine+strlen(InpLine)-1) *puc_yenptr='\0';
          return FileCopyFunc(FlNm, Time, InpLine, FlNm, us_flg_copydelmove);
       case 'F': 
       case 'f':
       case ' ':
          if(ul_copyfilenum > 1) break;
          ShowFileList();
          puc_yenptr=jstrrchr(InpLine, '\\');
          if (puc_yenptr == InpLine+strlen(InpLine)-1) {
             ShowMsgNameNg();
             KeyInfo.chChar=ESC;
             return 0;
          }
          if(puc_yenptr) { 
             if(*(puc_yenptr-1) !=':') {  /* InpLine �͕K����΃p�X(X:\.....) */
                *puc_yenptr='\0';
                if(strlen(InpLine)) {
                   apr_creatdir=CreateDirFunc(InpLine);
                   CreateDirFuncRc(apr_creatdir);
                   *puc_yenptr='\\';
                   if (apr_creatdir) return apr_creatdir;
                }
             }
          }
          return FileCopyFunc(FlNm,Time,InpLine, NULL, us_flg_copydelmove);
    }

    KeyInfo.chChar=ESC; 
    ShowFileList();
    return 0;
 }


/*****************************************************************/
/**   FileCopy_ConverttoAbsolutePath                             **/
/*****************************************************************/
 ULONG FileCopy_ConverttoAbsolutePath(PSZ psz_inputpath)
{
   UCHAR  usz_pathnameclone[_MAX_PATH]={0}, 
          usz_otherdrivepathname[_MAX_PATH]={0};
   PUCHAR puc_pathname;
   ULONG  ul_DriveNo, ul_PathLen;
   APIRET apr_pathexist;


   strcpy(usz_pathnameclone, psz_inputpath); 
   puc_pathname = usz_pathnameclone 
                + strspn(usz_pathnameclone, " ");  /* �擪�̋󔒂����� */

   switch(*(puc_pathname)) {
      case '\\':   /* �擪��'\' */
         if(*(puc_pathname+1) =='\\') {
             /* �l�b�g���[�N�h���C�u(UNC��)  \\aaaa\bbb\ccc... */
             return 0;
         } else {
             /* �J�����g�h���C�u�̐�΃o�X */
             sprintf(psz_inputpath, "%s%s", DriveDis, usz_pathnameclone);
             return 0;
         }
      case ':':  /* �ꕶ���ڂ�':' -> �G���[ */
      case '\0':
         return 0;
      default:
         if(*(puc_pathname+1) ==':') {
            /* �h���C�u�w�肠�� */
            if(*(puc_pathname+2) =='\\') {
                /* �ʃh���C�u�̐�΃p�X */
                return 0;
            } else { 
                /* �ʃh���C�u�̑��΃p�X */
                sprintf(usz_otherdrivepathname, "%c:\\", *puc_pathname);
                ul_DriveNo=(*(puc_pathname)<'a'?
                         *(puc_pathname)-64 : *(puc_pathname)-96);
                ul_PathLen=sizeof(usz_otherdrivepathname)-3;
                apr_pathexist=DosQueryCurrentDir(ul_DriveNo,
                               usz_otherdrivepathname+3, &ul_PathLen);
                if(!apr_pathexist) {
                   if(*(puc_pathname+2)=='\0' || *(puc_pathname+2)==' ') {
                      strcpy(psz_inputpath, usz_otherdrivepathname);
                   } else {
                      _jmakepath(psz_inputpath, NULL, 
                                 usz_otherdrivepathname, puc_pathname+2, NULL);
                   }
                }
                return apr_pathexist;
            }
         } else {
            /* �J�����g�h���C�u�̑��΃p�X */
             _jmakepath(psz_inputpath, DriveDis, PathDis, puc_pathname, NULL);
             return 0;
         }
   }
}


/*****************************************************************/
/**   FileCopyFunc                                              **/
/*****************************************************************/
 APIRET FileCopyFunc(PSZ FlNm, PSZ Time, PSZ DirNm, PSZ NewFlNm, USHORT us_flg_copydelmove)
 {
    APIRET  rca=0;  /* �K�������� */
    ULONG ul_flg_doscopy;
    UCHAR TargetFl[_MAX_PATH];
    FILEFINDBUF3  ffb3_FileInfo3={0};

  /*-----------------------------------------------*/
  /*  �ړI�̃t�@�C�������f�B���N�g�����{�t�@�C���� */
  /*  ��������Ȃ��̂őO�����č���Ă���           */
  /*-----------------------------------------------*/
    if(NewFlNm == NULL) {
       strcpy(TargetFl, DirNm);
    } else {
       _jmakepath(TargetFl, NULL, DirNm, NewFlNm, NULL);
    }

    if(OverWrite==OVERWRITE) 
       ul_flg_doscopy=DCPY_FAILEAS|DCPY_EXISTING; /* �L�������킹���R�s�[ */
    else 
       ul_flg_doscopy=DCPY_FAILEAS;  /* ���ꖼ������΂�߂� */

  /*--------------------------------------*/
  /* ��芸������x�R�s�[���Ă݂�         */
  /*--------------------------------------*/
    FileCopyFuncDisp(FlNm, us_flg_copydelmove);
    switch(us_flg_copydelmove) {
       case FLAG_MOVE_SAMEDRIVE:
          rca=DosMove(FlNm, TargetFl);
          break;
       case FLAG_COPY_DELETE:
          rca=DosCopy(FlNm, DirNm, ul_flg_doscopy);
          if(!rca) {
             ChangeAttributeFunc(FlNm, 0, 0, 0);
             DosDelete(FlNm);
          }
          break;
       default:
          rca=DosCopy(FlNm, DirNm, ul_flg_doscopy);
    }
    if (rca!=ERROR_ACCESS_DENIED) return rca;
           /* �����̃t�@�C�������݂��Ȃ����A�S�Ẵt�@ */
           /* �C�����㏑�����Ă���Ȃ炱���܂łŏI��   */

    /*-------------------------------*/
    /*  ERROR_ACCESS_DENIED�̏ꍇ    */
    /*  DirNm�̒��ɓ���̧�ق����邩  */
    /*-------------------------------*/
    rca=FileCopyFuncTarget_ExitsOrNot(TargetFl, &ffb3_FileInfo3);
   
    /*------------------------------------------------*/
    /* ���łȂ����DirNm(��߰��)���̂��̂�����̧�ق�  */
    /*------------------------------------------------*/
    if (rca){
       strcpy(TargetFl, DirNm);
       rca=FileCopyFuncTarget_ExitsOrNot(TargetFl, &ffb3_FileInfo3);
    }
    if (rca) return rca;  /* �����̃t�@�C�����Ȃ��ʂ̌����ŃR�s�[�ł��Ȃ� */

    switch(OverWrite){
       case NOCOPY: 
          return 0;
       case RESET:
       case ONLYTHIS:
       case ONLYTHIS_TIME:
       case ONLYTHIS_NOCP:
          FileCopyFuncOption(FlNm, TargetFl, us_flg_copydelmove);
          /* Overwrite��I�ђ��� */
    }
    
    switch(OverWrite){
       case TIMECOMP: 
       case ONLYTHIS_TIME: 
          if(0 >= FileCopyFuncTimeComp(Time, &ffb3_FileInfo3)) return 0; 
       case OVERWRITE:
       case ONLYTHIS:
          FileCopyFuncDisp(FlNm, us_flg_copydelmove);
          if(ffb3_FileInfo3.attrFile&FILE_READONLY){
             switch(us_g_flg_readonly) {
                case READONLY_IGNORE_ALL:
                   ChangeAttributeFunc(TargetFl, 0, 0, 0);
                   break;
                case READONLY_NOTIGNORE_ALL:
                   return 0;
                default:
                   if(FileCopyFuncOptionRo(FlNm, TargetFl, us_flg_copydelmove)
                       == FLAG_CANCELED_BY_USER) return 0;
                   if(us_g_flg_readonly==READONLY_NOTIGNORE_ALL
                    ||us_g_flg_readonly==READONLY_NOTIGNORE_THIS) return 0;
             }
          }
          switch(us_flg_copydelmove) {
             case FLAG_MOVE_SAMEDRIVE:
                rca=DosDelete(TargetFl);
                if (!rca) rca=DosMove(FlNm,TargetFl);
                break;
             case FLAG_COPY_DELETE:
                rca=DosCopy(FlNm, DirNm, DCPY_FAILEAS|DCPY_EXISTING);
                if (!rca) {
                   ChangeAttributeFunc(FlNm, 0, 0, 0);
                   rca=DosDelete(FlNm);
                }
                break;
             default:
                rca=DosCopy(FlNm, DirNm, DCPY_FAILEAS|DCPY_EXISTING);
          }
          break;
       case NOCOPY:
       case ONLYTHIS_NOCP:
          return 0;
    }
    return rca;
 }

/*****************************************************************/
/**   FileCopyFunc_Target_ExitsOrNot                            **/
/*****************************************************************/
 APIRET FileCopyFuncTarget_ExitsOrNot(PSZ psz_targetfile, 
                                      PFILEFINDBUF3 pffb3_FileInfo3)
 {
    /********   DosFindFirst �p   ********/
    ULONG          ul_FlFindAtr = 0x00000037;  
    LHANDLE        lh_DirHandle=HDIR_SYSTEM;   /* =0x0001 */
    ULONG          ul_FindCnt = 1;

    APIRET  apr_existornot;

    // �t�@�C�����X�g�擾���ɖ������[�v���鎖��������̑΍�
    if( CodePage[0]!=CodePage[1] ){
        // ���s�̃R�[�h�y�[�W����R�[�h�y�[�W�łȂ��ꍇ�A�ꎞ�I��
        // ��R�[�h�y�[�W��I������B
        DosSetProcessCp(CodePage[1]);
    }

    apr_existornot=DosFindFirst(psz_targetfile, &lh_DirHandle, ul_FlFindAtr, 
                                (PVOID)pffb3_FileInfo3, sizeof(FILEFINDBUF3), 
                                &ul_FindCnt, FIL_STANDARD);
    if(!apr_existornot) DosFindClose(lh_DirHandle);

    // �t�@�C�����X�g�擾���ɖ������[�v���鎖��������̑΍�
    if( CodePage[0]!=CodePage[1] ){
        // �R�[�h�y�[�W�����ɖ߂��B
        DosSetProcessCp(CodePage[0]);
    }

    return apr_existornot;
}


/****************************************************************/
/**   FileCopyFuncDisp                                         **/
/****************************************************************/
 void FileCopyFuncDisp(PSZ FlNm, USHORT us_flg_copydelmove)
 {
    if(English){
       strcpy(MsgTxt[0]," Now copying file(s). ");
       strcpy(MsgTxt[1],"                      ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C���̃R�s�[���ł�");
       strcpy(MsgTxt[1],"                      ");
    }

    strcpy(MsgTxt[1]+1,FlNm);
    if (us_flg_copydelmove==FLAG_MOVE_SAMEDRIVE) { 
       if(English){
          strcpy(MsgTxt[0]," Now moving file(s).  ");
       }
       else{
          memcpy(MsgTxt[0]+10,"�ړ����ł�  ",12);
       }
    }

    if (FirstDisp) {
       ShowMsgBox(2, bt_g_InformWindowColor);
       FirstDisp=0;
    } else {
       ShowMsgBox_Line(1, bt_g_InformWindowColor);
    }
 }

/****************************************************************/
/**   FileCopyFuncOption                                       **/
/****************************************************************/
 void FileCopyFuncOption(PSZ psz_sourcefile, PSZ psz_targetfile, 
                         USHORT us_flg_copydelmove)
 {
    UCHAR usz_sourcefullname[_MAX_PATH]={0}, usz_targetfullname[_MAX_PATH]={0};
    ULONG ul_pathlen;

    if(English){
       strcpy(MsgTxt[0],"There is the file of same name.                      ");
       strcpy(MsgTxt[1],"                                                     ");
       strcpy(MsgTxt[2],"                                                     ");
       strcpy(MsgTxt[3],"                                                     ");
       strcpy(MsgTxt[4],"Select action.                                       ");
       strcpy(MsgTxt[5],"  O. Overwrite                                       ");
       strcpy(MsgTxt[6],"  T. Overwtite if source file is newer               ");
       strcpy(MsgTxt[7],"  C. No overwrite                                    ");
       strcpy(MsgTxt[8],"                                                     ");
       strcpy(MsgTxt[9],"    N/Esc:Cancel  [Shift+]:Apply other target too    ");
    }
    else{
       strcpy(MsgTxt[0],"������̧�ق����݂��܂�.                              ");
       strcpy(MsgTxt[1],"                                                     ");
       strcpy(MsgTxt[2],"                                                     ");
       strcpy(MsgTxt[3],"                                                     ");
       strcpy(MsgTxt[4],"�������@��I�����ĉ�����.                            ");
       strcpy(MsgTxt[5],"  �n.�㏑������                                      ");
       strcpy(MsgTxt[6],"  �s.�������V������Ώ㏑������                      ");
       strcpy(MsgTxt[7],"  �b.�㏑�����Ȃ�                                    ");
       strcpy(MsgTxt[8],"                                                     ");
       strcpy(MsgTxt[9],"           �m/Esc:���    [Shift+]�ňꊇ�w��         ");
    }


    ul_pathlen=sizeof(usz_sourcefullname)-3;
    sprintf(usz_sourcefullname, "%s\\", DriveDis);
    DosQueryCurrentDir(0,usz_sourcefullname+3,&ul_pathlen);
    if(strlen(usz_sourcefullname) > 3) strcat(usz_sourcefullname, "\\"); 
    strcat(usz_sourcefullname, psz_sourcefile);

    strcpy(usz_targetfullname, psz_targetfile);

    FileCopyFuncOption_StringsAdjust(usz_sourcefullname, strlen(MsgTxt[0])-10);
    FileCopyFuncOption_StringsAdjust(usz_targetfullname, strlen(MsgTxt[0])-10);

    if(us_flg_copydelmove == FLAG_COPY_ONLY) {
       if(English){
          sprintf(MsgTxt[1], "  Source of copy: %s", usz_sourcefullname);
          sprintf(MsgTxt[2], "  Destination   : %s", usz_targetfullname);
       }
       else{
          sprintf(MsgTxt[1], "  ���-��: %s", usz_sourcefullname);
          sprintf(MsgTxt[2], "  ���-��: %s", usz_targetfullname);
       }
    } else {
       if(English){
          sprintf(MsgTxt[1], "  Source of move: %s", usz_sourcefullname);
          sprintf(MsgTxt[2], "  Destination   : %s", usz_targetfullname);
       }
       else{
          sprintf(MsgTxt[1], "  �ړ���: %s", usz_sourcefullname);
          sprintf(MsgTxt[2], "  �ړ���: %s", usz_targetfullname);
       }
    }

    ShowMsgBox(10, bt_g_WarningWindowColor);

    OverWrite=RESET;
    do {
       KbdCharIn(&KeyInfo,IO_WAIT,0);
       switch(KeyInfo.chChar){
          case 'O': 
          case 'o': 
             OverWrite=ONLYTHIS; 
             break;
          case 'T': 
          case 't': 
             OverWrite=ONLYTHIS_TIME; 
             break;
          case 'C': 
          case 'c': 
             OverWrite=ONLYTHIS_NOCP; 
             break;
          case 'N': 
          case 'n': 
          case ESC: 
             OverWrite = NOCOPY;
             KeyInfo.chChar=ESC; 
             ShowMsgBoxNull();
             return;
       }
    }while(OverWrite==RESET);

    if (KeyInfo.fsState&KBDSTF_LEFTSHIFT || KeyInfo.fsState&KBDSTF_RIGHTSHIFT){
       switch(OverWrite) {
          case ONLYTHIS:
              OverWrite = OVERWRITE;
              break;
          case ONLYTHIS_TIME:
              OverWrite = TIMECOMP;
              break;
          case ONLYTHIS_NOCP:
              OverWrite = NOCOPY;
              break;
       }
    }

    ShowMsgBoxNull();
    FirstDisp=1;
    FileCopyFuncDisp(" ", us_flg_copydelmove);
 }

/****************************************************************/
/**   FileCopyFuncOption_StringsAdjust                         **/
/****************************************************************/
 void FileCopyFuncOption_StringsAdjust(PSZ psz_fullfilename, ULONG ul_maxlen)
 {
     PUCHAR puc_yen_tail=NULL, puc_yen_head=NULL;
     UCHAR usz_fnamebuff[_MAX_PATH]={0};
     

     if(strlen(psz_fullfilename) <= ul_maxlen) return;

     strcpy(usz_fnamebuff, psz_fullfilename);

     puc_yen_tail = jstrrchr(usz_fnamebuff, '\\');     
     if(puc_yen_tail == usz_fnamebuff +3 ) return;  // \ �͂P���� => f:\hogehoge.hoge in root 

     for(;;) {
        *puc_yen_tail = '\0';
        puc_yen_head = jstrrchr(usz_fnamebuff, '\\');
        *puc_yen_tail = '\\';
        if (puc_yen_head == NULL || strlen(puc_yen_head) > ul_maxlen - 6 ) {
            sprintf(psz_fullfilename+3, "...%s", puc_yen_tail);
            return ;
        }
        puc_yen_tail = puc_yen_head; 
     }
 } 


/*****************************************************************/
/**   FileCopyFuncOptionRo                                      **/
/*****************************************************************/
 USHORT FileCopyFuncOptionRo(PSZ FlNm, PSZ Target, USHORT us_flg_copydelmove)
 {

    PUCHAR puc_yenptr;

    if(English){
       strcpy(MsgTxt[0],"The file of destination has read-only attribute. ");
       strcpy(MsgTxt[1],"                                                 ");
       strcpy(MsgTxt[2],"                                                 ");
       strcpy(MsgTxt[3],"Select action.                                   ");
       strcpy(MsgTxt[4]," Y(Enter). Overwrite                             ");
       strcpy(MsgTxt[5]," C.        No overwrite                          ");
       strcpy(MsgTxt[6],"                                                 ");
       strcpy(MsgTxt[7],"   N/Esc:Cancel  [Shift+]:Apply other target too ");
    } else {
       strcpy(MsgTxt[0],"���Đ悪ذ�ޥ��ذ��̧�قł�       ");
       strcpy(MsgTxt[1],"                                  ");
       strcpy(MsgTxt[2],"                                  ");
       strcpy(MsgTxt[3],"�������@��I�����ĉ�����.         ");
       strcpy(MsgTxt[4]," �x(Enter). �㏑������            ");
       strcpy(MsgTxt[5]," �b.        �㏑�����Ȃ�          ");
       strcpy(MsgTxt[6],"                                  ");
       strcpy(MsgTxt[7]," �m/Esc:���   [Shift+]�ňꊇ�w�� ");
    }

    puc_yenptr=jstrrchr(Target, '\\');
    if(!puc_yenptr) {
       puc_yenptr=Target;
    } else {
       puc_yenptr++;
    }
    if(us_flg_copydelmove == FLAG_COPY_ONLY) {
       sprintf(MsgTxt[1],
                English ? "Destination of copy: %s" :
                          "���-��: %s", puc_yenptr);
       sprintf(MsgTxt[1], "���-��: %s", puc_yenptr);
    } else {
       sprintf(MsgTxt[1],
                English ? "Destination of move: %s" :
                          "�ړ���: %s", puc_yenptr);
       sprintf(MsgTxt[1], "�ړ���: %s", puc_yenptr);
    }
    ShowMsgBox(8, bt_g_WarningWindowColor);

    us_g_flg_readonly=READONLY_RESET;
    do {
       KbdCharIn(&KeyInfo,IO_WAIT,0);
       switch(KeyInfo.chChar){
          case 'Y': 
          case 'y': 
          case ENTER:
             us_g_flg_readonly=READONLY_IGNORE_THIS; 
             ChangeAttributeFunc(Target, 0, 0, 0);  /* �S�Ă̑������N���A */
             break;
          case 'C': 
          case 'c': 
             us_g_flg_readonly=READONLY_NOTIGNORE_THIS; 
             break;
          case 'N': 
          case 'n': 
          case ESC: 
             KeyInfo.chChar=ESC; 
             ShowMsgBoxNull();
             return FLAG_CANCELED_BY_USER;
       }
    }while(us_g_flg_readonly==READONLY_RESET);

    if (KeyInfo.fsState&KBDSTF_LEFTSHIFT || KeyInfo.fsState&KBDSTF_RIGHTSHIFT){
       switch(us_g_flg_readonly) {
          case READONLY_IGNORE_THIS:
             us_g_flg_readonly=READONLY_IGNORE_ALL; 
             break;
          case READONLY_NOTIGNORE_THIS:
             us_g_flg_readonly=READONLY_NOTIGNORE_ALL; 
             break;
       }
    }

    ShowMsgBoxNull();
    FirstDisp=1;
    FileCopyFuncDisp(FlNm, us_flg_copydelmove); 
    return NO_ERROR;
  
 }

/*****************************************************************/
/**   FileCopyFuncTimeComp                                      **/
/*****************************************************************/
 INT FileCopyFuncTimeComp(PSZ Time, const PFILEFINDBUF3 pffb3_FileInfo3)
 {
    UCHAR Time1[124]={0}, Time2[124]; 

    memcpy(Time1, Time, (DISP_MK-DISP_DT)); 
      /*Time1 �̍Ō�ɂ͏������̎��� \0 �����̂܂ܕt�� */

    sprintf(Time2,"%04.4d-%02.2d-%02.2d %02.2d:%02.2d\0",
                  (pffb3_FileInfo3->fdateLastWrite.year+1980),
                  pffb3_FileInfo3->fdateLastWrite.month,
                  pffb3_FileInfo3->fdateLastWrite.day,
                  pffb3_FileInfo3->ftimeLastWrite.hours,
                  pffb3_FileInfo3->ftimeLastWrite.minutes);

    return strcmp(Time1,Time2);
 }
 
/*****************************************************************/
/**   FileCopyRc                                                **/
/*****************************************************************/
 void FileCopyRc(APIRET apr_FileCopy)
 {
    switch(apr_FileCopy){
       case NO_ERROR: 
          ShowFileList_PrevFile(FLAG_DRAW_FILELIST, FlDis[SelFl].Nm+DISP_FN);
          if (KeyInfo.chChar==ESC) {
             ShowMsgCopyStop();
          } else {
             ShowMsgCopyOk(); 
          }
          break;
       case ERROR_INVALID_NAME: 
       case ERROR_FILENAME_EXCED_RANGE:
          ShowMsgNameNg(); 
          break;
       case ERROR_SHARING_VIOLATION: 
          ShowMsgDeleteErr(); 
          break;
       case ERROR_PATH_NOT_FOUND: 
          ShowMsgPassNg(InpLine); 
          break;
       default: 
          ErrorMsgDisp(apr_FileCopy, InpLine);
          break;
    }
 }

/****************************************************************/
/**   FileDelete                                               **/
/****************************************************************/
 void FileDelete(void)
 {
    APIRET apr_Delete;
    UCHAR  usz_fnamesave[_MAX_PATH];

    /************ ���̈ꕶ�͐�΂ɏ����Ă͑ʖ� *****************/
    if(!FlCnt) return;
    if(!strcmp(FlDis[SelFl].Nm+DISP_FN, ".")
             ||!strcmp(FlDis[SelFl].Nm+DISP_FN, "..")) return;
    /***********************************************************/

    if(English){
       strcpy(MsgTxt[0],"Delete a file.             ");
       strcpy(MsgTxt[1]," File:                     ");
       strcpy(MsgTxt[2],"                           ");
       strcpy(MsgTxt[3],"  Y:yes(Space)  N:no(Esc)  ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C�����폜���܂�       ");
       strcpy(MsgTxt[1]," File:                     ");
       strcpy(MsgTxt[2],"                           ");
       strcpy(MsgTxt[3]," �x:yes(Space)  �m:no(Esc) ");
    }
    
    strcpy(MsgTxt[1]+6,FlDis[SelFl].Nm+DISP_FN);

    if(GetYesorNo_withMsgBox(' ', 4, bt_g_NormalWindowColor,
              FLAG_GETYESORNO_MSGBOXCLEAR)==ESC)  return;

    strcpy(usz_fnamesave, FlDis[SelFl].Nm+DISP_FN);  
                        /* �t�@�C�����̑ޔ� [QFile()�΍�] */

    FileDeleteFuncDisp(FLAG_FIRST, "");
    apr_Delete = FileDeleteFunc(usz_fnamesave, FlDis[SelFl].Atr);

    QDriveSize();
    ReDrawAfterDelete();
    FileDeleteRc(apr_Delete);
 }

/****************************************************************/
/**   FileDeleteFunc                                           **/
/****************************************************************/
 APIRET FileDeleteFunc(PSZ FlNm, BYTE FlAtr)
 {
    APIRET apr_Delete;

    if (FlAtr&FILE_SYSTEM||FlAtr&FILE_HIDDEN||FlAtr&FILE_READONLY){
       if(English){
          strcpy(MsgTxt[0],"Target file has system/hidden/read-only attribute.");
          strcpy(MsgTxt[1],"Delete it?                                        ");
          strcpy(MsgTxt[2]," File:                                            ");
          strcpy(MsgTxt[3],"                                                  ");
          strcpy(MsgTxt[4],"             Y:yes(Space)  N:no(Esc)              ");
       }
       else{
          strcpy(MsgTxt[0],"����/�B��/ذ�ޥ��ذ��̧�قł�");
          strcpy(MsgTxt[1],"�폜���܂���                 ");
          strcpy(MsgTxt[2]," File:                       ");
          strcpy(MsgTxt[3],"                             ");
          strcpy(MsgTxt[4],"  �x:yes(Space)  �m:no(Esc)  ");
       }
       
       strcpy(MsgTxt[2]+6, FlNm);
       
       if(GetYesorNo_withMsgBox(' ', 5, bt_g_WarningWindowColor,
            FLAG_GETYESORNO_MSGBOXNULL)==ESC) return NO_ERROR;

       FileDeleteFuncDisp(FLAG_FIRST, "");
       ChangeAttributeFunc(FlNm, 0, 0, 0);  /* ���ׂĂ̑������N���A */
    }

    if (!(FlAtr&FILE_DIRECTORY)) {
       FileDeleteFuncDisp(FLAG_NOT_FIRST, FlNm);
       apr_Delete = DosDelete(FlNm);
       if (apr_Delete) strcpy(InpLine, FlNm);  /* �G���[�\����InpLine���g���Ă��� */
    } else{
       if(English){
          strcpy(MsgTxt[0],"The target is directory.   ");
          strcpy(MsgTxt[1],"Delete it?                 ");
          strcpy(MsgTxt[2]," Dir:                      ");
          strcpy(MsgTxt[3],"                           ");
          strcpy(MsgTxt[4],"  Y:yes(Space)  N:no(Esc)  ");
       }
       else{
          strcpy(MsgTxt[0],"�f�B���N�g���[�ł�         ");
          strcpy(MsgTxt[1],"�폜���܂���               ");
          strcpy(MsgTxt[2]," Dir:                      ");
          strcpy(MsgTxt[3],"                           ");
          strcpy(MsgTxt[4]," �x:yes(Space)  �m:no(Esc) ");
       }

       strcpy(MsgTxt[2]+5,FlNm);

       if(GetYesorNo_withMsgBox(' ', 5, bt_g_WarningWindowColor,
            FLAG_GETYESORNO_MSGBOXNULL)==ESC) return NO_ERROR;

       FileDeleteFuncDisp(FLAG_FIRST, "");
       apr_Delete=DeleteDirContents(FlNm);
       if (!apr_Delete) {
          FileDeleteFuncDisp(FLAG_NOT_FIRST, FlNm);
          apr_Delete=DosDeleteDir(FlNm);
       }
    }
    return apr_Delete;
 }

/****************************************************************/
/**   FileDeleteFuncDisp                                       **/
/****************************************************************/
 void FileDeleteFuncDisp(USHORT us_flg_firstdisp, PSZ FlNm)
 {
    if(English){
       strcpy(MsgTxt[0],"Now deleting file(s).");
       strcpy(MsgTxt[1],"                     ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C���̍폜���ł�");
       strcpy(MsgTxt[1],"                    ");
    }

    if (us_flg_firstdisp == FLAG_FIRST) {
       ShowMsgBox(2, bt_g_InformWindowColor);
    } else {
       strcpy(MsgTxt[1]+1,FlNm);
       ShowMsgBox_Line(1, bt_g_InformWindowColor);
    }
 }

/****************************************************************/
/**   FileDeleteRc                                             **/
/****************************************************************/
 void FileDeleteRc(APIRET apr_FileDelete)
 {
    if (KeyInfo.chChar==ESC) {
       ShowMsgDeleteStop(); 
       return;
    } 
    
    switch(apr_FileDelete){
       case NO_ERROR: 
          return;
       case ERROR_SHARING_VIOLATION: 
       case ERROR_CURRENT_DIRECTORY: 
          ShowMsgDeleteErr(); 
          break;
       case ERROR_ACCESS_DENIED: 
          ShowMsgDeleteDeny(); 
          break;
       default: 
          ErrorMsgDisp(apr_FileDelete, InpLine);
    }
 }

/****************************************************************/
/**   FileEdit                                                 **/
/****************************************************************/
 void FileEdit(PSZ psz_EditFile, ULONG ul_MarkFileNum,
               USHORT us_flg_silent, ULONG ul_startline)
 {
    UCHAR  usz_ObjInputs[CMDSTR_MAX];
    BOOL   bl_success = TRUE;
 
    memset(InpLine, 0, sizeof(InpLine));
    if(ul_MarkFileNum == 0) {
       ExecAssocProgramParm_NamewithSpace(psz_EditFile, InpLine, FALSE);
    } else {
       bl_success = ExecAssocProgramParm_NameSet(InpLine, 
                       strlen(EditorCfg.EditorProg.uszProgName)
                       +strlen(EditorCfg.EditorProg.uszParamList)+5, FALSE);
                        // +5 �͍s�ԍ���(5+2=7)��������Ώ\�����낤�Ƃ̔��f                       

       if(bl_success == FALSE) {
           ShowMsgTooLongStr();
           return ;
       }
    }

    if(us_flg_silent==FLAG_NOISY_START) {
       if(English){
          strcpy(MsgTxt[0],"Edit file(s).                              ");
          strcpy(MsgTxt[1],"  Text editor:                             ");
          strcpy(MsgTxt[2],"  - Create another session                 ");
          strcpy(MsgTxt[3],"                                           ");
          strcpy(MsgTxt[4],"Enter target file name.                    ");
          strcpy(MsgTxt[5],"                                           ");
          strcpy(MsgTxt[6],"                                           ");
          strcpy(MsgTxt[7],"       Enter:Execute     Esc:Cancel        ");
       }
       else{
          strcpy(MsgTxt[0],"�t�@�C���̕ҏW�����܂�                     ");
          strcpy(MsgTxt[1],"  �O����ި���:                             ");
          strcpy(MsgTxt[2],"  ���ʾ���݂𐶐�����                      ");
          strcpy(MsgTxt[3],"                                           ");
          strcpy(MsgTxt[4],"�ҏW����t�@�C�������w�肵�ĉ�����         ");
          strcpy(MsgTxt[5],"                                           ");
          strcpy(MsgTxt[6],"                                           ");
          strcpy(MsgTxt[7],"       Enter:���s        Esc:���          ");
       }

       strcpy(MsgTxt[1]+15, EditorCfg.EditorProg.uszProgName);
       Change_FlagMark(EditorCfg.EditorProg.usSession, 2, 2);

       if(KbdLineIn(8, bt_g_NormalWindowColor, 5, InpLine,
             FLAG_INPUTWIN_NO_OPTION|FLAG_INPUTWIN_MSGBOXCLEAR)==ESC) return;
    }

    if(ul_startline && strlen(EditorCfg.EditorProg.uszParamList)) {
       FileEdit_SetLineOption(usz_ObjInputs, EditorCfg.EditorProg.uszParamList,
                              ul_startline, InpLine);
    } else {
       strcpy(usz_ObjInputs, InpLine);
    }
    ExecAssocProgramFunc(FLAG_NO_MARK, EditorCfg.EditorProg.usSession, 
                         AutoClose, EditorCfg.EditorProg.uszProgName, 
                         English ? "Edit file(Another session)" : "�t�@�C���̕ҏW�i�ʃv���Z�X�j", 
                         usz_ObjInputs);
    if (EditorCfg.EditorProg.usSession) {
       if(ul_MarkFileNum) QFile();  /* �}�[�N������ */
       ShowFileList();
    } 

 }

/****************************************************************/
/**   FileEdit_SetLineOption                                   **/
/****************************************************************/
 void FileEdit_SetLineOption(PSZ psz_ObjInputs, PSZ psz_EditorLineOption, 
                             ULONG ul_startline, PSZ psz_editfile)
 {
    PUCHAR puc_Sharp_ptr, puc_AndC_ptr;
    UCHAR  usz_lineoption[128];

    puc_Sharp_ptr=strstr(psz_EditorLineOption, "##");

    if(puc_Sharp_ptr) {
       *(puc_Sharp_ptr) = '\0';
       sprintf(usz_lineoption, "%s%lu%s", psz_EditorLineOption, 
                  ul_startline, puc_Sharp_ptr+2);
       *(puc_Sharp_ptr) = '#';
    } else {
       sprintf(usz_lineoption, "%s%lu", psz_EditorLineOption, ul_startline);
    }

    puc_AndC_ptr=strstr(usz_lineoption, "&C");
    if(!puc_AndC_ptr) puc_AndC_ptr=strstr(usz_lineoption, "&c");

    if(puc_AndC_ptr) {
       *(puc_AndC_ptr) = '\0';
       sprintf(psz_ObjInputs, "%s%s%s", usz_lineoption, psz_editfile, 
                                        puc_AndC_ptr+2);
    } else {
       sprintf(psz_ObjInputs, "%s %s", usz_lineoption, psz_editfile);
    }

 }

/****************************************************************/
/**   FileFind                                                 **/
/****************************************************************/
 void FileFind(void)
 {
    ULONG ul_flg_filefound;
    CHAR c_FindStartDir[4]={0}, c_fname_found[_MAX_PATH], 
         c_CurrentDir[_MAX_PATH];

    if(English){
       strcpy(MsgTxt[0],"Find file.                         ");
       strcpy(MsgTxt[1],"                                   ");
       strcpy(MsgTxt[2],"Enter target file name.            ");
       strcpy(MsgTxt[3],"                                   ");
       strcpy(MsgTxt[4],"                                   ");
       strcpy(MsgTxt[5],"      Enter:OK     Esc:Cancel      ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C�����������܂�             ");
       strcpy(MsgTxt[1],"                                 ");
       strcpy(MsgTxt[2],"�����t�@�C�������w�肵�ĉ�����   ");
       strcpy(MsgTxt[3],"                                 ");
       strcpy(MsgTxt[4],"                                 ");
       strcpy(MsgTxt[5],"     Enter:���s   Esc:���       ");
    }

    if(KbdLineIn(6, bt_g_NormalWindowColor, 3, NULL, 
                 FLAG_INPUTWIN_NO_OPTION)==ESC){
       ShowFileList();
       return;
    }
    
    if(English){
       strcpy(MsgTxt[2],"Appoint range of the find process. ");
       strcpy(MsgTxt[3],"                                   ");
       strcpy(MsgTxt[4],"  \\(Enter): Under root directory   ");
       strcpy(MsgTxt[5],"  .(Space): Under current directory");
    }
    else{
       strcpy(MsgTxt[2],"�����͈͂��w�肵�ĉ�����         ");
       strcpy(MsgTxt[3],"                                 ");
       strcpy(MsgTxt[4],"  \\(Enter): ���h���C�u�S��       ");
       strcpy(MsgTxt[5],"  .(Space): ���f�B���N�g���ȉ�   ");
    }

    ShowMsgBox(6, bt_g_NormalWindowColor);
    do {
       KbdCharIn(&KeyInfo,IO_WAIT,0); 
       switch(KeyInfo.chChar){
          case '\\':
          case ENTER: 
             strcpy(c_FindStartDir, "\\");
             break;
          case '.': 
          case ' ': 
             strcpy(c_FindStartDir, ".");
             break;
          case ESC: 
             ShowFileList();
             return;
       }
    }while(c_FindStartDir[0] == '\0');
       
    ShowFileList();
    SetFullCurrentPathName(c_CurrentDir); 

    FileFindDisp(FLAG_FIRST, "");
    ul_flg_filefound = FileFindDir(c_FindStartDir, c_fname_found);  
       
    /* ������Ȃ��������͂��Ƃ�Dir�֖߂� */
    if (ul_flg_filefound != FLAG_FILE_FOUND) DosSetCurrentDir(c_CurrentDir); 
    QDir(); 
    QFile(); 

    /* �����������͂���File�ɃJ�[�\�������킹�� */
    if (ul_flg_filefound == FLAG_FILE_FOUND) PrevFileDirSearch(c_fname_found); 
    ShowFileList(); 

    switch(ul_flg_filefound) {
       case FLAG_CANCELED_BY_USER:
          ShowMsgFindStop(); 
          break;
       case FLAG_FILE_NOT_FOUND:
          ShowMsgNotFound();
          break;
    }
 }

/**************************************************************/
/**   FileFindDir                                            **/
/**************************************************************/
 ULONG FileFindDir(PSZ DirNm, PSZ psz_fname_found)
 {
    ULONG ul_flg_filefound = FLAG_FILE_NOT_FOUND, ul_PathLen, ul_count;
    UCHAR FulDirNm[_MAX_PATH];
    
    DosSetCurrentDir(DirNm);
    ul_PathLen=(ULONG)(sizeof(PathDis)-1);
    DosQueryCurrentDir(0,PathDis+1,&ul_PathLen);

    SetFullDirName(FulDirNm);
    FileFindDisp(FLAG_NOT_FIRST, FulDirNm);

    QFile_LoadFileList(FLAG_LOADFILELIST_NOTDIR, InpLine);
    if(FlCnt) {
       for (ul_count=0; ul_count<FlCnt; ul_count++) {
          ul_flg_filefound = FileFindMatch(FlDis[ul_count].Nm+DISP_FN, FulDirNm);
          switch(ul_flg_filefound) {
             case FLAG_FILE_FOUND: 
                strcpy(psz_fname_found, FlDis[ul_count].Nm+DISP_FN);
             case FLAG_CANCELED_BY_USER:
                return ul_flg_filefound;
          }
       }
       ShowMsgBoxNull();
       FileFindDisp(FLAG_FIRST, FulDirNm);
    }

    KbdCharIn(&KeyInfo, IO_NOWAIT, 0);
    if(KeyInfo.chChar == ESC) return FLAG_CANCELED_BY_USER;

    QFile_LoadFileList(FLAG_LOADFILELIST_DIRONLY, "*.*");
    for (ul_count=0; ul_count<FlCnt; ul_count++){
       if(strcmp(FlDis[ul_count].Nm+DISP_FN, ".")
              && strcmp(FlDis[ul_count].Nm+DISP_FN, "..")) {
          ul_flg_filefound = FileFindDir(FlDis[ul_count].Nm+DISP_FN, psz_fname_found);
          if (ul_flg_filefound != FLAG_FILE_NOT_FOUND) return ul_flg_filefound;
          QFile_LoadFileList(FLAG_LOADFILELIST_DIRONLY, "*.*");
       }
    }

    DosSetCurrentDir("..");
    return FLAG_FILE_NOT_FOUND; 
 }

/****************************************************************/
/**   FileFindMatch                                            **/
/****************************************************************/
ULONG FileFindMatch(PSZ psz_filename, PSZ psz_fulldirname)
 {
    if(English){
       strcpy(MsgTxt[0],"Target file was found.                      ");
       strcpy(MsgTxt[1],"                                            ");
       strcpy(MsgTxt[2],"                                            ");
       strcpy(MsgTxt[3],"Y(Enter) : Jump to there                    ");
       strcpy(MsgTxt[4],"N(Space) : Search next target               ");
       strcpy(MsgTxt[5],"C(Esc)   : Cancel                           ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C����������܂���                    ");
       strcpy(MsgTxt[1],"                                            ");
       strcpy(MsgTxt[2],"                                            ");
       strcpy(MsgTxt[3],"�x(Enter) �F���̃f�B���N�g���[�Ɉړ�����    ");
       strcpy(MsgTxt[4],"�m(Space) �F����T��                        ");
       strcpy(MsgTxt[5],"�b(Esc)   �F�����𒆎~����                  ");
    }

    sprintf(MsgTxt[1], " %s%s", psz_fulldirname, psz_filename);

    ShowMsgBox(6, bt_g_NormalWindowColor);
    for(;;) {
       KbdCharIn(&KeyInfo,IO_WAIT,0); 
       switch(KeyInfo.chChar){
          case ENTER: 
          case 'y':
          case 'Y': 
             return FLAG_FILE_FOUND;
          case 'N': 
          case 'n': 
          case ' ':
             return FLAG_FILE_NOT_FOUND;
          case 'C': 
          case 'c': 
          case ESC:   
             return FLAG_CANCELED_BY_USER;
       }
    }
 }

/****************************************************************/
/**   FileFindDisp                                             **/
/****************************************************************/
 void FileFindDisp(USHORT us_flg_firstdisp, PSZ Current_DirNm)
 {
    strcpy(MsgTxt[0],
           English ? "Now searching file:                         " :
                     "�t�@�C���̌������ł��F                      ");
    strcpy(MsgTxt[1],"                                            ");
    
    if (us_flg_firstdisp==FLAG_FIRST) {
       strcpy(English ? MsgTxt[0]+20 : MsgTxt[0]+22, InpLine);
       ShowMsgBox(2, bt_g_InformWindowColor);
    } else {
       strcpy(MsgTxt[1]+1,Current_DirNm);
       ShowMsgBox_Line(1, bt_g_InformWindowColor);
    }
 }

/****************************************************************/
/**   FileMark                                                 **/
/****************************************************************/
 void FileMark(void)
 {
#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
    ULONG ul_filesize;
#else
    unsigned long long ull_filesize;
#endif

    /************ ���̈ꕶ�͐�΂ɏ����Ă͑ʖ� *****************/
    if(!FlCnt) return;
    if(!strcmp(FlDis[SelFl].Nm+DISP_FN, ".")
             ||!strcmp(FlDis[SelFl].Nm+DISP_FN, "..")) return;
    /***********************************************************/

    if (!(FlDis[SelFl].Atr&FILE_DIRECTORY)) {
#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
       ul_filesize=FlDis[SelFl].cbFile; 
    } else {
       ul_filesize=0;
#else
       ull_filesize=FlDis[SelFl].cbFile; 
    } else {
       ull_filesize=0;
#endif
    }
    if (FlDis[SelFl].Mark==0) {
       memcpy(FlDis[SelFl].Nm+DISP_MK,English ? "* " : "��",2);
       ++MarkCnt; 

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
       MarkSize += ul_filesize; 
#else
       MarkSize += ull_filesize; 
#endif
       FlDis[SelFl].Mark=1;

    } else {
       memcpy(FlDis[SelFl].Nm+DISP_MK,"  ",2);
       --MarkCnt; 

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
       MarkSize -= ul_filesize; 
#else
       MarkSize -= ull_filesize; 
#endif
       FlDis[SelFl].Mark=0;
    }

    FileMarkInfoDisp_Set(MarkCnt, MarkSize);
    ShowMarkFileNumberSize();
 }

/****************************************************************/
/**   FileMarkAll                                              **/
/****************************************************************/
 void FileMarkAll(void)
 {
#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
    ULONG  ul_count, ul_filesize;
#else
    ULONG  ul_count;
    unsigned long long ull_filesize;
#endif
  
    if (MarkCnt){
       MarkCnt=0; 
       MarkSize=0;
       for(ul_count=0; ul_count<FlCnt; ul_count++) {
          memcpy(FlDis[ul_count].Nm+DISP_MK,"  ",2);
          FlDis[ul_count].Mark=0;
       }
    } else {
       MarkCnt=0; 
       MarkSize=0;
       for(ul_count=0; ul_count<FlCnt; ul_count++){
          if ((strcmp(FlDis[ul_count].Nm+DISP_FN,"."))
                      &&(strcmp(FlDis[ul_count].Nm+DISP_FN,".."))){
             memcpy(FlDis[ul_count].Nm+DISP_MK, English ? "* " : "��",2);
             if (!(FlDis[ul_count].Atr&FILE_DIRECTORY)) {
#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
                ul_filesize=FlDis[ul_count].cbFile;
             } else {
                ul_filesize=0;
#else
                ull_filesize=FlDis[ul_count].cbFile; 
             } else {
                ull_filesize=0;
#endif
             }
             ++MarkCnt; 

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
             MarkSize+=ul_filesize; 
#else
             MarkSize+=ull_filesize; 
#endif
             FlDis[ul_count].Mark=1;
          }
       }
    }   
    
    FileMarkInfoDisp_Set(MarkCnt, MarkSize);
    ShowFileList();
 }

/****************************************************************/
/**   FileMarkRefresh                                          **/
/****************************************************************/
 void FileMarkRefresh(void)
 {
    ULONG  ul_count;

    for(ul_count=0; ul_count<FlCnt; ul_count++) {
       memcpy(FlDis[ul_count].Nm+DISP_MK
        ,(FlDis[ul_count].Mark==0) ? "  " : English ? "* " : "��" ,2);
    }
    
    FileMarkInfoDisp_Set(MarkCnt, MarkSize);
 }


/****************************************************************/
/**   FileMarkInfoDisp_Set                                     **/
/****************************************************************/
#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
 void FileMarkInfoDisp_Set(ULONG ul_MarkCnt, ULONG ul_MarkSize)
#else
 void FileMarkInfoDisp_Set(ULONG ul_MarkCnt, unsigned long long ull_MarkSize)
#endif
 {
    memset(MarkCntDis+2, 0, sizeof(MarkCntDis)-2);
    if (ul_MarkCnt) {

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
       sprintf(MarkCntDis,
                English ? "* %u(%uK)" :
                          "��%u(%uK)",ul_MarkCnt, ul_MarkSize/1024ul);
#else
       sprintf(MarkCntDis,
                English ? "* %u(%lluK)" :
                          "��%u(%lluK)",ul_MarkCnt, ull_MarkSize/1024ull);
#endif

    } else { 

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
       sprintf(MarkCntDis,
                English ? "- %u(%uK)" :
                          "��%u(%uK)",ul_MarkCnt, ul_MarkSize/1024ul);
#else
       sprintf(MarkCntDis,
                English ? "- %u(%lluK)" :
                          "��%u(%lluK)",ul_MarkCnt, ull_MarkSize/1024ull);
#endif

    }
 }

/****************************************************************/
/**   FileMaskDisp                                             **/
/****************************************************************/
 void FileMaskDisp(void)
 {
    if(English){
       strcpy(MsgTxt[0],"Set the mask(wild card) for file list.      ");
       strcpy(MsgTxt[1],"                                            ");
       strcpy(MsgTxt[2],"                                            ");
       strcpy(MsgTxt[3],"                                            ");
       strcpy(MsgTxt[4],"          Enter:OK      Esc:Cancel          ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C���E�}�X�N(ܲ��ޥ����)������ύX���܂�");
       strcpy(MsgTxt[1],"                                            ");
       strcpy(MsgTxt[2],"                                            ");
       strcpy(MsgTxt[3],"                                            ");
       strcpy(MsgTxt[4],"       Enter:���s      Esc:���             ");
    }

    if(KbdLineIn(5, bt_g_NormalWindowColor, 2, FlMask, 
                 FLAG_INPUTWIN_NO_OPTION)==ESC){
       ShowFileList();
    } else {
       memset(FlMask, 0, sizeof(FlMask));
       strcpy(FlMask,InpLine);
       QFile(); 
       ShowFileList_FilePosition(0);
       ShowFileMask();
    }
 }

/****************************************************************/
/**   FileMove                                                 **/
/****************************************************************/
 void FileMove(void)
 {
    UCHAR uc_inputchar, usz_fnamesave[_MAX_PATH]={0}, usz_tstampsave[16]={0};  
    USHORT us_flg_copydelmove, us_flg_samedrive, us_flg_inthedir =0;
    APIRET apr_filemove;
    PUCHAR puc_inputwinstr=NULL;

    /**************���̈ꕶ�͐�΂ɏ����Ă͑ʖ�*******************/
    if(!FlCnt) return;
    if(!strcmp(FlDis[SelFl].Nm+DISP_FN, ".")
             ||!strcmp(FlDis[SelFl].Nm+DISP_FN, "..")) return;
    /*************************************************************/

    do {
       if(FlDis[SelFl].Atr&FILE_DIRECTORY) {                                     
           if(English){
              strcpy(MsgTxt[0],"Move a directory.                                 ");
              strcpy(MsgTxt[1]," File:                                            ");
              strcpy(MsgTxt[2]," - [F1] Move contents of a directory              ");
           }
           else{
              strcpy(MsgTxt[0],"�f�B���N�g�����ړ����܂�                          ");
              strcpy(MsgTxt[1]," File:                                            ");
              strcpy(MsgTxt[2]," ��[F1] �f�B���N�g���̒��g���R�s�[����            ");
           }
           Change_FlagMark(us_flg_inthedir, 2, 1);                               
       } else {                                                                  
           strcpy(MsgTxt[0],
                  English ? "Move a file.                                      " :
                            "�t�@�C�����ړ����܂�                              ");
           strcpy(MsgTxt[1]," Dir:                                             ");
           strcpy(MsgTxt[2],"                                                  ");
       }                                                                         

       strcpy(MsgTxt[3],"                                                  ");
       if(English){
          strcpy(MsgTxt[4],"Enter destination directory(Up arrow key:history).");
          strcpy(MsgTxt[5],"                                                  ");
          strcpy(MsgTxt[6],"                                                  ");
          strcpy(MsgTxt[7],"             Enter:OK      Esc:Cancel             ");
       }
       else{
          strcpy(MsgTxt[4],"�ړ�����w�肵�ĉ�����              (������˽�ذ) ");
          strcpy(MsgTxt[5],"                                                  ");
          strcpy(MsgTxt[6],"                                                  ");
          strcpy(MsgTxt[7],"            Enter:���s       Esc:���             ");
       }
    
       strcpy(MsgTxt[1]+6, FlDis[SelFl].Nm+DISP_FN);

       uc_inputchar=KbdLineIn(8, bt_g_NormalWindowColor, 5, puc_inputwinstr,
                       FLAG_INPUTWIN_HISTRY_ON|FLAG_INPUTWIN_MSGBOXCLEAR
                       |FLAG_INPUTWIN_TABKEY_ON|FLAG_INPUTWIN_FUNCKEY_ON);  
       switch(uc_inputchar) {
          case ESC:
             return;
          case ENTER:
             break;
         case PF1:       
            if(FlDis[SelFl].Atr&FILE_DIRECTORY) { 
                us_flg_inthedir = !us_flg_inthedir;
                puc_inputwinstr=InpLine;          
            }                         
            break;                                
          default:
             puc_inputwinstr=HistryBox(FLAG_HISTRY_PATH);
       }
    }while(uc_inputchar!=ENTER);

    apr_filemove=FileCopy_ConverttoAbsolutePath(InpLine);
    if(apr_filemove) {    
       FileCopyRc(apr_filemove);
       return;
    }

    if(SameDriveCheck(&us_flg_samedrive)) return; /* ���͕������s���̎� */
    if(us_flg_samedrive){
       us_flg_copydelmove=FLAG_MOVE_SAMEDRIVE;
    } else {
       us_flg_copydelmove=FLAG_COPY_DELETE;
    }
    if(SameDirCheck(FlDis[SelFl].Nm+DISP_FN)) return;

    OverWrite=RESET; 
    us_g_flg_readonly=READONLY_RESET;
    FirstDisp=1;


    strcpy(usz_fnamesave, FlDis[SelFl].Nm+DISP_FN);  
    memcpy(usz_tstampsave, FlDis[SelFl].Nm+DISP_DT, (DISP_MK-DISP_DT)); 
                        /* �t�@�C�����̑ޔ� [QFile()�΍�] */

    if (FlDis[SelFl].Atr&FILE_DIRECTORY) {
       apr_filemove=FileCopyDir(usz_fnamesave, us_flg_copydelmove, us_flg_inthedir);
       if(!apr_filemove) DosDeleteDir(usz_fnamesave);
    } else {
       apr_filemove = FileCopyFl(usz_fnamesave, usz_tstampsave, 
                                 us_flg_copydelmove, 1);
    }
    ReDrawAfterDelete();
    QDriveSize();
    if (KeyInfo.chChar==ESC)  
       ShowMsgMoveStop();
    else                       
       FileCopyRc(apr_filemove);
    
    JumpHistInsert(FLAG_HISTRY_PATH, InpLine);
 }

/****************************************************************/
/**   FileName                                                 **/
/****************************************************************/
 void FileName(ULONG ul_markcnt)
 {
    ULONG   ul_count;
    PUCHAR  puc_defaultstr;
    UCHAR uszNewName[_MAX_PATH]={0};

    if(!FlCnt) return;
    if(!ul_markcnt) {
       if(!strcmp(FlDis[SelFl].Nm+DISP_FN, ".") || 
          !strcmp(FlDis[SelFl].Nm+DISP_FN, ".."))  return;
       puc_defaultstr=FlDis[SelFl].Nm+DISP_FN;
    } else {
       puc_defaultstr=NULL;
    }
    
    if(English){
       strcpy(MsgTxt[0],ul_markcnt ?
                        "Rename marked files(or directories). " :
                        "Rename a file(or directory).         ");
       strcpy(MsgTxt[1],"                                     ");
       strcpy(MsgTxt[2],"Enter new name.                      ");
       strcpy(MsgTxt[3],"                                     ");
       strcpy(MsgTxt[4],"                                     ");
       strcpy(MsgTxt[5],"       Enter:OK     Esc:Cancel       ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C���^�f�B���N�g�����������܂�   ");
       strcpy(MsgTxt[1],"                                     ");
       strcpy(MsgTxt[2],"�V�������O���w�肵�ĉ�����           ");
       strcpy(MsgTxt[3],"                                     ");
       strcpy(MsgTxt[4],"                                     ");
       strcpy(MsgTxt[5],"        Enter:���s  Esc:���         ");
    }

    if(KbdLineIn(6, bt_g_NormalWindowColor, 3, puc_defaultstr,
                 FLAG_INPUTWIN_MSGBOXCLEAR)==ESC) return;

    if(ul_markcnt) {
       if(!strchr(InpLine, '*') && !strchr(InpLine, '?')) {
          if(English){
             strcpy(MsgTxt[0],"Use wild card if you want");
             strcpy(MsgTxt[1],"rename marked files.     ");
          }
          else{
             strcpy(MsgTxt[0],"�}�[�N�t�@�C������������ꍇ��");
             strcpy(MsgTxt[1],"���C���h�J�[�h���g�p���ĉ�����");
          }
          MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
          return;
       }
       for (ul_count=0; ul_count<FlCnt; ul_count++) {
          KbdCharIn(&KeyInfo, IO_NOWAIT, 0);
          if(KeyInfo.chChar==ESC) break;
          if (FlDis[ul_count].Mark) {
             DosEditName(1, FlDis[ul_count].Nm+DISP_FN, InpLine, 
                        uszNewName, sizeof(uszNewName));
             FileNameChangeFunc(FlDis[ul_count].Nm+DISP_FN, uszNewName);
          }
       }
    } else{
       FileNameChangeFunc(FlDis[SelFl].Nm+DISP_FN, InpLine);
    }

    QFile(); 
    ShowFileList(); 
 }

/****************************************************************/
/**   FileName_Case                                            **/
/****************************************************************/
 VOID FileName_Case(ULONG ul_markcnt)
 {
    USHORT us_flag_case=FLAG_NAME_NOTDEFINE;
    ULONG  ul_count;

    if(!FlCnt) return;
    if(!ul_markcnt) {
       if(!strcmp(FlDis[SelFl].Nm+DISP_FN, ".")
             || !strcmp(FlDis[SelFl].Nm+DISP_FN, "..")) return;
    }
    
    if(English){
       strcpy(MsgTxt[0],"Change upper/lower case                    ");
       strcpy(MsgTxt[1],"                of file(or directory) name.");
       strcpy(MsgTxt[2],"                                           ");
       strcpy(MsgTxt[3],"                                           ");
       strcpy(MsgTxt[4],"  L(Enter). Lower case all                 ");
       strcpy(MsgTxt[5],"  U(Space). Upper case all                 ");
       strcpy(MsgTxt[6],"  C. Upper case only top of name           ");
       strcpy(MsgTxt[7],"  E. Upper case only top of name and ext.  ");
       strcpy(MsgTxt[8],"                          Esc:Cancel       ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C���^�f�B���N�g������                 ");
       strcpy(MsgTxt[1],"              �啶����������ύX���܂�     ");
       strcpy(MsgTxt[2],"                                           ");
       strcpy(MsgTxt[3],"                                           ");
       strcpy(MsgTxt[4],"  �k(Enter). ���ׂď�����                  ");
       strcpy(MsgTxt[5],"  �t(Space). ���ׂđ啶��                  ");
       strcpy(MsgTxt[6],"  �b. �t�@�C���̐擪�̂ݑ啶���A���͏����� ");
       strcpy(MsgTxt[7],"  �d. �g���q�̐擪���啶���A���͏�����     ");
       strcpy(MsgTxt[8],"                          Esc:���         ");
    }

    if(ul_markcnt) {
       sprintf(MsgTxt[2],
                English ? "  File/Dir: Marked files( %lu )" :
                          "  File/Dir: �}�[�N�t�@�C��( %lu ��)", ul_markcnt);
    } else {
       sprintf(MsgTxt[2], "  File/Dir: %s", FlDis[SelFl].Nm+DISP_FN);
    }
    
    ShowMsgBox(9, bt_g_NormalWindowColor);
    do{
       KbdCharIn(&KeyInfo,IO_WAIT,0); 
       switch(KeyInfo.chChar){
          case ENTER:
          case 'l':  
          case 'L':  
             us_flag_case=FLAG_NAME_LOWER;
             break;
          case ' ':
          case 'u':  
          case 'U':  
             us_flag_case=FLAG_NAME_UPPER;
             break;
          case 'c':  
          case 'C':  
             us_flag_case=FLAG_NAME_CAP;
             break;
          case 'e':  
          case 'E':  
             us_flag_case=FLAG_NAME_EXT;
             break;
          case ESC:  
             ShowFileList();
             return;
       }
    }while(us_flag_case==FLAG_NAME_NOTDEFINE);
    ShowFileList(); 

    if(ul_markcnt) {
       for (ul_count=0; ul_count<FlCnt; ul_count++) {
          KbdCharIn(&KeyInfo, IO_NOWAIT, 0);
          if(KeyInfo.chChar==ESC) break;
          if (FlDis[ul_count].Mark) 
             FileNameChange_Case(FlDis[ul_count].Nm+DISP_FN, us_flag_case);
       }
    } else{
       FileNameChange_Case(FlDis[SelFl].Nm+DISP_FN, us_flag_case);
    }
    
    QFile(); 
    ShowFileList(); 
    return;
 }

/****************************************************************/
/**   FileNameChange_Case                                      **/
/****************************************************************/
 VOID FileNameChange_Case(PSZ psz_oldname, USHORT us_flg_case)
 {
    UCHAR uc_newname[_MAX_PATH];
    PUCHAR puc_priodptr;

    strcpy(uc_newname, psz_oldname);
    switch(us_flg_case){
       case FLAG_NAME_LOWER:
          jstrlwr(uc_newname);
          break;
       case FLAG_NAME_UPPER:
          jstrupr(uc_newname);
          break;
       case FLAG_NAME_CAP:  
          jstrlwr(uc_newname);
          uc_newname[0]=toupper(uc_newname[0]);
          break;
       case FLAG_NAME_EXT:  
          jstrlwr(uc_newname);
          uc_newname[0]=toupper(uc_newname[0]);
          puc_priodptr=uc_newname;
          while((puc_priodptr=strchr(puc_priodptr, '.')) != NULL) {
             puc_priodptr++;  
             *puc_priodptr=toupper(*puc_priodptr);
          }
          break;
    }

    FileNameChangeFunc(psz_oldname, uc_newname);
    return;
 }

/****************************************************************/
/**   FileNameChangeFunc                                       **/
/****************************************************************/
 VOID FileNameChangeFunc(PSZ psz_oldname, PSZ psz_newname)
 {
    APIRET apr_DosMove;

    apr_DosMove=DosMove(psz_oldname, psz_newname);
    switch(apr_DosMove) {
       case NO_ERROR:
          break;
       case ERROR_ACCESS_DENIED:
          ShowMsgNameErr(psz_oldname);
          break;
       default:   
          ErrorMsgDisp(apr_DosMove, psz_oldname);
    }
    return;
 }

/*****************************************************************/
/**  FileNameCompDefault                                        **/
/*****************************************************************/
 INT FileNameCompDefault(const void *PFlDisX)
 {
    struct _FlDis *PX=(struct _FlDis *)PFlDisX;
    
    if(!strcmp(PX->Nm+DISP_FN,"..")) return 1;
    if(!strcmp(PX->Nm+DISP_FN,"."))  return 2;
    if(PX->Atr&FILE_SYSTEM) {
       if (PX->Atr&FILE_DIRECTORY)  return 3;
       else                   return 4;
    }
    if (PX->Atr&FILE_DIRECTORY) return 5;
    return 6;
 }


/****************************************************************/
/**  FileNameComp                                              **/
/****************************************************************/
 int FileNameComp(PSZ n1, PSZ n2)
 {
    if (CaseOfSort)  
       return strcmp (n1,n2);
    else             
       return stricmp(n1,n2);
 }

/****************************************************************/
/**  FileExtentionComp                                         **/
/****************************************************************/
 int FileExtentionComp(PSZ n1, PSZ n2)
 {
    int     ext_cmp_result;
    PUCHAR  ext_ptr1, ext_ptr2;

    ext_ptr1 = strrchr(n1, '.');
    ext_ptr2 = strrchr(n2, '.');

    if(ext_ptr1) {
       if(ext_ptr2) {
          if(!(ext_cmp_result=FileNameComp(ext_ptr1+1, ext_ptr2+1))) 
             return FileNameComp(n1, n2);
          else
             return ext_cmp_result;
       } else {
          return 1;
       }
    } else {
       if(ext_ptr2) 
          return -1;
       else         
          return FileNameComp(n1, n2);
    }

 }

/****************************************************************/
/**  FileNameCompOption                                        **/
/****************************************************************/
 int FileNameCompOption(const void *PFlDis1, const void *PFlDis2)
 {
    struct _FlDis *P1=(struct _FlDis *)PFlDis1;
    struct _FlDis *P2=(struct _FlDis *)PFlDis2;
    
    INT i_sortdeault=FileNameCompDefault(PFlDis1)
                    -FileNameCompDefault(PFlDis2);
    if(i_sortdeault != 0) return i_sortdeault;

    switch(KindOfSort){
       case 'N':
       case 'n':
       default :
          return FileNameComp(P1->Nm+DISP_FN, P2->Nm+DISP_FN);
       case 'E':
       case 'e':
          return FileExtentionComp(P1->Nm+DISP_FN, P2->Nm+DISP_FN);
       case 'T':
       case 't':
          return strcmp(P2->Nm+DISP_DT, P1->Nm+DISP_DT);   
       case 'S':
       case 's':
#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
          return (P2->cbFile - P1->cbFile);
#else
          {
              if(P2->cbFile < P1->cbFile) return -1;
              else if(P2->cbFile > P1->cbFile) return 1;
              else return 0;
          }
#endif
    }
 }

/****************************************************************/
/**   FilePathSearch                                           **/
/****************************************************************/
 APIRET FilePathSearch(PSZ psz_programname, PSZ psz_fullfilename,
                       ULONG ul_fullfilename_bufsize)
 {
    return DosSearchPath(SEARCH_CUR_DIRECTORY|SEARCH_ENVIRONMENT,
                         "PATH", psz_programname, 
                         psz_fullfilename, ul_fullfilename_bufsize);
 }

/****************************************************************/
/**   FileSort                                                 **/
/****************************************************************/
 void FileSort(void)
 {
    if(English){
       strcpy(MsgTxt[0],"Sort file list.             ");
       strcpy(MsgTxt[1]," Select type of sort.       ");
       strcpy(MsgTxt[2],"                            ");
       strcpy(MsgTxt[3]," N. Filename                ");
       strcpy(MsgTxt[4]," E. Extension               ");
       strcpy(MsgTxt[5]," T. Time(Newer)             ");
       strcpy(MsgTxt[6]," S. Size(Bigger)            ");
       strcpy(MsgTxt[7],"                            ");
       strcpy(MsgTxt[8],"             Esc:Cancel     ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C���ꗗ�̃\\�[�g�����܂�");
       strcpy(MsgTxt[1]," ��ĕ��@��I�����ĉ�����    ");
       strcpy(MsgTxt[2],"                            ");
       strcpy(MsgTxt[3]," �m.�t�@�C����              ");
       strcpy(MsgTxt[4]," �d.�g���q                  ");
       strcpy(MsgTxt[5]," �s.����   (�V������)       ");
       strcpy(MsgTxt[6]," �r.�T�C�Y (�傫����)       ");
       strcpy(MsgTxt[7],"                            ");
       strcpy(MsgTxt[8],"             Esc:���       ");
    }

    ShowMsgBox(9, bt_g_NormalWindowColor);
    for(;;) {
       KbdCharIn(&KeyInfo,IO_WAIT,0); 
       switch(KeyInfo.chChar){
          case ESC:
             ShowFileList();
             return;
          case 'n':
          case 'N':
          case 'e':
          case 'E':
          case 't':
          case 'T':
          case 's':
          case 'S':
             KindOfSort = KeyInfo.chChar;
             qsort(FlDis, FlCnt, sizeof(struct _FlDis), FileNameCompOption);
             ShowFileList_FilePosition(0);
             return;
          default:;
       }
    }    
 }
/****************************************************************/
/**   FuncEvent                                                **/
/****************************************************************/
 void FuncEvent(UCHAR uc_scancode)
 {
    switch(uc_scancode){
       case ARROW_UP: 
          if (FileRow>0){
             ShowFileList_Line(FlDis[SelFl].Nm, FileRow, 
                               FlDis[SelFl].DisAtr[0], FlDis[SelFl].Atr);
             --SelFl;
             --FileRow;
             ShowFileList_Line(FlDis[SelFl].Nm, FileRow, 
                               FlDis[SelFl].DisAtr[1], FlDis[SelFl].Atr);
             ShowFileList_CurrFileInfo(SelFl);
          } else if(PageNo>1) {
             ShowFileList_FilePosition(SelFl-1);
          }
          break;
       case ARROW_LEFT:
          if (FileRow>FILER_LISTWINSIZE-1){
             ShowFileList_Line(FlDis[SelFl].Nm, FileRow, 
                               FlDis[SelFl].DisAtr[0], FlDis[SelFl].Atr);
             SelFl-=FILER_LISTWINSIZE;
             FileRow-=FILER_LISTWINSIZE;
             ShowFileList_Line(FlDis[SelFl].Nm, FileRow, 
                               FlDis[SelFl].DisAtr[1], FlDis[SelFl].Atr);
             ShowFileList_CurrFileInfo(SelFl);
          } else if(PageNo>1) {
             ShowFileList_FilePosition(SelFl-FILER_LISTWINSIZE);
          }
          break;
       case SPACE:
          FileMark();
          if (SelFl==FlCnt-1){  /* �Ō�̍s�̏ꍇ�͒P�ɏ����������� */
             ShowFileList_Line(FlDis[SelFl].Nm, FileRow, 
                               FlDis[SelFl].DisAtr[1], FlDis[SelFl].Atr);
             return;
          }
       case ARROW_DOWN: 
          if(FlCnt==0) break;
          if (FileRow<FILER_LISTFILENUM-1 && SelFl<FlCnt-1){
             ShowFileList_Line(FlDis[SelFl].Nm, FileRow, 
                               FlDis[SelFl].DisAtr[0], FlDis[SelFl].Atr);
             ++SelFl;
             ++FileRow;
             ShowFileList_Line(FlDis[SelFl].Nm, FileRow, 
                               FlDis[SelFl].DisAtr[1], FlDis[SelFl].Atr);
             ShowFileList_CurrFileInfo(SelFl);
          } else if (FlCnt-StartFl>FILER_LISTFILENUM) {
             ShowFileList_FilePosition(SelFl+1);
          } 
          break;
       case ARROW_RIGHT: 
          if(FlCnt==0) break;
          if((SelFl+FILER_LISTWINSIZE+FILER_LISTFILENUM)/FILER_LISTFILENUM == PageNo) {
             if(SelFl+FILER_LISTWINSIZE<FlCnt) {
                ShowFileList_Line(FlDis[SelFl].Nm, FileRow, 
                                  FlDis[SelFl].DisAtr[0], FlDis[SelFl].Atr);
                SelFl+=FILER_LISTWINSIZE;
                FileRow+=FILER_LISTWINSIZE;
                ShowFileList_Line(FlDis[SelFl].Nm, FileRow, 
                                  FlDis[SelFl].DisAtr[1], FlDis[SelFl].Atr);
                ShowFileList_CurrFileInfo(SelFl);
             } else {
                if((SelFl-StartFl)/FILER_LISTWINSIZE != (FlCnt-1-StartFl)/FILER_LISTWINSIZE) {
                   ShowFileList_FilePosition(FlCnt-1);
                }
             }
          } else {
             if(SelFl+FILER_LISTWINSIZE<FlCnt) {
                ShowFileList_FilePosition(SelFl+FILER_LISTWINSIZE);
             } else {
                if((SelFl-StartFl)/FILER_LISTWINSIZE != (FlCnt-1-StartFl)/FILER_LISTWINSIZE) {
                   ShowFileList_FilePosition(FlCnt-1);
                }
             }
          }
          break;
       case PAGE_UP:
          if (PageNo>1) {
             ShowFileList_FilePosition((PageNo-2)*FILER_LISTFILENUM+FileRow);
          }else if(PageNo==1 && FileRow>0) {
             ShowFileList_FilePosition(0);
          }
          break;
       case PAGE_DOWN:
          if (FlCnt-StartFl > FILER_LISTFILENUM+FileRow){
             ShowFileList_FilePosition(PageNo*FILER_LISTFILENUM+FileRow);
          }else if(FlCnt-StartFl <= FILER_LISTFILENUM+FileRow 
                   && FlCnt-StartFl != FileRow) {
             ShowFileList_FilePosition(FlCnt-1);
          }
          break;
       case HOME: 
       case HOME98:
          ShowFileList_FilePosition(0);
          break;
       case END: 
          ShowFileList_FilePosition(FlCnt-1);
          break;
       case INSERT: 
          FileMarkAll(); 
          break;
       case DELETE: 
          Serch1Char(FLAG_FIRST); 
          break;
       case PF1: 
          ShowHelp(); 
          break;
       case PF2: 
          ChangeSetup(); 
          break;
       case PF3: 
          HistryBox(FLAG_HISTRY_DIRECTRY);
          SaveHistoryFile_toDisk();
          break;
       case PF4: 
          MacroDisp(MarkCnt); 
          break;
       case PF5: 
          QDrive();
          QDir();
          ReDrawAfterDelete();
          break;
       case PF6:
          OpenObjectOnDesktop(".", FILE_DIRECTORY);
          break;
       case PF9:
          ObjectCopy_HPFS_FAT(FlDis[SelFl].Nm+DISP_FN, MarkCnt);
          break;
       case PF10:
          ChangeCodePage();
          break;
       case PF11:
          SaveHistoryFile_toDisk();
          FileExecFunc_AnotherSession(FLAG_NO_MARK, "", FlstrExeFl, 
                                      ".", 1, SSF_TYPE_DEFAULT); 
                                      /* AutoClose=1 */
          break;
       case PF12: 
          ShowMsgVersionInfo(); 
          break;
       default:;
    }
 }

/****************************************************************/
/**   GetCodePage                                              **/
/****************************************************************/
 void GetCodePage(SHORT s_flg_first)
 {
        ULONG nul;
        
        jstring_init(); /* DBCS���e�[�u���擾 */

        if (s_flg_first == FLAG_FIRST) {
            DosQueryCp( sizeof(CodePage) ,CodePage ,&nul );
            ul_g_initialCodePage = CodePage[0];
        }
        if(CodePage[0]==932 || CodePage[0]==942 || CodePage[0]==943){
            // ���s�̃R�[�h�y�[�W��932 / 942 / 943�i���{��j
            English = ForceEnglish;  // �uEnglishMode=1�v�ŉp�ꃂ�[�h�Œ�

            DisableJapanFunc = FALSE; // ���{��łɈˑ������@�\�����e
            us_g_flg_dosmode = FLAG_DOSMODE_DOSV;
            DisableCharCode = FALSE; // �r���[�A�̃L�����R�[�h�؂�ւ��@�\������

            // �r���L�����i�f�t�H���g�����{��j
            LineChar_V[0]     =  0x05; // 
            LineChar_H[0]     =  0x06; // 
            LineChar_UR[0]    =  0x03; // 
      //    LineChar_HU[0]    =  0x15; // 
            LineChar_UL[0]    =  0x04; // 
      //    LineChar_VR[0]    =  0x19; // 
      //    LineChar_VH[0]    =  0x10; // 
      //    LineChar_VL[0]    =  0x17; // 
            LineChar_DR[0]    =  0x01; // 
            LineChar_HD[0]    =  0x16; // 
            LineChar_DL[0]    =  0x02; // 
        } else {
            // ���s�̃R�[�h�y�[�W��932 / 942 /943�i���{��j�łȂ�
            English = TRUE; // �p�ꃂ�[�h
            DisableCharCode = TRUE; // �r���[�A�̃L�����R�[�h�؂�ւ��@�\���֎~
            // �r���L������ς���
            switch( CodePage[0] ){
                case 437: // �p��
                case 850: // ������
                case 852: // ���e����Q(�`�F�R�X���o�L�A�A�n���K���[�A�|�[�����h�A���[�S�X���r�A)
                case 857: // �g���R��
                case 860: // �|���g�K����
                case 861: // �A�C�X�����h
                case 863: // �J�i�_�E�t�����X�ꌗ
                case 865: // �k����
		// �p��p�Ɍr���ύX
                    LineChar_V[0]     = 0xBA; // 
                    LineChar_H[0]     = 0xCD; // 
                    LineChar_UR[0]    = 0xC8; // 
//                  LineChar_HU[0]    = 0xCA; // 
                    LineChar_UL[0]    = 0xBC; // 
//                  LineChar_VR[0]    = 0xCC; // 
//                  LineChar_VH[0]    = 0xCE; // 
//                  LineChar_VL[0]    = 0xB9; // 
                    LineChar_DR[0]    = 0xC9; // 
                    LineChar_HD[0]    = 0xCB; // 
                    LineChar_DL[0]    = 0xBB; // 
                    break;
                default:
                // �R�[�h�y�[�W���s�� �� �r���͎g��Ȃ�
                    LineChar_V[0]     = '|'; // 
                    LineChar_H[0]     = '-'; // 
                    LineChar_UR[0]    = '+'; // 
//                  LineChar_HU[0]    = '+'; // 
                    LineChar_UL[0]    = '+'; // 
//                  LineChar_VR[0]    = '+'; // 
//                  LineChar_VH[0]    = '+'; // 
//                  LineChar_VL[0]    = '+'; // 
                    LineChar_DR[0]    = '+'; // 
                    LineChar_HD[0]    = '+'; // 
                    LineChar_DL[0]    = '+'; // 
            }

            if( CodePage[1]==932 || CodePage[1]==942 || CodePage[1]==943){
                // ��R�[�h�y�[�W��932/942/943�i���{��j �� ���{��łɈˑ������@�\�����e
                DisableJapanFunc = FALSE; // ���{��łɈˑ������@�\�����e
                us_g_flg_dosmode = FLAG_DOSMODE_DOSV;
            } else {
                // ��R�[�h�y�[�W��932/942/943�i���{��j�łȂ� �� ���{��łɈˑ������@�\���֎~
                DisableJapanFunc = TRUE;
                us_g_flg_dosmode = FLAG_DOSMODE_PCDOS;
            }
        } 
}

/****************************************************************/
/**   GetMode                                                  **/
/****************************************************************/
 void GetMode(void)
 {
    VIOMODEINFO   VioModeInfo={0};
    KBDINFO       kbi_status={0};
    UCHAR         usz_winsize[8];

    VioModeInfo.cb = sizeof(VioModeInfo);   
    VioGetMode(&VioModeInfo, VIO_HANDLE );   
    RowMax=VioModeInfo.row;
    ColMax=VioModeInfo.col;

    if(ColMax < 60) ColMax = 60;
    if(RowMax < 15) RowMax = 15;
    if(RowMax!=VioModeInfo.row || ColMax!=VioModeInfo.col) {
       sprintf(usz_winsize, "%hu,%hu\0", ColMax, RowMax);
       ChangeWindowSizeFunc(usz_winsize);

       VioGetMode(&VioModeInfo, VIO_HANDLE );   
       RowMax=VioModeInfo.row;
       ColMax=VioModeInfo.col;
    }


    Vio_CursorShape(FLAG_CURSOR_HIDDEN);

    kbi_status.cb =sizeof(KBDINFO);
    KbdGetStatus(&kbi_status, 0);
    kbi_status.fsMask = KEYBOARD_BINARY_MODE;
    KbdSetStatus(&kbi_status, 0);
 
}

/****************************************************************/
/**   GetOriginDir                                             **/
/****************************************************************/
 void GetOriginDir(void)
 {
    UCHAR drive[_MAX_DRIVE], dir[_MAX_PATH], my_filename[_MAX_PATH] ;

    /*----------------------------------------------------------*/
    /* ���s�t�@�C���̃t���p�X�́A���W���[���n���h������擾���� */
    /*----------------------------------------------------------*/
    PTIB ptib;
    PPIB ppib;

    DosGetInfoBlocks(&ptib , &ppib);
    DosQueryModuleName(ppib->pib_hmte, sizeof(FlstrExeFl), FlstrExeFl);
    jstrlwr(FlstrExeFl);

#ifdef IBMCSET
    {
    UCHAR ext[_MAX_EXT];
    _splitpath(FlstrExeFl,  drive, dir, my_filename, ext);
    }
#else
    _splitpath(FlstrExeFl,  drive, dir, my_filename, NULL );
#endif

    _jmakepath(FlstrDirFl,  drive, dir, my_filename, "dir");
    _jmakepath(FlstrHstFl,  drive, dir, my_filename, "hst");
    _jmakepath(FlstrPhsFl,  drive, dir, my_filename, "phs");
    _jmakepath(FlstrIniFl,  drive, dir, my_filename, "ini");
    
    /* ----------------------- */
    /* query long file support */
    /* ----------------------- */
#ifndef IBMCSET  /* ��e�ʃt�@�C���΍�����Ȃ� */
    lfs_QueryLargeFileSupport();
#endif
    
    /*---------------------*/
    /* DLL�t�@�C���̃��[�h */
    /*---------------------*/
    FNovaDllLoad();
}

/*****************************************************************/
/**   GotoAnotherDir                                            **/
/*****************************************************************/
 VOID GotoAnotherDir(PSZ psz_GotoDir)
 {
    UCHAR uc_subdirname_backup[_MAX_PATH]={0};
    PUCHAR puc_yenptr;

    if(!strcmp(psz_GotoDir, ".")) return;   /* �J�����gDir�Ȃ牽�����Ȃ� */

    /* �eDir�Ɉړ�����ۂɂ͌��݂�SubDir���𒲂ׂĂ��� */
    if(!strcmp(psz_GotoDir, "..")) {  
       puc_yenptr=jstrrchr(PathDis, '\\');
       if(puc_yenptr) strcpy(uc_subdirname_backup, puc_yenptr+1);
    } else if(!strcmp(psz_GotoDir, "\\")) { 
       strcpy(uc_subdirname_backup, PathDis+1); 
       puc_yenptr=jstrchr(uc_subdirname_backup, '\\');
       if(puc_yenptr) *puc_yenptr='\0';
    }

    DosSetCurrentDir(psz_GotoDir); /* �ړ��Ɏ��s���Ă����̂܂ܑ����� */
                                   /* FD,MO�Ȃǂ��������ꂽ���̂���  */  
    QDriveSize();
    QDir();
    if(uc_subdirname_backup[0]=='\0') {
       QFile();                   /* <- ������psz_GotoDir�������ς�� */
       ShowFileList_FilePosition(0);
    } else {
       ShowFileList_PrevFile(FLAG_DRAW_FILELIST, uc_subdirname_backup);
    }
    SetFullCurrentPathName(uc_subdirname_backup);
    JumpHistInsert(FLAG_HISTRY_PATH, uc_subdirname_backup);

 }

/*****************************************************************/
/**  GetYesorNo_withMsgBox                                      **/
/*****************************************************************/
UCHAR GetYesorNo_withMsgBox(UCHAR uc_yeschar, USHORT us_msgboxrow,
                             BYTE bt_msgboxattr, USHORT us_flg_option)
 {
    UCHAR uc_inputchar=0;
    
    ShowMsgBox(us_msgboxrow, bt_msgboxattr);
    do {
       KbdCharIn(&KeyInfo,IO_WAIT,0);
       switch(KeyInfo.chChar) {
          case 'N':
          case 'n':
          case ESC:
             uc_inputchar = ESC;
             break;
          case 'Y':
          case 'y':
             uc_inputchar = ENTER;
             break;
          case ENTER:
             if(uc_yeschar==ENTER) uc_inputchar = ENTER;
             break;
          case ' ':
             if(uc_yeschar==' ') uc_inputchar = ENTER;
             break;
          default:
             if(us_flg_option & FLAG_GETYESORNO_FUNCKEY_ON) {
                switch(KeyInfo.chScan) {
                   case PF1:
                   case PF2:
                   case PF3:
                   case PF4:
                   case PF5:
                   case PF6:
                   case PF7:
                   case PF8:
                   case PF9:
                   case PF10:
                   case PF11:
                   case PF12:
                      return KeyInfo.chScan;
                }
            }
       }
    }while(!uc_inputchar);

    if(us_flg_option & FLAG_GETYESORNO_MSGBOXCLEAR) ShowFileList();
    if(us_flg_option & FLAG_GETYESORNO_MSGBOXNULL)  ShowMsgBoxNull();

    return uc_inputchar;
 
 }

/*****************************************************************/
/**   InitCustomize                                             **/
/*****************************************************************/
 void InitCustomize(SHORT s_flg_first)
 {
    UCHAR   IniFileIn[256], *IniFileEnd;

    USHORT us_setup, us_flg_IniSection=0;
    FILE *fl_filestar_ini;

    if(!(fl_filestar_ini=fopen(FlstrIniFl, "r"))) return;
    
    /*** �ēǂݍ��݂̎����l���Ċg���q�ƃ}�N���֌W�������� ***/
    InitCustomize_ClearExternalProg(&AssocCnt,    ASSOC_MAX,    AssocProg);
    InitCustomize_ClearExternalProg(NULL,         36,           MacroProg);
    InitCustomize_ClearExternalProg(&UnpackerCnt, UNPACKER_MAX, UnpackerProg);
    InitCustomize_ClearExternalProg(&PackerCnt,   PACKER_MAX,   PackerProg);
    InitCustomize_ClearViewerCfg(s_flg_first);
    InitCustomize_ClearEditorCfg(s_flg_first);

    while(fgets(IniFileIn, sizeof(IniFileIn), fl_filestar_ini)) {
       if(*IniFileIn != ' ') {
          /*-----------------------------------*/
          /* �󔒂Q�����͖���            */
          /*-----------------------------------*/
          strtok(IniFileIn, "\n");
          IniFileEnd=strstr(IniFileIn,"  "); 
          if (IniFileEnd!=NULL) *IniFileEnd = '\0'; 
       
          /*----------------------------------*/
          /* �L�[���[�h��T��                 */
          /*----------------------------------*/
          if (!memcmp(IniFileIn,"<General>",9)) {
             us_flg_IniSection=INI_GENERAL;
          } else if (!memcmp(IniFileIn,"<Editor>",8)) {
             us_flg_IniSection=INI_EDITOR;
          } else if (!memcmp(IniFileIn,"<Viewer>",8)) {
             us_flg_IniSection=INI_VIEWER;
          } else if (!memcmp(IniFileIn,"<Extension>",11)) {
             us_flg_IniSection=INI_EXTENTION;
          } else if (!memcmp(IniFileIn,"<Macro>",7)) {
             us_flg_IniSection=INI_MACRO;
          } else if (!memcmp(IniFileIn,"<Unpacker>",10)) {
             us_flg_IniSection=INI_UNPACKER;
          } else if (!memcmp(IniFileIn,"<Packer>",8)) {
             us_flg_IniSection=INI_PACKER;
          } else if (!memcmp(IniFileIn,"<Color>",7)) {
             us_flg_IniSection=INI_COLOR;
          }
       
          switch(us_flg_IniSection){
             case INI_GENERAL: 
                SetupGeneral(s_flg_first, IniFileIn); 
                break;
             case INI_EDITOR: 
                SetupEditor(IniFileIn); 
                break;
             case INI_VIEWER: 
                SetupViewer(IniFileIn);
                break;
             case INI_EXTENTION: 
                us_setup=SetupExtention(IniFileIn, &AssocProg[AssocCnt]);
                if(!us_setup&&AssocCnt<ASSOC_MAX) AssocCnt++;
                break;
             case INI_MACRO:
                MacroSetup(IniFileIn); 
                break;
             case INI_UNPACKER:
                us_setup=SetupUnpacker(IniFileIn, UnpackerCnt);
                if(!us_setup&&UnpackerCnt<UNPACKER_MAX) UnpackerCnt++;
                break;
             case INI_PACKER:
                us_setup=SetupExtention(IniFileIn, &PackerProg[PackerCnt]);
                if(!us_setup&&PackerCnt<PACKER_MAX) PackerCnt++;
                break;
             case INI_COLOR:
                ColorSetup(IniFileIn);
                break;
             default: 
                break;
          }
       }
    } 
    fclose(fl_filestar_ini);
 }


/*****************************************************************/
/**   InitCustomize_ClearExternalProg                           **/
/*****************************************************************/
VOID InitCustomize_ClearExternalProg(PUSHORT pus_prognum,
                     USHORT us_progmax, PEXTERNALPROG pExternalProg) 
{
    USHORT us_count;
    
    if(pus_prognum) *pus_prognum=0;
    for(us_count=0; us_count<us_progmax; us_count++) {
       memset(pExternalProg, 0, sizeof(EXTERNALPROG));
       pExternalProg++;
    }
}
/*****************************************************************/
/**   InitCustomize_ClearViewerCfg                              **/
/*****************************************************************/
VOID InitCustomize_ClearViewerCfg(SHORT s_flg_first)
{
    if(s_flg_first==FLAG_FIRST) {
       ViewerCfg.usUseExtViewer = 0;
       ViewerCfg.ulTabSize = 4;
    }

    InitCustomize_ClearExternalProg(NULL, 1,  &(ViewerCfg.ViewerProg));
}

/*****************************************************************/
/**   InitCustomize_ClearEditorCfg                              **/
/*****************************************************************/
VOID InitCustomize_ClearEditorCfg(SHORT s_flg_first)
{
    InitCustomize_ClearExternalProg(NULL, 1,  &(EditorCfg.EditorProg));

    EditorCfg.usLineSetTop = 0;
    EditorCfg.EditorProg.usSession = 1;
    strcpy(EditorCfg.EditorProg.uszProgName, "E.EXE");

}

/****************************************************************/
/**   LoadHistoryFile_fromDisk                                 **/
/****************************************************************/
 void LoadHistoryFile_fromDisk(VOID)
 {
    LoadHistoryFile(FlstrDirFl, HistoryBufDir[0], sizeof(HistoryBufDir[0]));
    LoadHistoryFile(FlstrHstFl, HistoryBufHst[0], sizeof(HistoryBufHst[0]));
    LoadHistoryFile(FlstrPhsFl, HistoryBufPhs[0], sizeof(HistoryBufPhs[0]));
 }

/****************************************************************/
/**   LoadHistoryFile                                          **/
/****************************************************************/
 void LoadHistoryFile(PSZ psz_filename, PUCHAR puc_histbuf, ULONG ul_bufsize)
 {
    ULONG  ul_count;
    PCHAR  pc_Crlf_ptr; 
    FILE  *fl_filestar_dir;
    PUCHAR puc_buftop;
   
    puc_buftop=puc_histbuf;
    for (ul_count=0; ul_count<HISTORY_MAX; ul_count++){
       *puc_buftop='\0';
       puc_buftop+=ul_bufsize;
    }

    if(!(fl_filestar_dir=fopen(psz_filename,"r"))) return; 
    
    puc_buftop=puc_histbuf;
    for (ul_count=0; ul_count<HISTORY_MAX; ul_count++){
       if (!(fgets(puc_buftop, ul_bufsize, fl_filestar_dir))) break;
       pc_Crlf_ptr=strchr(puc_buftop,'\n');
       if (pc_Crlf_ptr) *pc_Crlf_ptr ='\0';   
       puc_buftop+=ul_bufsize;
    }
    fclose(fl_filestar_dir);
 }

/****************************************************************/
/**   SaveHistoryFile_toDisk                                   **/
/****************************************************************/
 void SaveHistoryFile_toDisk(VOID)
 {
    SaveHistoryFile(FlstrDirFl, HistoryBufDir[0], sizeof(HistoryBufDir[0]));
    SaveHistoryFile(FlstrHstFl, HistoryBufHst[0], sizeof(HistoryBufHst[0]));
    SaveHistoryFile(FlstrPhsFl, HistoryBufPhs[0], sizeof(HistoryBufPhs[0]));
 }

/****************************************************************/
/**   SaveHistoryFile                                          **/
/****************************************************************/
 void SaveHistoryFile(PSZ psz_filename, PUCHAR puc_histbuf, ULONG ul_bufsize)
 {
    ULONG  ul_count;
    FILE  *fl_filestar_dir;
    PUCHAR puc_buftop;
   
    if(!(fl_filestar_dir=fopen(psz_filename,"w"))) return; 
    
    puc_buftop=puc_histbuf;
    for (ul_count=0; ul_count<HISTORY_MAX; ul_count++){
       fprintf(fl_filestar_dir,"%s\n", puc_buftop);
       puc_buftop+=ul_bufsize;
    }

    fclose(fl_filestar_dir);
 }


/****************************************************************/
/**   JumpDirRead                                              **/
/****************************************************************/
 void JumpDirRead(USHORT us_flg_dir_hst)
 {
    USHORT us_count;

    for (us_count=0; us_count<HISTORY_MAX; us_count++){
       memset(ListTxt[us_count]+2, 0, sizeof(ListTxt[us_count])-2);
    }

    for (us_count=0; us_count<HISTORY_MAX; us_count++){
       switch(us_flg_dir_hst) {
          case FLAG_HISTRY_DIRECTRY:
             strcpy(ListTxt[us_count]+2, HistoryBufDir[us_count]);
             break;
          case FLAG_HISTRY_COMMAND:
             strcpy(ListTxt[us_count]+2, HistoryBufHst[us_count]);
             break;
          case FLAG_HISTRY_PATH:
             strcpy(ListTxt[us_count]+2, HistoryBufPhs[us_count]);
             break;
          default:
             return;
       }
    }
 }

/****************************************************************/
/**   JumpDirSaveFunc                                          **/
/****************************************************************/
 void JumpDirSaveFunc(USHORT us_flg_dir_hst)
 {
    USHORT us_count;

    for (us_count=0; us_count<HISTORY_MAX; us_count++){
       switch(us_flg_dir_hst) {
          case FLAG_HISTRY_DIRECTRY:
             strcpy(HistoryBufDir[us_count], ListTxt[us_count]+2);
             break;
          case FLAG_HISTRY_COMMAND:
             strcpy(HistoryBufHst[us_count], ListTxt[us_count]+2);
             break;
          case FLAG_HISTRY_PATH:
             strcpy(HistoryBufPhs[us_count], ListTxt[us_count]+2);
             break;
          default:
             return;
       }
    }
 }


/****************************************************************/
/**   JumpHistInsert                                           **/
/****************************************************************/
 void JumpHistInsert(USHORT us_flg_dir_hst, PSZ psz_savedir)
 {
    USHORT us_count, us_no_record=0;
    PSZ psz_drivepath;

    JumpDirRead(us_flg_dir_hst); /* �����t�@�C���̓ǂݍ��� */

    psz_drivepath = psz_savedir + strspn(psz_savedir, " ");  /* �擪�̋󔒂����� */

    for (us_count=0; us_count<HISTORY_MAX; us_count++){
       if (!(stricmp(ListTxt[us_count]+2, psz_drivepath))) { 
          /* �����Ɋ��ɓo�^�ς݂Ȃ炻�����牺�����ւ�*/
          us_no_record=us_count;
          break;
       }  
       if (ListTxt[us_count][2] == '\0') us_no_record=us_count;     /* �����ɂ͓o�^����ĂȂ� */
    }
    
    for (us_count=us_no_record; us_count<HISTORY_MAX-1; us_count++) {
       memset(ListTxt[us_count]+2, 0, sizeof(ListTxt[us_count])-2); 
                                                      /* �Â�������������   */
       strcpy(ListTxt[us_count]+2, ListTxt[us_count+1]+2);          
                                                      /* �ȉ�����J��グ */
    }
    memset(ListTxt[HISTORY_MAX-1]+2, 0, sizeof(ListTxt[HISTORY_MAX-1])-2);    
    strcpy(ListTxt[HISTORY_MAX-1]+2, psz_drivepath);  /* �Ō�͍ŐV�̕���   */
    
    JumpDirSaveFunc(us_flg_dir_hst);
 }

/****************************************************************/
/**   KbdEvent                                                 **/
/****************************************************************/
 void KbdEvent(void)
 {
    do {
       KbdCharIn(&KeyInfo,IO_WAIT, 0);
       Convert_WordStarLikeKey(&KeyInfo, FLAG_MODE_FILER);
       if((KeyInfo.bNlsShift!=0)&&(KeyInfo.bNlsShift!=64)) { /* FEP���͑S�p */
          if(iskanji(KeyInfo.chChar)==TRUE) {
             DosSleep(10L);                     // Warp 4.51 ��IME���x��
             KbdCharIn(&KeyInfo,IO_NOWAIT, 0);  // 2byte�����͓ǂݎ̂� 
             KeyInfo.chChar = 0xff;
          }
       }
    }while (KeyInfo.chChar > 0x7f);

    if (KeyInfo.fsState&KBDSTF_LEFTSHIFT || KeyInfo.fsState&KBDSTF_RIGHTSHIFT){
       if (isalpha(KeyInfo.chChar)) {
          MacroFunc(KeyInfo.chChar, MarkCnt);
          return;
       }
       if(KeyInfo.chChar==ENTER) {
          if(!MarkCnt) {
             if (CheckExtention(FlDis[SelFl].Nm+DISP_FN,".exe")
               ||CheckExtention(FlDis[SelFl].Nm+DISP_FN,".cmd")
               ||CheckExtention(FlDis[SelFl].Nm+DISP_FN,".com")
               ||CheckExtention(FlDis[SelFl].Nm+DISP_FN,".bat")) {
                  ViewFile_Ready(FlDis[SelFl].Nm+DISP_FN,FALSE); 
                  return;
             }
          } 
          FileEdit(FlDis[SelFl].Nm+DISP_FN, MarkCnt, FLAG_SILENT_START, 0); 
          return;
       }      
    }
    
    switch(KeyInfo.chChar){
       case ENTER:
          if (MarkCnt) {
             MarkFileExec();
             return;
          }
          if (FlDis[SelFl].Atr&FILE_DIRECTORY){
             GotoAnotherDir(FlDis[SelFl].Nm+DISP_FN);
             return;
          } 
          if (CheckExtention(FlDis[SelFl].Nm+DISP_FN,".exe")
            ||CheckExtention(FlDis[SelFl].Nm+DISP_FN,".cmd")
            ||CheckExtention(FlDis[SelFl].Nm+DISP_FN,".com")
            ||CheckExtention(FlDis[SelFl].Nm+DISP_FN,".bat")) {
             ExecProgram();    
             return;
          }
          if(ExecAssocProgram(FLAG_NO_MARK, FlDis[SelFl].Nm+DISP_FN) == MYFUNC_EXEC) 
             return;
          ViewFile_Ready(FlDis[SelFl].Nm+DISP_FN,FALSE);
          break;
       case ESC: 
          QuitFilestar(); 
          break;
       case BACK:
          GotoAnotherDir("..");
          break;
       case '\\':
          GotoAnotherDir("\\");
          break;
       case '0':
          break;
       case '1':
       case '2':
       case '3':
       case '4':
       case '5':
       case '6':
       case '7':
       case '8':
       case '9':
          ChangeDriveFunc(KeyInfo.chChar);  
          break;
       case 'a': 
       case 'A':
          ChangeAttribute(FlDis[SelFl].Nm+DISP_FN, FlDis[SelFl].Atr, MarkCnt);
          break;
       case 'b': 
       case 'B':
          if (!(FlDis[SelFl].Atr&FILE_DIRECTORY)) {
             ViewFile_Ready(FlDis[SelFl].Nm+DISP_FN,TRUE);
          }
          break;
       case 'c': 
       case 'C': 
          if (MarkCnt) 
             MarkFileCopy(MarkCnt);
          else         
             FileCopy();
          break;
       case 'd': 
       case 'D':
          if (MarkCnt)  
             MarkFileDelete();
          else 
             FileDelete();
          break;
       case 'e': 
       case 'E': 
          FileEdit(FlDis[SelFl].Nm+DISP_FN, MarkCnt, FLAG_NOISY_START, 0); 
          break;
       case 'f': 
       case 'F': 
          FileFind(); 
          break;
       case 'h': 
       case 'H': 
          ChangeDriveDir(FLAG_CHDIR_CHANGE);
          break;
       case 'i': 
       case 'I':
          if (MarkCnt) {
             MarkFileIcon();
          } else {
             MakeIcon(FlDis[SelFl].Nm+DISP_FN, FLAG_NO_MARK);
          }
          break;
       case 'j': 
       case 'J': 
          ChangeDriveDir(FLAG_CHDIR_JUMP);
          break;
       case 'k': 
       case 'K': 
          CreateDir(); 
          break;
       case 'l': 
       case 'L': 
          ChangeDrive(); 
          break;
       case 'm': 
       case 'M': 
          if (MarkCnt) {
             MarkFileMove(MarkCnt);
          } else {
             FileMove();
          }
          break;
       case 'n': 
       case 'N':
          FileName(MarkCnt); 
          break;
       case 'o': 
       case 'O': 
          OpenObjectOnDesktop(FlDis[SelFl].Nm+DISP_FN, 
                              FlDis[SelFl].Atr&FILE_DIRECTORY);
          break;
       case 'p': 
       case 'P': 
          Archive_Pack(FlDis[SelFl].Nm+DISP_FN, MarkCnt);
          break;
       case 'q': 
       case 'Q': 
          QuitFilestar(); 
          break;
       case 'r': 
       case 'R':
          FileName_Case(MarkCnt); 
          break;
       case 's': 
       case 'S': 
          FileSort(); 
          break;
       case 'u':
       case 'U':
          Archive_Unpack(FlDis[SelFl].Nm+DISP_FN, MarkCnt);
          break;
       case 'v': 
       case 'V':
          if (!(FlDis[SelFl].Atr&FILE_DIRECTORY)) {
             ViewFile_Ready(FlDis[SelFl].Nm+DISP_FN,FALSE);
          } else {
             GotoAnotherDir(FlDis[SelFl].Nm+DISP_FN);
          }
          break;
       case 'w': 
       case 'W': 
          ChangeWindowSize(); 
          break;
       case 'x': 
       case 'X': 
          ExecCommand(); 
          break;
       case 'y': 
       case 'Y': 
          FileMaskDisp(); 
          break;
       case '.': 
          CommandProcess(); 
          break;
       case '@': 
          if (FlDis[SelFl].Atr&FILE_DIRECTORY) 
             SummarySize(FlDis[SelFl].Nm+DISP_FN);
          break;
       case '!': 
          FileListType=1; 
          ShowFileList_FilePosition(SelFl);
          break;
       case '\"': 
          FileListType=2; 
          ShowFileList_FilePosition(SelFl);
          break;
       case '#': 
          FileListType=3; 
          ShowFileList_FilePosition(SelFl);
          break;
       case '%': 
          FileListType=5; 
          ShowFileList_FilePosition(SelFl);
          break;
       case CTRL_G:
          us_g_flg_8_3rule=!us_g_flg_8_3rule; 
          ShowFileList();
          break;
       case CTRL_L:
          Serch1Char(FLAG_NOT_FIRST); 
          break;
       case CTRL_T:
          ChangeTimeStamp(FlDis[SelFl].Nm+DISP_FN, MarkCnt);
          break;
       case CTRL_V:
          ChangeVolumeLabel();
          break;
       default : 
          FuncEvent(KeyInfo.chScan);
    }
 }

/****************************************************************/
/**   KbdLineIn                                                **/
/****************************************************************/
 UCHAR KbdLineIn(USHORT us_msgboxrow, BYTE bt_msgboxattr, USHORT us_LineSeq, 
                 PUCHAR puc_inputwinstr, USHORT us_flg_jump)
 {
    USHORT us_LineInRow, us_LineInCol, us_LineWidth,
           us_CurrPos, us_InpLineLen, us_InpLineSize,
           us_CurrDispStart, us_offset;
    UCHAR  uc_BackupStrings[_MAX_PATH]={0}, usz_dispbuff[256];
    USHORT us_flg_inputmode=FLAG_INSERT_MODE, us_flg_fnameset=0;
    PUCHAR puc_fname_ptr;

    ShowMsgBox(us_msgboxrow, bt_msgboxattr);  
    /* ��������Global�ϐ�BoxTop, BoxLeft, BoxWide ���ݒ肳��� */
                                                 
    us_LineInRow = BoxTop+us_LineSeq+2;      /* ���͑��̍s       */
    us_LineInCol = BoxLeft+3;                /* ���͑��̍��[�̗� */
    us_LineWidth = BoxWide-6;                /* ���͑��̕�       */

    /*-------------------------------*/
    /**     ���͑���ݒu            **/
    /*-------------------------------*/
    if(puc_inputwinstr != InpLine) {
       memset(InpLine, 0, sizeof(InpLine));
       if(puc_inputwinstr != NULL) strcpy(InpLine, puc_inputwinstr);
    }
    
    VioWrtNAttr(&bt_g_InputLineColor, us_LineWidth, us_LineInRow, 
                us_LineInCol, VIO_HANDLE);  

    /*-------------------------*/
    /*   �J�[�\���̌`���Z�b�g  */
    /*-------------------------*/
    if(us_flg_jump&FLAG_INPUTWIN_OVERWRITE) us_flg_inputmode=FLAG_OVERWRITE_MODE;
    Vio_CursorShape(us_flg_inputmode);
    
    /*---------------------------------*/
    /**    ������\���̂��߂̏����l   **/
    /*---------------------------------*/
    us_InpLineSize = sizeof(InpLine);    /* ���͂ł���ő啶����+1           */
    us_InpLineLen  = strlen(InpLine);    /* ���݂̕�����                     */
    if(us_InpLineLen < us_LineWidth) {   /* ���݂̕��������\�������Z���Ȃ� */
       us_CurrPos = us_InpLineLen;       /* �J�[�\���͕�����̍Ō��         */
    } else {
       us_CurrPos = 0;                   /* �łȂ���Ε�����̐擪��         */
    }
    if(us_flg_jump&FLAG_INPUTWIN_CURSORHEAD)  /* �t���O�Ŏw�肳��Ă����    */
       us_CurrPos = 0;                        /* �������ɕ�����̐擪��      */
    us_CurrDispStart = 0;                /* �\���͕�����̐擪����           */
    
    
    /*-----------------------------------------------------------------*/
    /**              ������̓��́E�\�����[�v                         **/
    /*-----------------------------------------------------------------*/
    for(;;) {
       /* �Q�o�C�g�����̂����炪�\������Ȃ��悤�Ɉ�U�o�b�t�@�ɐ؂�o�� */
       /* �\���̐擪���Q�o�C�g������TailByte�����ׂ� */
       us_offset = (USHORT)(_jstr_now(InpLine, &InpLine[us_CurrDispStart]));
       memset(usz_dispbuff, 0 , us_LineWidth+2);
       /* �\���̍Ōオ�Q�o�C�g������LeadByte�Ȃ炻���͐؂�o���Ȃ� */
       jmemcpy(usz_dispbuff+us_offset, &InpLine[us_CurrDispStart+us_offset], 
               us_LineWidth-us_offset);
       
       VioWrtCharStr(usz_dispbuff, 
                            us_LineWidth ,us_LineInRow,us_LineInCol,VIO_HANDLE);
       VioSetCurPos(us_LineInRow, 
                            us_LineInCol+us_CurrPos-us_CurrDispStart, VIO_HANDLE);

       if(us_flg_fnameset==0) {
          /* �ʏ���� */
          KbdCharIn(&KeyInfo,IO_WAIT,0);
          Convert_WordStarLikeKey(&KeyInfo, FLAG_MODE_INPUTWIN);
       } else {
          /* �J�����g�t�@�C������}�� */
          KbdFlushBuffer(0);
          KeyInfo.chChar = *puc_fname_ptr;
          puc_fname_ptr++;
          if (KeyInfo.chChar == '\0') us_flg_fnameset = 0;
       }

       switch (KeyInfo.chChar) {
          case ENTER:  /* ���ɓ��͍ς݂����`�F�b�N */
             if(!(us_flg_jump&FLAG_INPUTWIN_NOSTRINGS_OK))
                if (!strlen(InpLine)) break;
          case ESC:    /* �J�[�\���������ďI�� */
             Vio_CursorShape(FLAG_CURSOR_HIDDEN);
             if(us_flg_jump&FLAG_INPUTWIN_MSGBOXCLEAR) ShowFileList();
             return KeyInfo.chChar;
          case PFK:    /****** ����L�[��������Ă���\�� ******/
          case ARROW:  
             switch (KeyInfo.chScan){
                case HOME:  /* �\�����J�[�\�����擪�� */
                case HOME98:
                   us_CurrPos=0;
                   us_CurrDispStart=0;
                   break;
                case END:   /* �\�����J�[�\�����Ō�� */
                   us_CurrPos=us_InpLineLen;
                   if(us_InpLineLen-1 > us_LineWidth) {
                      us_CurrDispStart = us_InpLineLen-us_LineWidth+1;
                   }
                   break;
                case PF1: /* �t�@���N�V�����L�[ */
                case PF2: 
                case PF3: 
                case PF4: 
                case PF5: 
                case PF6: 
                case PF7: 
                case PF8: 
                case PF9: 
                case PF10: 
                case PF11: 
                case PF12: 
                   if (us_flg_jump&FLAG_INPUTWIN_FUNCKEY_ON){
                      Vio_CursorShape(FLAG_CURSOR_HIDDEN);
                      return KeyInfo.chScan;
                   }
                   break;
                case ARROW_UP: /* �����̕\���̂��ߏI�� */
                   if (us_flg_jump&FLAG_INPUTWIN_HISTRY_ON){
                      Vio_CursorShape(FLAG_CURSOR_HIDDEN);
                      return KeyInfo.chScan;
                   }
                   break;
                case ARROW_LEFT:  /* �J�[�\�����ꕶ���O�� */
                   us_offset = (USHORT)(_jstr_dec(InpLine, &InpLine[us_CurrPos]));
                   if(us_offset==0) break;
                   us_CurrPos -=us_offset; 
                   if (us_CurrDispStart > us_CurrPos){
                      us_CurrDispStart = us_CurrPos;
                   }
                   break;
                case ARROW_RIGHT: /* �J�[�\�����ꕶ����� */
                   us_offset = (USHORT)(_jstr_inc(InpLine, &InpLine[us_CurrPos]));
                   if(us_offset==0) break;
                   us_CurrPos+=us_offset;
                   if (us_CurrDispStart+us_LineWidth-1 < us_CurrPos){
                      us_CurrDispStart = us_CurrPos-us_LineWidth+1;
                   }
                   break;
                case DELETE:      /* �J�[�\���ʒu�̕������폜 */ 
                   us_offset = (USHORT)(_jstr_inc(InpLine, &InpLine[us_CurrPos]));
                   if(us_offset==0) break;
                   us_InpLineLen -= us_offset ;
                   memset(&InpLine[us_CurrPos], 0, us_offset);
                   sprintf(InpLine, "%s%s", InpLine, &InpLine[us_CurrPos+us_offset]);
                   memset(&InpLine[us_InpLineLen], 0, us_offset);
                   break;
                case INSERT:      /* �}���^�㏑�����[�h�̃t���O���g�O�� */
                   us_flg_inputmode= !us_flg_inputmode;
                   Vio_CursorShape(us_flg_inputmode);
                   break;
                case ARROW_DOWN:
                case PAGE_UP:
                case PAGE_DOWN:
                   break;
                default:
                   if(KeyInfo.chChar != PFK) goto REIGAI; /* DBCS �̕Њ��� */
                   break;
             }
             break;
          case CTRL_Y:      /* ���͑��̃N���A */
             us_CurrPos=0;
             us_CurrDispStart=0;
             us_InpLineLen = 0; 
             memset(InpLine, 0 , sizeof(InpLine));
             break;
          case BACK:   /* �J�[�\���̈ꕶ���O���폜 */
             us_offset = (USHORT)(_jstr_dec(InpLine, &InpLine[us_CurrPos]));
             if(us_offset==0) break;
             us_CurrPos -= us_offset; 
             us_InpLineLen -= us_offset; 
             memset(&InpLine[us_CurrPos], 0, us_offset);
             sprintf(InpLine, "%s%s", InpLine, &InpLine[us_CurrPos+us_offset]);
             memset(&InpLine[us_InpLineLen], 0, us_offset);
             if (us_CurrDispStart > us_CurrPos){
                us_CurrDispStart = us_CurrPos;
             }
             break;
        REIGAI:
          default: 
             if(us_flg_jump&FLAG_INPUTWIN_TABKEY_ON) {
                if(KeyInfo.chChar=='\t')  {
                   us_flg_fnameset=1;
                   puc_fname_ptr = FlDis[SelFl].Nm+DISP_FN;
                }
             }
             if(KeyInfo.chChar<0x20 || KeyInfo.chChar == 0x7f) break;
             if (us_InpLineLen < us_InpLineSize-1) {
                if(us_flg_inputmode != FLAG_INSERT_MODE) {
                   us_offset = (USHORT)(_jstr_inc(InpLine, &InpLine[us_CurrPos]));
                   /* ���̏�Ɉꕶ���㏑�� */
                   InpLine[us_CurrPos] = KeyInfo.chChar;
                   us_CurrPos++;
                   if(us_InpLineLen < us_CurrPos) us_InpLineLen = us_CurrPos;
                   if(us_offset == 2 && iskanji(KeyInfo.chChar) == FALSE) { 
                      /* �Q�o�C�g�������P�o�C�g�����ŏ㏑�� -> �Q�o�C�g�ڂ��󔒂�*/
                      InpLine[us_CurrPos] = ' ';
                   }
                } else {
                   /* ���̏�Ɉꕶ���}�� */
                   us_InpLineLen++;
                   strcpy(uc_BackupStrings, &InpLine[us_CurrPos]);
                   InpLine[us_CurrPos] = '\0';
                   us_CurrPos++;
                   sprintf(InpLine, "%s%c%s", InpLine, KeyInfo.chChar, uc_BackupStrings);
                }
                if (us_CurrDispStart+us_LineWidth-1 < us_CurrPos)
                   us_CurrDispStart = us_CurrPos-us_LineWidth+1;
             }
             break;
       }
    } 

 }

/****************************************************************/
/**   Vio_CursorShape                                          **/
/****************************************************************/
 void Vio_CursorShape(USHORT us_flg_inputmode)
 {
    VIOCURSORINFO CursorInfo ={0};

    VioGetCurType(&CursorInfo, VIO_HANDLE);
    switch(us_flg_inputmode) {
       case FLAG_INSERT_MODE:
          CursorInfo.yStart=-50;   /* �}�����[�h�Ȃ琳���`�̃J�[�\�� */
          CursorInfo.cEnd  =-100;
          CursorInfo.attr  =0;
          break;
       case FLAG_OVERWRITE_MODE:
          CursorInfo.yStart=0;     /* �㏑�����[�h�Ȃ璷���`�̃J�[�\�� */
          CursorInfo.cEnd  =-100;
          CursorInfo.attr  =0;
          break;
       case FLAG_CURSOR_HIDDEN:   
          CursorInfo.attr  = -1;
          break;
       case FLAG_CURSOR_DISP:
           CursorInfo.attr =0;
    }   
    VioSetCurType(&CursorInfo,VIO_HANDLE);
 }

/****************************************************************/
/**   HistryBox_Set                                            **/
/****************************************************************/
 USHORT HistryBox_Set(USHORT us_flg_dir_hst, USHORT us_listnum)
 {
    USHORT us_count;
    
    switch(us_flg_dir_hst) {
       case FLAG_HISTRY_DIRECTRY:
          strcpy(MsgTxt[0],
                        English ? "The jump directories(Space:Show history of directories)" :
                                  "�W�����v�E�f�B���N�g�� (Space �� �f�B���N�g���̗�����)");
          break;
       case FLAG_HISTRY_COMMAND:
          strcpy(MsgTxt[0],
                        English ? "History of command                                     " :
                                  "�R�}���h�̗���                                        ");
          break;
       case FLAG_HISTRY_PATH:
          strcpy(MsgTxt[0],
                        English ? "History of directories(Space:Show the jump directories)" :
                                  "�f�B���N�g���̗��� (Space �� �W�����v�E�f�B���N�g����)");
          break;
       case FLAG_HISTRY_ASSOCPROG:
          strcpy(MsgTxt[0],
                        English ? "List of registered program for extension               " :
                                  "�g���q�o�^�v���O�����ꗗ                              ");
          break;
    }
    if(us_flg_dir_hst!=FLAG_HISTRY_ASSOCPROG) {
       strcpy(MsgTxt[us_listnum+1],
                          English ? "I/Ins:Regi  D/Del:Dele  Enter:Sele  Esc:Canc  Tab:Next " :
                                    "I/Ins:�o�^  D/Del:�폜  Enter:�I��  Esc:���  Tab:��  ");
    } else {
       strcpy(MsgTxt[us_listnum+1],
                          English ? "                      Enter:Select  Esc:Cancel         " :
                                    "                        Enter:�I��  Esc:���          ");
    }

    for (us_count=1; us_count<us_listnum+1; us_count++)
       strcpy(MsgTxt[us_count],   "                                                      ");
    
    return us_listnum+2;
 }

/****************************************************************/
/**   HistryBox                                                **/
/****************************************************************/
 PUCHAR HistryBox(USHORT us_flg_dir_hst)
 {
    UCHAR  uc_flg_operate;
    USHORT us_histry_number=HISTORY_MAX-1;  /* �Ō�̗��� */
    
    JumpDirRead(us_flg_dir_hst); /* �����t�@�C���̓ǂݍ��� */
    for(;;) {
       ShowMsgBox(HistryBox_Set(us_flg_dir_hst, HISTORY_MAX), 
                  bt_g_NormalWindowColor);
       uc_flg_operate=HistryBoxDisp(&us_histry_number, HISTORY_MAX);
    
       switch(uc_flg_operate){
          case ENTER:
             ShowFileList();
             return ListTxt[us_histry_number]+2;
          case 'i': 
          case 'I':
             ShowFileList();
             HistryInsert(us_flg_dir_hst, us_histry_number);
             break;
          case 'd': 
          case 'D':
             ShowFileList();
             HistryDelete(us_flg_dir_hst, us_histry_number); 
             break;
          case ESC: 
             ShowFileList();
             return InpLine;
          case '\t':
             switch(us_flg_dir_hst) {
                case FLAG_HISTRY_DIRECTRY:
                   us_flg_dir_hst=FLAG_HISTRY_COMMAND;
                   break;
                case FLAG_HISTRY_PATH:
                   us_flg_dir_hst=FLAG_HISTRY_DIRECTRY;
                   break;
                case FLAG_HISTRY_COMMAND:
                   us_flg_dir_hst=FLAG_HISTRY_PATH;
                   break;
             }
             JumpDirRead(us_flg_dir_hst); /* �����t�@�C���̓ǂݍ��� */
             break;
          case ' ':
             switch(us_flg_dir_hst) {
                case FLAG_HISTRY_DIRECTRY:
                   us_flg_dir_hst=FLAG_HISTRY_PATH;
                   break;
                case FLAG_HISTRY_PATH:
                   us_flg_dir_hst=FLAG_HISTRY_DIRECTRY;
                   break;
             }
             JumpDirRead(us_flg_dir_hst); /* �����t�@�C���̓ǂݍ��� */
             break;
       }
    }
 }

/*****************************************************************/
/**   HistryBoxDisp                                             **/
/*****************************************************************/
 UCHAR HistryBoxDisp(PUSHORT pus_histry_number, USHORT us_max_listnum)
 {
    USHORT us_count,  us_hist_back;
    
    for (us_count=0; us_count<us_max_listnum; us_count++) {
       if(*pus_histry_number == us_count) {
          VioWrtCharStrAtt(ListTxt[us_count], BoxWide-6, 
                           BoxTop+us_count+3, BoxLeft+3, 
                           &bt_g_HistryWindowCursorColor, VIO_HANDLE);
       } else {
          VioWrtCharStrAtt(ListTxt[us_count], BoxWide-6, 
                           BoxTop+us_count+3, BoxLeft+3, 
                           &bt_g_HistryWindowColor, VIO_HANDLE);
       }
    }
    
    us_hist_back = *pus_histry_number;
    
    for(;;) {
       KbdCharIn(&KeyInfo,IO_WAIT,0);
       Convert_WordStarLikeKey(&KeyInfo, FLAG_MODE_HISTORY);

       switch(KeyInfo.chChar){
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
             us_hist_back = *pus_histry_number;
             *pus_histry_number = KeyInfo.chChar-0x31;
             if(*pus_histry_number>=us_max_listnum) {
                *pus_histry_number=us_hist_back;
                break;
             }
          case ENTER:
             if(*pus_histry_number>=us_max_listnum) break;
             if (ListTxt[*pus_histry_number][2]!=0
                       &&ListTxt[*pus_histry_number][2]!=' ') {
                return ENTER;
             }
             break;
          case ESC: 
          case 'i': 
          case 'I': 
          case 'd': 
          case 'D': 
          case '\t':
          case ' ':
             return KeyInfo.chChar;
          case PFK: 
          case ARROW: 
             switch(KeyInfo.chScan){
                case ARROW_UP:
                   us_hist_back = *pus_histry_number;
                   if (*pus_histry_number>0) {
                      (*pus_histry_number) -=1;
                   }else{
                      (*pus_histry_number) =us_max_listnum-1;
                   }
                   break;
                case ARROW_DOWN:
                   us_hist_back = *pus_histry_number;
                   if (*pus_histry_number<us_max_listnum-1) {
                      (*pus_histry_number) +=1;
                   }else{
                      (*pus_histry_number) =0;
                   }
                   break;
                case PAGE_UP:
                case HOME:
                case HOME98:
                   us_hist_back = *pus_histry_number;
                   (*pus_histry_number) = 0;
                   break;
                case PAGE_DOWN:
                case END:
                   us_hist_back = *pus_histry_number;
                   (*pus_histry_number) = us_max_listnum-1;
                   break;
                case INSERT: 
                   return 'i'; 
                case DELETE: 
                   return 'd'; 
                case PF3:
                   return ESC;
             }
       
       }
       if(us_hist_back != *pus_histry_number) {
          VioWrtCharStrAtt(ListTxt[*pus_histry_number], BoxWide-6, 
                           BoxTop+(*pus_histry_number)+3, BoxLeft+3, 
                           &bt_g_HistryWindowCursorColor, VIO_HANDLE);
          VioWrtCharStrAtt(ListTxt[us_hist_back], BoxWide-6, 
                           BoxTop+us_hist_back+3, BoxLeft+3, 
                           &bt_g_HistryWindowColor, VIO_HANDLE);
       }
    }  
 }

/****************************************************************/
/**   HistryDelete                                             **/
/****************************************************************/
 void HistryDelete(USHORT us_flg_dir_hst, USHORT us_histry_number)
 {
    switch(us_flg_dir_hst) { 
       case FLAG_HISTRY_DIRECTRY:
       case FLAG_HISTRY_PATH:
          strcpy(MsgTxt[0],
                 English ? "Remove a directory in the list.     " :
                           "�o�^�ς݂̃f�B���N�g�����폜���܂�  ");
          break;
       case FLAG_HISTRY_COMMAND:
          strcpy(MsgTxt[0],
                 English ? "Remove a command in the list.       " :
                           "�o�^�ς݂̃R�}���h���폜���܂�      ");
          break;
    }
    strcpy(MsgTxt[1],"                                    ");
    strcpy(MsgTxt[2],"                                    ");
    strcpy(MsgTxt[3],
           English ? "       Enter:OK    Esc:Cancel       " :
                     "       Enter:���s    Esc:���       ");

    strcpy(MsgTxt[1], ListTxt[us_histry_number]+2);

    if(GetYesorNo_withMsgBox(ENTER, 4, bt_g_NormalWindowColor,
            FLAG_GETYESORNO_MSGBOXCLEAR)==ESC) return;

    memset(ListTxt[us_histry_number]+2, 0, sizeof(ListTxt[us_histry_number])-2);
    JumpDirSaveFunc(us_flg_dir_hst);
 }

/****************************************************************/
/**   HistryInsert                                             **/
/****************************************************************/
 VOID HistryInsert(USHORT us_flg_dir_hst, USHORT us_histry_number)
 {
    PUCHAR  puc_drivepath, puc_inputwinstr;
    UCHAR   usz_currdir[_MAX_PATH];
    
    switch(us_flg_dir_hst) { 
       case FLAG_HISTRY_DIRECTRY:
       case FLAG_HISTRY_PATH:
          SetFullCurrentPathName(usz_currdir); 
          puc_inputwinstr=usz_currdir;
          strcpy(MsgTxt[0],
                 English ? "Register a new directory.             " :
                           "�f�B���N�g���̓o�^                    ");
          break;
       case FLAG_HISTRY_COMMAND:
          puc_inputwinstr=NULL;
          strcpy(MsgTxt[0],
                 English ? "Register a new command.               " :
                           "�R�}���h�̓o�^                        ");
          break;
    }
    strcpy(MsgTxt[1],"                                      ");
    strcpy(MsgTxt[2],"                                      ");
    strcpy(MsgTxt[3],"                                      ");
    strcpy(MsgTxt[4],
           English ? "       Enter:OK      Esc:Cancel       " :
                     "        Enter:���s    Esc:���        ");

    if(KbdLineIn(5, bt_g_NormalWindowColor, 2, puc_inputwinstr, 
                 FLAG_INPUTWIN_NO_OPTION)==ESC) {
       ShowFileList();
    } else {
       puc_drivepath = InpLine + strspn(InpLine, " "); /* ���̋󔒂��΂� */
       memset(ListTxt[us_histry_number]+2, 0, sizeof(ListTxt[us_histry_number])-2);
       strcpy(ListTxt[us_histry_number]+2, puc_drivepath);
       JumpDirSaveFunc(us_flg_dir_hst);
    }
 }

/*****************************************************************/
/**   MacroDisp_Show                                            **/
/*****************************************************************/
 void MacroDisp_Show(VOID)
 {
    USHORT us_count;
 
    /* MsgTxt[0]��65�����łȂ��Ƃ����Ȃ� */
    memset(MsgTxt[0],0,sizeof(MsgTxt[0]));    
    strcpy(MsgTxt[0],
            English ? "Execute macro [Shift+]                                           " :
                      "�}�N���̎��s [Shift+]                                            "); 
    
    for (us_count=1; us_count<14; us_count++) {
       memset(MsgTxt[us_count], 0, sizeof(MsgTxt[us_count])); /* �O�̎c�[������ */
       if (MacroProg[us_count-1].uszProgName[0]!=0){
          sprintf(MsgTxt[us_count],    "%cSS%d:%s %s", us_count+64,  
                                        MacroProg[us_count-1].usSession, 
                                        MacroProg[us_count-1].uszProgName,  
                                        MacroProg[us_count-1].uszParamList);
          if(MacroProg[us_count-1].usSilent == 1)  MsgTxt[us_count][2] ='Q';
       } else {
          sprintf(MsgTxt[us_count],    "%c", us_count+64);
       }

       memset(MsgTxt[us_count]+33, 0, sizeof(MsgTxt[us_count])-34); /* �O�̎c�[������ */
       if (MacroProg[us_count+12].uszProgName[0]!=0){
          sprintf(MsgTxt[us_count]+33,  "%cSS%d:%s %s", us_count+77,  
                                        MacroProg[us_count+12].usSession, 
                                        MacroProg[us_count+12].uszProgName,  
                                        MacroProg[us_count+12].uszParamList);
          if(MacroProg[us_count+12].usSilent == 1)  MsgTxt[us_count][35] ='Q';
       } else {
          sprintf(MsgTxt[us_count]+33, "%c", us_count+77);
       }
    }
    ShowMsgBox(14, bt_g_NormalWindowColor);

    for (us_count=1;us_count<14; us_count++) {
       VioWrtCharStrAtt(MsgTxt[us_count],   1, BoxTop+2+us_count, BoxLeft+3, 
                        &bt_g_WindowKeyWordColor,VIO_HANDLE);
       VioWrtCharStrAtt(MsgTxt[us_count]+33,1, BoxTop+2+us_count, BoxLeft+36,
                        &bt_g_WindowKeyWordColor,VIO_HANDLE);
    }
}

/*****************************************************************/
/**   MacroDisp                                                 **/
/*****************************************************************/
 void MacroDisp(ULONG ul_markfilenum)
 {
    ULONG ul_rcMacroFunc;
    
    MacroDisp_Show();
    for (;;) {
       KbdCharIn(&KeyInfo,IO_WAIT,0);
       if ((KeyInfo.chChar==ESC)||KeyInfo.chScan==PF4) {
          ShowFileList();
          return;
       }
       if(isalpha(KeyInfo.chChar)) {
          ShowFileList();
          ul_rcMacroFunc = MacroFunc(KeyInfo.chChar, ul_markfilenum);
          if(ul_rcMacroFunc != MYFUNC_NOT_EXEC) return;
          MacroDisp_Show();
       }
    }
 }

/*****************************************************************/
/**   MacroFunc                                                 **/
/*****************************************************************/
 ULONG MacroFunc(UCHAR uc_inputchar, ULONG ul_markfilenum)
 {
    USHORT us_MacroNumber;  /* 0-25 �̐���, A-Z �ɑΉ� */

    us_MacroNumber = uc_inputchar>'Z' ? uc_inputchar-97 : uc_inputchar-65;

    if (MacroProg[us_MacroNumber].uszProgName[0]==0) return MYFUNC_NOT_EXEC;
    ExecAssocProgram_MsgBox(FlDis[SelFl].Nm+DISP_FN, 
                   MacroProg[us_MacroNumber].uszProgName, 
                   MacroProg[us_MacroNumber].uszParamList,
                   MacroProg[us_MacroNumber].usSilent,
                   MacroProg[us_MacroNumber].usSession,                   
                   AutoClose, FLAG_NO_MARK, 
                   ul_markfilenum, FLAG_EXECPROG_KEYMACRO);

    QDriveSize();
    return MYFUNC_EXEC;
 }


/*****************************************************************/
/**   MacroSetup                                                **/
/*****************************************************************/
 void MacroSetup(PSZ IniFileIn)
 {
    USHORT us_MacroNumber;  /* 0-25 �̐���, A-Z �ɑΉ� */
    PUCHAR puc_strptr;

    if(!(puc_strptr=SetupGlobalFlag_SearchValuePtr(IniFileIn, "Shift+"))) {
       return;
    }
    if (!isalpha(*puc_strptr)) return;

    us_MacroNumber = *puc_strptr>'Z' ? *puc_strptr-97 : *puc_strptr-65;
    SetupMacroProgram(puc_strptr+2, &MacroProg[us_MacroNumber]);
 
 }


/*****************************************************************/
/**   MakeIcon                                                  **/
/*****************************************************************/
 void MakeIcon(PSZ psz_IconFilename, USHORT us_flg_markfile)
 {
    if(!FlCnt) return;
    if(!strcmp(psz_IconFilename, ".") ||!strcmp(psz_IconFilename, "..")) return;

    if (CheckExtention(psz_IconFilename,".exe")
      ||CheckExtention(psz_IconFilename,".cmd")
      ||CheckExtention(psz_IconFilename,".com")
      ||CheckExtention(psz_IconFilename,".bat")) {
       if (us_flg_markfile == FLAG_MARK) 
          MakePrgIconFunc(psz_IconFilename, FLAG_EXE_EXTENSION); 
       else 
          MakePrgIcon(psz_IconFilename, FLAG_EXE_EXTENSION);
       return;
    } 
    
    if (CheckExtention(psz_IconFilename,".inf")) {
       if (us_flg_markfile == FLAG_MARK) 
          MakePrgIconFunc(psz_IconFilename, FLAG_INF_EXTENSION); 
       else 
          MakePrgIcon(psz_IconFilename, FLAG_INF_EXTENSION);
       return;
    } 
    
    if (us_flg_markfile == FLAG_MARK) 
       MakeShadowIconFunc(psz_IconFilename); 
    else 
       MakeShadowIcon(psz_IconFilename);
    return;
 }

/*****************************************************************/
/**   MakeShadowIcon                                            **/
/*****************************************************************/
 void MakeShadowIcon(PSZ psz_IconFilename)
 {
    if(English){
       strcpy(MsgTxt[0],"Create a shadow icon to the desktop.");
       strcpy(MsgTxt[1],"Object:                             ");
       strcpy(MsgTxt[2],"                                    ");
       strcpy(MsgTxt[3],"       Enter:OK    Esc:Cancel       ");
    }
    else{
       strcpy(MsgTxt[0],"�޽�į�߂ɼ��޳���݂�o�^���܂�");
       strcpy(MsgTxt[1],"Object:                        ");
       strcpy(MsgTxt[2],"                               ");
       strcpy(MsgTxt[3],"     Enter:���s    Esc:���    ");
    }
    
    strcpy(MsgTxt[1]+7, psz_IconFilename);
    
    if(GetYesorNo_withMsgBox(ENTER, 4, bt_g_NormalWindowColor,
            FLAG_GETYESORNO_MSGBOXCLEAR)==ESC) return;

    if (MakeShadowIconFunc(psz_IconFilename) != NULLHANDLE) 
       ShowMsgIconOk();
    else 
       ShowMsgIconErr();

 }

/*****************************************************************/
/**   MakeShadowIconFunc                                        **/
/*****************************************************************/
 HOBJECT MakeShadowIconFunc(PSZ psz_IconFilename)
 {
    UCHAR uc_ObjSetupString[_MAX_PATH], FulDirNm[_MAX_PATH];

    /* DLL�̃��[�h�̃`�F�b�N */
    if(!pfnCreateObject) return NULLHANDLE; 

    SetFullDirName(FulDirNm);
    sprintf(uc_ObjSetupString,"SHADOWID=%s%s;", FulDirNm, psz_IconFilename);

    return pfnCreateObject("WPShadow",         /* ObjectClass��                  */
                           "",                 /* Object�̃^�C�g��<-�����I�ɐݒ� */
                           uc_ObjSetupString,  /* Setup �p�����[�^               */
                           "<WP_DESKTOP>",     /* Object�����ꏊ               */
                           CO_FAILIFEXISTS);   /* Object�����ɂ���ꍇ�͍��Ȃ� */
 }

/*****************************************************************/
/**   MakePrgIcon                                               **/
/*****************************************************************/
 void MakePrgIcon(PSZ psz_IconFilename, USHORT us_flg_extension)
 {
    PCHAR  pc_priod_ptr;
    UCHAR  usz_icontitle[_MAX_PATH];
    
    if(us_flg_extension == FLAG_INF_EXTENSION) {
       strcpy(MsgTxt[0],
              English ? "Create a INF icon to the desktop.           " :
                        "�f�X�N�g�b�v�ɂh�m�e�A�C�R����o�^���܂�    ");
    } else {
       strcpy(MsgTxt[0],
              English ? "Create a program icon to the desktop.       " :
                        "�f�X�N�g�b�v�Ƀv���O�����A�C�R����o�^���܂�");
    }
    strcpy(MsgTxt[1],"Object:                                     ");
    strcpy(MsgTxt[2],"                                            ");
    strcpy(MsgTxt[3],
           English ? "Enter title(^ is a line feed).              " :
                     "�^�C�g�����w�肵�ĉ������i���s��^)          ");
    strcpy(MsgTxt[4],"                                            ");
    strcpy(MsgTxt[5],"                                            ");
    strcpy(MsgTxt[6],
           English ? "          Enter:OK      Esc:Cancel          " :
                     "       Enter:���s     Esc:���              ");

    strcpy(MsgTxt[1]+7, psz_IconFilename);
    
    pc_priod_ptr=strrchr(psz_IconFilename, '.');
    if(pc_priod_ptr) {
       *pc_priod_ptr='\0'; 
       strcpy(usz_icontitle, psz_IconFilename);
       *pc_priod_ptr='.'; 
    } else {
       strcpy(usz_icontitle, psz_IconFilename);
    }

    if(KbdLineIn(7, bt_g_NormalWindowColor, 4, usz_icontitle,
                 FLAG_INPUTWIN_MSGBOXCLEAR) == ESC) return;
    
    if (MakePrgIconFunc(psz_IconFilename, us_flg_extension) != NULLHANDLE)  
       ShowMsgIconOk();
    else  
       ShowMsgIconErr();

 }

/*****************************************************************/
/**   MakePrgIconFunc                                           **/
/*****************************************************************/
 HOBJECT MakePrgIconFunc(PSZ psz_IconFilename, USHORT us_flg_extension)
 {
    UCHAR uc_ObjSetupString[_MAX_PATH], FulDirNm[_MAX_PATH];

    /* DLL�̃��[�h�̃`�F�b�N */
    if(!pfnCreateObject) return NULLHANDLE; 
 
    SetFullDirName(FulDirNm);
    if(us_flg_extension == FLAG_INF_EXTENSION) {
       sprintf(uc_ObjSetupString,"EXENAME=VIEW.EXE;PARAMETERS=%s%s;", 
                                     FulDirNm, psz_IconFilename);
    } else {
       sprintf(uc_ObjSetupString,"EXENAME=%s%s;", FulDirNm, psz_IconFilename);
    }

    return pfnCreateObject("WPProgram",       /* ObjectClass��                  */
                           InpLine,           /* Object�̃^�C�g�� <- ���͕���   */
                           uc_ObjSetupString, /* Setup �p�����[�^               */
                           "<WP_DESKTOP>",    /* Object�����ꏊ               */
                           CO_FAILIFEXISTS);  /* Object�����ɂ���ꍇ�͍��Ȃ� */
 }

/****************************************************************/
/**   MarkFileCopy                                             **/
/****************************************************************/
 void MarkFileCopy(ULONG ul_markcnt)
 {
    UCHAR  uc_inputchar;
    USHORT us_dummy, us_flg_inthedir=0, us_flg_dir=1;
    APIRET apr_filecopy=0;
    ULONG  FlCntSv, im, ul_count;
    PUCHAR puc_inputwinstr=NULL;

    for (ul_count=0; ul_count<FlCnt&&us_flg_dir==1; ul_count++) {
       if (FlDis[ul_count].Mark) {
          if(!(FlDis[ul_count].Atr&FILE_DIRECTORY)) us_flg_dir=0;
       }
    }
    
    do {
       if(us_flg_dir == 1) {
          if(English){
             strcpy(MsgTxt[0],"Copy marked directories.                          ");
             strcpy(MsgTxt[1],"  - [F1]Copy contents of directories              ");
          }
          else{
             strcpy(MsgTxt[0],"���}�[�N���ꂽ�f�B���N�g�����R�s�[���܂�          ");
             strcpy(MsgTxt[1],"  ��[F1]�f�B���N�g���̒��g���R�s�[����            ");
          }
          Change_FlagMark(us_flg_inthedir, 1, 2);
       } else {
          if(English){
             strcpy(MsgTxt[0],"Copy marked files.                                ");
             strcpy(MsgTxt[1],"                                                  ");
          }
          else{
             strcpy(MsgTxt[0],"���}�[�N�t�@�C�����R�s�[���܂�                    ");
             strcpy(MsgTxt[1],"                                                  ");
          }
       }
       strcpy(MsgTxt[2],"                                                  ");
       strcpy(MsgTxt[3],
              English ? "Enter destination directory(Up arrow key:history)." :
                        "�R�s�[����w�肵�ĉ�����            (������˽�ذ) ");
       strcpy(MsgTxt[4],"                                                  ");
       strcpy(MsgTxt[5],"                                                  ");
       strcpy(MsgTxt[6],
              English ? "           Enter:OK          Esc:Cancel           " :
                        "            Enter:���s      Esc:���              ");
    
       uc_inputchar = KbdLineIn(7, bt_g_NormalWindowColor, 4, puc_inputwinstr,
                         FLAG_INPUTWIN_HISTRY_ON|FLAG_INPUTWIN_MSGBOXCLEAR|
                         FLAG_INPUTWIN_FUNCKEY_ON);   
       switch(uc_inputchar) {
          case ESC:
             return;
          case ENTER:
             break;
          case PF1:             
             if(us_flg_dir==1) {   
                 us_flg_inthedir = !us_flg_inthedir; 
                 puc_inputwinstr=InpLine;            
             }                                       
             break;                                  
          default:
             puc_inputwinstr=HistryBox(FLAG_HISTRY_PATH);
       }
    }while(uc_inputchar!=ENTER);

    apr_filecopy=FileCopy_ConverttoAbsolutePath(InpLine);
    if(apr_filecopy) {    
       FileCopyRc(apr_filecopy);
       return;
    }

    if(SameDriveCheck(&us_dummy)) return; /* ���͕������s�� */
    for (ul_count=0; ul_count<FlCnt; ul_count++){
       if (FlDis[ul_count].Mark){
          if(SameDirCheck(FlDis[ul_count].Nm+DISP_FN)) return;
       }
    }

    OverWrite=RESET;
    us_g_flg_readonly=READONLY_RESET;
    
    FlCntSv=FlCnt;
    for (ul_count=0; ul_count<FlCnt; ul_count++){
       SvDis[ul_count].Mark=FlDis[ul_count].Mark; 
       SvDis[ul_count].Atr=FlDis[ul_count].Atr;
       strcpy(SvDis[ul_count].Nm, FlDis[ul_count].Nm+DISP_FN); 
       memcpy(SvDis[ul_count].Time, FlDis[ul_count].Nm+DISP_DT, (DISP_MK-DISP_DT));
    }
    
    FirstDisp=1;
    for (im=0; im<FlCntSv&&!apr_filecopy&&KeyInfo.chChar!=ESC; ++im) 
       if (SvDis[im].Mark){
          KbdCharIn(&KeyInfo,IO_NOWAIT,0);
          if (SvDis[im].Atr&FILE_DIRECTORY) {
             apr_filecopy=FileCopyDir(SvDis[im].Nm, FLAG_COPY_ONLY, us_flg_inthedir);
          } else {
             apr_filecopy=FileCopyFl(SvDis[im].Nm, SvDis[im].Time, 
                                     FLAG_COPY_ONLY, ul_markcnt);
          }
       /*QDriveSize();*/
    }
    QFile();
    ShowFileList();
    FileCopyRc(apr_filecopy);
    JumpHistInsert(FLAG_HISTRY_PATH, InpLine);
 }

/****************************************************************/
/**   MarkFileDelete                                           **/
/****************************************************************/
 void MarkFileDelete(void)
 {
    APIRET apr_FileDelFunc=NO_ERROR;
    ULONG  FlCntSv, ul_count;
    
    if(English){
       strcpy(MsgTxt[0],"Delete marked files.        ");
       strcpy(MsgTxt[1],"                            ");
       strcpy(MsgTxt[2],"  Y:yes(Space)   N:no(Esc)  ");
    }
    else{
       strcpy(MsgTxt[0],"���}�[�N�t�@�C�����폜���܂�");
       strcpy(MsgTxt[1],"                            ");
       strcpy(MsgTxt[2]," �x:yes(Space)   �m:no(Esc) ");
    }
 
    if(GetYesorNo_withMsgBox(' ', 3, bt_g_NormalWindowColor,
            FLAG_GETYESORNO_MSGBOXCLEAR)==ESC) return;

    FlCntSv=FlCnt;
    for (ul_count=0; ul_count<FlCnt; ul_count++){
       SvDis[ul_count].Mark=FlDis[ul_count].Mark; 
       strcpy(SvDis[ul_count].Nm, FlDis[ul_count].Nm+DISP_FN); 
       SvDis[ul_count].Atr=FlDis[ul_count].Atr;
    }

    FileDeleteFuncDisp(FLAG_FIRST, "");
    for (ul_count=0; ul_count<FlCntSv; ul_count++) {
       if (SvDis[ul_count].Mark){
          KbdCharIn(&KeyInfo,IO_NOWAIT,0);
          apr_FileDelFunc=FileDeleteFunc(SvDis[ul_count].Nm, SvDis[ul_count].Atr);
          QDriveSize();
       }
       if(apr_FileDelFunc || KeyInfo.chChar==ESC) break;
    }
    ReDrawAfterDelete();
    FileDeleteRc(apr_FileDelFunc);
 }

/****************************************************************/
/**   MarkFileExec                                             **/
/****************************************************************/
 void MarkFileExec(void)
 {
    ULONG  ul_count;

    if(English){
       strcpy(MsgTxt[0],"        Execute marked files.       ");
       strcpy(MsgTxt[1],"   (Only registered of extension)   ");
       strcpy(MsgTxt[2],"                                    ");
       strcpy(MsgTxt[3],"      Y:yes(Enter)   N:no(Esc)      ");
    }
    else{
       strcpy(MsgTxt[0],"���}�[�N�t�@�C���̘A�����s���s���܂�");
       strcpy(MsgTxt[1],"   (�g���q�֘A�t����۸��т̂�)      ");
       strcpy(MsgTxt[2],"                                    ");
       strcpy(MsgTxt[3],"     �x:yes(Enter)   �m:no(Esc)     ");
    }

    if(GetYesorNo_withMsgBox(ENTER, 4, bt_g_NormalWindowColor,
            FLAG_GETYESORNO_MSGBOXCLEAR)==ESC) return;

    for (ul_count=0; ul_count<FlCnt; ul_count++) {
       KbdCharIn(&KeyInfo, IO_NOWAIT, 0);
       if(KeyInfo.chChar==ESC) break;

       if (FlDis[ul_count].Mark) {
          if (!(FlDis[ul_count].Atr&FILE_DIRECTORY)){
             if(ExecAssocProgram(FLAG_MARK, FlDis[ul_count].Nm+DISP_FN)
                               ==MYFUNC_EXEC) {
                DosSleep(500L);  /* �N�����I������܂ő҂��Ȃ��Ƃ����Ȃ� */
             }
          }
       }
    }

    /* ����Z�b�V�����Ńv���O���������s���ꂽ�\��������̂� */
    /* �t�@�C�����X�g�����łȂ���ʑS�̂�\��������           */
    ShowFileList_PrevFile(FLAG_DRAW_SCREEN, FlDis[SelFl].Nm+DISP_FN);
 }

/****************************************************************/
/**   MarkFileMove                                             **/
/****************************************************************/
 void MarkFileMove(ULONG ul_markcnt)
 {
    UCHAR  uc_inputchar;
    ULONG  FlCntSv, im, ul_count; 
    USHORT us_flg_copydelmove, us_flg_samedrive, us_flg_dir=1, us_flg_inthedir=0;
    APIRET apr_filemove=0;
    PUCHAR puc_inputwinstr=NULL;
    
    for (ul_count=0; ul_count<FlCnt&&us_flg_dir==1; ul_count++) {
       if (FlDis[ul_count].Mark) {
          if(!(FlDis[ul_count].Atr&FILE_DIRECTORY)) us_flg_dir=0;
       }
    }

    do {
       if(us_flg_dir == 1) {
          if(English){
             strcpy(MsgTxt[0],"Move marked directories.                          ");
             strcpy(MsgTxt[1],"  - [F1]Move contents in directories              ");
          }
          else{
             strcpy(MsgTxt[0],"���}�[�N���ꂽ�f�B���N�g�����ړ����܂�            ");
             strcpy(MsgTxt[1],"  ��[F1]�f�B���N�g���̒��g���ړ�����              ");
          }
          Change_FlagMark(us_flg_inthedir, 1, 2);
       } else {
          if(English){
             strcpy(MsgTxt[0],"Move marked files.                                ");
             strcpy(MsgTxt[1],"                                                  ");
          }
          else{
             strcpy(MsgTxt[0],"���}�[�N�t�@�C�����ړ����܂�                      ");
             strcpy(MsgTxt[1],"                                                  ");
          }
       }
       strcpy(MsgTxt[2],"                                                  ");
       strcpy(MsgTxt[3],
              English ? "Enter destination directory(Up arrow key:history)." :
                        "�ړ�����w�肵�ĉ�����              (������˽�ذ) ");
       strcpy(MsgTxt[4],"                                                  ");
       strcpy(MsgTxt[5],"                                                  ");
       strcpy(MsgTxt[6],
              English ? "           Enter:OK          Esc:Cancel           " :
                        "            Enter:���s   Esc:���                 ");

       uc_inputchar = KbdLineIn(7, bt_g_NormalWindowColor, 4, puc_inputwinstr,
                         FLAG_INPUTWIN_HISTRY_ON|FLAG_INPUTWIN_MSGBOXCLEAR|
                         FLAG_INPUTWIN_FUNCKEY_ON);   
       switch(uc_inputchar) {
          case ESC:
             return;
          case ENTER:
             break;
          case PF1:             
             if(us_flg_dir==1) {   
                 us_flg_inthedir = !us_flg_inthedir; 
                 puc_inputwinstr=InpLine;            
             }                                       
             break;                                  
          default:
             puc_inputwinstr=HistryBox(FLAG_HISTRY_PATH);
       }
    }while(uc_inputchar!=ENTER);
    
    apr_filemove=FileCopy_ConverttoAbsolutePath(InpLine);
    if(apr_filemove) {    
       FileCopyRc(apr_filemove);
       return;
    }

    if(SameDriveCheck(&us_flg_samedrive)) return; /* ���͕������s�� */
    if(us_flg_samedrive) {
       us_flg_copydelmove=FLAG_MOVE_SAMEDRIVE;
    } else {
       us_flg_copydelmove=FLAG_COPY_DELETE;
    }
    for (ul_count=0; ul_count<FlCnt; ul_count++){
       if (FlDis[ul_count].Mark){
          if(SameDirCheck(FlDis[ul_count].Nm+DISP_FN)) return;
       }
    }


    OverWrite=RESET;
    us_g_flg_readonly=READONLY_RESET;


    FlCntSv=FlCnt;
    for (ul_count=0; ul_count<FlCnt; ul_count++){
       SvDis[ul_count].Mark=FlDis[ul_count].Mark;
       SvDis[ul_count].Atr=FlDis[ul_count].Atr;
       strcpy(SvDis[ul_count].Nm, FlDis[ul_count].Nm+DISP_FN); 
       memcpy(SvDis[ul_count].Time, FlDis[ul_count].Nm+DISP_DT, (DISP_MK-DISP_DT)); 
    }
    
    FirstDisp=1;
    for (im=0;im<FlCntSv&&!apr_filemove&&KeyInfo.chChar!=ESC;++im) 
       if (SvDis[im].Mark){
          KbdCharIn(&KeyInfo,IO_NOWAIT,0);
          if (SvDis[im].Atr&FILE_DIRECTORY) {
             apr_filemove=FileCopyDir(SvDis[im].Nm, us_flg_copydelmove, us_flg_inthedir);
             if(!apr_filemove) DosDeleteDir(SvDis[im].Nm);
          } else {
             apr_filemove=FileCopyFl(SvDis[im].Nm, SvDis[im].Time, 
                                     us_flg_copydelmove, ul_markcnt);
          }
          if (apr_filemove) {
             if (KeyInfo.chChar!=ESC) FileCopyRc(apr_filemove);
             return;
          }
       QDriveSize();
    }

    ReDrawAfterDelete();
    if (KeyInfo.chChar==ESC) ShowMsgMoveStop();
    JumpHistInsert(FLAG_HISTRY_PATH, InpLine);
 }

/****************************************************************/
/**   MarkFileIcon                                             **/
/****************************************************************/
 void MarkFileIcon(void)
 {
    ULONG  ul_count;

    if(English){
       strcpy(MsgTxt[0],"Create icons of marked files.        ");
       strcpy(MsgTxt[1],"                                     ");
       strcpy(MsgTxt[2],"      Y:yes(Enter)   N:no(Esc)       ");
    }
    else{
       strcpy(MsgTxt[0],"��ϰ�̧�ق̘A���A�C�R���o�^���s���܂�");
       strcpy(MsgTxt[1],"                                     ");
       strcpy(MsgTxt[2],"     �x:yes(Enter)   �m:no(Esc)      ");
    }

    if(GetYesorNo_withMsgBox(ENTER, 3, bt_g_NormalWindowColor,
            FLAG_GETYESORNO_MSGBOXCLEAR)==ESC) return;

    ShowMsgIconReg();
    for (ul_count=0; ul_count<FlCnt; ul_count++) {
       if (FlDis[ul_count].Mark) MakeIcon(FlDis[ul_count].Nm+DISP_FN, FLAG_MARK);
    }
    QFile(); 
    ShowFileList();
 }

/****************************************************************/
/**  ObjectCopy_HPFS_FAT                                        */
/****************************************************************/
void ObjectCopy_HPFS_FAT(PSZ psz_filename, ULONG ul_MarkFileNum)
 {
    UCHAR uc_inputchar;
    PUCHAR puc_inputwinstr=NULL;
 
    if(!FlCnt) return ;
    if(ul_MarkFileNum == 0) {
       if(!strcmp(psz_filename, ".") || !strcmp(psz_filename, "..")) return;
    }

    do {
       if(English){
          strcpy(MsgTxt[0],"Copy file(s) between HPFS and FAT.                ");
          strcpy(MsgTxt[1]," File:                                            ");
          strcpy(MsgTxt[2],"                                                  ");
          strcpy(MsgTxt[3],"Enter destination directory(Up arrow key:history).");
          strcpy(MsgTxt[4],"                                                  ");
          strcpy(MsgTxt[5],"                                                  ");
          strcpy(MsgTxt[6],"            Enter:OK        Esc:Cancel            ");
       }
       else{
          strcpy(MsgTxt[0],"HPFS <-> FAT �Ԃ̃t�@�C���R�s�[���s�Ȃ��܂�       ");
          strcpy(MsgTxt[1]," File:                                            ");
          strcpy(MsgTxt[2],"                                                  ");
          strcpy(MsgTxt[3],"�R�s�[����t���p�X�Ŏw�肵�ĉ�����  (������˽�ذ) ");
          strcpy(MsgTxt[4],"                                                  ");
          strcpy(MsgTxt[5],"                                                  ");
          strcpy(MsgTxt[6],"           Enter:���s         Esc:���            ");
       }

       if(ul_MarkFileNum==0) {
          strcpy(MsgTxt[1]+6, psz_filename);
       } else {
          strcpy(MsgTxt[1]+6,
                    English ? "Marked files" :
                              "�}�[�N�t�@�C��");
       }

       uc_inputchar = KbdLineIn(7, bt_g_NormalWindowColor, 4, puc_inputwinstr,
                         FLAG_INPUTWIN_HISTRY_ON|FLAG_INPUTWIN_MSGBOXCLEAR); 
       switch(uc_inputchar) {
          case ESC:
             return;
          case ENTER:
             break;
          default:
             puc_inputwinstr=HistryBox(FLAG_HISTRY_PATH);
       }
    }while(uc_inputchar!=ENTER);
    
    if(ul_MarkFileNum==0) {
       ObjectCopy_HPFS_FAT_CurrentFile(psz_filename, InpLine);
    } else {
       ObjectCopy_HPFS_FAT_MarkFile(InpLine);
    }
 }

/****************************************************************/
/**  ObjectCopy_HPFS_FAT_CurrentFile                            */
/****************************************************************/
VOID ObjectCopy_HPFS_FAT_CurrentFile(PSZ psz_filename_from, 
                                     PSZ psz_dirname_to)
 {
    USHORT us_flg_objcpy;

    FirstDisp=1;
    FileCopyFuncDisp(psz_filename_from, FLAG_COPY_ONLY);
    us_flg_objcpy = ObjectCopy_HPFS_FAT_Func(psz_filename_from, psz_dirname_to);

    ShowFileList();
    switch(us_flg_objcpy) {
       case FLAG_OBJCPY_NO_TARGETPATH:
          ShowMsgPassNo(psz_dirname_to);
          return ;
       case FLAG_OBJCPY_FAIL_COPY:
          ShowMsgSameName();
          return ;
    }

    ShowMsgCopyOk();
    JumpHistInsert(FLAG_HISTRY_PATH, InpLine);
    return ;
 }

/****************************************************************/
/**  ObjectCopy_HPFS_FAT_MarkFile                               */
/****************************************************************/
VOID ObjectCopy_HPFS_FAT_MarkFile(PSZ psz_dirname_to)
 {
    USHORT us_flg_objcpy, us_flg_copyok=0;
    ULONG  ul_count;


    FirstDisp=1;            /* ���߂ĕ\�� */
    FileCopyFuncDisp("", FLAG_COPY_ONLY);   
               /* ������FirstDisp=0�i���߂ĂłȂ��j�ƂȂ� */

    for(ul_count=0; ul_count < FlCnt && KeyInfo.chChar!=ESC; ul_count++) { 
       KbdCharIn(&KeyInfo,IO_NOWAIT,0);
       if (FlDis[ul_count].Mark){
          FileCopyFuncDisp(FlDis[ul_count].Nm+DISP_FN, FLAG_COPY_ONLY);
          us_flg_objcpy = ObjectCopy_HPFS_FAT_Func
                             (FlDis[ul_count].Nm+DISP_FN, 
                              psz_dirname_to);
          switch(us_flg_objcpy) {
             case FLAG_OBJCPY_NO_TARGETPATH:
                ShowFileList();
                ShowMsgPassNo(psz_dirname_to);
                return;
             case FLAG_OBJCPY_FAIL_COPY:
                ShowFileList();
                ShowMsgSameName();
                FirstDisp=1; /* ����FileCopyFuncDisp(); �����߂Ă̕\���ɂ��� */
                break;
             default:
                us_flg_copyok=1;
          }
       }
    }

    ShowFileList();
    if(us_flg_copyok==1) JumpHistInsert(FLAG_HISTRY_PATH, InpLine);

    QFile();
    if(KeyInfo.chChar==ESC) {
       ShowMsgCopyStop();
    } else {
       ShowMsgCopyOk();
    }
    return;
 }

/****************************************************************/
/**  ObjectCopy_HPFS_FAT_Func                                   */
/****************************************************************/
USHORT ObjectCopy_HPFS_FAT_Func(PSZ psz_filename_from, PSZ psz_dirname_to)
 {
    HOBJECT ho_Obj_from, ho_Obj_to;
    UCHAR FulFlNm[_MAX_PATH];

    /* DLL�̃��[�h�̃`�F�b�N */
    if(!pfnQueryObject || !pfnCopyObject) return NO_ERROR; 

    SetFullFileName(psz_filename_from, FulFlNm);
    ho_Obj_from = pfnQueryObject(FulFlNm);
    ho_Obj_to   = pfnQueryObject(psz_dirname_to);

    if(ho_Obj_to == NULLHANDLE) return FLAG_OBJCPY_NO_TARGETPATH;

    if(pfnCopyObject(ho_Obj_from, ho_Obj_to, 0) == NULLHANDLE) 
       return FLAG_OBJCPY_FAIL_COPY;

    return NO_ERROR;
 }

/****************************************************************/
/**  OpenObjectOnDesktop                                        */
/****************************************************************/
void OpenObjectOnDesktop(PSZ psz_filename, BYTE bt_fileattr)
 {
    HOBJECT ho_OpenObj;
    UCHAR usz_fullfilename[_MAX_PATH];
    
    /* DLL�̃��[�h�̃`�F�b�N */
    if(!pfnQueryObject || !pfnSetObjectData) return; 
    
    SetFullFileName(psz_filename, usz_fullfilename);
    ho_OpenObj=pfnQueryObject(usz_fullfilename);
    pfnSetObjectData(ho_OpenObj,"OPEN=DEFAULT");    /*  �I�u�W�F�N�g���I�[�v��  */
    if (bt_fileattr&FILE_DIRECTORY) {                     /*  �f�B���N�g���Ȃ�        */
       DosSleep(100L);                              /*  ��������܂�0.1�b�҂�   */
       pfnSetObjectData(ho_OpenObj,"OPEN=DEFAULT"); /*  �E�B���h�E�Ƀt�H�[�J�X  */
    }

//  WinOpenObject(ho_OpenObj, 0, TRUE);             /*  �I�u�W�F�N�g���I�[�v��  */
//  if (bt_fileattr&FILE_DIRECTORY) {               /*  �f�B���N�g���Ȃ�        */
//     DosSleep(100L);                              /*  ��������܂�0.1�b�҂�   */
//     WinOpenObject(ho_OpenObj, 0, TRUE);          /*  �E�B���h�E�Ƀt�H�[�J�X  */
//  }
 }

/****************************************************************/
/**   PrevFileDirSearch                                        **/
/****************************************************************/
 void PrevFileDirSearch(PUCHAR puc_PrevFileDir)
 {
    ULONG  ul_count;

    for (ul_count=0; ul_count<FlCnt; ul_count++) {
       if (!stricmp(FlDis[ul_count].Nm+DISP_FN, puc_PrevFileDir)) break; 
    }
    
    if(ul_count==FlCnt) {
       Set_ShowFileList_Parm(0);
    } else {
       Set_ShowFileList_Parm(ul_count);
    }
 }

/*****************************************************************/
/**   QDrive                                                    **/
/*****************************************************************/
 void QDrive(void)
 {
    ULONG  ul_DriveNo, ul_DriveMap;
    FSINFO fsi_FSinfo={0};

    ul_DriveNo=0L;                         /* �J�����g�h���C�u�w�� */
    DosQueryCurrentDisk(&ul_DriveNo, &ul_DriveMap);
    DriveDis[0]= (CHAR)ul_DriveNo + 0x40;  /* �Ή�����A���t�@�x�b�g�� */

    memset(Label, 0, sizeof(Label));   /* 11Byte�ȏ��Vol.Label�͂Ȃ� */
    if (!DosQueryFSInfo(ul_DriveNo, FSIL_VOLSER, (PVOID)&fsi_FSinfo, 
                        sizeof(FSINFO))) {
       strcpy(Label, fsi_FSinfo.vol.szVolLabel);  
    }
    ShowVolumeLabel();
    ShowCurrentDriveName();
    QDriveSize();
 }

/*****************************************************************/
/**   QDriveSize                                                **/
/*****************************************************************/
 void QDriveSize(void)
 {
    FSALLOCATE fsa_FSinfo={0};

    memset(FreeDis, 0, sizeof(FreeDis));
    if(!DosQueryFSInfo(0L, FSIL_ALLOC, 
                        (PVOID)&fsa_FSinfo, sizeof(FSALLOCATE))) {

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
       sprintf(FreeDis,"Free:%luK/%luK", 
           fsa_FSinfo.cbSector*fsa_FSinfo.cSectorUnit*fsa_FSinfo.cUnitAvail/1024ul,
           fsa_FSinfo.cbSector*fsa_FSinfo.cSectorUnit*fsa_FSinfo.cUnit/1024ul);
#else
       unsigned long long ull_totaldrivesize = 
                            (unsigned long long)fsa_FSinfo.cbSector
                           *(unsigned long long)fsa_FSinfo.cSectorUnit
                           *(unsigned long long)fsa_FSinfo.cUnit/1024ull;
       unsigned long long ull_availdrivesize = 
                            (unsigned long long)fsa_FSinfo.cbSector
                           *(unsigned long long)fsa_FSinfo.cSectorUnit
                           *(unsigned long long)fsa_FSinfo.cUnitAvail/1024ull;

       sprintf(FreeDis,"Free:%lluK/%lluK", ull_availdrivesize, ull_totaldrivesize);
#endif

    } else {
       strcpy(FreeDis,"Free:0K/0K");
    } 
    ShowCurrentDriveSize();
 }

/****************************************************************/
/**   QDir                                                     **/
/**------------------------------------------------------------**/
/*  ���݂�Dir����       PathDis[]�ɃZ�b�g                       */
/****************************************************************/
 void QDir(void)
 {
    ULONG ul_PathLen;

    ul_PathLen=(ULONG)(sizeof(PathDis)-1);
    memset(PathDis+1, 0, ul_PathLen);
    DosQueryCurrentDir(0,PathDis+1,&ul_PathLen);

    ShowCurrentDirName();
 }

/*****************************************************************/
/**   QFile                                                     **/
/*****************************************************************/
 APIRET QFile(void)
 {
    APIRET apr_FindFirst;

    apr_FindFirst=QFile_LoadFileList(FLAG_LOADFILELIST_ANYFILE, FlMask);

    memset(FlCntDis, 0, sizeof(FlCntDis));

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
    sprintf(FlCntDis,"Files:%u(%uK)", FlCnt, CurrentSize/1024ul);
#else
    sprintf(FlCntDis,"Files:%u(%lluK)", FlCnt, CurrentSize/1024ull);
#endif

    FileMarkInfoDisp_Set(MarkCnt, MarkSize);

    if (AlwaysSort) 
       qsort(FlDis,FlCnt,sizeof(struct _FlDis),FileNameCompOption);

    return apr_FindFirst;
 }

/*****************************************************************/
/**   QFile_LoadFileList                                        **/
/*****************************************************************/
 APIRET QFile_LoadFileList(ULONG ul_FlFindAtr, PSZ psz_filemask)
 {
    APIRET apr_FindFirst;
    
    /*** DosFindFirst, DosFindNext �p�ϐ� ***/
    LHANDLE       lh_DirHandle=HDIR_SYSTEM;  /* =0x0001 */
#ifdef IBMCSET  /* ��e�ʃt�@�C���΍�����Ȃ� */
    FILEFINDBUF3  ffb3_FileInfo3={0};
#else
    FILEFINDBUF3L  ffb3_FileInfo3={0};
#endif
    ULONG         ul_FindCnt  =1;            

    if( CodePage[0]!=CodePage[1] ){
        // ���s�̃R�[�h�y�[�W����R�[�h�y�[�W�łȂ��ꍇ�A�ꎞ�I��
        // ��R�[�h�y�[�W��I������B
        // ��R�[�h�y�[�W�p�̃t�@�C�������܂ރf�B���N�g���ɂāA���R�[�h�y�[�W
        // �� DosFindNext ���J��Ԃ��ƁA�������[�v�ɂȂ鎖������͗l�B
        DosSetProcessCp(CodePage[1]);
    }
   
    FlCnt=0; 
    PageNo=1; 
    CurrentSize=0; 
    MarkCnt=0; 
    MarkSize=0;
    
    apr_FindFirst = GetFileSystem(DriveDis, &us_g_filesystem);
    if(!apr_FindFirst) {
#ifdef IBMCSET  /* ��e�ʃt�@�C���΍�����Ȃ� */
       apr_FindFirst = DosFindFirst(psz_filemask, &lh_DirHandle, ul_FlFindAtr,
                                 (PVOID)&ffb3_FileInfo3, sizeof(FILEFINDBUF3),
                                 &ul_FindCnt, FIL_STANDARD);
#else
       apr_FindFirst = lfs_DosFindFirst(psz_filemask, &lh_DirHandle, ul_FlFindAtr,
                                 (PVOID)&ffb3_FileInfo3, sizeof(FILEFINDBUF3L),
                                 &ul_FindCnt, FIL_STANDARDL);
#endif
    }
    if (!apr_FindFirst) {   
       if(SetFileInfo(&ffb3_FileInfo3)) FlCnt++; 

       ul_FindCnt=1;
#ifdef IBMCSET  /* ��e�ʃt�@�C���΍�����Ȃ� */
       while(!DosFindNext(lh_DirHandle, (PVOID)&ffb3_FileInfo3,
                          sizeof(FILEFINDBUF3), &ul_FindCnt)) {
#else
       while(!lfs_DosFindNext(lh_DirHandle, (PVOID)&ffb3_FileInfo3,
                          sizeof(FILEFINDBUF3L), &ul_FindCnt, FIL_STANDARDL)) {
#endif
          if(SetFileInfo(&ffb3_FileInfo3)) FlCnt++; 

          if(ul_g_maxfilenum!=0 && ul_g_maxfilenum<=FlCnt) break;
          ul_FindCnt  =1;            
       }
       DosFindClose(lh_DirHandle);
    }

    if( CodePage[0]!=CodePage[1] ){  // �t�@�C�����X�g�擾���ɖ������[�v���鎖��������̑΍�
        // �R�[�h�y�[�W�����ɖ߂��B
        DosSetProcessCp(CodePage[0]);
    }

    if(!FlCnt) memset(&FlDis[0], 0, sizeof(struct _FlDis)); 
    return apr_FindFirst;
}

/*****************************************************************/
/**   QuitFilestar                                              **/
/*****************************************************************/
 void QuitFilestar(VOID)
 {
    if(English){
       strcpy(MsgTxt[0],"      Exit FileNova.      ");
       strcpy(MsgTxt[1],"                          ");
       strcpy(MsgTxt[2]," Y:yes(Enter)   N:no(Esc) ");
    }
    else{
       strcpy(MsgTxt[0],"     FileNova �̏I��      ");
       strcpy(MsgTxt[1],"                          ");
       strcpy(MsgTxt[2],"�x:yes(Enter)   �m:no(Esc)");
    }

    if(GetYesorNo_withMsgBox(ENTER, 3, bt_g_NormalWindowColor,
                       FLAG_GETYESORNO_NO_OPTION)==ESC) {
       ShowFileList(); 
       return;
    }
    puts(CLEAR); 
    SigTerm(0); /* �v���Z�X�I������ */
 }


/*****************************************************************/
/**   ReDrawAfterDelete                                         **/
/*****************************************************************/
 void ReDrawAfterDelete(void)
 {
    QFile();
    if (!FlCnt) 
       ShowFileList_FilePosition(0);
    else if (SelFl>=FlCnt) 
       ShowFileList_FilePosition(FlCnt-1);
    else 
       ShowFileList();
 }

/*****************************************************************/
/**   RedrawScreen                                              **/
/*****************************************************************/
 void RedrawScreen(void)
 {
    SetWallColor();
    ShowVolumeLabel();
    ShowCurrentDriveName();
    ShowCurrentDirName();
    ShowFileNumberSize();
    ShowCurrentDriveSize();

    ShowFileList_FilePosition(SelFl);

 }

/*****************************************************************/
/**   SameDirCheck                                              **/
/*****************************************************************/
 ULONG SameDirCheck(PSZ psz_filename)
 {
    UCHAR currDir[_MAX_PATH]; 

    SetFullCurrentPathName(currDir);
    if (strcmp(InpLine,".") && stricmp(InpLine,currDir)) {
       SetFullFileName(psz_filename, currDir);
       if (stricmp(InpLine, currDir))   return 0;
    }
    ShowMsgSameDir(); 
    return 1;
 }

/*****************************************************************/
/**   SameDriveCheck                                            **/
/*---------------------------------------------------------------*/
/*     �Ԃ�l  0(SameDrive�`�F�b�N����)      /1(���s)            */
/*---------------------------------------------------------------*/
/*     �Q�Ƃ���O���[�o���ϐ� InpLine[]  ���͂��ꂽ������        */
/*                            DriveDis[0] ���݂̃h���C�u�L��     */
/*****************************************************************/
 ULONG SameDriveCheck(PUSHORT pus_flg_samedrive)
 {
    PCHAR pc_colon_ptr;
    CHAR c_drivechar;

    *pus_flg_samedrive=0;

    if (!(pc_colon_ptr=jstrchr(InpLine,':'))) {
       /* ':'������ �� ����h���C�u�̉\���̃`�F�b�N */
       /* �p�X�擪�� "\\" �ł���ꍇ�́A�l�b�g���[�N�p�X �� �ʃh���C�u���� */
       *pus_flg_samedrive = (InpLine[0]!='\\'&&InpLine[1]!='\\');
       return 0;
    }
    if (pc_colon_ptr == (PCHAR)InpLine) {      /* �P�����ڂ�':'�̓G���[ */
       ShowMsgNameNg();
       return 1;
    }
   
    c_drivechar = toupper(*(pc_colon_ptr-1));
    if (c_drivechar == DriveDis[0]) *pus_flg_samedrive=1;
    return 0;

 }

/*****************************************************************/
/**   Serch1Char                                                **/
/*****************************************************************/
 void Serch1Char(USHORT us_flg_first)
 {
    UCHAR uc_InputChar, uc_lowercase;
    ULONG  ul_count;
    static UCHAR uc_savechar=0;

    if(us_flg_first == FLAG_FIRST) {
       if(English){
          strcpy(MsgTxt[0],"Search a top character of file name. ");
          strcpy(MsgTxt[1],"(Target is under the cursor position)");
          strcpy(MsgTxt[2],"Push a key of search character.      ");
       }
       else{
          strcpy(MsgTxt[0],"�t�@�C�����̓��o�������܂�");
          strcpy(MsgTxt[1],"�i�J�[�\\���ʒu����̎��j  ");
          strcpy(MsgTxt[2],"���o�����L�[�������ĉ�����");
       }

       ShowMsgBox(3, bt_g_NormalWindowColor);
       do {
          KbdCharIn(&KeyInfo,IO_WAIT,0); 
          if((uc_InputChar=KeyInfo.chChar) == ESC) {
             ShowFileList();
             return;
          }
       } while (!(isprint(uc_InputChar))); /* �\���\�ȕ��� 0x20 - 0x7e */
       uc_savechar=uc_InputChar;
       ShowFileList();
    } else {
       uc_InputChar=uc_savechar;
       if(!isprint(uc_InputChar)) return;
    }
    uc_lowercase = tolower(uc_InputChar);
    for(ul_count=SelFl+1; ul_count<FlCnt; ul_count++) 
       if (uc_lowercase == tolower(FlDis[ul_count].Nm[DISP_FN])) break; 

    if (ul_count==FlCnt) 
       Serch1CharNg(uc_InputChar);
    else 
       ShowFileList_FilePosition(ul_count);
 }

/*****************************************************************/
/**   Serch1CharNg                                              **/
/*****************************************************************/
 void Serch1CharNg(UCHAR uc_inputchar)
 {
    if(English){
       strcpy(MsgTxt[0], "There is not a file beginning   ");
       sprintf(MsgTxt[1],"by a letter of \'%c\' hereunder.", uc_inputchar);
    }
    else{
       sprintf(MsgTxt[0],"\'%c\' �Ŏn�܂�t�@�C����    ", uc_inputchar);
       strcpy(MsgTxt[1], "���̉��ɂ͂���܂���         ");
    }

    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_NOWAIT);
 }

/*****************************************************************/
/**   SetFileInfo                                               **/
/*****************************************************************/
#ifdef IBMCSET  /* ��e�ʃt�@�C���΍�����Ȃ� */
 BOOL SetFileInfo(const PFILEFINDBUF3 pffb3_FileInfo3)
#else
 BOOL SetFileInfo(const PFILEFINDBUF3L pffb3_FileInfo3)
#endif
 {
    static ULONG FileMax=0;  /* ���ݓ��I�Ƀ��������m�ۍς݂̃t�@�C���� */
 
    /*--------------------------*/
    /* ���I����������U����s�� */
    /*--------------------------*/
    if(FlCnt>=FileMax){
       ULONG  newFileMax = FileMax + 1000; /* �V�t�@�C���ő吔 */
       size_t oldsizef = sizeof(struct _FlDis) * FileMax; /* ���T�C�Y(1) */
       size_t oldsizes = sizeof(struct _SvDis) * FileMax; /* ���T�C�Y(2) */
       size_t newsizef = sizeof(struct _FlDis) * newFileMax; /* �V�T�C�Y(1) */
       size_t newsizes = sizeof(struct _SvDis) * newFileMax; /* �V�T�C�Y(2) */
       struct _FlDis* newFlDis = (struct _FlDis*)malloc(newsizef); /* �V�o�b�t�@�|�C���^(1) */
       struct _SvDis* newSvDis = (struct _SvDis*)malloc(newsizes); /* �V�o�b�t�@�|�C���^(2) */
       if(newFlDis&&newSvDis){
          /*--------------------*/
          /* ����������U�萬�� */
          /*--------------------*/
          if(oldsizef) memcpy( newFlDis ,FlDis ,oldsizef );
          if(oldsizes) memcpy( newSvDis ,SvDis ,oldsizes );
          free(FlDis);
          free(SvDis);
          FlDis = newFlDis;
          SvDis = newSvDis;
          FileMax = newFileMax;
       } else {
          /*--------------------*/
          /* ����������U�莸�s */
          /*--------------------*/
          free(newFlDis);
          free(newSvDis);
          return FALSE;
       }
    }

    memset(FlDis[FlCnt].Nm,' ',FILE_DISPLEN); 
    memset(FlDis[FlCnt].LongNm, 0, _MAX_PATH); 
    FlDis[FlCnt].Mark=0;
   
#ifdef IBMCSET  /* ��e�ʃt�@�C���΍�����Ȃ� */
    sprintf(FlDis[FlCnt].Nm," %10u  %04.4d-%02.2d-%02.2d %02.2d:%02.2d  %s\0",
#else
    sprintf(FlDis[FlCnt].Nm," %10llu  %04.4d-%02.2d-%02.2d %02.2d:%02.2d  %s\0",
#endif
                               pffb3_FileInfo3->cbFile,
                              (pffb3_FileInfo3->fdateLastWrite.year+1980),
                               pffb3_FileInfo3->fdateLastWrite.month,
                               pffb3_FileInfo3->fdateLastWrite.day,
                               pffb3_FileInfo3->ftimeLastWrite.hours,
                               pffb3_FileInfo3->ftimeLastWrite.minutes,
                               pffb3_FileInfo3->achName);

    FlDis[FlCnt].Atr=pffb3_FileInfo3->attrFile;
    if (FlDis[FlCnt].Atr&FILE_DIRECTORY) {
       memcpy(FlDis[FlCnt].Nm+6,"<Dir>",5);
    } else {

       /* �t�@�C���T�C�Y���o���Ă����D�����񂩂�t�ϊ����Ȃ� */
       FlDis[FlCnt].cbFile = pffb3_FileInfo3->cbFile;
       CurrentSize+=pffb3_FileInfo3->cbFile;
    }

    if (FlDis[FlCnt].Atr&FILE_SYSTEM){
       FlDis[FlCnt].DisAtr[0] = bt_g_SystemFileColor;
       FlDis[FlCnt].DisAtr[1] = bt_g_SystemFileCursorColor;
    } else if (FlDis[FlCnt].Atr&FILE_HIDDEN){
       FlDis[FlCnt].DisAtr[0] = bt_g_HiddenFileColor;
       FlDis[FlCnt].DisAtr[1] = bt_g_HiddenFileCursorColor;
    } else if (FlDis[FlCnt].Atr&FILE_READONLY){
       FlDis[FlCnt].DisAtr[0] = bt_g_ReadOnlyFileColor;
       FlDis[FlCnt].DisAtr[1] = bt_g_ReadOnlyFileCursorColor;
    } else if (FlDis[FlCnt].Atr&FILE_DIRECTORY){
       FlDis[FlCnt].DisAtr[0] = bt_g_DirectryColor;
       FlDis[FlCnt].DisAtr[1] = bt_g_DirectryCursorColor;
    } else {
       FlDis[FlCnt].DisAtr[0] = bt_g_NormalFileColor;
       FlDis[FlCnt].DisAtr[1] = bt_g_NormalFileCursorColor;
    }

    if(us_g_filesystem) {  
       GetEALongName(pffb3_FileInfo3->achName, FlDis[FlCnt].LongNm);
    }
    
    return TRUE;
 }

/*****************************************************************/
/**   SetupEditor                                               **/
/*****************************************************************/
 void SetupEditor(PSZ IniFileIn)
 {
    if(SetupGlobalFlag_GetString(IniFileIn, "EditorName=", 1, 
                       EditorCfg.EditorProg.uszProgName, "E.EXE")) return;

    if(SetupGlobalFlag_FromInifileData(IniFileIn, "EditSession=", 
                       &(EditorCfg.EditorProg.usSession), 1, 0)) return ;

    if(SetupGlobalFlag_GetString(IniFileIn, "EditorLineOption=", 0, 
                       EditorCfg.EditorProg.uszParamList, ""))  return;

    if(SetupGlobalFlag_FromInifileData(IniFileIn, "EditorLineSetTop=", 
                       &(EditorCfg.usLineSetTop), 0, 1)) return;
 }

/*****************************************************************/
/**   SetupViewer                                               **/
/*****************************************************************/
 void SetupViewer(PSZ IniFileIn)
 {
    USHORT us_dummy;
    
    if(SetupGlobalFlag_FromInifileData(IniFileIn, 
                     "InternalViewerTabSize=", &us_dummy, 4, 8)) {
       ViewerCfg.ulTabSize=(ULONG)us_dummy;
       return ;
    }
    if(SetupGlobalFlag_FromInifileData(IniFileIn, "UseExternalViewer=", 
                              &(ViewerCfg.usUseExtViewer), 0, 1)) return ;

    if (!memcmp(IniFileIn,"ExternalViewer=",15)){ 
       if(SetupMacroProgram(IniFileIn+15, &(ViewerCfg.ViewerProg))) {
          ViewerCfg.usUseExtViewer=0;
       }
    }

    // �e�L�X�g�r���[�A�ɂ����錟���̑召�������ꎋ���f�t�H���g�ɂ���I�v�V����
    if(SetupGlobalFlag_FromInifileData(IniFileIn, "DefaultCaseSensitive=", 
                              &(ViewerCfg.usDefaultCaseSensitive), 1, 0)) return;
 }


/*****************************************************************/
/**   SetupExtention                                            **/
/*****************************************************************/
 USHORT SetupExtention(PSZ IniFileIn, PEXTERNALPROG pExpernalProg)
 {
    PCHAR pc_equal_ptr;

    if(SetupExtProg_Session(IniFileIn, &(pExpernalProg->usSession), 
                                       &(pExpernalProg->usSilent))) return 1;

    pc_equal_ptr=strchr(IniFileIn+4,'=');
    if (pc_equal_ptr){
       *pc_equal_ptr = '\0';
       sprintf(pExpernalProg->uszExtention, ".%s", IniFileIn+4);
    } else {
       return 1;
    }
    return SetupExtProg_NameAndParam(pc_equal_ptr+1, 
                                     pExpernalProg->uszProgName,
                                     pExpernalProg->uszParamList);
 }


/*****************************************************************/
/**   SetupExtProg_Session                                      **/
/*****************************************************************/
 USHORT SetupExtProg_Session(PSZ psz_databuff, 
                             PUSHORT pus_session, PUSHORT pus_silent)
 {
    if (!memicmp(psz_databuff,"SS1",3)) {
       *pus_session=1;
       *pus_silent=0;
    } else if (!memicmp(psz_databuff,"SS0",3)) { 
       *pus_session=0;
       *pus_silent=0;
    } else if (!memicmp(psz_databuff,"SQ1",3)) {
       *pus_session=1;
       *pus_silent=1;
    } else if (!memicmp(psz_databuff,"SQ0",3)) { 
       *pus_session=0;
       *pus_silent=1;
    } else {
       return 1;
    }
    return 0;
 }

/*****************************************************************/
/**   SetupExtProg_NameAndParam                                 **/
/*****************************************************************/
 USHORT SetupExtProg_NameAndParam(PSZ psz_databuff, PSZ psz_pgmname,
                             PSZ psz_parameter)
 {
    PCHAR pc_space_ptr;

    pc_space_ptr=strchr(psz_databuff,' ');
    if (pc_space_ptr) {  
       *pc_space_ptr='\0';
       strcpy(psz_parameter, pc_space_ptr+1);
    } 
    strcpy(psz_pgmname, psz_databuff);

    /* �t���O�w�莞�A�p�����[�^�������Ȃ� &f ��}�� */
    if(*psz_parameter=='\0' && us_g_flg_auto_AndF==1) strcpy(psz_parameter, "&f");

    return 0;
 }

/*****************************************************************/
/**   SetupMacroProgram                                         **/
/*****************************************************************/
 USHORT SetupMacroProgram(PSZ psz_databuf, PEXTERNALPROG pExternalProg)
 {
    if(SetupExtProg_Session(psz_databuf, &(pExternalProg->usSession), 
                                         &(pExternalProg->usSilent))) return 1;

    return SetupExtProg_NameAndParam(psz_databuf+4, pExternalProg->uszProgName,
                                     pExternalProg->uszParamList);
 }


/*****************************************************************/
/**   SetupUnpacker                                             **/
/*****************************************************************/
 USHORT SetupUnpacker(PSZ IniFileIn, USHORT us_unpackernum)
 {
    if(SetupGlobalFlag_GetString(IniFileIn, "UnpackDir=", 1, UnpackDir, "")) {
       return 1;
    }
    if(SetupGlobalFlag_FromInifileData(IniFileIn, "UnpackToEachSubdir=", 
                                       &us_g_unpack_dir, 0, 1)) {
       return 1;
    }
    if(SetupGlobalFlag_FromInifileData(IniFileIn, "JumpToUnpackDir=", 
                                 &us_g_flg_JumpToUnpackDir, 0, 1)) {
       return 1;
    }
    return SetupExtention(IniFileIn, &UnpackerProg[us_unpackernum]);

 }

/*****************************************************************/
/**   SetupGeneral                                              **/
/*****************************************************************/
 void SetupGeneral(SHORT s_flg_first, PSZ IniFileIn)
 {
    PUCHAR puc_strptr;

    if(s_flg_first == FLAG_FIRST) {
       if(SetupGlobalFlag_GetString(IniFileIn, "StartupDir=", 1, StartupDir, "")) 
          return;
       if((puc_strptr=SetupGlobalFlag_SearchValuePtr(IniFileIn, 
                                                  "WindowSize="))!=NULL) {
          strtok(IniFileIn, " \n");
          if(sscanf(puc_strptr,"%hu,%hu",&ColMax,&RowMax)==2) {
             ChangeWindowSizeFunc(puc_strptr);
          }
          return;
       }
       puc_strptr=SetupGlobalFlag_SearchValuePtr(IniFileIn, "FilerColumn=");
       if(puc_strptr) {
          if(sscanf(puc_strptr,"%hu",&FileListType)!=1) {
             FileListType=1;
          }
          switch(FileListType) { 
             case 1:
             case 2:
             case 3:
             case 5:
                break;
             default:
               FileListType=2;
          }
          return;  
       }                       
    }

    if(SetupGlobalFlag_FromInifileData(IniFileIn, 
                       "ExecSession=", &ExecSession, 1, 0)) return;
    if(SetupGlobalFlag_FromInifileData(IniFileIn, 
                       "AlwaysSort=",  &AlwaysSort,  0, 1)) return;
    if(SetupGlobalFlag_FromInifileData(IniFileIn, 
                       "CaseOfSort=",  &CaseOfSort,  0, 1)) return;
    if(SetupGlobalFlag_FromInifileData(IniFileIn, 
                       "AutoClose=",   &AutoClose,   1, 0)) return;

    if(SetupGlobalFlag_FromInifileData(IniFileIn, 
                          "UseDosVMode=", &us_g_flg_dosmode,   
                          FLAG_DOSMODE_DOSV, FLAG_DOSMODE_PCDOS)) return;
    if(SetupGlobalFlag_FromInifileData(IniFileIn, 
                       "AutoFileNameInsert=", &us_g_flg_auto_AndF, 1, 0)) return;  

    if((puc_strptr=SetupGlobalFlag_SearchValuePtr(IniFileIn, 
                                                  "KindOfSort="))!=NULL) {
       KindOfSort=*puc_strptr;
       return;
    }

    if(SetupGlobalFlag_GetValueAsULONG(IniFileIn, "MaxFileNumber=",
                                &ul_g_maxfilenum, MAX_FILE)) return;
    if(SetupGlobalFlag_GetString(IniFileIn, "CommandShell=", 1, 
                                 ShellName, "CMD.EXE")) return;

    if(SetupGlobalFlag_FromInifileData(IniFileIn, 
                       "EnglishMode=", &ForceEnglish, 0, 1)) return;
 }

/*****************************************************************/
/**   SetupGlobalFlag_FromInifileData                          **/
/*****************************************************************/
 USHORT SetupGlobalFlag_FromInifileData(PSZ IniFileIn, PSZ psz_keyword, 
                     PUSHORT pus_flagvalue,  USHORT us_default, USHORT us_notdefault)
 {
    USHORT us_readornot;   
    ULONG  ul_value;
    
    us_readornot=SetupGlobalFlag_GetValueAsULONG(IniFileIn, 
                                   psz_keyword, &ul_value, (ULONG)us_default);
    if(us_readornot) {
       if((USHORT)ul_value!=us_notdefault) { 
          *pus_flagvalue=us_default;
       }else{
          *pus_flagvalue=us_notdefault;
       } 
    }
    return us_readornot;  
 } 

/*****************************************************************/
/**   SetupGlobalFlag_GetValueAsULONG                           **/
/*****************************************************************/
 USHORT SetupGlobalFlag_GetValueAsULONG(PSZ IniFileIn, PSZ psz_keyword,
                            PULONG pul_flagvalue, ULONG ul_default)
 {
    PUCHAR puc_valueptr;
 
    puc_valueptr=SetupGlobalFlag_SearchValuePtr(IniFileIn, psz_keyword);

    if(puc_valueptr) {
       strtok(IniFileIn, " \n");
       if(sscanf(puc_valueptr,"%lu",pul_flagvalue)!=1) {
          *pul_flagvalue=ul_default;
       }
       return 1;  /* �t���O�̓Z�b�g�� */
    }
    return 0;  /* �t���O�͖��Z�b�g */
 } 

/*****************************************************************/
/**   SetupGlobalFlag_GetStrings                                **/
/*****************************************************************/
 USHORT SetupGlobalFlag_GetString(PSZ IniFileIn, PSZ psz_keyword,
                    USHORT us_flg_nospace, PSZ psz_inputbuff, PSZ psz_defaultstr)
 {
    PUCHAR puc_strptr;

    puc_strptr=SetupGlobalFlag_SearchValuePtr(IniFileIn, psz_keyword);

    if(puc_strptr) {
       if(us_flg_nospace) strtok(IniFileIn, " \n");
       if(*puc_strptr!='\0') {
          strcpy(psz_inputbuff, puc_strptr);
       } else {
          strcpy(psz_inputbuff, psz_defaultstr);
       }
       return 1;  /* �t���O�̓Z�b�g�� */
    }
    return 0;  /* �t���O�͖��Z�b�g */
 } 


/*****************************************************************/
/**   SetupGlobalFlag_SearchValuePtr                            **/
/*****************************************************************/
 PUCHAR SetupGlobalFlag_SearchValuePtr(PSZ IniFileIn, PSZ psz_keyword) 
 {
    ULONG ul_keywordlen;
    
    ul_keywordlen=strlen(psz_keyword);
    if(!memcmp(IniFileIn, psz_keyword, ul_keywordlen)) {
        return IniFileIn+ul_keywordlen;
    }
    return NULL;
 } 


/*****************************************************************/
/**   SetWallColor                                              **/
/*****************************************************************/
 void SetWallColor(void)
 {
    USHORT us_len;

    VioWrtNAttr(&bt_g_FilerTytleBarColor, ColMax, FILER_TITLE_ROW, 0, VIO_HANDLE);
    VioWrtCharStr(FILESTAR_VERSION[English], us_len=strlen(FILESTAR_VERSION[English]), 
                  FILER_TITLE_ROW, 0, VIO_HANDLE);
    VioWrtNChar(" ", ColMax-us_len, FILER_TITLE_ROW, us_len, VIO_HANDLE);

    VioWrtNAttr(&bt_g_FilerBackGroundColor, (RowMax-2)*ColMax, 
                FILER_TITLE_ROW+1, 0, VIO_HANDLE);

    VioWrtNAttr(&bt_g_FilerFunctionBarColor, ColMax, RowMax-1, 0, VIO_HANDLE);
    VioWrtCharStr(Footer[English], us_len=strlen(Footer[English]), RowMax-1, 0, VIO_HANDLE);
    VioWrtNChar(" ", ColMax-us_len, RowMax-1, us_len, VIO_HANDLE);

    VioWrtNAttr(&bt_g_FilerWallColor, ColMax, FILER_TOP_MARGIN-1, 0,VIO_HANDLE);
    VioWrtNChar(LineChar_H,                  ColMax, FILER_TOP_MARGIN-1, 0,VIO_HANDLE);
    ShowFileMask();
 }

/*****************************************************************/
/**   SetFullCurrentPathName                                    **/
/**      FulDirNm[] �ɃJ�����gDir�̐�΃p�X�����Z�b�g           **/
/*****************************************************************/
 void SetFullCurrentPathName(PSZ FulDirNm)
 {
    sprintf(FulDirNm, "%c:%s", DriveDis[0], PathDis); 
 }

/*****************************************************************/
/**   SetFullDirName                                            **/
/**      FulDirNm[] �ɃJ�����gDir�̐�΃p�X�����Z�b�g           **/
/*****************************************************************/
 void SetFullDirName(PSZ FulDirNm)
 {
    SetFullCurrentPathName(FulDirNm);

    /* ���[�g�f�B���N�g���ȊO�Ȃ�'\\'�����ɂ��� */
    if(strlen(FulDirNm) > 3) strcat(FulDirNm, "\\");
 }

/*****************************************************************/
/**   SetFullFileName                                           **/
/**      FulFlNm[] �ɐ�΃p�X�t���t�@�C�������Z�b�g             **/
/*****************************************************************/
 void SetFullFileName(PSZ psz_filename, PSZ FulFlNm)
 {
    UCHAR  *yenptr;
    
    if(!strcmp(psz_filename, ".")) {    /*  �J�����gDir */ 
       SetFullCurrentPathName(FulFlNm);
       return;
    } 
    if(!strcmp(psz_filename, "..")) {   /*  �eDir  */
       SetFullCurrentPathName(FulFlNm);
       if((yenptr=jstrrchr(FulFlNm, '\\')) != NULL) *yenptr='\0';
       return;
    } 
    
    SetFullDirName(FulFlNm);
    strcat(FulFlNm, psz_filename);      /* ����ȊO */
    return;
 
 }

/*****************************************************************/
/**    Set_ShowFileList_Parm                                    **/
/*****************************************************************/
 void Set_ShowFileList_Parm(ULONG ul_currentfile_number)
 {
    SelFl=ul_currentfile_number;
    PageNo=(SelFl+FILER_LISTFILENUM) / FILER_LISTFILENUM; 
    StartFl=(PageNo-1) * FILER_LISTFILENUM;
    FileRow=SelFl-StartFl;
 }

/*****************************************************************/
/**   ShowFileList_FilePosition                                 **/
/*****************************************************************/
 void ShowFileList_FilePosition(ULONG ul_currentfile_number)
 {
    Set_ShowFileList_Parm(ul_currentfile_number);
    ShowFileList();
 }
/*****************************************************************/
/**   ShowFileList_PrevFile                                     **/
/*****************************************************************/
 void ShowFileList_PrevFile(USHORT us_flg_drawregion, PSZ psz_prevfilename)
 {
    UCHAR uc_prevfname_backup[_MAX_PATH];

    if(us_flg_drawregion==FLAG_DRAW_SCREEN) GetMode();

    strcpy(uc_prevfname_backup, psz_prevfilename);
    QFile();
    PrevFileDirSearch(uc_prevfname_backup);

    if(us_flg_drawregion==FLAG_DRAW_SCREEN) 
       RedrawScreen();
    else 
       ShowFileList(); 

 }


/*****************************************************************/
/**   ShowVolumeLabel                                           **/
/*****************************************************************/
 void ShowVolumeLabel(VOID)
 {
    USHORT LavelDisLen=11;

    VioWrtCharStrAtt(Label, LavelDisLen, FILER_VOL_PATH_ROW, 
                     1, &bt_g_VolumLabelColor, VIO_HANDLE);
 }

/*****************************************************************/
/**   ShowCurrentDriveName                                      **/
/*****************************************************************/
 void ShowCurrentDriveName(VOID)
 {
    VioWrtCharStrAtt(DriveDis,strlen(DriveDis),FILER_VOL_PATH_ROW,
                     13, &bt_g_CurrentPathColor, VIO_HANDLE);
 }

/*****************************************************************/
/**   ShowCurrentDirName                                        **/
/*****************************************************************/
 void ShowCurrentDirName(VOID)
 {
    VioWrtCharStrAtt(PathDis,ColMax-16,FILER_VOL_PATH_ROW,
                     15, &bt_g_CurrentPathColor, VIO_HANDLE);
 }

/*****************************************************************/
/**   ShowFileNumberSize                                        **/
/*****************************************************************/
 void ShowFileNumberSize(VOID)
 {
    USHORT  FlCntDisLen=22;

    VioWrtCharStrAtt(FlCntDis,FlCntDisLen, FILER_PATHINFO_ROW, 1,
                     &bt_g_CurrentPathInfomColor,VIO_HANDLE);
 }

/*****************************************************************/
/**   ShowMarkFileNumberSize                                    **/
/*****************************************************************/
 void ShowMarkFileNumberSize(VOID)
 {
    USHORT  MarkCntDisLen=18;
 
    VioWrtCharStrAtt(MarkCntDis,MarkCntDisLen, FILER_PATHINFO_ROW, 23,
                     &bt_g_CurrentPathInfomColor,VIO_HANDLE);
 }

/*****************************************************************/
/**   ShowCurrentDriveSize                                      **/
/*****************************************************************/
 void ShowCurrentDriveSize(void)
 {
    USHORT us_size_FreeDis=24; 

    VioWrtCharStrAtt(FreeDis, us_size_FreeDis, FILER_PATHINFO_ROW, 46,
                     &bt_g_CurrentPathInfomColor, VIO_HANDLE);
 }

/*****************************************************************/
/**   ShowFileMask                                              **/
/*****************************************************************/
 void ShowFileMask(void)
{
    VioWrtCharStrAtt(FlMask, ColMax-70, FILER_PATHINFO_ROW, 70, 
                     &bt_g_FileMaskColor, VIO_HANDLE);
}

/*****************************************************************/
/**   ShowFileList                                           **/
/*****************************************************************/
 void ShowFileList(VOID)
 {
    CHAR c_PageDisplay[64];   
    USHORT us_PageDisplen=31; /* �y�[�W���̕\���g */
    USHORT us_row, us_col, us_count, us_pagelen, us_dispextra;
    ULONG  ul_count_file;

    /* ���݂̃f�B���N�g���̃t�@�C���� */
    ShowFileNumberSize();
    /* ���݂̃f�B���N�g���̃}�[�N�t�@�C���� */
    ShowMarkFileNumberSize();

   /*----------------------*/
   /* �t�@�C�����X�g��\�� */
   /*----------------------*/
   us_dispextra = ColMax%FileListType;
   for (us_count=0; us_count<FILER_LISTWINSIZE ; us_count++) {
       us_row = us_count;
       ul_count_file = StartFl + us_count;
       for(us_col=0; us_col < FileListType; us_col++) {
          ShowFileList_Line(FlDis[ul_count_file].Nm, us_row, 
                         FlDis[ul_count_file].DisAtr[ul_count_file==SelFl],
                         FlDis[ul_count_file].Atr);
          ul_count_file += FILER_LISTWINSIZE;
          us_row        += FILER_LISTWINSIZE;
       }
       /* ����\���̎����ɗ]����������h��Ԃ� */
       if(us_dispextra >0) {
          VioWrtNAttr(&bt_g_FilerBackGroundColor, us_dispextra, 
                   us_count+FILER_TOP_MARGIN, ColMax-us_dispextra, VIO_HANDLE);
          VioWrtNChar(" ", us_dispextra, 
                   us_count+FILER_TOP_MARGIN, ColMax-us_dispextra, VIO_HANDLE);
       }
    }

    ShowFileList_CurrFileInfo(SelFl);

    /*----------------*/
    /* �y�[�W����\�� */
    /*----------------*/
    memset(c_PageDisplay ,0, sizeof(c_PageDisplay));
    VioWrtCharStr(c_PageDisplay, us_PageDisplen, 0, ColMax-1-us_PageDisplen, VIO_HANDLE);

    PageNo=(SelFl+FILER_LISTFILENUM) / FILER_LISTFILENUM;
    sprintf(c_PageDisplay, "CodePage[%u] Page:%u/%u", 
                     CodePage[0], PageNo, (FlCnt-1+FILER_LISTFILENUM)/FILER_LISTFILENUM);
    us_pagelen=strlen(c_PageDisplay);
    if(us_pagelen>us_PageDisplen) us_pagelen=us_PageDisplen;

    VioWrtCharStr(c_PageDisplay, us_pagelen, 0, ColMax-1-us_pagelen, VIO_HANDLE);

    /* �J�[�\���̏ꏊ���Z�b�g */
    VioSetCurPos(FileRow+FILER_TOP_MARGIN, 0, VIO_HANDLE);

 }


/*****************************************************************/
/**   ShowFileList_CurrFileInfo                                 **/
/*****************************************************************/
 VOID ShowFileList_CurrFileInfo(ULONG ul_SelFl)
 {
   UCHAR usz_dispuff[256]={0}; /* 16bit �A�h���X�̕ǂ�����邽�߂̃o�b�t�@ */

   if(FlCnt) {
      strcpy(usz_dispuff, " -----");
      if(us_g_filesystem && *(FlDis[ul_SelFl].LongNm)) {
         memcpy(usz_dispuff+6, FlDis[ul_SelFl].Nm, DISP_FN-DISP_SZ);
         strcat(usz_dispuff, FlDis[ul_SelFl].LongNm);
      } else {
         strcat(usz_dispuff, FlDis[ul_SelFl].Nm);
      }
      if (FlDis[ul_SelFl].Atr&FILE_SYSTEM)    usz_dispuff[2]='S';
      if (FlDis[ul_SelFl].Atr&FILE_HIDDEN)    usz_dispuff[3]='H';  
      if (FlDis[ul_SelFl].Atr&FILE_READONLY)  usz_dispuff[4]='R';
      if (FlDis[ul_SelFl].Atr&FILE_DIRECTORY) usz_dispuff[1]='D';
      if (FlDis[ul_SelFl].Atr&FILE_ARCHIVED)  usz_dispuff[5]='A';
   }
   VioWrtCharStrAtt(usz_dispuff, ColMax, FILER_FILEINFO_ROW, 
                    0, &(FlDis[SelFl].DisAtr[0]), VIO_HANDLE);
 }

/*****************************************************************/
/**   ShowFileList_Line                                         **/
/*****************************************************************/
 VOID ShowFileList_Line(PSZ psz_currfile, USHORT us_currrow, 
                        BYTE bt_attr, BYTE bt_fileattr)
 {
   UCHAR usz_dispuff[256]={0}; /* 16bit �A�h���X�̕ǂ�����邽�߂̃o�b�t�@ */
   BOOL  bl_buffset=FALSE;
   USHORT us_dispcolumn, us_disprow, us_dispwidth;

   us_dispwidth  = ColMax / FileListType;
   us_dispcolumn = us_currrow / FILER_LISTWINSIZE;
   us_disprow    = us_currrow - us_dispcolumn * FILER_LISTWINSIZE;

   if((ULONG)us_currrow+StartFl < FlCnt) {
      if(us_g_flg_8_3rule || FileListType > 1) 
         bl_buffset=ShowFileList_SetExtentionSort(psz_currfile, 
                                    usz_dispuff, us_dispwidth, bt_fileattr);
      if(bl_buffset==FALSE) strcpy(usz_dispuff, psz_currfile); 
   } else {
      bt_attr = bt_g_FilerBackGroundColor;
   }
   VioWrtCharStrAtt(usz_dispuff, us_dispwidth, us_disprow+FILER_TOP_MARGIN, 
                    us_dispwidth*us_dispcolumn, &bt_attr, VIO_HANDLE);

    /* �J�[�\���̏ꏊ���Z�b�g */
    VioSetCurPos(us_disprow+FILER_TOP_MARGIN, us_dispwidth*us_dispcolumn, 
                 VIO_HANDLE);
 }


/*****************************************************************/
/**   ShowFileList_SetExtentionSort                             **/
/*****************************************************************/
 BOOL ShowFileList_SetExtentionSort(PSZ psz_currfile, PSZ psz_dispbuff,
                                    USHORT us_dispwidth, BYTE bt_fileattr)
 {
   PUCHAR puc_nameptr=psz_currfile+DISP_FN, puc_extptr;
   USHORT us_ext_dispcolumn=15;  /* �g���q��15�����ڂ���\�� */
   USHORT us_fnamespace;
   UCHAR  usz_flsize[16]={0};
   PUCHAR puc_offset;

   switch(FileListType) {
      case 1:
      default:
         if(*puc_nameptr=='.')                          return FALSE;  /* �擪��. */
         if(!(puc_extptr=jstrrchr(puc_nameptr, '.')))   return FALSE;  /* .����   */
         if((puc_extptr-puc_nameptr)>us_ext_dispcolumn) return FALSE;  /* Long FN */
      
         memcpy(psz_dispbuff, psz_currfile, puc_extptr-psz_currfile); 
         strcpy(psz_dispbuff+DISP_FN+us_ext_dispcolumn, puc_extptr); 
         return TRUE;

      case 2:
         memcpy(usz_flsize, psz_currfile, DISP_DT-DISP_SZ-2);
         puc_offset = usz_flsize+strspn(usz_flsize, " ");
         us_fnamespace = us_dispwidth - (DISP_MK-DISP_DT-1)
                                      - strlen(puc_offset)-2;
         jmemcpy(psz_dispbuff, psz_currfile+DISP_MK, us_fnamespace);
         psz_dispbuff += (ULONG)(us_fnamespace+1);
         memcpy(psz_dispbuff, puc_offset, strlen(puc_offset));
         psz_dispbuff += (strlen(puc_offset)+1);
         memcpy(psz_dispbuff, psz_currfile+DISP_DT+2, DISP_MK-DISP_DT-2);
         return TRUE;
      case 3:
         memcpy(usz_flsize, psz_currfile, DISP_DT-DISP_SZ-2);
         puc_offset = usz_flsize+strspn(usz_flsize, " ");
         us_fnamespace = us_dispwidth - strlen(puc_offset)-2;
         jmemcpy(psz_dispbuff, psz_currfile+DISP_MK, us_fnamespace);
         psz_dispbuff += (ULONG)(us_fnamespace+1);
         memcpy(psz_dispbuff, puc_offset, strlen(puc_offset));
         return TRUE;
      case 5:
         us_fnamespace = us_dispwidth;
         if (bt_fileattr&FILE_DIRECTORY) us_fnamespace--;
         jmemcpy(psz_dispbuff, psz_currfile+DISP_MK, us_fnamespace);
         if (bt_fileattr&FILE_DIRECTORY)  strcat(psz_dispbuff, "\\"); 
         return TRUE;
   }
 }

/******************************************************************/
/**   SetHelpMsg                                                 **/
/******************************************************************/
 USHORT SetHelpMsg(PUSHORT pus_helppage)
{
    if((*pus_helppage) < 1) *pus_helppage = 1;
    if((*pus_helppage) > 6) *pus_helppage = 6;
   
    switch(*pus_helppage) {
       case 1:
         if(English){
            strcpy(MsgTxt[0], "  FileNova Quick Reference  1/6                             ");
            strcpy(MsgTxt[1], "                                                            ");
            strcpy(MsgTxt[2], "[ Control keys ]                                            ");
            strcpy(MsgTxt[3], "  Left/Up : Move cursor        Insert: Mark all files       ");
            strcpy(MsgTxt[4], "Right/Down: Ditto              Delete: Search a top char... ");
            strcpy(MsgTxt[5], "  PageUp  : Previous page      Enter : Into directory       ");
            strcpy(MsgTxt[6], "  PageDown: Next page                : Exec(exe/com/cmd/bat)");
            strcpy(MsgTxt[7], "   Home   : Top of file              : Exec for extension   ");
            strcpy(MsgTxt[8], "   End    : Bottom of file           : View(Others)         ");
            strcpy(MsgTxt[9], " BackSpace: Parrent directory  Shift+Enter: Text editor     ");
            strcpy(MsgTxt[10],"   Esc    : Exit FileNova            : View(exe/com/cmd/bat)");
            strcpy(MsgTxt[11],"                                                            ");
            strcpy(MsgTxt[12],"                     Down/PageDown:Next   Enter/Esc:Back    ");
         }
         else{
            strcpy(MsgTxt[0], "  FileNova �̎g�p����  1/6                                  ");
            strcpy(MsgTxt[1], "                                                            ");
            strcpy(MsgTxt[2], "������L�[�̋@�\\                                            ");
            strcpy(MsgTxt[3], "   ����   : ����           Insert: �S�t�@�C���̃}�[�N   ");
            strcpy(MsgTxt[4], "   ����   : ����w           Delete: �t�@�C���̓��o��     ");
            strcpy(MsgTxt[5], "  PageUp  : �O�y�[�W�w         Enter : �f�B���N�g���̒���   ");
            strcpy(MsgTxt[6], "  PageDown: ���y�[�W�w               : ���s(exe/com/cmd/bat)");
            strcpy(MsgTxt[7], "   Home   : �ŏ��̃t�@�C����         : �g���q�o�^Prog���s   ");
            strcpy(MsgTxt[8], "   End    : �Ō�̃t�@�C����         : ���e�\\���i��L�ȊO�j ");
            strcpy(MsgTxt[9], " BackSpace: �e�f�B���N�g����   Shift+Enter: �G�f�B�^�N��    ");
            strcpy(MsgTxt[10],"   Esc    : �I��                     : �\\��(exe/com/cmd/bat)");
            strcpy(MsgTxt[11],"                                                            ");
            strcpy(MsgTxt[12],"                     Down/PageDown:����   Enter/Esc:�߂�    ");
         }
         break;
       case 2:
         if(English){
            strcpy(MsgTxt[0], "  FileNova Quick Reference  2/6                             ");
            strcpy(MsgTxt[1], "                                                            ");
            strcpy(MsgTxt[2], "[ Alphabet keys(1/2) ]                                      ");
            strcpy(MsgTxt[3], "  A Set attribute (File/Dir)   I Create icon                ");
            strcpy(MsgTxt[4], "  B Binary view(File)          J Jump directory             ");
            strcpy(MsgTxt[5], "  C Copy(File/Dir)             K Make directory             ");
            strcpy(MsgTxt[6], "  D Delete(File/Dir)           L Change current drive       ");
            strcpy(MsgTxt[7], "  E Edit(Invoke text editor)   M Move(File/Dir)             ");
            strcpy(MsgTxt[8], "  F Find(File)                 N Rename(File/Dir)           ");
            strcpy(MsgTxt[9], "  G                            O Open WPS_Object(File/Dir)  ");
            strcpy(MsgTxt[10],"  H Change current directory   P Pack to archive file       ");
            strcpy(MsgTxt[11],"                                                            ");
            strcpy(MsgTxt[12],"   Up/PageUp:Prev    Down/PageDown:Next   Enter/Esc:Back    ");
         }
         else{
            strcpy(MsgTxt[0], "  FileNova �̎g�p����  2/6                                  ");
            strcpy(MsgTxt[1], "                                                            ");
            strcpy(MsgTxt[2], "�������L�[�̋@�\\(1/2)                                      ");
            strcpy(MsgTxt[3], "  A �����ύX(File/Dir)         I �A�C�R���o�^               ");
            strcpy(MsgTxt[4], "  B �o�C�i���\\��(File)         J �f�B���N�g���̃W�����v     ");
            strcpy(MsgTxt[5], "  C ����(File/Dir)             K �f�B���N�g���쐬           ");
            strcpy(MsgTxt[6], "  D �폜(File/Dir)             L �h���C�u�ύX               ");
            strcpy(MsgTxt[7], "  E �ҏW(�O��Editor�N��)       M �ړ�(File/Dir)             ");
            strcpy(MsgTxt[8], "  F ����(File)                 N ���O�ύX(File/Dir)         ");
            strcpy(MsgTxt[9], "  G                            O WPS_Object���J��(File/Dir) ");
            strcpy(MsgTxt[10],"  H �J�����g�f�B���N�g���ύX   P ���Ƀt�@�C���쐬           ");
            strcpy(MsgTxt[11],"                                                            ");
            strcpy(MsgTxt[12],"   Up/PageUp:�O��    Down/PageDown:����   Enter/Esc:�߂�    ");
         }
         break;
       case 3:
         if(English){
            strcpy(MsgTxt[0], "  FileNova Quick Reference  3/6                             ");
            strcpy(MsgTxt[1], "                                                            ");
            strcpy(MsgTxt[2], "[ Alphabet keys(2/2) ]                                      ");
            strcpy(MsgTxt[3], "  Q Exit FileNova              Y Set a mask of file list    ");
            strcpy(MsgTxt[4], "  R Upper/Lower case(File/Dir) Z                            ");
            strcpy(MsgTxt[5], "  S Sort file list             1-9 Change current drive(A-I)");
            strcpy(MsgTxt[6], "  T                            @ Calculate size of directory");
            strcpy(MsgTxt[7], "  U Unpack archive file        \\ To root directory          ");
            strcpy(MsgTxt[8], "  V View(File)                 . Execute a command shell    ");
            strcpy(MsgTxt[9], "  W Resize window              Shift+1,2,3,5 : Set 1-5 lines");
            strcpy(MsgTxt[10],"  X Execute(Use CMD.EXE)            [!,\",#,%]               ");
            strcpy(MsgTxt[11],"                                                            ");
            strcpy(MsgTxt[12],"   Up/PageUp:Prev    Down/PageDown:Next   Enter/Esc:Back    ");
         }
         else{
            strcpy(MsgTxt[0], "  FileNova �̎g�p����  3/6                                  ");
            strcpy(MsgTxt[1], "                                                            ");
            strcpy(MsgTxt[2], "�������L�[�̋@�\\(2/2)                                      ");
            strcpy(MsgTxt[3], "  Q �I��                       Y �t�@�C���\\���}�X�N�ύX    ");
            strcpy(MsgTxt[4], "  R �啶���������ύX(File/Dir) Z                            ");
            strcpy(MsgTxt[5], "  S �\\���̃\\�[�g              1-9 �h���C�u��A-I�ɕύX       ");
            strcpy(MsgTxt[6], "  T                            @ ���t�@�C���T�C�Y�v�Z(Dir)  ");
            strcpy(MsgTxt[7], "  U ���Ƀt�@�C���̉�         \\ ���[�g�f�B���N�g���Ɉړ�   ");
            strcpy(MsgTxt[8], "  V ���e�\\��(File)             .  Command Shell �N��        ");
            strcpy(MsgTxt[9], "  W Window Size �ύX           Shift+1,2,3,5 :  1-5��\\��   ");
            strcpy(MsgTxt[10],"  X ���s(CMD.EXE�o�R)               [!,\",#,%]               ");
            strcpy(MsgTxt[11],"                                                            ");
            strcpy(MsgTxt[12],"   Up/PageUp:�O��    Down/PageDown:����   Enter/Esc:�߂�    ");
         }
         break;
       case 4:
         if(English){
            strcpy(MsgTxt[0], "  FileNova Quick Reference  4/6                             ");
            strcpy(MsgTxt[1], "                                                            ");
            strcpy(MsgTxt[2], "[ CTRL+Alphabet keys(1/2) ]                                 ");
            strcpy(MsgTxt[3], "  A                            I                            ");
            strcpy(MsgTxt[4], "  B                            J                            ");
            strcpy(MsgTxt[5], "  C (PageUp)                   K                            ");
            strcpy(MsgTxt[6], "  D (Right allow)              L                            ");
            strcpy(MsgTxt[7], "  E (Up allow)                 M (Enter)                    ");
            strcpy(MsgTxt[8], "  F                            N                            ");
            strcpy(MsgTxt[9], "  G Separate an extension      O                            ");
            strcpy(MsgTxt[10],"  H (Backspace)                P                            ");
            strcpy(MsgTxt[11],"                                                            ");
            strcpy(MsgTxt[12],"   Up/PageUp:Prev    Down/PageDown:Next   Enter/Esc:Back    ");
         }
         else{
            strcpy(MsgTxt[0], "  FileNova �̎g�p����  4/6                                  ");
            strcpy(MsgTxt[1], "                                                            ");
            strcpy(MsgTxt[2], "��CTRL+�����L�[�̋@�\\(1/2)                                  ");
            strcpy(MsgTxt[3], "  A                            I                            ");
            strcpy(MsgTxt[4], "  B                            J                            ");
            strcpy(MsgTxt[5], "  C PageDown�L�[�Ɠ���         K                            ");
            strcpy(MsgTxt[6], "  D ���L�[�Ɠ���               L                            ");
            strcpy(MsgTxt[7], "  E ���L�[�Ɠ���               M Enter�L�[�Ɠ���            ");
            strcpy(MsgTxt[8], "  F                            N                            ");
            strcpy(MsgTxt[9], "  G �g���q�̕����\\����ON/OFF   O                            ");
            strcpy(MsgTxt[10],"  H Backspace�L�[�Ɠ���        P                            ");
            strcpy(MsgTxt[11],"                                                            ");
            strcpy(MsgTxt[12],"   Up/PageUp:�O��    Down/PageDown:����   Enter/Esc:�߂�    ");
         }
         break;
       case 5:
         if(English){
            strcpy(MsgTxt[0], "  FileNova Quick Reference  5/6                             ");
            strcpy(MsgTxt[1], "                                                            ");
            strcpy(MsgTxt[2], "[ CTRL+Alphabet keys(2/2) ]                                 ");
            strcpy(MsgTxt[3], "  Q                            Y                            ");
            strcpy(MsgTxt[4], "  R (PageUp)                   Z                            ");
            strcpy(MsgTxt[5], "  S (Left allow)                                            ");
            strcpy(MsgTxt[6], "  T Change time stamps                                      ");
            strcpy(MsgTxt[7], "  U                                                         ");
            strcpy(MsgTxt[8], "  V Edit volume label                                       ");
            strcpy(MsgTxt[9], "  W                                                         ");
            strcpy(MsgTxt[10],"  X (Down)                                                  ");
            strcpy(MsgTxt[11],"                                                            ");
            strcpy(MsgTxt[12],"   Up/PageUp:Prev    Down/PageDown:Next   Enter/Esc:Back    ");
         }
         else{
            strcpy(MsgTxt[0], "  FileNova �̎g�p����  5/6                                  ");
            strcpy(MsgTxt[1], "                                                            ");
            strcpy(MsgTxt[2], "��CTRL+�����L�[�̋@�\\(2/2)                                  ");
            strcpy(MsgTxt[3], "  Q                            Y �@�@�@�@�@�@�@�@�@�@�@     ");
            strcpy(MsgTxt[4], "  R PageUp�L�[�Ɠ���           Z                            ");
            strcpy(MsgTxt[5], "  S ���L�[�Ɠ���               �@�@�@�@�@�@�@�@�@�@�@�@     ");
            strcpy(MsgTxt[6], "  T �^�C���X�^���v�ύX         �@�@�@�@�@�@�@�@�@�@�@�@�@�@ ");
            strcpy(MsgTxt[7], "  U                            �@�@�@�@�@�@�@�@�@�@�@�@     ");
            strcpy(MsgTxt[8], "  V �{�����[�����x���ύX                                    ");
            strcpy(MsgTxt[9], "  W                            �@�@�@�@�@�@�@�@�@�@�@�@�@   ");
            strcpy(MsgTxt[10],"  X ���L�[�Ɠ����@�@�@                                      ");
            strcpy(MsgTxt[11],"                                                            ");
            strcpy(MsgTxt[12],"   Up/PageUp:�O��    Down/PageDown:����   Enter/Esc:�߂�    ");
         }
         break;
       case 6:
         if(English){
            strcpy(MsgTxt[0], "  FileNova Quick Reference  6/6                             ");
            strcpy(MsgTxt[1], "                                                            ");
            strcpy(MsgTxt[2], "[ Function keys ]                                           ");
            strcpy(MsgTxt[3], "                                                            ");
            strcpy(MsgTxt[4], "  F1  Show this help           F7                           ");
            strcpy(MsgTxt[5], "  F2  Customize                F8                           ");
            strcpy(MsgTxt[6], "  F3  Edit history                                          ");
            strcpy(MsgTxt[7], "  F4  Macro                    F9   Copy between HPFS & FAT ");
            strcpy(MsgTxt[8], "                               F10  Change Code Page        ");
            strcpy(MsgTxt[9], "  F5  Refresh                  F11  Duplicate FileNova      ");
            strcpy(MsgTxt[10],"  F6  Open current directory   F12  Product information     ");
            strcpy(MsgTxt[11],"                                                            ");
            strcpy(MsgTxt[12],"   Up/PageUp:Prev                         Enter/Esc:Back    ");
         }
         else{
            strcpy(MsgTxt[0], "  FileNova �̎g�p����  6/6                                  ");
            strcpy(MsgTxt[1], "                                                            ");
            strcpy(MsgTxt[2], "���t�@���N�V�����L�[�̋@�\\                                 ");
            strcpy(MsgTxt[3], "                                                            ");
            strcpy(MsgTxt[4], "  F1  �w���v                   F7                           ");
            strcpy(MsgTxt[5], "  F2  �ݒ�ύX                 F8                           ");
            strcpy(MsgTxt[6], "  F3  �����Ǘ�                                              ");
            strcpy(MsgTxt[7], "  F4  �}�N���I��               F9   HPFS<->FAT�Ԃ̃R�s�[    ");
            strcpy(MsgTxt[8], "                               F10  �R�[�h�y�[�W�؂芷��    ");
            strcpy(MsgTxt[9], "  F5  �ŐV�\\��                 F11  FileNova�������ЂƂN��");
            strcpy(MsgTxt[10],"  F6  ���݂��ިڸ�؂�WPS�ɊJ�� F12  �o�[�W�������          ");
            strcpy(MsgTxt[11],"                                                            ");
            strcpy(MsgTxt[12],"   Up/PageUp:�O��                         Enter/Esc:�߂�    ");
         }
         break;
    }   
    
    return 13; 

}

/******************************************************************/
/**   ShowHelp                                                   **/
/******************************************************************/
 void ShowHelp(void)
{
    USHORT us_helppage=1;
   
    for(;;) {
       ShowMsgBox(SetHelpMsg(&us_helppage), bt_g_InformWindowColor);

       KbdCharIn(&KeyInfo,IO_WAIT,0); 
       Convert_WordStarLikeKey(&KeyInfo, FLAG_MODE_FILER);
       switch(KeyInfo.chChar){
          case ESC:
          case ENTER:
             ShowFileList();
             return;
       }
       switch(KeyInfo.chScan){
          case ARROW_UP:
          case PAGE_UP:
             us_helppage--;
             break;
          case ARROW_DOWN:
          case PAGE_DOWN:
             us_helppage++;
             break;
          case PF1:
             ShowFileList();
             return;
       }
    }

}

/*****************************************************************/
/**   ShowMsgBox                                                **/
/*****************************************************************/
 void ShowMsgBox(USHORT us_msgboxrow, BYTE bt_msgboxattr)
 {
    BoxWide=strlen(MsgTxt[0]); 
    if (BoxWide+7<ColMax) {
       BoxWide+=6;
    } else {
       BoxWide=ColMax;
    }

    if (us_msgboxrow+4 < FILER_LISTWINSIZE-1) { 
       BoxHigh = us_msgboxrow+4; 
    } else { 
       BoxHigh = FILER_LISTWINSIZE-1;
    }
    BoxTop=(RowMax-BoxHigh)/2+1;
    if(BoxTop < FILER_TOP_MARGIN) BoxTop=FILER_TOP_MARGIN;
    BoxLeft=(ColMax-BoxWide)/2;

    ShowMsgBox_OutLine(us_msgboxrow, bt_msgboxattr);
 }

/*****************************************************************/
/**   ShowMsgBox_Line                                           **/
/*****************************************************************/
 void ShowMsgBox_Line(USHORT us_DispRow, BYTE bt_msgboxattr)
 {
    if (us_DispRow<BoxHigh-4) 
       VioWrtCharStrAtt(MsgTxt[us_DispRow], BoxWide-6,
                BoxTop+2+us_DispRow, BoxLeft+3, &bt_msgboxattr, VIO_HANDLE);
 }

/*****************************************************************/
/**   ShowMsgBox_OutLine                                        **/
/**-------------------------------------------------------------**/
/**  ���� BoxWide = (MsgTxt�̕�����)+6,                         **/
/**       BoxHigh= (MsgTxt�̗�)+4, �݂̂��l��                 **/
/**     ����ȊO�͂���������Hard Cording�����Ƃ����Ȃ��Ɩ��Ӗ�  **/
/*****************************************************************/
 void ShowMsgBox_OutLine(USHORT us_msgboxrow, BYTE bt_msgboxattr)
 {
    USHORT us_count;

    VioWrtNAttr(&bt_msgboxattr,BoxWide,  BoxTop,          BoxLeft,          VIO_HANDLE);
    VioWrtNChar (LineChar_DR,  1,        BoxTop,          BoxLeft,          VIO_HANDLE);
    VioWrtNChar (LineChar_H,   BoxWide-2,BoxTop,          BoxLeft+1,        VIO_HANDLE);
    VioWrtNChar (LineChar_DL,  1,        BoxTop,          BoxLeft+BoxWide-1,VIO_HANDLE);
    VioWrtNAttr(&bt_msgboxattr,BoxWide,  BoxTop+1,        BoxLeft,          VIO_HANDLE);
    VioWrtNChar (LineChar_V,   1,        BoxTop+1,        BoxLeft,          VIO_HANDLE);
    VioWrtNChar (" ",          BoxWide-2,BoxTop+1,        BoxLeft+1,        VIO_HANDLE);
    VioWrtNChar (LineChar_V,   1,        BoxTop+1,        BoxLeft+BoxWide-1,VIO_HANDLE);

    for (us_count=0; us_count<us_msgboxrow; us_count++){
       if (us_count<BoxHigh-4) {
          VioWrtNAttr(&bt_msgboxattr,3,BoxTop+2+us_count,BoxLeft,  VIO_HANDLE);
          VioWrtNChar (" ",          2,BoxTop+2+us_count,BoxLeft+1,VIO_HANDLE);
          VioWrtNChar (LineChar_V,   1,BoxTop+2+us_count,BoxLeft,  VIO_HANDLE);
          VioWrtNAttr(&bt_msgboxattr,3,BoxTop+2+us_count,BoxLeft+BoxWide-3,VIO_HANDLE);
          VioWrtNChar (" ",          2,BoxTop+2+us_count,BoxLeft+BoxWide-3,VIO_HANDLE);
          VioWrtNChar (LineChar_V,   1,BoxTop+2+us_count,BoxLeft+BoxWide-1,VIO_HANDLE);
       }
       ShowMsgBox_Line(us_count, bt_msgboxattr);
    }

    VioWrtNAttr(&bt_msgboxattr,BoxWide,  BoxTop+BoxHigh-2,BoxLeft,          VIO_HANDLE);
    VioWrtNChar (LineChar_V,   1,        BoxTop+BoxHigh-2,BoxLeft,          VIO_HANDLE);
    VioWrtNChar (" ",          BoxWide-2,BoxTop+BoxHigh-2,BoxLeft+1,        VIO_HANDLE);
    VioWrtNChar (LineChar_V,   1,        BoxTop+BoxHigh-2,BoxLeft+BoxWide-1,VIO_HANDLE);
    VioWrtNAttr(&bt_msgboxattr,BoxWide,  BoxTop+BoxHigh-1,BoxLeft,          VIO_HANDLE);
    VioWrtNChar (LineChar_UR,  1,        BoxTop+BoxHigh-1,BoxLeft,          VIO_HANDLE);
    VioWrtNChar (LineChar_H,   BoxWide-2,BoxTop+BoxHigh-1,BoxLeft+1,        VIO_HANDLE);
    VioWrtNChar (LineChar_UL,  1,        BoxTop+BoxHigh-1,BoxLeft+BoxWide-1,VIO_HANDLE);
 }

/*****************************************************************/
/**   ShowMsgBoxNull                                            **/
/*****************************************************************/
 void ShowMsgBoxNull(void)
 {
    USHORT us_count;

    for (us_count=0; us_count<BoxHigh; us_count++){
       VioWrtNAttr(&bt_g_FilerBackGroundColor,
                         BoxWide,BoxTop+us_count,BoxLeft,VIO_HANDLE);
       VioWrtNChar (" ", BoxWide,BoxTop+us_count,BoxLeft,VIO_HANDLE);
    }
 }

/******************************************************************/
/**   ShowMsgCopyOk                                              **/
/******************************************************************/
 void ShowMsgCopyOk(void)
 {
    if(English){
       strcpy(MsgTxt[0],"Copying/Moving file(s)");
       strcpy(MsgTxt[1],"    was completed.    ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C���̃R�s�[�^�ړ�");
       strcpy(MsgTxt[1],"    ���������܂���    ");
    }

    MsgBoxDisp(2, bt_g_InformWindowColor, IO_NOWAIT);
 }

/******************************************************************/
/**   ShowMsgCopyStop                                            **/
/******************************************************************/
 void ShowMsgCopyStop(void)
 {
    ShowFileList();

    if(English){
       strcpy(MsgTxt[0],"  Copying file(s) ");
       strcpy(MsgTxt[1],"   was canceled.  ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C���̃R�s�[��");
       strcpy(MsgTxt[1],"  ���~����܂���  ");
    }

    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
 }

/******************************************************************/
/**   ShowMsgCrcErr                                              **/
/******************************************************************/
 void ShowMsgCrcErr(void)
 {
    strcpy(MsgTxt[0],
           English ? "Data CRC error detected." :
                     "�f�[�^�b�q�b�G���[�ł�");

    MsgBoxDisp(1, bt_g_WarningWindowColor, IO_WAIT);
 }

/******************************************************************/
/**   ShowMsgDeleteErr                                           **/
/******************************************************************/
 void ShowMsgDeleteErr(void)
 {
    if(English){
       strcpy(MsgTxt[0],"The file(or directory) can't copy/delete.");
       strcpy(MsgTxt[1],"Other processes may be referring to it.  ");
    }
    else{
       strcpy(MsgTxt[0],"̧��/�ިڸ�ذ�̺�߰/�폜���ł��܂���   ");
       strcpy(MsgTxt[1],"������۾��ŎQ�ƒ��łȂ����m�F���ĉ�����");
    }
 
    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
 }

/******************************************************************/
/**   ShowMsgDeleteDeny                                          **/
/******************************************************************/
 void ShowMsgDeleteDeny(void)
 {
    if(English){
       strcpy(MsgTxt[0],"Deleting file(s) was failed.      ");
       strcpy(MsgTxt[1],"Check an attribute of target file.");
    }
    else{
       strcpy(MsgTxt[0],"̧�ق̍폜���ł��܂���    ");
       strcpy(MsgTxt[1],"�����݋֎~���m�F���ĉ�����");
    }
    
    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
 }

/******************************************************************/
/**   ShowMsgDeleteStop                                          **/
/******************************************************************/
 void ShowMsgDeleteStop(void)
 {
    ShowFileList();
    if(English){
       strcpy(MsgTxt[0],"Deleting file(s)");
       strcpy(MsgTxt[1],"  was canceled. ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C���̍폜��");
       strcpy(MsgTxt[1]," ���~����܂��� ");
    }

    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
 }

/******************************************************************/
/**   ShowMsgDiskFull                                            **/
/******************************************************************/
 void ShowMsgDiskFull(void)
 {
    if(English){
       strcpy(MsgTxt[0],"    Disk full.    ");
    }
    else{
       strcpy(MsgTxt[0],"�f�B�X�N����t�ł�");
    }

    MsgBoxDisp(1, bt_g_WarningWindowColor, IO_WAIT);
 }

/******************************************************************/
/**   ShowMsgDriveErr                                            **/
/******************************************************************/
 void ShowMsgDriveErr(void)
 {
    if(English){
       strcpy(MsgTxt[0],"    Drive is     ");
       strcpy(MsgTxt[1],"  not connected. ");
    }
    else{
       strcpy(MsgTxt[0],"  ���̃h���C�u��  ");
       strcpy(MsgTxt[1],"�ڑ�����Ă��܂���");
    }

    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
 }

/******************************************************************/
/**   ShowMsgDriveNotReady                                       **/
/******************************************************************/
 void ShowMsgDriveNotReady(void)
 {
    strcpy(MsgTxt[0],
           English ? " Drive is not ready." :
                     "�h���C�u���������ł�");

    MsgBoxDisp(1, bt_g_WarningWindowColor, IO_WAIT);
 }

/******************************************************************/
/**   ShowMsgErr                                                 **/
/******************************************************************/
 void ShowMsgErr(APIRET apr_errorcode)
 {
    strcpy(MsgTxt[0],
           English ? " The error occurred." :
                     "�G���[���������܂���");
    strcpy(MsgTxt[1],"                    ");

    sprintf(MsgTxt[1]," RC: %u", apr_errorcode);

    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
 }

/******************************************************************/
/**   ShowMsgExecErr                                             **/
/******************************************************************/
 void ShowMsgExecErr(APIRET apr_errorcode, PSZ psz_execerr_fname)
 {
    if(English){
       strcpy(MsgTxt[0],"The error of execution program occurred.");
       strcpy(MsgTxt[1],"Return code:                            ");
       strcpy(MsgTxt[2],"Msg:                                    ");
    }
    else{
       strcpy(MsgTxt[0],"�v���O�����̎��s�ŃG���[���������܂���");
       strcpy(MsgTxt[1],"���^�[���R�[�h:                       ");
       strcpy(MsgTxt[2],"Msg:                                  ");
    }
    
    sprintf(English ? MsgTxt[1]+13 : MsgTxt[1]+16,"%04d", apr_errorcode);
    strcpy(MsgTxt[2]+4, psz_execerr_fname);

    MsgBoxDisp(3, bt_g_WarningWindowColor, IO_WAIT);
 }

/******************************************************************/
/**   ShowMsgExecNotF                                            **/
/******************************************************************/
 void ShowMsgExecNotF(PSZ psz_notfound_fname)
 {
    if(English){
       strcpy(MsgTxt[0],"The error of execution program occurred.");
       strcpy(MsgTxt[1],"This file is not found.                 ");
       strcpy(MsgTxt[2],"Msg:                                    ");
    }
    else{
       strcpy(MsgTxt[0],"�v���O�����̎��s�ŃG���[���������܂���");
       strcpy(MsgTxt[1],"�ȉ��̃t�@�C����������܂���        ");
       strcpy(MsgTxt[2],"Msg:                                  ");
    }

    strcpy(MsgTxt[2]+4, psz_notfound_fname);

    MsgBoxDisp(3, bt_g_WarningWindowColor, IO_WAIT);
 }

/******************************************************************/
/**   ShowMsgExecOk                                              **/
/******************************************************************/
 void ShowMsgExecOk(void)
 {
    if(English){
       strcpy(MsgTxt[0],"Execution program ");
       strcpy(MsgTxt[1],"    succeeded.    ");
    }
    else{
       strcpy(MsgTxt[0],"�v���O�����̎��s��");
       strcpy(MsgTxt[1],"  �������܂���    ");
    }

    MsgBoxDisp(2, bt_g_InformWindowColor, IO_NOWAIT);
 }

/******************************************************************/
/**   ShowMsgFindStop                                            **/
/******************************************************************/
 VOID ShowMsgFileNotFound(PSZ psz_filename) 
 {
    strcpy(MsgTxt[0],
           English ? "Target file is not found.         " :
                     "�w�肳�ꂽ�t�@�C����������܂���");
    strcpy(MsgTxt[1],"                                  ");

    sprintf(MsgTxt[1], " File: %s", psz_filename);

    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
 }

/******************************************************************/
/**   ShowMsgFindStop                                            **/
/******************************************************************/
 void ShowMsgFindStop(void)
 {
    ShowFileList();

    if(English){
       strcpy(MsgTxt[0],"Searching file(s)");
       strcpy(MsgTxt[1],"  was canceled.  ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C���̌�����");
       strcpy(MsgTxt[1]," ���~����܂��� ");
    }

    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
 }

/******************************************************************/
/**   ShowMsgFormatErr                                           **/
/******************************************************************/
 void ShowMsgFormatErr(void)
 {
    if(English){
       strcpy(MsgTxt[0],"Format of this drive");
       strcpy(MsgTxt[1],"     is unknown.    ");
    }
    else{
       strcpy(MsgTxt[0],"��ײ�ނ�̫�ϯĂ�");
       strcpy(MsgTxt[1]," �F���ł��܂��� ");
    }

    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
 }


/*******************************************************************/
/**   ShowMsgIconErr                                              **/
/*******************************************************************/
 void ShowMsgIconErr(void)
 {
    if(English){
       strcpy(MsgTxt[0],"Creating the icon was failed.               ");
       strcpy(MsgTxt[1],"There may be already an icon of same name.  ");
    }
    else{
       strcpy(MsgTxt[0],"�G���|���������A�C�R���͓o�^����܂���ł���");
       strcpy(MsgTxt[1],"�������O�̃A�C�R�����Ȃ����m�F���ĉ�����    ");
    }

    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
 }

/*******************************************************************/
/**   ShowMsgIconOk                                               **/
/*******************************************************************/
 void ShowMsgIconOk(void)
 {
    if(English){
       strcpy(MsgTxt[0],"  Creating icon(s) was  ");
       strcpy(MsgTxt[1],"        completed.      ");
    }
    else{
       strcpy(MsgTxt[0],"�f�X�N�g�b�v�ɃA�C�R����");
       strcpy(MsgTxt[1],"    �o�^����܂���      ");
    }

    MsgBoxDisp(2, bt_g_InformWindowColor, IO_NOWAIT);
 }

/*******************************************************************/
/**   ShowMsgIconReg                                              **/
/*******************************************************************/
 void ShowMsgIconReg(void)
 {
    if(English){
       strcpy(MsgTxt[0],"Now creating icon(s).");
       strcpy(MsgTxt[1],"                     ");
    }
    else{
       strcpy(MsgTxt[0],"�A�C�R���̓o�^���ł�");
       strcpy(MsgTxt[1],"                    ");
    }

    ShowMsgBox(2, bt_g_InformWindowColor);
 }

/*******************************************************************/
/**   ShowMsgInvalidExe                                           **/
/*******************************************************************/
 VOID ShowMsgInvalidExe(PSZ psz_filename)
 {
    strcpy(MsgTxt[0],
           English ? "This file is not executable.    " :
                     "���s�\\�ȃt�@�C���ł͂���܂���");
    strcpy(MsgTxt[1],"                                ");

    sprintf(MsgTxt[1]," File: %s", psz_filename);

    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);

 }

/*****************************************************************/
/**   ShowMsgLocked                                             **/
/*****************************************************************/
 void ShowMsgLocked(void)
 {
    strcpy(MsgTxt[0],
           English ? "This drive is locked by other proccess." :
                     "��ײ�ނ�������۾���ۯ�����Ă��܂�");

    MsgBoxDisp(1, bt_g_WarningWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowMsgMoveStop                                           **/
/*****************************************************************/
 void ShowMsgMoveStop(void)
 {
    if(English){
       strcpy(MsgTxt[0]," Moving file(s) ");
       strcpy(MsgTxt[1],"  was canceled. ");
    }
    else{
       strcpy(MsgTxt[0],"�t�@�C���̈ړ���");
       strcpy(MsgTxt[1]," ���~����܂��� ");
    }

    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowMsgNameErr                                            **/
/*****************************************************************/
 void ShowMsgNameErr(PSZ psz_oldname)
 {
    if(English){
       strcpy(MsgTxt[0],"Renaming file(or directory) was failed.           ");
       strcpy(MsgTxt[1],"                                                  ");
       strcpy(MsgTxt[2],"                                                  ");
       strcpy(MsgTxt[3],"There may be already a file of same name.         ");
       strcpy(MsgTxt[4],"Or, other processes may be referring to this file.");
    }
    else{
       strcpy(MsgTxt[0],"���O�̕ύX���ł��܂���                ");
       strcpy(MsgTxt[1],"                                      ");
       strcpy(MsgTxt[2],"                                      ");
       strcpy(MsgTxt[3],"���ꖼ�̃t�@�C�����Ȃ����m�F���ĉ�����");
       strcpy(MsgTxt[4],"���̃v���Z�X�ŎQ�ƒ��̉\\��������܂�");
    }

    sprintf(MsgTxt[1], "  File/Dir : %s",  psz_oldname);

    MsgBoxDisp(5, bt_g_WarningWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowMsgChangeDirNameUsing                                 **/
/*****************************************************************/
 void ShowMsgChangeDirNameUsing(PSZ psz_oldname)
 {
    if(English){
       strcpy(MsgTxt[0],"Renaming directory was failed.        ");
       strcpy(MsgTxt[1],"                                      ");
       strcpy(MsgTxt[2],"                                      ");
       strcpy(MsgTxt[3],"This directory is used by other       ");
       strcpy(MsgTxt[4],"processes now.                        ");
    }
    else{
       strcpy(MsgTxt[0],"���O�̕ύX���ł��܂���                ");
       strcpy(MsgTxt[1],"                                      ");
       strcpy(MsgTxt[2],"                                      ");
       strcpy(MsgTxt[3],"���̃f�B���N�g���͑��̃v���Z�X�����ݎg");
       strcpy(MsgTxt[4],"�g�p���Ă��܂�                        ");
    }

    sprintf(MsgTxt[1], "  Dir : %s",  psz_oldname);

    MsgBoxDisp(5, bt_g_WarningWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowMsgNameLong                                           **/
/*****************************************************************/
 void ShowMsgNameLong(void)
 {
    strcpy(MsgTxt[0],
           English ? "The name is too long." :
                     "���O�����߂��܂�");

    MsgBoxDisp(1, bt_g_WarningWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowMsgNameNg                                             **/
/*****************************************************************/
 void ShowMsgNameNg(void)
 {
    strcpy(MsgTxt[0],
           English ? "The appointment is invalid." :
                     "�w�肪�����ł�");

    MsgBoxDisp(1, bt_g_WarningWindowColor, IO_WAIT);
 }

/******************************************************************/
/**   ShowMsgNotFound                                            **/
/******************************************************************/
 void ShowMsgNotFound(void)
 {
    ShowFileList();
    strcpy(MsgTxt[0],
           English ? "Target file is not found." :
                     "���̃t�@�C���͌�����܂���");

    MsgBoxDisp(1, bt_g_WarningWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowMsgPassNg                                             **/
/*****************************************************************/
 void ShowMsgPassNg(PSZ psz_error_fname)
 {
    if(English){
       strcpy(MsgTxt[0],"The file of same name already exists.");
       strcpy(MsgTxt[1],"The directory can't create/copy.     ");
       strcpy(MsgTxt[2],"                                     ");
    }
    else{
       strcpy(MsgTxt[0],"���̖��O��̧�قƂ��đ��݂��Ă��܂�");
       strcpy(MsgTxt[1],"�ިڸ�ذ�̍쐬/��߰�͂ł��܂���   ");
       strcpy(MsgTxt[2],"                                  ");
    }
    
    strcpy(MsgTxt[2]+2, psz_error_fname);

    MsgBoxDisp(3, bt_g_WarningWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowMsgPassNo                                             **/
/*****************************************************************/
 void ShowMsgPassNo(PSZ psz_dirname)
 {
    strcpy(MsgTxt[0],
           English ? "The directory is not found.               " :
                     "�w�肳�ꂽ�f�B���N�g����������܂���");
    strcpy(MsgTxt[1],"                                      ");

    sprintf(MsgTxt[1], "  Dir: %s", psz_dirname);

    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowMsgSameDir                                            **/
/*****************************************************************/
 void ShowMsgSameDir(void)
 {
    if(English){
       strcpy(MsgTxt[0],"Copying to same directory");
       strcpy(MsgTxt[1],"     is not possible.    ");
    }
    else{
       strcpy(MsgTxt[0],"�����ިڸ�ذ�ւ�     ");
       strcpy(MsgTxt[1],"��߰/�ړ��͂ł��܂���");
    }
    strcpy(MsgTxt[2],"                     ");

    strcpy(MsgTxt[2]+1,InpLine);

    MsgBoxDisp(3, bt_g_WarningWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowMsgSameName                                           **/
/*****************************************************************/
 void ShowMsgSameName(void)
 {
    strcpy(MsgTxt[0],
           English ? "The file(or directory) of same name already exists." :
                     "���ꖼ�����݂��܂�");
    
    MsgBoxDisp(1, bt_g_WarningWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowMsgSectorNotFound                                     **/
/*****************************************************************/
 void ShowMsgSectorNotFound(void)
 {
    strcpy(MsgTxt[0],
           English ? "Sector is not found." :
                     "�Z�N�^�[��������܂���");

    MsgBoxDisp(1, bt_g_WarningWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowMsgSharedErr                                          **/
/*****************************************************************/
 void ShowMsgSharedErr(PSZ psz_filename)
 {
    if(English){
       strcpy(MsgTxt[0],"Other processes refer to this file now. ");
       strcpy(MsgTxt[1],"This file can't access.                 ");
    }
    else{
       strcpy(MsgTxt[0],"���̃v���Z�X�Ŏg�p���̂��߃t�@�C�������");
       strcpy(MsgTxt[1],"�t�@�C�����̕ύX�^�\\�����͂ł��܂���  ");
    }
    strcpy(MsgTxt[2],"                                        ");

    if(psz_filename) sprintf(MsgTxt[2], "File: %s", psz_filename);

    MsgBoxDisp(3, bt_g_WarningWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowMsgTooLongStr                                         **/
/*****************************************************************/
 void ShowMsgTooLongStr(void)
 {
    ShowFileList();
    if(English){
       strcpy(MsgTxt[0],"Inputted string is too long.        ");
       strcpy(MsgTxt[1],"This command can't execute.         ");
    }
    else{
       strcpy(MsgTxt[0],"���͂��ꂽ�����񒷂��������z���܂���");
       strcpy(MsgTxt[1],"�R�}���h�͎��s����܂���@�@�@�@�@�@");
    }

    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowMsgVersionInfo                                        **/
/*****************************************************************/
 void ShowMsgVersionInfo(void)
 {
    if(English){
       strcpy(MsgTxt[0],"                                               ");
       strcpy(MsgTxt[1],"                                               ");
       strcpy(MsgTxt[2]," <FileNova is based on FileStar Version 2.33>  ");
       strcpy(MsgTxt[3],"                                               ");
       strcpy(MsgTxt[4]," Copyright    George(Takahiro Shimada)         ");
       strcpy(MsgTxt[5],"                 (KGG02311@nifty.ne.jp)        ");
       strcpy(MsgTxt[6]," Current Maintenance   Toshiaki Okabayashi     ");
       strcpy(MsgTxt[7],"                 (sctokab@ipc.shizuoka.ac.jp)  ");
    } else {
       strcpy(MsgTxt[0],"                                               ");
       strcpy(MsgTxt[1],"                                               ");
       strcpy(MsgTxt[2]," <FileNova is based on FileStar Version 2.33>  ");
       strcpy(MsgTxt[3],"                                               ");
       strcpy(MsgTxt[4],"���쌠�ҁE�J����    �feorge(���c���L)          ");
       strcpy(MsgTxt[5],"                 (KGG02311@nifty.ne.jp)        ");
       strcpy(MsgTxt[6],"����ҎҁE�A����    ���ї���                   ");
       strcpy(MsgTxt[7],"                 (sctokab@ipc.shizuoka.ac.jp)  ");
    }
    strcpy(MsgTxt[0], FILESTAR_VERSION[English]);
    strcpy(MsgTxt[1], FILESTAR_DATETIME);

    MsgBoxDisp(8, bt_g_InformWindowColor, IO_WAIT);


    if(English){
       strcpy(MsgTxt[0],"                                               ");
       strcpy(MsgTxt[1],"                                               ");
       strcpy(MsgTxt[2],"    Special thanks for their contribution      ");
       strcpy(MsgTxt[3],"                                               ");
       strcpy(MsgTxt[4],"      A.Y.DAYO, achain, chagrin, kenn,         ");
       strcpy(MsgTxt[5],"                                               ");
       strcpy(MsgTxt[6],"        and some people sending bug reports... ");
       strcpy(MsgTxt[7],"                                               ");
    } else {
       strcpy(MsgTxt[0],"  Filenova �̊J���ɂ����͉�������              ");
       strcpy(MsgTxt[1],"           �ȉ��̕��X�ɐS��芴�Ӓv���܂�      ");
       strcpy(MsgTxt[2],"                                               ");
       strcpy(MsgTxt[3],"      A.Y.DAYO ����, �����Ⴂ�� ����           ");
       strcpy(MsgTxt[4],"         chagrin ����, kenn ����               ");
       strcpy(MsgTxt[5],"                                               ");
       strcpy(MsgTxt[6],"   ���̑��A�o�O���|�[�g�������艺�������F����  ");
       strcpy(MsgTxt[7],"                                               ");
    }

//    GetMode();
//    sprintf(MsgTxt[7], "     CodePage  %d,  %d,  %d", CodePage[0], CodePage[1], CodePage[2]);

    MsgBoxDisp(8, bt_g_InformWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowMsgWriteProtect                                       **/
/*****************************************************************/
 void ShowMsgWriteProtect(void)
 {
    strcpy(MsgTxt[0],
           English ? "Write protected." :
                     "�������݋֎~�ł�");
    strcpy(MsgTxt[1],"                ");
    
    strcpy(MsgTxt[1]+1, InpLine);
    MsgBoxDisp(2, bt_g_WarningWindowColor, IO_WAIT);
 }

/*****************************************************************/
/**   ShowNewDrive                                              **/
/*****************************************************************/
 void ShowNewDrive(void)
 {
    APIRET apr_FindFirst;
    
    QDrive();
    QDir();
    apr_FindFirst = QFile();
    ShowFileList_FilePosition(0);
    if (apr_FindFirst == ERROR_NOT_DOS_DISK) 
       ShowMsgFormatErr();
 }

/******************************************************************/
/**   ShowSummarySize                                            **/
/******************************************************************/
#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
 void ShowSummarySize(PSZ psz_dirname, ULONG ul_FileSizeSum, ULONG ul_filecount )
#else
 void ShowSummarySize(PSZ psz_dirname, unsigned long long ull_FileSizeSum, ULONG ul_filecount )
#endif
 {
    if(English){
       strcpy(MsgTxt[0],"Total size of this directory.      ");
       strcpy(MsgTxt[1],"                                   ");
       strcpy(MsgTxt[2],"Directory     :                    ");
       strcpy(MsgTxt[3],"Number of file:                    ");
       strcpy(MsgTxt[4],"Total size    :                    ");
    }
    else{
       strcpy(MsgTxt[0],"�f�B���N�g���ȉ��̑��t�@�C���T�C�Y ");
       strcpy(MsgTxt[1],"                                   ");
       strcpy(MsgTxt[2],"�f�B���N�g����:                    ");
       strcpy(MsgTxt[3],"�t�@�C����    :                    ");
       strcpy(MsgTxt[4],"�T�C�Y���v    :                    ");
    }

    strcpy (MsgTxt[2]+16, psz_dirname);

    if(English){
       sprintf(MsgTxt[3]+16,"%u", ul_filecount);
#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
       sprintf(MsgTxt[4]+16,"%u Byte", ul_FileSizeSum);
#else
       sprintf(MsgTxt[4]+16,"%llu Byte", ull_FileSizeSum);
#endif
    }
    else{
       sprintf(MsgTxt[3]+16,"%u", ul_filecount);
#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
       sprintf(MsgTxt[4]+16,"%u �o�C�g", ul_FileSizeSum);
#else
       sprintf(MsgTxt[4]+16,"%llu �o�C�g", ull_FileSizeSum);
#endif
    }

    MsgBoxDisp(5, bt_g_InformWindowColor, IO_WAIT);
 }

/******************************************************************/
/*   MsgBoxDisp                                                   */
/******************************************************************/
VOID MsgBoxDisp(USHORT us_msgboxrow, BYTE us_msgboxattr, 
                USHORT us_flag_wait)
{
    ShowMsgBox(us_msgboxrow, us_msgboxattr); 
    if(us_flag_wait == IO_WAIT) 
       KbdCharIn(&KeyInfo,IO_WAIT,0); 
    else
       DosSleep(400L);  /* 0.4�b�\�� */

    ShowFileList(); 
 }

/**************************************************************/
/**   SummarySize                                            **/
/**************************************************************/
 VOID SummarySize(PSZ DirNm)
 {

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
    ULONG  ul_FileSizeSum=0ul;
#else
    unsigned long long ull_FileSizeSum=0ull;
#endif
    ULONG ul_filecount = 0;

    USHORT us_flg_filesize;
    UCHAR  usz_currentdir[_MAX_PATH], usz_targetdir[_MAX_PATH];

    strcpy(usz_targetdir, DirNm); /* �p�X���̑ޔ�(QFile�p)*/
    SetFullCurrentPathName(usz_currentdir);

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
    SummarySizeDisp(FLAG_FIRST, "", ul_FileSizeSum);
    us_flg_filesize=SummarySizeCalc(DirNm, usz_currentdir, &ul_FileSizeSum, &ul_filecount ); 
#else
    SummarySizeDisp(FLAG_FIRST, "", ull_FileSizeSum);
    us_flg_filesize=SummarySizeCalc(DirNm, usz_currentdir, &ull_FileSizeSum, &ul_filecount ); 
#endif
    
    QFile();
    ShowFileList();
    if(us_flg_filesize != FLAG_CANCELED_BY_USER) {

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
       ShowSummarySize(usz_targetdir, ul_FileSizeSum, ul_filecount);
#else
       ShowSummarySize(usz_targetdir, ull_FileSizeSum, ul_filecount);
#endif
    }
 }

/**************************************************************/
/**   SummarySizeCalc                                        **/
/**************************************************************/
#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
 USHORT SummarySizeCalc(PSZ DirNm, PSZ psz_parentdir, PULONG pul_FileSizeSum, PULONG pul_filecount )
#else
 USHORT SummarySizeCalc(PSZ DirNm, PSZ psz_parentdir, unsigned long long *pull_FileSizeSum, PULONG pul_filecount )
#endif
 {
    ULONG  ul_count, ul_PathLen, ul_dircount=0;
    USHORT us_flg_filesize = NO_ERROR;
    UCHAR  usz_FulFlNm[_MAX_PATH];


    DosSetCurrentDir(DirNm);
    ul_PathLen=(ULONG)(sizeof(PathDis)-2);
    DosQueryCurrentDir(0, PathDis+1, &ul_PathLen);

    /*----------------------------------*/
    /*   �܂�Dir�ȊO�̃T�C�Y�����v      */
    /*----------------------------------*/
    QFile_LoadFileList(FLAG_LOADFILELIST_ANYFILE, "*.*"); 

    {
      int i;
      for( i = 0 ;i<FlCnt ;i++ ){
        if( !(FlDis[i].Atr&FILE_DIRECTORY) ) (*pul_filecount)++;
      }
    }

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
    *pul_FileSizeSum += CurrentSize; 
    SetFullCurrentPathName(usz_FulFlNm);
    SummarySizeDisp(FLAG_NOT_FIRST, usz_FulFlNm, *pul_FileSizeSum);
#else
    *pull_FileSizeSum += CurrentSize; 
    SetFullCurrentPathName(usz_FulFlNm);
    SummarySizeDisp(FLAG_NOT_FIRST, usz_FulFlNm, *pull_FileSizeSum);
#endif

    /*---------------------------------*/
    /*   SubDir�݂̂̃��X�g�����      */
    /*---------------------------------*/
    for (ul_count=0; ul_count<FlCnt
                     &&us_flg_filesize != FLAG_CANCELED_BY_USER; ul_count++){
       KbdCharIn(&KeyInfo,IO_NOWAIT,0);
       if(KeyInfo.chChar == ESC) us_flg_filesize = FLAG_CANCELED_BY_USER;
       if(FlDis[ul_count].Atr&FILE_DIRECTORY) {
          FlDis[ul_dircount]=FlDis[ul_count];
          ul_dircount++;
       }
    }

    /*---------------------------------*/
    /*   SubDir�̒����ċA�I�ɒ��ׂ�    */
    /*---------------------------------*/
    for (ul_count=0; ul_count<ul_dircount
                     &&us_flg_filesize != FLAG_CANCELED_BY_USER; ul_count++){
       if(strcmp(FlDis[ul_count].Nm+DISP_FN, ".")
              &&strcmp(FlDis[ul_count].Nm+DISP_FN, "..")) {
              
#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
          us_flg_filesize = SummarySizeCalc(FlDis[ul_count].Nm+DISP_FN, "..", pul_FileSizeSum, pul_filecount );
#else
          us_flg_filesize = SummarySizeCalc(FlDis[ul_count].Nm+DISP_FN, "..", pull_FileSizeSum, pul_filecount );
#endif

          QFile_LoadFileList(FLAG_LOADFILELIST_DIRONLY, "*.*"); 
             /*�@���X�g�̍�蒼�� */
       }
    }

    DosSetCurrentDir(psz_parentdir);
    memset(PathDis+1, 0, ul_PathLen);
    DosQueryCurrentDir(0, PathDis+1, &ul_PathLen);
    return us_flg_filesize ;
 }

/****************************************************************/
/**   SummarySizeDisp                                          **/
/****************************************************************/
#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
 void SummarySizeDisp(USHORT us_flg_firstdisp, PSZ FlNm, ULONG Size)
#else
 void SummarySizeDisp(USHORT us_flg_firstdisp, PSZ FlNm, unsigned long long Size)
#endif
 {
    if(English){
       strcpy(MsgTxt[0],"Now calculating total size:             ");
       strcpy(MsgTxt[1],"                                        ");
    }
    else{
       strcpy(MsgTxt[0],"�T�C�Y���v�̌v�Z��:                   ");
       strcpy(MsgTxt[1],"                                      ");
    }

    if (us_flg_firstdisp == FLAG_FIRST) {
       ShowMsgBox(2, bt_g_InformWindowColor);
    } else {

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */
       sprintf( English ? MsgTxt[0]+28 : MsgTxt[0]+26, "%lu", Size);
#else
       sprintf( English ? MsgTxt[0]+28 : MsgTxt[0]+26, "%llu", Size);
#endif
       strcpy(MsgTxt[1]+1, FlNm);
       ShowMsgBox_Line(0, bt_g_InformWindowColor);
       ShowMsgBox_Line(1, bt_g_InformWindowColor);
    }
 }

/*****************************************************************/
/**   ViewFile_Ready                                            **/
/*****************************************************************/
 void ViewFile_Ready(PSZ psz_filename,BOOL binary)
 {
    ULONG ul_logicalline=0L;
    APIRET apr_existornot, apr_viewfile;
#ifdef IBMCSET  /* ��e�ʃt�@�C���΍�����Ȃ� */
    FILESTATUS3 fs3_PathInfo3={{0}};
#else
    FILESTATUS3L fs3_PathInfo3={{0}};
#endif
    ULONG ul_filesize;

    if(!FlCnt) return;
#ifdef IBMCSET  /* ��e�ʃt�@�C���΍�����Ȃ� */
    apr_existornot=DosQueryPathInfo(psz_filename, FIL_STANDARD,
                              &fs3_PathInfo3, sizeof(FILESTATUS3));
#else
    apr_existornot=lfs_DosQueryPathInfo(psz_filename, FIL_STANDARDL,
                              &fs3_PathInfo3, sizeof(FILESTATUS3L));
#endif
    if(apr_existornot) {
       ErrorMsgDisp(apr_existornot, psz_filename);
       QDriveSize();
       ReDrawAfterDelete();
       return;
    }

    if(!binary) {
       if(ViewerCfg.usUseExtViewer) {
          if(strlen(ViewerCfg.ViewerProg.uszProgName)) 
             ViewFile_ExternalViewer(psz_filename);
          return;
       }   
    }

#ifdef IBMCSET  /* ��e�ʃt�@�C���΍�����Ȃ� */
       ul_filesize = fs3_PathInfo3.cbFile;
#else
    /* file size restriction for NovaView, smaller than 2GB */
    if(fs3_PathInfo3.cbFile > MAX_VIWER_FILESIZE ) {
       ul_filesize = MAX_VIWER_FILESIZE;
    } else {
       ul_filesize = (ULONG)fs3_PathInfo3.cbFile;
    }
#endif

    ul_logicalline = (ULONG)(EditorCfg.usLineSetTop); 
    apr_viewfile=ViewFile(psz_filename, ul_filesize, 
                          &ul_logicalline, &(ViewerCfg.ulTabSize),
                          ViewerCfg. usDefaultCaseSensitive, CodePage[0] ,binary );
    switch(apr_viewfile) {
       default:
          RedrawScreen();
          ErrorMsgDisp(apr_viewfile, psz_filename);
          return;
       case FLAG_VIEWFILE_CALLEDITOR:
          if(EditorCfg.EditorProg.usSession == 1) RedrawScreen();
          FileEdit(psz_filename, 0, FLAG_SILENT_START, ul_logicalline);
          return;
       case FLAG_VIEWFILE_CALLEXTVIEWER:
          if(!strlen(ViewerCfg.ViewerProg.uszProgName)) {
             RedrawScreen();
          } else {
             if(ViewerCfg.ViewerProg.usSession == 1) RedrawScreen();
             if(ViewerCfg.ViewerProg.usSession == 0 
               && ViewFile_ExternalViewer(psz_filename)) {
                 RedrawScreen(); /* ��ʂ̗�������� */
             }
          }
          return;
       case FLAG_VIEWFILE_NOERROR:
          RedrawScreen();
          return;
    }   
  }


/*****************************************************************/
/**   ViewFile_ExternalViewer                                   **/
/*****************************************************************/
APIRET ViewFile_ExternalViewer(PSZ psz_filename)
 {
     return ExecAssocProgram_MsgBox(psz_filename, 
                    ViewerCfg.ViewerProg.uszProgName,  
                    ViewerCfg.ViewerProg.uszParamList, 
                    ViewerCfg.ViewerProg.usSilent = 1, 
                    ViewerCfg.ViewerProg.usSession, 
                    AutoClose,  FLAG_NO_MARK, 1, FLAG_EXECPROG_VIEWER);
 }


/*****************************************************************/
/**   ErrorMsgDisp                                              **/
/*****************************************************************/
 void ErrorMsgDisp(APIRET apr_errorcode, PSZ psz_filename)
 {
    switch(apr_errorcode){
       case NO_ERROR:
          break;
       case ERROR_WRITE_PROTECT: 
          ShowMsgWriteProtect(); 
          break;
       case ERROR_INVALID_NAME: 
          ShowMsgNameNg(); 
          break;
       case ERROR_FILENAME_EXCED_RANGE:
          ShowMsgNameLong(); 
          break;
       case ERROR_INVALID_DRIVE: 
          ShowMsgDriveErr(); 
          break;
       case ERROR_SHARING_VIOLATION: 
          ShowMsgSharedErr(psz_filename); 
          break;
       case ERROR_FILE_NOT_FOUND: 
          ShowMsgFileNotFound(psz_filename); 
          break;
       case ERROR_PATH_NOT_FOUND: 
          ShowMsgPassNo(psz_filename); 
          break;
       case ERROR_DISK_FULL: 
          ShowMsgDiskFull(); 
          break;
       case ERROR_DRIVE_LOCKED: 
          ShowMsgLocked(); 
          break;
       case ERROR_CRC: 
          ShowMsgCrcErr(); 
          break;
       case ERROR_NOT_READY: 
          ShowMsgDriveNotReady(); 
          break;
       case ERROR_SECTOR_NOT_FOUND: 
          ShowMsgSectorNotFound(); 
          break;
       case ERROR_NOT_DOS_DISK: 
          ShowMsgFormatErr(); 
          break;
       case ERROR_INVALID_EXE_SIGNATURE:
       case ERROR_EXE_MARKED_INVALID:
          ShowMsgInvalidExe(psz_filename);
          break;
       case ERROR_DIRECTORY_IN_CDS:
          ShowMsgChangeDirNameUsing(psz_filename);
          break;
       default: 
          ShowMsgErr(apr_errorcode); 
          break;
    }
 }


