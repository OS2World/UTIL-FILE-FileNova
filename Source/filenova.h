/******************************************************************/
/*  filenova �p�C���N���[�h�t�@�C��                               */
/******************************************************************/
/*-------------------------------------------*/
/*  �萔�}�N��                               */
/*-------------------------------------------*/
 #define  VIO_HANDLE        0

 #define  CLEAR   "\033[2J"
 
 #define  MAX_VIWER_FILESIZE    0x7fffffff
 
 #define  MAX_FILE      10000
 #define  FILE_DISPLEN    250
 #define  ASSOC_MAX       200
 #define  UNPACKER_MAX     32
 #define  PACKER_MAX       32
 #define  CMDSTR_MAX     1024
 #define  HISTORY_MAX      12
 
 #define  PFK            0    /* Key Char Code */
 #define  BACK           8
 #define  ESC           27
 #define  ENTER         13
 #define  ARROW        224
 #define  CTRL_A         1
 #define  CTRL_B         2
 #define  CTRL_C         3
 #define  CTRL_D         4
 #define  CTRL_E         5
 #define  CTRL_F         6
 #define  CTRL_G         7
 #define  CTRL_H         8
 #define  CTRL_I         9
 #define  CTRL_J        10
 #define  CTRL_K        11
 #define  CTRL_L        12
 #define  CTRL_M        13
 #define  CTRL_N        14
 #define  CTRL_O        15
 #define  CTRL_P        16
 #define  CTRL_Q        17
 #define  CTRL_R        18
 #define  CTRL_S        19
 #define  CTRL_T        20
 #define  CTRL_U        21
 #define  CTRL_V        22
 #define  CTRL_W        23
 #define  CTRL_X        24
 #define  CTRL_Y        25
 #define  CTRL_Z        26
 
 #define  SPACE         57    /* Key Scan Code */
 #define  PF1           59
 #define  PF2           60
 #define  PF3           61
 #define  PF4           62
 #define  PF5           63
 #define  PF6           64
 #define  PF7           65
 #define  PF8           66
 #define  PF9           67
 #define  PF10          68
 #define  PF11         133
 #define  PF12         134
 #define  ARROW_UP      72
 #define  ARROW_DOWN    80
 #define  ARROW_LEFT    75
 #define  ARROW_RIGHT   77
 #define  PAGE_UP       73
 #define  PAGE_DOWN     81
 #define  DELETE        83
 #define  INSERT        82
 #define  HOME          71
 #define  HOME98        119  /* PC-98x1�ɂ�����HOME�̃X�L�����R�[�h */
 #define  END           79

 #define  CR            '\x0D'       /* ���s�R�[�h */
 #define  LF            '\x0A'
 #define  CRLFDISP      "\x1B"

 #define  VIO_BLACK          0x00  /* �J���[�p���b�g */
 #define  VIO_DARKBLUE       0x01
 #define  VIO_DARKGREEN      0x02
 #define  VIO_DARKCYAN       0x03
 #define  VIO_DARKRED        0x04
 #define  VIO_DARKMAGENTA    0x05
 #define  VIO_DARKYELLOW     0x06
 #define  VIO_DARKWHITE      0x07
 #define  VIO_GRAY           0x08
 #define  VIO_BRIGHTBLUE     0x09
 #define  VIO_BRIGHTGREEN    0x0A
 #define  VIO_BRIGHTCYAN     0x0B
 #define  VIO_BRIGHTRED      0x0C
 #define  VIO_BRIGHTMAGENTA  0x0D
 #define  VIO_BRIGHTYELLOW   0x0E
 #define  VIO_BRIGHTWHITE    0x0F


 #define  DISP_SZ    0         /* �T�C�Y�\���̈ʒu     */
 #define  DISP_DT   13         /* �����\���̈ʒu       */
 #define  DISP_MK   29         /* �t�@�C���}�[�N�̈ʒu */
 #define  DISP_FN   31         /* �t�@�C�����\���̈ʒu */

 #define  MYFUNC_NOT_EXEC  1   /* ����֐��̕Ԃ�l  ���s����Ȃ����� */
 #define  MYFUNC_EXEC      0   /*                   ���s���ꂽ       */

 #define  FLAG_NO_MARK  0      /* �J�[�\���t�@�C���̏������������t���O */
 #define  FLAG_MARK     1      /* �}�[�N�t�@�C���̏������������t���O   */

 #define  FLAG_EXE_EXTENSION 0 /* �g���q�����s�`���ł��鎖�������t���O */
 #define  FLAG_INF_EXTENSION 1 /* �g���q��.INF�ł��鎖�������t���O     */

 #define  FLAG_FIRST      0    /* ���̃��[�`�����͂��߂ČĂ΂�鎖�������t���O */
 #define  FLAG_NOT_FIRST  1    /*               ���ɌĂ΂�Ă��鎖������       */

 #define  FLAG_FILE_NOT_FOUND   0  /* �������ʂ̕Ԃ�l�F������Ȃ����� */
 #define  FLAG_FILE_FOUND       1  /*                 �F��������       */
 #define  FLAG_CANCELED_BY_USER 2  /*                 �F�r���Œ��~       */

 #define  FLAG_DRAW_FILELIST  0    /* �t�@�C�����X�g�݂̂����ւ���  */
 #define  FLAG_DRAW_SCREEN    1    /* ��ʑS�̂����ւ���            */

 #define  FLAG_MODE_FILER     0    /* �t�@�C���E���[�h */
 #define  FLAG_MODE_VIEWER    1    /* �r���[���E���[�h */
 #define  FLAG_MODE_INPUTWIN  2    /* ���͑����[�h */
 #define  FLAG_MODE_HISTORY   3    /* �������[�h */


 #define  FLAG_NAME_NOTDEFINE 0    /* Rename �̍ۂ� Case ������ */
 #define  FLAG_NAME_LOWER     1    /* Rename �̍ۂ� Case ������ */
 #define  FLAG_NAME_UPPER     2    /* Rename �̍ۂ� Case �啶�� */
 #define  FLAG_NAME_CAP       3    /* Rename �̍ۂ� Case �擪�̂ݑ啶�� */
 #define  FLAG_NAME_EXT       4    /* Rename �̍ۂ� Case �g���q���擪�̂ݑ啶�� */

 #define  FLAG_INSERT_MODE     0    /* ���̓��[�h�͌��ݑ}�����[�h   */
 #define  FLAG_OVERWRITE_MODE  1    /* ���̓��[�h�͌��ݏ㏑�����[�h */
 #define  FLAG_CURSOR_HIDDEN  10    /* �J�[�\���͔�\�� */
 #define  FLAG_CURSOR_DISP    11    /* �J�[�\���͕\��   */
                                    /*Insert �� Overwrite �͕K��0��1�̊֌W�� */

 #define  FLAG_OBJCPY_NO_TARGETPATH  1   /* �^�[�Q�b�g�p�X���Ȃ� */
 #define  FLAG_OBJCPY_FAIL_COPY      2   /* �R�s�[�Ɏ��s����     */

 #define  FLAG_HISTRY_DIRECTRY  1  /* �W�����v�f�B���N�g���̗��� */
 #define  FLAG_HISTRY_COMMAND   2  /* �R�}���h�̗���             */
 #define  FLAG_HISTRY_PATH      3  /* ���̑��̃p�X�̗���         */
 #define  FLAG_HISTRY_ASSOCPROG 4  /* �g���q�o�^�v���O�����̑I�� */

 
 #define  FLAG_INPUTWIN_NO_OPTION     0  /* �I�v�V�����Ȃ�    */
 #define  FLAG_INPUTWIN_HISTRY_ON     1  /* �q�X�g���@�\�g�p  */
 #define  FLAG_INPUTWIN_NOSTRINGS_OK  2  /* ���͂��Ȃ��Ă���  */
 #define  FLAG_INPUTWIN_OVERWRITE     4  /* �㏑�����[�h�ŊJ�n*/
 #define  FLAG_INPUTWIN_CURSORHEAD    8  /* �J�[�\����擪�ց@*/
 #define  FLAG_INPUTWIN_MSGBOXCLEAR  16  /* �I�������͑����N���A*/
 #define  FLAG_INPUTWIN_FUNCKEY_ON   32  /* �t�@���N�V�����L�[�̓��͉�*/
 #define  FLAG_INPUTWIN_TABKEY_ON    64  /* TAB�L�[�̓��͉�   */
                                   /* �����̓r�b�g�_���a�Ŏg���� */

 #define  FLAG_GETYESORNO_NO_OPTION    0  /* �I�v�V�����Ȃ�            */
 #define  FLAG_GETYESORNO_MSGBOXCLEAR  1  /* �I�����t�@�C�����X�g�ŏ���*/
 #define  FLAG_GETYESORNO_MSGBOXNULL   2  /* �I�����󔒂ŏ���          */
 #define  FLAG_GETYESORNO_FUNCKEY_ON     4  /* �t�@���N�V�����L�[�̓��͉�*/
                                   /* �����̓r�b�g�_���a�Ŏg���� */

 #define  FLAG_EXECPROG_KEYMACRO   0  /* �}�N���o�^���ꂽ�v���O���������s */
 #define  FLAG_EXECPROG_EXTENTION  1  /* �g���q�o�^���ꂽ�v���O���������s */
 #define  FLAG_EXECPROG_PACKER     2  /* ���k�v���O���������s             */
 #define  FLAG_EXECPROG_UNPACKER   4  /* �𓀃v���O���������s             */
 #define  FLAG_EXECPROG_VIEWER     5  /* �O���r���[�������s               */


 #define  FLAG_COPY_ONLY       1   /* �t�@�C�����R�s�[���邾��       */
 #define  FLAG_COPY_DELETE     2   /* �t�@�C�����R�s�[���������     */ 
 #define  FLAG_MOVE_SAMEDRIVE  3   /* �t�@�C���𓯂��h���C�u���ňړ� */

 #define  FLAG_CHDIR_JUMP    1  /* ChangeDriveDir �� Jump���[�h�ŌĂяo�� */
 #define  FLAG_CHDIR_CHANGE  2  /* ChangeDriveDir �� ���̓��[�h�ŌĂяo�� */

 #define  FLAG_NOISY_START   0
 #define  FLAG_SILENT_START  1

 #define  FLAG_LOADFILELIST_ANYFILE  0x00000037
 #define  FLAG_LOADFILELIST_DIRONLY  0x00001037
 #define  FLAG_LOADFILELIST_NOTDIR   0x00000027
 

 #define  INI_GENERAL       1    /*  Ini �t�@�C���ŉ���ݒ肵�Ă��邩 */
 #define  INI_EDITOR        2
 #define  INI_EXTENTION     3
 #define  INI_MACRO         4
 #define  INI_UNPACKER      5
 #define  INI_COLOR         6
 #define  INI_VIEWER        7
 #define  INI_PACKER        8

 #define  RESET          0    /* �t�@�C���̏㏑���̎�� */
 #define  OVERWRITE      1     
 #define  TIMECOMP       2     
 #define  NOCOPY         3     
 #define  ONLYTHIS       4     
 #define  ONLYTHIS_TIME  5     
 #define  ONLYTHIS_NOCP  6     
 
 #define  READONLY_RESET           0   /* ReadOnly �𖳎����邩 */
 #define  READONLY_IGNORE_THIS     1
 #define  READONLY_IGNORE_ALL      2
 #define  READONLY_NOTIGNORE_THIS  3
 #define  READONLY_NOTIGNORE_ALL   4
 
 #define  FLAG_VIEWFILE_NOERROR       0
 #define  FLAG_VIEWFILE_CALLEXTVIEWER 0xfffffffe
 #define  FLAG_VIEWFILE_CALLEDITOR    0xffffffff
 
 #define  FLAG_DOSMODE_NOTUSE  0xffff
 #define  FLAG_DOSMODE_PCDOS   0
 #define  FLAG_DOSMODE_DOSV    1
 #define  STRING_DOSMODE_PCDOS  "*DOS_MODE=PC-DOS\0\0"
 #define  STRING_DOSMODE_DOSV   "*DOS_MODE=DOS/V\0\0"

/*---------------------------------------*/
/* �O���v���O�����p�\����                */
/*---------------------------------------*/
typedef struct _ExternalProg{
   USHORT usSession;
   USHORT usSilent;
   UCHAR  uszExtention[32];
   UCHAR  uszProgName [124];
   UCHAR  uszParamList[124];
} EXTERNALPROG;
typedef EXTERNALPROG *PEXTERNALPROG;

/*----------------------------------------*/
/* �֐��v���g�^�C�v                       */
/*----------------------------------------*/
 void   ChangeAttribute(PSZ, USHORT, ULONG);
 void   ChangeAttributeDisp(USHORT, PSZ);
 void   ChangeAttributeFlag(UCHAR, PUSHORT, PUSHORT, PUSHORT);
 APIRET ChangeAttributeFunc(PUCHAR, USHORT, USHORT, USHORT);
 ULONG  ChangeAttributeFunc_BitSet(USHORT, ULONG, ULONG);

 void   ChangeDrive(void);

 void   ChangeSetup(void);
 void   ChangeSetupFuncAlwaysSort(void);
 void   ChangeSetupFuncAutoClose(void);
 void   ChangeSetupFuncEditorName(VOID);
 void   ChangeSetupFuncEditSession(void);
 void   ChangeSetupFuncExecSession(void);
 BOOL   ChangeSetupFuncIniRead(void);
 void   ChangeWindowSize(void);
 void   ChangeWindowSizeFunc(PSZ);

 void   CommandProcess(void);

 APIRET CopyDirContents(PSZ, PSZ, PSZ, USHORT);

 void   CreateDir(void);
 APIRET CreateDirFunc(PSZ);
 APIRET CreateDirFunc_API(PSZ);
 void   CreateDirFuncRc(APIRET);

 APIRET DeleteDirContents(PSZ);

 ULONG  ExecAssocProgram(USHORT, PSZ);
 UCHAR  ExecAssocProgram_Select(PUSHORT);
 APIRET ExecAssocProgram_MsgBox(PSZ, PSZ, PSZ, USHORT, USHORT, USHORT, USHORT, ULONG, USHORT);
 APIRET ExecAssocProgram_IfProgExist(USHORT, USHORT, USHORT, PSZ, PSZ, PSZ);
 void   ExecAssocProgramFunc(USHORT, USHORT, USHORT, PSZ, PSZ, PSZ);
 BOOL   ExecAssocProgramParm(PSZ, PSZ, PSZ, PSZ, USHORT, USHORT, BOOL*);
 BOOL   ExecAssocProgramParm_NameSet(PSZ, USHORT, BOOL);
 void   ExecAssocProgramParm_NamewithSpace(PSZ, PSZ, BOOL);
 BOOL   ExecAssocProgramParm_Restruct(PSZ, PSZ, PSZ, USHORT, BOOL);
 BOOL   ExecAssocProgramParm_RestructString(PSZ, PSZ, USHORT, BOOL);
 void   ExecCommand(void);
 void   ExecProgram(void);

 void   FileCopy(void);
 APIRET FileCopyDir(PSZ, USHORT, USHORT);
 APIRET FileCopyFl(PSZ, PSZ, USHORT, ULONG);
 APIRET FileCopyFunc(PSZ, PSZ, PSZ, PSZ, USHORT);
 APIRET FileCopyFuncTarget_ExitsOrNot(PSZ, PFILEFINDBUF3);
 void   FileCopyFuncDisp(PSZ, USHORT);
 void   FileCopyFuncOption(PSZ, PSZ, USHORT);
 USHORT FileCopyFuncOptionRo(PSZ, PSZ, USHORT);
 INT    FileCopyFuncTimeComp(PSZ, const PFILEFINDBUF3);
 void   FileCopyRc(APIRET);
 ULONG  FileCopy_ConverttoAbsolutePath(PSZ);
 void   FileCopyFuncOption_StringsAdjust(PSZ, ULONG);

 void   FileDelete(void);
 APIRET FileDeleteFunc(PSZ, BYTE);
 void   FileDeleteFuncDisp(USHORT, PSZ);
 void   FileDeleteRc(APIRET);

 VOID   FileEdit(PSZ, ULONG, USHORT, ULONG);
 VOID   FileEdit_SetLineOption(PSZ, PSZ, ULONG, PSZ);
 void   FileFind(void);
 ULONG  FileFindDir(PSZ, PSZ);
 VOID   FileFindDisp(USHORT, PSZ);
 ULONG  FileFindMatch(PSZ, PSZ);

 void FileMark(void);
 void FileMarkAll(void);
 void FileMarkRefresh(void);

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */ 
 void FileMarkInfoDisp_Set(ULONG, ULONG);
#else                                             
 void FileMarkInfoDisp_Set(ULONG, unsigned long long);
#endif                                            

 void FileMaskDisp(void);

 void FileMove(void);

 VOID FileName(ULONG);
 VOID FileName_Case(ULONG);
 VOID FileNameChange_Case(PSZ, USHORT);
 void FileNameChangeFunc(PSZ, PSZ);
 INT  FileNameCompDefault(const void *);
 int  FileNameCompOption(const void *, const void *);
 int  FileNameComp(PSZ, PSZ);
 int  FileExtentionComp(PSZ, PSZ);

 APIRET FilePathSearch(PSZ, PSZ, ULONG);

 void FileSort(void);

 void FuncEvent(UCHAR);

 void GetCodePage(SHORT);
 void GetMode(void);
 void GetOriginDir(void);
 void GetParm(void);
 void GoStartupDir(void);
 void InitCustomize(SHORT);
 VOID InitCustomize_ClearExternalProg(PUSHORT, USHORT, PEXTERNALPROG); 
 VOID InitCustomize_ClearViewerCfg(SHORT);
 VOID InitCustomize_ClearEditorCfg(SHORT);

 VOID JumpDirRead(USHORT);
 void JumpDirSaveFunc(USHORT);
 VOID JumpHistInsert(USHORT, PSZ);

 void  KbdEvent(void);
 UCHAR KbdLineIn(USHORT, BYTE, USHORT, PUCHAR, USHORT);
 VOID  Vio_CursorShape(USHORT);
 void  KbdLineInHist(void);

 void  ListBoxDisp(void);
 void  ListBoxDispFunc(void);

 void  MacroDisp(ULONG);
 void  MacroDisp_Show(VOID);
 ULONG MacroFunc(UCHAR, ULONG);
 void  MacroSetup(PSZ);
 
 void    MakeIcon(PSZ, USHORT);
 void    MakePrgIcon(PSZ, USHORT);
 HOBJECT MakePrgIconFunc(PSZ, USHORT);
 void    MakeShadowIcon(PSZ);
 HOBJECT MakeShadowIconFunc(PSZ);
 
 void MarkFileCopy(ULONG);
 void MarkFileDelete(void);
 void MarkFileExec(void);
 void MarkFileIcon(void);
 void MarkFileMove(ULONG);
 
 void OpenObjectOnDesktop(PSZ, BYTE);
 void OpenObjectOnDesktop_withoutPath(PSZ, BYTE);
 
 void   QDrive(void);
 void   QDriveSize(void);
 void   QDir(void);
 APIRET QFile(void);
 APIRET QFile_LoadFileList(ULONG, PSZ);
 void   QuitFilestar(void);
 void   QuitFileNovaFunc(void);
 void   ReDrawAfterDelete(void);
 void   RedrawScreen(void);
 ULONG  SameDirCheck(PSZ);
 ULONG  SameDriveCheck(PUSHORT);
 void   Serch1Char(USHORT);
 void   Serch1CharNg(UCHAR);

#ifdef IBMCSET  /* ��e�ʃt�@�C���΍�����Ȃ� */
 BOOL   SetFileInfo(const PFILEFINDBUF3);
#else
 BOOL   SetFileInfo(const PFILEFINDBUF3L);
#endif

 void   SetFullCurrentPathName(PSZ);
 void   SetFullDirName(PSZ);
 void   SetFullFileName(PSZ, PSZ);

 VOID   SetupEditor(PSZ);
 VOID   SetupViewer(PSZ);
 USHORT SetupExtention(PSZ, PEXTERNALPROG);
 USHORT SetupMacroProgram(PSZ, PEXTERNALPROG);
 USHORT SetupExtProg_Session(PSZ, PUSHORT, PUSHORT);
 USHORT SetupExtProg_NameAndParam(PSZ, PSZ, PSZ);
 USHORT SetupUnpacker(PSZ, USHORT);
 VOID   SetupGeneral(SHORT, PSZ);
 USHORT SetupGlobalFlag_FromInifileData(PSZ, PSZ, PUSHORT,  USHORT, USHORT);
 USHORT SetupGlobalFlag_GetValueAsULONG(PSZ, PSZ, PULONG, ULONG);
 USHORT SetupGlobalFlag_GetString(PSZ, PSZ, USHORT, PSZ, PSZ);
 PUCHAR SetupGlobalFlag_SearchValuePtr(PSZ, PSZ); 


 void SetWallColor(void);
 void ShowMsgBox(USHORT, BYTE);
 void ShowMsgBox_Line(USHORT, BYTE);
 void ShowMsgBox_OutLine(USHORT, BYTE);
 void ShowMsgBoxNull(void);
 void ShowMsgCopyOk(void);
 void ShowMsgCopyStop(void);
 void ShowMsgCrcErr(void);
 void ShowMsgCreateDirErr(void);
 void ShowMsgDeleteErr(void);
 void ShowMsgDeleteDeny(void);
 void ShowMsgDeleteStop(void);
 void ShowMsgDiskFull(void);
 void ShowMsgDriveErr(void);
 void ShowMsgDriveNotReady(void);
 void ShowMsgErr(APIRET);
 void ShowMsgExecErr(APIRET, PSZ);
 void ShowMsgExecNotF(PSZ);
 void ShowMsgExecOk(void);
 void ShowMsgNotFound(void);
 void ShowMsgFileNotFound(PSZ);
 void ShowMsgFindStop(void);
 void ShowMsgFormatErr(void);
 void ShowMsgIconErr(void);
 void ShowMsgIconNa(void);
 void ShowMsgIconOk(void);
 void ShowMsgIconReg(void);
 VOID ShowMsgInvalidExe(PSZ);
 void ShowMsgHistryErr(void);
 void ShowMsgLocked(void);
 void ShowMsgMoveStop(void);
 void ShowMsgNameErr(PSZ);
 void ShowMsgChangeDirNameUsing(PSZ);
 void ShowMsgNameLong(void);
 void ShowMsgNameNg(void);
 void ShowMsgOpenErr(void);
 void ShowMsgParmDirErr(void);
 void ShowMsgPassNg(PSZ);
 void ShowMsgPassNo(PSZ);
 void ShowMsgSameDir(void);
 void ShowMsgSameName(void);
 void ShowMsgSectorNotFound(void);
 void ShowMsgSharedErr(PSZ);
 void ShowMsgStartUpDirErr(void);
 void ShowMsgTooLongStr(void);
 void ShowMsgVersionInfo(void);
 void ShowMsgWriteProtect(void);
 void ShowNewDrive(void);

#ifdef IBMCSET  /* 64bit�������T�|�[�g����Ȃ� */ 
 VOID   ShowSummarySize(PSZ, ULONG,ULONG);
 USHORT SummarySizeCalc(PSZ, PSZ, PULONG,PULONG);
 VOID   SummarySizeDisp(USHORT, PSZ, ULONG);
#else                                             
 VOID   ShowSummarySize(PSZ, unsigned long long,ULONG);
 USHORT SummarySizeCalc(PSZ, PSZ, unsigned long long *,PULONG);
 VOID   SummarySizeDisp(USHORT, PSZ, unsigned long long);
#endif                                            

 VOID   SummarySize(PSZ);

 void   ViewFile_Ready(PSZ,BOOL);
 APIRET ViewFile_ExternalViewer(PSZ);
 APIRET ViewFile(PSZ, ULONG, PULONG, PULONG, BOOL, ULONG, BOOL);  

 VOID   ColorSetup(PSZ);
 BYTE   ColorSetup_BackGroundChange(PSZ, PSZ, BYTE);
 BYTE   ColorSetup_ForeGroundChange(PSZ, PSZ, BYTE);
 BYTE   ColorSetup_GetColor(PSZ, PSZ);

 ULONG  Archive_Pack(PSZ, ULONG);
 VOID   Archive_Unpack(PSZ, ULONG);
 APIRET Archive_Unpack_CurrentFile(USHORT, PSZ, PSZ, USHORT, USHORT);
 APIRET Archive_Unpack_MarkFile(PSZ, USHORT, USHORT);
 VOID   Archive_Unpack_GetSubDirName(PSZ, PSZ, PSZ, PSZ);

 VOID   ChangeTimeStamp(PSZ, ULONG);
 APIRET ChangeTimeStampGet(PSZ, PSZ);
 APIRET ChangeTimeStampGetCurrentTime(PSZ);
 APIRET ChangeTimeStampSet(PSZ, PSZ);
 BOOL   CheckTimeStampStr(PSZ);
 VOID   ChangeTimeStamp_MakeString(PSZ, const PFDATE, const PFTIME); 
 BOOL   ChangeTimeStamp_MakeStructure(PSZ, PFDATE, PFTIME);

 VOID   ChangeVolumeLabel(VOID);
 APIRET ChangeVolumeLabelSet(PSZ);

 void ChangeCodePage(void);
 void ChangeCodePageFunc(ULONG);


 USHORT CheckExtention(PSZ, PSZ);
 VOID   ChangeDriveFunc(UCHAR);
 APIRET ChangeDriveFunc_API(UCHAR);
 APIRET ChangeDriveDirFunc(PSZ);
 VOID   ChangeDriveDir(USHORT);
 VOID   Change_FlagMark(USHORT, USHORT, USHORT);
 VOID   CmdExec_SameSession(USHORT, PSZ, USHORT);
 UCHAR  CreateDir_YesorNo(PSZ, USHORT);
 APIRET CreateAndEnterDir(PSZ);
 VOID   GotoAnotherDir(PSZ);
 UCHAR  GetYesorNo_withMsgBox(UCHAR, USHORT, BYTE, USHORT);
 UCHAR  GetYesorNo_withMsgBoxClear(UCHAR, USHORT, BYTE, USHORT);
 VOID   MsgBoxDisp(USHORT, BYTE, USHORT);
 VOID   PrevFileDirSearch(PUCHAR);
 
 VOID   ShowVolumeLabel(VOID);
 VOID   ShowCurrentDriveName(VOID);
 VOID   ShowCurrentDirName(VOID);
 VOID   ShowFileNumberSize(VOID);
 VOID   ShowMarkFileNumberSize(VOID);
 VOID   ShowCurrentDriveSize(VOID);
 VOID   ShowFileMask(VOID);

 VOID   ShowFileList_PrevFile(USHORT, PSZ);
 VOID   ShowFileList_FilePosition(ULONG);
 VOID   ShowFileList(VOID);
 VOID   ShowFileList_CurrFileInfo(ULONG);
 VOID   ShowFileList_Line(PSZ, USHORT, BYTE, BYTE);
 VOID   Set_ShowFileList_Parm(ULONG);
 BOOL   ShowFileList_SetExtentionSort(PSZ, PSZ, USHORT, BYTE);
 
 VOID   ShowHelp(VOID);
 USHORT SetHelpMsg (PUSHORT);
 VOID   FileExecFunc_AnotherSession(USHORT, PSZ, PSZ, PSZ, USHORT, USHORT); 
 VOID   FileExecFunc_UseWinAPI(PSZ, PSZ, PSZ, PSZ, USHORT, ULONG); 

 PUCHAR HistryBox(USHORT);
 USHORT HistryBox_Set(USHORT, USHORT);
 UCHAR  HistryBoxDisp(PUSHORT, USHORT);
 VOID   HistryInsert(USHORT, USHORT);
 void   HistryDelete(USHORT, USHORT);

 VOID   ObjectCopy_HPFS_FAT(PSZ, ULONG);
 VOID   ObjectCopy_HPFS_FAT_CurrentFile(PSZ, PSZ);
 VOID   ObjectCopy_HPFS_FAT_MarkFile(PSZ);
 USHORT ObjectCopy_HPFS_FAT_Func(PSZ, PSZ);     

 VOID   LoadHistoryFile(PSZ, PUCHAR, ULONG);
 VOID   LoadHistoryFile_fromDisk(VOID);
 VOID   SaveHistoryFile(PSZ, PUCHAR, ULONG);
 VOID   SaveHistoryFile_toDisk(VOID);

 VOID   ErrorMsgDisp(APIRET, PSZ);


 extern USHORT English; 
 extern BOOL DisableCharCode; 

