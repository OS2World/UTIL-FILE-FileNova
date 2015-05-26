 /*********************************************************************/
 /*  NovaView Version 3.00                      2008.04.17            */
 /*********************************************************************/
 #define  INCL_DOS
 #define  INCL_VIO
 #define  INCL_KBD
 #define  INCL_DOSFILEMGR
 #define  INCL_DOSMEMMGR
 #define  INCL_DOSSESMGR
 #define  INCL_ERRORS
 #include <os2.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #ifdef __EMX__
    #define ultoa  _ultoa
 #endif

#if !defined(IBMCSET) // 大容量ファイル対策をしない
 #include "lfsatype.h"
#endif
 #include "filenova.h"
 #include "jstring.h"
 #include "charcode.h"
 #include "getkeyif.h"
 #include "unicode.h"

 #ifndef IBMCSET  /* 大容量ファイル対策をしない */
    #include "lfiles.h"
 #endif

 ULONG  ViewFile_Key_ArrowUp(ULONG, ULONG, ULONG, USHORT);
 ULONG  ViewFile_Key_ArrowDown(ULONG, ULONG, ULONG, ULONG, USHORT);
 ULONG  ViewFile_Key_PageUp(ULONG, ULONG, ULONG, ULONG, USHORT);
 ULONG  ViewFile_Key_PageDown(ULONG, ULONG, ULONG, ULONG, ULONG, USHORT);
 ULONG  ViewFile_Key_Home(ULONG, ULONG, ULONG, ULONG, USHORT);
 ULONG  ViewFile_Key_End(ULONG, ULONG, ULONG, ULONG, ULONG, USHORT);

 USHORT ViewFile_TotalNumDisp(ULONG,BOOL);
 USHORT ViewFileLine_BuffSet(PSZ, ULONG, USHORT, ULONG, USHORT);
 USHORT ViewFileLine_Disp(USHORT, ULONG, USHORT, ULONG, USHORT);
 VOID   ViewFileLine2(USHORT, ULONG, ULONG, USHORT);
 PUCHAR ViewFileLine_CheckCRLF(ULONG, USHORT, ULONG, USHORT);
 PUCHAR ViewFileLine_CheckCRLF_UTF7(ULONG, USHORT, ULONG);
 PUCHAR ViewFileLine_CheckCRLF_UTF16(ULONG, USHORT, ULONG);

 VOID   ViewFilePage_Disp(ULONG, ULONG, ULONG, ULONG, USHORT);
 VOID   ViewFileTitle(PSZ, USHORT, ULONG);
 VOID   ViewFile_LineNumDisp(ULONG, USHORT, BOOL);

 int    ViewFile_CheckDBCS(PUCHAR, PUCHAR, USHORT);
 int    ViewFile_CheckDBCS_UTF8(PUCHAR, PUCHAR);
 BOOL   ViewFile_CheckDBCS_EUC(PUCHAR, PUCHAR);
 ULONG  ViewFile_SetLineHeadPtr(PUCHAR, ULONG, ULONG, PULONG, PUSHORT, USHORT, ULONG, USHORT);
 ULONG  ViewFile_GetLogicalLineNum(ULONG);

 VOID   ViewFile_ShowHelp(ULONG, ULONG, ULONG, ULONG, USHORT);
 ULONG  ViewFileFoundPage_Disp(ULONG, ULONG, ULONG, ULONG, ULONG, USHORT);
 ULONG  ViewFile_JumpLine(ULONG, ULONG, BOOL);
 BOOL   ViewFile_ChangeDispParam(UCHAR, PULONG, PUSHORT);
 BOOL   ViewFile_ChangeCharCode(PUSHORT);

 ULONG  ViewFile_SearchString(USHORT, PUSHORT, PULONG, ULONG, ULONG, PSZ, ULONG, USHORT);
 ULONG  ViewFile_SearchSameString(USHORT, USHORT, PULONG, ULONG, ULONG, ULONG, PSZ, ULONG, USHORT); 
 ULONG  ViewFile_ForwardFirstSearchString (USHORT, ULONG, ULONG, ULONG, PSZ);
 ULONG  ViewFile_ForwardNextSearchString  (USHORT, ULONG, ULONG, ULONG, PSZ);
 PUCHAR ViewFile_ForwardSearchStringEngine(PUCHAR, PUCHAR, PSZ, USHORT);

 ULONG  ViewFile_ForwardFirstSearchString2 (USHORT, ULONG, ULONG, ULONG, PSZ, ULONG, USHORT);
 ULONG  ViewFile_ForwardNextSearchString2 (USHORT, ULONG, ULONG, ULONG, PSZ, ULONG, USHORT);
 ULONG  ViewFile_ForwardSearchStringEngine2(ULONG, ULONG, PSZ, USHORT, ULONG, USHORT);
 ULONG  ViewFile_BackwardFirstSearchString2 (USHORT, ULONG, ULONG, ULONG, PSZ, ULONG, USHORT);
 ULONG  ViewFile_BackwardNextSearchString2 (USHORT, ULONG, ULONG, ULONG, PSZ, ULONG, USHORT);
 ULONG  ViewFile_BackwardSearchStringEngine2(ULONG, ULONG, PSZ, USHORT, ULONG, USHORT);


 ULONG  ViewFile_BackwardFirstSearchString (USHORT, ULONG, ULONG, ULONG, PSZ);
 ULONG  ViewFile_BackwardNextSearchString  (USHORT, ULONG, ULONG, ULONG, PSZ);
 PUCHAR ViewFile_BackwardSearchStringEngine(PUCHAR, PUCHAR, PSZ, USHORT);

 ULONG  ViewFile_ForwardFirstSearchStringBin (USHORT, ULONG, ULONG, ULONG, PSZ);
 ULONG  ViewFile_ForwardNextSearchStringBin  (USHORT, ULONG, ULONG, ULONG, PSZ);
 ULONG  ViewFile_BackwardFirstSearchStringBin (USHORT, ULONG, ULONG, ULONG, PSZ);
 ULONG  ViewFile_BackwardNextSearchStringBin  (USHORT, ULONG, ULONG, ULONG, PSZ);

 ULONG  ViewFile_GetLineNum(PUCHAR, ULONG, ULONG);

 VOID   ViewFile_TerminateTread(TID, PVOID, HEV, HFILE);

#define FLAG_SEARCH_FORWARD    0
#define FLAG_SEARCH_BACK       1
#define FLAG_SEARCH_NOT_MATCH  0xffffffff

#define VIEWER_START_ROW   1
#define VIEWER_END_ROW     (RowMax-1)
#define VIEWER_ROW_SIZE    (RowMax-1)
#define BUFFBLOCKSIZE  0x00010000   /* 64kByte */

/*------------------------------------------------*/
/*  画面表示                                      */
/*------------------------------------------------*/
 extern USHORT  RowMax,ColMax;
 extern UCHAR   MsgTxt[20][_MAX_PATH];
 extern UCHAR   InpLine[CMDSTR_MAX];
 extern UCHAR   FlstrExeFl[MAX_FILE];

 extern BYTE   bt_g_ViewerTytleBarColor;
 extern BYTE   bt_g_ViewerCharcterColor;
 extern BYTE   bt_g_ViewerCRLFColor;
 extern BYTE   bt_g_ViewerCRColor;
 extern BYTE   bt_g_ViewerLFColor;
 extern BYTE   bt_g_ViewerBackGroundColor;
 extern BYTE   bt_g_ViewerSearchStrColor;
 extern BYTE   bt_g_NormalWindowColor;
 extern BYTE   bt_g_InformWindowColor;

/*extern*/ BOOL DisableCharCode = FALSE; // TRUEでキャラコード切り替え機能を禁止

 UCHAR*        STAR_VIEW_VERSION[2]={ " NovaView Ver3.00  表\示ﾌｧｲﾙ" ," NovaView Ver3.00  View file" };

/*---------------------------------------*/
/*  別スレッド用のプロトタイプ＋変数     */
/*---------------------------------------*/
void _System ThreadLoadFile(ULONG);

/*  別スレッドとの連絡用の変数    */
static APIRET  apr_g_thread=NO_ERROR;
static PVOID   pv_filebuff;
static ULONG   ul_g_restfilesize;
static HEV     hev_g_readsize;

static ULONG ul_alreadyreadsize;

/*------------------------------------*/
/*  バッファ上の各行頭のポインタ      */
/*------------------------------------*/
 #define MAX_ROWNUM   0x100000       /* 最大で1048576行*4 = 4MByte */
 static PUCHAR puc_rownumber[MAX_ROWNUM];

 BOOL  bl_g_flg_showCRLF = TRUE;

 static int utf7_setb_s = 0; /* UTF7のSetBフラグ */
 static BOOL utf16_little = FALSE; /* UTF16のタイプ判別。FALSE=ビッグエンディアン、TRUE=リトルエンディアン */
  
/*****************************************************************/
/**   ViewFile                                                 **/
/*****************************************************************/
 APIRET ViewFile(PSZ psz_filename, ULONG ul_filesize, 
                 PULONG pul_logicalline, PULONG pul_tabsize,
                 BOOL ul_defcasesensitive, ULONG ul_codepage ,BOOL binary )
 {
    KBDKEYINFO  KeyInfo;
    TID     tid_Thread=0;               
    APIRET  apr_creatthread, apr_semaph, apr_openfile;

    ULONG   ul_totalline, ul_currentline, ul_lastline, 
            ul_foundline=FLAG_SEARCH_NOT_MATCH,
            ul_postcount=0, ul_totalpostcount=0,
            ul_Action=0;
    USHORT  us_dispcol_linenum, us_flg_loadfinish=FALSE;
    USHORT  us_charcode=CODE_AUTO;
    USHORT  us_flg_searchdirect, 
            us_flg_searchcase=ul_defcasesensitive;
    HEV     hev_readsize=NULLHANDLE;
    HFILE   hf_FileHandle;

    static UCHAR   usz_searchstr[CMDSTR_MAX]={0}; 


    /*---------------------------------------------*/
    /*    ファイラ画面をビューワ画面に切り換え     */
    /*---------------------------------------------*/
    ViewFileTitle(psz_filename, CODE_AUTO, ul_codepage);
    VioWrtNAttr(&bt_g_ViewerBackGroundColor,VIEWER_ROW_SIZE*ColMax, 
                   VIEWER_START_ROW,0,0); 

    /*-----------------------------------------*/
    /* ファイルのオープン                      */
    /*-----------------------------------------*/
#ifdef IBMCSET  /* 大容量ファイル対策をしない */
    apr_openfile = DosOpen(psz_filename, &hf_FileHandle, &ul_Action, 
#else
    apr_openfile = lfs_DosOpen(psz_filename, &hf_FileHandle, &ul_Action, 
#endif
                           0L, FILE_NORMAL, 
                           OPEN_ACTION_FAIL_IF_NEW|OPEN_ACTION_OPEN_IF_EXISTS, 
                           OPEN_ACCESS_READONLY|OPEN_SHARE_DENYNONE, 0L );
    if(apr_openfile) return apr_openfile;

    /*-----------------------------------------*/
    /* 別スレッドでファイル読み込み開始        */
    /*-----------------------------------------*/
    apr_semaph=DosCreateEventSem(NULL, &hev_readsize, 0L, FALSE);
    if(apr_semaph) {
       DosClose(hf_FileHandle);
       return apr_semaph;
    }
    hev_g_readsize=hev_readsize;    /* 外部変数の初期化（忘れるな！） */
    apr_g_thread=NO_ERROR;          
    pv_filebuff=NULL;               
    ul_g_restfilesize=ul_filesize;
    ul_alreadyreadsize=0;

    apr_creatthread=DosCreateThread(&tid_Thread, (PFNTHREAD)&ThreadLoadFile, 
                    (ULONG)(&hf_FileHandle), CREATE_READY|STACK_SPARSE, 8192L);
    if(apr_creatthread) {
       ViewFile_TerminateTread(tid_Thread, pv_filebuff, hev_readsize, hf_FileHandle);
       return apr_creatthread;
    }
    /*------------------------------------------*/
    /* 最初のバッファにデータが入るまで待つ     */
    /*------------------------------------------*/
    apr_semaph=DosWaitEventSem(hev_readsize, 10000L); 
    if(apr_semaph) {
       ViewFile_TerminateTread(tid_Thread, pv_filebuff, hev_readsize, hf_FileHandle);
       if(apr_semaph==ERROR_TIMEOUT&&apr_g_thread)
          return apr_g_thread; /* サブスレッドで異常が起きた */
       else 
          return apr_semaph;  /* セマフォーの異常 */
    }
    apr_semaph=DosQueryEventSem(hev_readsize, &ul_postcount);
    if(apr_semaph) {
       ViewFile_TerminateTread(tid_Thread, pv_filebuff, hev_readsize, hf_FileHandle);
       return apr_semaph;  /*  セマフォーの異常 */
    }
    ul_alreadyreadsize = ul_postcount*BUFFBLOCKSIZE;
    ul_totalpostcount = ul_postcount;
    if(ul_alreadyreadsize>ul_filesize) ul_alreadyreadsize=ul_filesize;
    if(ul_alreadyreadsize==ul_filesize) {
        us_flg_loadfinish=TRUE;
        DosClose(hf_FileHandle);
    }
    us_charcode = binary ? CODE_BINARY : AutoEstimateCharCode(pv_filebuff, ul_alreadyreadsize,DisableCharCode,!hmoduconv);
	utf16_little = *((unsigned short*)pv_filebuff)==0xFEFF; /* 先頭２バイトが FF,FE = リトルエンディアン */

    ViewFileTitle(psz_filename, us_charcode, ul_codepage);

    /*------------------------------------------*/
    /* ファイルを行に分割後、内容表示開始       */
    /*------------------------------------------*/
    ul_totalline=ul_lastline=ul_currentline=0L;
    
    ul_totalline=ViewFile_SetLineHeadPtr(pv_filebuff, ul_totalline, 
                      ul_alreadyreadsize, &ul_lastline, &us_dispcol_linenum, 
                      ColMax, *pul_tabsize, us_charcode);
    ViewFile_LineNumDisp(ul_currentline, us_dispcol_linenum, us_charcode==CODE_BINARY);
    ViewFilePage_Disp(ul_currentline, ul_foundline, ul_totalline, 
                      *pul_tabsize, us_charcode);
    
    for(;;){
       /*----------------------------------------------*/
       /*   まだ読み込みが終了していない場合の処理     */
       /*----------------------------------------------*/
       if(us_flg_loadfinish==FALSE) {  
          do {
             DosSleep(10);
             apr_semaph=DosQueryEventSem(hev_readsize, &ul_postcount);
             if(apr_semaph) {
                ViewFile_TerminateTread(tid_Thread, pv_filebuff, hev_readsize, hf_FileHandle);
                return apr_semaph;  /*  セマフォーの異常 */
             }

             if(ul_totalpostcount<ul_postcount) {
                ul_alreadyreadsize = ul_postcount*BUFFBLOCKSIZE;
                ul_totalpostcount = ul_postcount;

                if(ul_alreadyreadsize>ul_filesize) ul_alreadyreadsize=ul_filesize;
                if(ul_alreadyreadsize==ul_filesize) {
                   us_flg_loadfinish=TRUE;
                   DosClose(hf_FileHandle);
                }
                ul_totalline=ViewFile_SetLineHeadPtr(puc_rownumber[ul_totalline], 
                               ul_totalline, ul_alreadyreadsize, &ul_lastline, 
                               &us_dispcol_linenum, ColMax, *pul_tabsize,
                               us_charcode);
                ViewFile_LineNumDisp(ul_currentline, us_dispcol_linenum, us_charcode==CODE_BINARY);
             } 
          }while(KbdCharIn(&KeyInfo,IO_NOWAIT,0));
          DosSleep(10);
       } else {
          ViewFile_LineNumDisp(ul_currentline, us_dispcol_linenum, us_charcode==CODE_BINARY);
          KbdCharIn(&KeyInfo,IO_WAIT,0);
       } 
       /*----------------------------------------*/
       /*     キー入力に従って画面の書替え       */
       /*----------------------------------------*/
       Convert_WordStarLikeKey(&KeyInfo, FLAG_MODE_VIEWER);
       switch(KeyInfo.chChar) {
          case 'b': 
          case 'B':
          case 'f': 
          case 'F':
             if(KeyInfo.chChar=='b' || KeyInfo.chChar=='B') {
                us_flg_searchdirect=FLAG_SEARCH_BACK;
             } else {
                us_flg_searchdirect=FLAG_SEARCH_FORWARD;
             }
             ul_foundline = ViewFile_SearchString(us_flg_searchdirect, 
                                &us_flg_searchcase, 
                                &ul_currentline, ul_lastline, ul_totalline, 
                                usz_searchstr, *pul_tabsize, us_charcode);
             break;
          case 'h': 
          case 'H':
          case 'l': 
          case 'L':
          case ' ':
          case CTRL_L:
             if(KeyInfo.chChar=='h' || KeyInfo.chChar=='H') {
                us_flg_searchdirect=FLAG_SEARCH_BACK;
             } else if(KeyInfo.chChar=='l' || KeyInfo.chChar=='L') {
                us_flg_searchdirect=FLAG_SEARCH_FORWARD;
             }
             ul_foundline = ViewFile_SearchSameString(us_flg_searchdirect, 
                                us_flg_searchcase, 
                                &ul_currentline, ul_foundline, ul_lastline, 
                                ul_totalline, usz_searchstr, *pul_tabsize,
                                us_charcode);
             break;
          case 'j':
          case 'J':
             ul_currentline=ViewFile_JumpLine(ul_currentline, ul_lastline ,us_charcode==CODE_BINARY );
             ViewFilePage_Disp(ul_currentline, ul_foundline, ul_totalline,
                               *pul_tabsize, us_charcode);
             break;
          case 'e':
          case 'E':
             if(*pul_logicalline == 0) { 
                if(ul_totalline > VIEWER_ROW_SIZE) {
                   *pul_logicalline=ViewFile_GetLogicalLineNum
                                        (ul_currentline+VIEWER_ROW_SIZE/2);
                } else {
                   *pul_logicalline=1;
                } 
             } else {
                *pul_logicalline=ViewFile_GetLogicalLineNum(ul_currentline);
             }
             ViewFile_TerminateTread(tid_Thread, pv_filebuff, hev_readsize, hf_FileHandle);
             return FLAG_VIEWFILE_CALLEDITOR;
          case 'v':
          case 'V':
             ViewFile_TerminateTread(tid_Thread, pv_filebuff, hev_readsize, hf_FileHandle);
             return FLAG_VIEWFILE_CALLEXTVIEWER;
          case ENTER:
          case ESC:
          case BACK:
          case 'q':
          case 'Q':
             ViewFile_TerminateTread(tid_Thread, pv_filebuff, hev_readsize, hf_FileHandle);
             return FLAG_VIEWFILE_NOERROR;
          case 'r':
          case 'R':
             if(bl_g_flg_showCRLF ==TRUE)  bl_g_flg_showCRLF = FALSE ;
             else bl_g_flg_showCRLF = TRUE ;
          case '4':
          case '8':
          case '@': 
             if(ViewFile_ChangeDispParam(KeyInfo.chChar, pul_tabsize, 
                                         &us_charcode) == TRUE) {
                PUCHAR puc_currentptr= puc_rownumber[ul_currentline];
                
                if(us_charcode==CODE_AUTO) {
                   us_charcode = AutoEstimateCharCode(pv_filebuff, ul_alreadyreadsize,
                                                      DisableCharCode,!hmoduconv);
                }
                ViewFileTitle(psz_filename, us_charcode, ul_codepage);
                ul_totalline=ViewFile_SetLineHeadPtr(puc_rownumber[0], 
                               0, ul_alreadyreadsize, &ul_lastline, 
                               &us_dispcol_linenum, ColMax, *pul_tabsize,
                               us_charcode);
                ul_currentline=ViewFile_GetLineNum(puc_currentptr, ul_lastline,
                                                   ul_totalline);
                if(ul_currentline>ul_lastline) ul_currentline=ul_lastline;
                ViewFile_LineNumDisp(ul_currentline, us_dispcol_linenum, us_charcode==CODE_BINARY);
             }
             ViewFilePage_Disp(ul_currentline, ul_foundline, ul_totalline,
                                  *pul_tabsize, us_charcode);
             break;
          case PFK:
          case ARROW:
             switch(KeyInfo.chScan){
                case ARROW_UP:
                   ul_currentline=ViewFile_Key_ArrowUp(ul_currentline, ul_foundline,
                                                       *pul_tabsize, us_charcode);
                   break;
                case ARROW_DOWN:
                   ul_currentline=ViewFile_Key_ArrowDown(ul_currentline, ul_foundline, 
                                                       ul_lastline, *pul_tabsize,
                                                       us_charcode);
                   break;
                case PAGE_UP:
                   ul_currentline=ViewFile_Key_PageUp(ul_currentline, ul_foundline, 
                                                      ul_totalline, *pul_tabsize, 
                                                      us_charcode);
                   break;
                case PAGE_DOWN:
                   ul_currentline=ViewFile_Key_PageDown(ul_currentline, ul_foundline, 
                                            ul_lastline, ul_totalline, *pul_tabsize, 
                                            us_charcode);
                   break;
                case HOME:
                   ul_currentline=ViewFile_Key_Home(ul_currentline, ul_foundline, 
                                                    ul_totalline, *pul_tabsize,
                                                    us_charcode);
                   break;
                case END:
                   ul_currentline=ViewFile_Key_End(ul_currentline, ul_foundline, 
                                          ul_lastline, ul_totalline, *pul_tabsize, 
                                          us_charcode);
                   break;
                case PF1:
                   ViewFile_ShowHelp(ul_currentline, ul_foundline, ul_totalline,
                                     *pul_tabsize, us_charcode);
                   break;
                case PF11:
                   SaveHistoryFile_toDisk();
                   FileExecFunc_AnotherSession(FLAG_MARK, "", FlstrExeFl,
                                             ".", 1, SSF_TYPE_DEFAULT);
                                            /* AutoClose=1 */ 
                   break; 
             }
       }
    }
 }

/*****************************************************************/
/**   ViewFile_Key_ArrowUp                                      **/
/*****************************************************************/
 ULONG ViewFile_Key_ArrowUp(ULONG ul_currentline, ULONG ul_foundline,
                            ULONG ul_tabsize, USHORT us_charcode)
 {
    if(ul_currentline) {
       VioScrollDn(VIEWER_START_ROW, 0, VIEWER_END_ROW, ColMax-1, 1," \0",0);
       ViewFileLine2(VIEWER_START_ROW, --ul_currentline, ul_tabsize,
                     us_charcode);
       if(ul_currentline == ul_foundline)
          VioWrtNAttr(&bt_g_ViewerSearchStrColor, ColMax, VIEWER_START_ROW, 0, 0);
    }
    return ul_currentline;
 }


/*****************************************************************/
/**   ViewFile_Key_ArrowDown                                    **/
/*****************************************************************/
 ULONG ViewFile_Key_ArrowDown(ULONG ul_currentline, ULONG ul_foundline, 
                              ULONG ul_lastline, ULONG ul_tabsize, 
                              USHORT us_charcode)
 {
    if(ul_currentline != ul_lastline) {
       VioScrollUp(VIEWER_START_ROW, 0, VIEWER_END_ROW, ColMax-1, 1," \0",0);
       ViewFileLine2(VIEWER_END_ROW, (++ul_currentline)+VIEWER_ROW_SIZE-1,
                     ul_tabsize, us_charcode);
       if(ul_currentline+VIEWER_ROW_SIZE-1 == ul_foundline)
          VioWrtNAttr(&bt_g_ViewerSearchStrColor, ColMax, VIEWER_END_ROW, 0, 0);
    }
    return ul_currentline;
 }

/*****************************************************************/
/**   ViewFile_Key_PageUp                                       **/
/*****************************************************************/
 ULONG ViewFile_Key_PageUp(ULONG ul_currentline, ULONG ul_foundline, 
                           ULONG ul_totalline, ULONG ul_tabsize, 
                           USHORT us_charcode)
 {
    if(!ul_currentline) return ul_currentline;

    if(ul_currentline<VIEWER_ROW_SIZE) {
       ul_currentline=0L;
    }else{
       ul_currentline-=VIEWER_ROW_SIZE;
    }
    ViewFilePage_Disp(ul_currentline, ul_foundline, ul_totalline,
                      ul_tabsize, us_charcode);

    return ul_currentline;
 }

/*****************************************************************/
/**   ViewFile_Key_PageDown                                     **/
/*****************************************************************/
 ULONG ViewFile_Key_PageDown(ULONG ul_currentline, ULONG ul_foundline, 
                             ULONG ul_lastline, ULONG ul_totalline, 
                             ULONG ul_tabsize, USHORT us_charcode)
 {
    if(ul_currentline == ul_lastline) return ul_currentline;

    if(ul_lastline-ul_currentline<VIEWER_ROW_SIZE) {
        ul_currentline=ul_lastline;
    }else{
        ul_currentline+=VIEWER_ROW_SIZE;
    }
    ViewFilePage_Disp(ul_currentline, ul_foundline, ul_totalline,
                      ul_tabsize, us_charcode);

    return ul_currentline; 
 }

/*****************************************************************/
/**   ViewFile_Key_Home                                         **/
/*****************************************************************/
 ULONG ViewFile_Key_Home(ULONG ul_currentline, ULONG ul_foundline, 
                         ULONG ul_totalline, ULONG ul_tabsize, 
                         USHORT us_charcode)
 {
    if(ul_currentline) 
       ViewFilePage_Disp(0, ul_foundline, ul_totalline, ul_tabsize, 
                         us_charcode);

    return 0;
 }

/*****************************************************************/
/**   ViewFile_Key_End                                          **/
/*****************************************************************/
 ULONG ViewFile_Key_End(ULONG ul_currentline, ULONG ul_foundline, 
                        ULONG ul_lastline,  ULONG ul_totalline, 
                        ULONG ul_tabsize, USHORT us_charcode)
 {
    if(ul_currentline != ul_lastline) {
      ViewFilePage_Disp(ul_lastline, ul_foundline, ul_totalline,
                        ul_tabsize, us_charcode);
    }
    return ul_lastline;
 }

/*****************************************************************/
/**   ViewFileTitle                                             **/
/*****************************************************************/
 VOID ViewFileTitle(PSZ psz_filename, USHORT us_charcode, ULONG ul_codepage)
 {
    UCHAR  ViewFlTitle[256]={0}; 
    PUCHAR psz_charcode_str;
    
    if (DisableCharCode) {
       switch(us_charcode) {
          case CODE_UTF8:
             sprintf(ViewFlTitle, "%s:%s [UTF-8]", STAR_VIEW_VERSION[English], psz_filename );
             break;
          case CODE_UTF7:
             sprintf(ViewFlTitle, "%s:%s [UTF-7]", STAR_VIEW_VERSION[English], psz_filename );
             break;
          case CODE_UTF16:
             sprintf(ViewFlTitle, "%s:%s [UTF-16%s]", STAR_VIEW_VERSION[English], psz_filename,
                                                      !utf16_little ? "BE" : "LE" );
             break;
		  case CODE_BINARY:
             sprintf(ViewFlTitle, "%s:%s [Binary]", STAR_VIEW_VERSION[English], psz_filename );
             break;
          default:
             sprintf(ViewFlTitle, "%s:%s [CodePage %d]", STAR_VIEW_VERSION[English], psz_filename, ul_codepage);
       }
    } else {
       switch(us_charcode) {
          case CODE_SJIS:
             psz_charcode_str="[SJIS]";
             break;    
          case CODE_JIS:
             psz_charcode_str="[JIS]";
             break;    
          case CODE_EUC:
             psz_charcode_str="[EUC]";
             break;    
          case CODE_LATIN:
             psz_charcode_str="[Latin]";
             break;    
          case CODE_CYRIL:
             psz_charcode_str="[Cyril]";
             break;    
          case CODE_KOI8:
             psz_charcode_str="[koi-8r]";
             break;    
          case CODE_UTF8:
             psz_charcode_str="[UTF-8]";
             break;    
          case CODE_UTF7:
             psz_charcode_str="[UTF-7]";
             break;    
          case CODE_UTF16:
             psz_charcode_str = !utf16_little ? "[UTF-16BE]" : "[UTF-16LE]";
             break;    
		  case CODE_BINARY:
             psz_charcode_str="[Binary]";
             break;
          default:
             psz_charcode_str="";
       }
       sprintf(ViewFlTitle, "%s:%s %s", STAR_VIEW_VERSION[English], psz_filename, psz_charcode_str);
    }
    
    VioWrtCharStrAtt(ViewFlTitle,ColMax,0,0,&bt_g_ViewerTytleBarColor,0);
 
 }

/*****************************************************************/
/**   ViewFile_TotalNumDisp                                     **/
/*****************************************************************/
 USHORT ViewFile_TotalNumDisp(ULONG ul_totalline,BOOL binary)
 {
    UCHAR  uc_linenum[16+3]; 
    USHORT us_dispcol_linenum;

    if( binary )
       sprintf(uc_linenum,"/%08X",ul_alreadyreadsize-1 );
    else
       sprintf(uc_linenum,
             English ? "/%lu lines" : "/%lu 行", ul_totalline+1);
    us_dispcol_linenum=ColMax-1-strlen(uc_linenum);

    VioWrtCharStr(uc_linenum, strlen(uc_linenum), 0, us_dispcol_linenum, 0);

    return us_dispcol_linenum;
 }
 
 
/*****************************************************************/
/**   ViewFile_LineNumDisp                                      **/
/*****************************************************************/
 VOID ViewFile_LineNumDisp(ULONG ul_currentline, USHORT us_dispcol_linenum, BOOL binary )
 {
    UCHAR  uc_linenum[16]={0}; 
    USHORT us_dispcolumn;
    static USHORT us_dispcolumn_old=0; /* 前回の長さを覚えておく */

    if( binary )
       sprintf( uc_linenum ,"%08X" ,ul_currentline*16 );
    else
       ultoa(ul_currentline+1, uc_linenum, 10);
    us_dispcolumn=strlen(uc_linenum);

    if(us_dispcolumn_old > us_dispcolumn) {
       VioWrtNChar(" ",us_dispcolumn_old-us_dispcolumn, 0, 
                       us_dispcol_linenum-us_dispcolumn_old, 0);
    }
    VioWrtCharStr(uc_linenum, us_dispcolumn, 0, 
                  us_dispcol_linenum-us_dispcolumn, 0);
    us_dispcolumn_old = us_dispcolumn;
 }

/*****************************************************************/
/**   ViewFileLine_CheckCRLF                                    **/
/*****************************************************************/
 PUCHAR ViewFileLine_CheckCRLF(ULONG ul_currentline, USHORT us_columnsize, 
                               ULONG ul_tabsize, USHORT us_charcode)
 {
    ULONG  ul_count, ul_backsize;
    SHORT  us_count;
    PUCHAR puc_char;
    BOOL   bl_jis_kanji=FALSE, bl_jis_kanji_1byte=FALSE;

    int utf8_siz = 0; /* UTF-8 の何バイト長の文字を処理中であるかの指標 */
    int utf8_cnt = 0; /* 同じく、何バイトが処理済かを示すカウンタ */

    if( us_charcode==CODE_UTF7 ){
        return ViewFileLine_CheckCRLF_UTF7(ul_currentline,us_columnsize,ul_tabsize);
    }
    if( us_charcode==CODE_UTF16 ){
	return ViewFileLine_CheckCRLF_UTF16(ul_currentline,us_columnsize,ul_tabsize);
    }
    if( us_charcode==CODE_BINARY ){
 	return puc_rownumber[ul_currentline]+16;
    }

    if(us_charcode == CODE_JIS) {
       for(ul_count=ul_currentline; ul_count > 0; ul_count--) {
          if(*(puc_rownumber[ul_count]-1)==CR
            || *(puc_rownumber[ul_count]-1)==LF) break;
       }
       for (puc_char = puc_rownumber[ul_count]; 
            puc_char < puc_rownumber[ul_currentline]; puc_char++) {
          if(CheckJisCode_KanjiOut(puc_char) ==TRUE) {
             puc_char+=2;
             bl_jis_kanji=FALSE;
          } else if(CheckJisCode_KanjiIn(puc_char) ==TRUE) {
             puc_char+=2;
             bl_jis_kanji=TRUE;
          }
       }
    }

    puc_char = puc_rownumber[ul_currentline];
    if( us_charcode==CODE_UTF8 ){
	/* バイトオーダーマークがあれば、スキップ */
	if( ((*(unsigned long*)puc_char)&0xFFFFFF)==0xBFBBEF ){
            puc_char += 3;
        }
    }

    for (us_count=0; us_count<us_columnsize; us_count++) {
       if(us_charcode == CODE_JIS) {
          if(CheckJisCode_KanjiOut(puc_char) ==TRUE) {
             puc_char+=3;
             bl_jis_kanji=FALSE;
          } else if(CheckJisCode_KanjiIn(puc_char) ==TRUE) {
             puc_char+=3;
             bl_jis_kanji=TRUE;
             bl_jis_kanji_1byte=FALSE;
          }
       }
       if(us_charcode == CODE_EUC) {
          if(*puc_char == 0x8e)  puc_char++;  // 半角カナ
       }

       if(us_charcode == CODE_UTF8) {
          if(!utf8_cnt){
             if(*puc_char>=0xc0){
                /* UTF-8 文字検出 */
                utf8_siz = (*puc_char<0xe0) ? 2 : (*puc_char<0xf0) ? 3 : 4;
                utf8_cnt = utf8_siz - 1;
                if(utf8_siz==3){
                   /* ３バイト文字 */
                   if( *puc_char==0xef && puc_char[1]>=0xbd && puc_char[1]<=0xbe ){
                      us_count -= 2; /* 半角カナ */
                   }
                   else{
                      us_count -= 1; /* 全角 */
                   }
                }
                else
                if(utf8_siz==4){
                   /* ４バイト文字 */
                   us_count -= 2;
                }
             }
          }
          else{
             utf8_cnt--;
          }
       }

       switch(*puc_char) {
          case LF:
             return ++puc_char;
          case CR:
             if(*(++puc_char)==LF) 
                return ++puc_char;
             else 
                return puc_char;
          case '\t': 
             us_count += ((ul_tabsize-(ULONG)(us_count)%ul_tabsize)-1);
             puc_char++; 
             break;
          case BACK:
             if(puc_char == puc_rownumber[ul_currentline]) {
                puc_char++;
                break; // 行頭の^Hは無視
             }
             ul_backsize=1;
             if(*(puc_char+1) == BACK) ul_backsize=2;
             if(us_charcode == CODE_JIS && ul_backsize==2 
                  && CheckJisCode_KanjiIn(puc_char+2) ==TRUE 
                  && CheckJisCode_KanjiOut(puc_char-3) ==TRUE 
                  && !memcmp(puc_char-ul_backsize-3, puc_char+ul_backsize+3, 
                           ul_backsize)) {
                puc_char += ul_backsize*2+3;
                us_count--;
             } else if(!memcmp(puc_char-ul_backsize, puc_char+ul_backsize, 
                               ul_backsize)
                     ||!memcmp(puc_char-ul_backsize, "__", ul_backsize) ) {
                puc_char += ul_backsize*2;
                us_count--;
             } else {
                puc_char++;
             }
             break;
          default:
             switch (us_charcode){
                case CODE_LATIN:
                case CODE_CYRIL:
                case CODE_KOI8:
                   us_count += (LatinCharToSjisChar(NULL, puc_char, us_charcode)-1); 
                   if(us_count == us_columnsize) puc_char--;
             }
             puc_char++; 
       }
       if(us_charcode == CODE_JIS && bl_jis_kanji==TRUE) {
          bl_jis_kanji_1byte = !bl_jis_kanji_1byte;
       }
    }

   if(us_charcode == CODE_UTF8) {
      /* 処理が済んでいない文字がある場合のポインタの調整 */
      if(utf8_cnt){
         puc_char -= utf8_siz - utf8_cnt;
      }
   }

    if(us_charcode == CODE_JIS) {
       if(bl_jis_kanji_1byte==TRUE) puc_char--;
    } else {
       puc_char -= ViewFile_CheckDBCS(puc_rownumber[ul_currentline], puc_char,
                             us_charcode);
    }
    return puc_char;
 }


/*****************************************************************/
/**   ViewFileLine_CheckCRLF_UTF7                               **/
/*****************************************************************/
 PUCHAR ViewFileLine_CheckCRLF_UTF7(ULONG ul_currentline, USHORT us_columnsize, 
                               ULONG ul_tabsize)
 {
    ULONG  ul_backsize;
    SHORT  us_count;
    PUCHAR puc_char;
	PUCHAR valid_char;

    puc_char = valid_char = puc_rownumber[ul_currentline];

    for (us_count=0; us_count<us_columnsize; us_count++) {
		if(*puc_char=='+' ){
			valid_char = puc_char;
			puc_char++;
			utf7_setb_s = 1;
		}
		if(utf7_setb_s){
			if( *puc_char=='-' ){
				puc_char++;
				utf7_setb_s = 0;
			}
			else{
				int lb = 0;
				unsigned short u16;
				while(1){
					if( !ISUTF7SETB(*puc_char) ){
						if( *puc_char=='-' ) puc_char++;
						if( us_count>us_columnsize ){
							puc_char = valid_char;
							utf7_setb_s = 1;
						}
						else{
							utf7_setb_s = 0;
						}
						break;
					}

					if( us_count>=us_columnsize ){
						puc_char = valid_char;
						utf7_setb_s = 1;
						break;
					}

					switch(++lb){
					case 1:
						u16 = (((unsigned short)DCUTF7SETB(*puc_char))<<10);
						break;
					case 2:
						u16 |= (unsigned short)(((unsigned short)DCUTF7SETB(*puc_char))<<4);
						break;
					case 3:
						u16 |= (unsigned short)(((unsigned short)DCUTF7SETB(*puc_char))>>2);
						us_count += (u16<0x80 || (u16>=0xFF61&&u16<=0xFF9F)) ? 1 : 2;
						u16 = (((unsigned short)DCUTF7SETB(*puc_char))<<14);
						break;
					case 4:
						u16 |= (unsigned short)(((unsigned short)DCUTF7SETB(*puc_char))<<8);
						break;
					case 5:
						u16 |= (unsigned short)(((unsigned short)DCUTF7SETB(*puc_char))<<2);
						break;
					case 6:
						u16 |= (unsigned short)(((unsigned short)DCUTF7SETB(*puc_char))>>4);
						us_count += (u16<0x80 || (u16>=0xFF61&&u16<=0xFF9F)) ? 1 : 2;
						u16 = (((unsigned short)DCUTF7SETB(*puc_char))<<12);
						break;
					case 7:
						u16 |= (unsigned short)(((unsigned short)DCUTF7SETB(*puc_char))<<6);
						break;
					case 8:
						u16 |= (unsigned short)DCUTF7SETB(*puc_char);
						us_count += (u16<0x80 || (u16>=0xFF61&&u16<=0xFF9F)) ? 1 : 2;
						lb = 0;
						break;
					}

					puc_char++;
					if( !lb && us_count<=us_columnsize ) valid_char = puc_char;
				}

				us_count--;
			}
			continue;
		}

       switch(*puc_char) {
          case LF:
             return ++puc_char;
          case CR:
			puc_char++;
             if(*puc_char==LF) 
                return ++puc_char;
             else 
                return puc_char;
          case '\t': 
             us_count += ((ul_tabsize-(ULONG)(us_count)%ul_tabsize)-1);
             puc_char++;
             break;
          case BACK:
             if(puc_char == puc_rownumber[ul_currentline]) {
                puc_char++;
                break; // 行頭の^Hは無視
             }
             ul_backsize=1;
             if(*(puc_char+1) == BACK) ul_backsize=2;
             if(!memcmp(puc_char-ul_backsize, puc_char+ul_backsize, 
                               ul_backsize)
                     ||!memcmp(puc_char-ul_backsize, "__", ul_backsize) ) {
                puc_char += ul_backsize;
                us_count--;
             } else {
                puc_char++;
             }
             break;
          default:
			puc_char++;
       }
    }

    return puc_char;
 }


/*****************************************************************/
/**   ViewFileLine_CheckCRLF_UTF16                                  **/
/*****************************************************************/
 PUCHAR ViewFileLine_CheckCRLF_UTF16(ULONG ul_currentline, USHORT us_columnsize, 
                               ULONG ul_tabsize)
 {
    ULONG  ul_backsize;
    SHORT  us_count;
    PUCHAR puc_char;
	int dbcs = 0;

    puc_char = puc_rownumber[ul_currentline];

	/* バイトオーダーマークがあれば、スキップ */
	switch( *((unsigned short*)puc_char) ){
		case 0xFFFE: case 0xFEFF: puc_char += 2;
	}

    for (us_count=0; us_count<us_columnsize; us_count++) {
		unsigned short u16 = UTF16WORD(puc_char,utf16_little);

		dbcs = 0;

		if( u16>=0xD800 && u16<0xDC00 ){
			/* サロゲート対象文字＝４バイト */
			puc_char += 4;
			dbcs = 4;
			continue;
		}

       switch(u16) {
          case LF:
             return puc_char+2;
          case CR:
			puc_char+=2;
			u16 = UTF16WORD(puc_char,utf16_little);

             if(u16==LF) 
                return puc_char+2;
             else 
                return puc_char;
          case '\t': 
             us_count += ((ul_tabsize-(ULONG)(us_count)%ul_tabsize)-1);
             puc_char+=2; 
             break;
          case BACK:
             if(puc_char == puc_rownumber[ul_currentline]) {
                puc_char+=2;
                break; // 行頭の^Hは無視
             }
             ul_backsize=1*2;
			 u16 = UTF16WORD(puc_char+2,utf16_little);
             if(u16 == BACK) ul_backsize=2*2;
             if(!memcmp(puc_char-ul_backsize, puc_char+ul_backsize, 
                               ul_backsize)
                     ||!memcmp(puc_char-ul_backsize, utf16_little?"_\0_\0":"\0_\0_", ul_backsize) ) {
                puc_char += ul_backsize*2;
                us_count--;
             } else {
                puc_char+=2;
             }
             break;
          default:
             puc_char += 2; 
             if( u16>=0x80 && !(u16>=0xFF61&&u16<=0xFF9F) ){
                 /* 7bit-ASCIIでない＆半角カナでない＝DBCS文字(２バイト) */
                 us_count++;
                 dbcs = 2;
             }
       }
    }

	if(us_count>us_columnsize) puc_char -= dbcs;

    return puc_char;
 }


/*****************************************************************/
/**   ViewFileLine2                                             **/
/*****************************************************************/
 VOID ViewFileLine2(USHORT us_LineSeq, ULONG ul_drawline, ULONG ul_tabsize,
                    USHORT us_charcode)
 {
    USHORT us_linelen;
    PUCHAR puc_endptr=puc_rownumber[ul_drawline+1]-1, 
           puc_lastptr=puc_rownumber[ul_drawline+1]-1;
    PBYTE  pbt_CRLFcolor = &bt_g_ViewerCRLFColor; 
    PSZ    psz_CRLF;
    if( us_charcode==CODE_UTF16 ){
       puc_endptr--;
       puc_lastptr--;
       switch( UTF16WORD(puc_rownumber[ul_drawline],utf16_little) ){
       case CR: case LF:
          /* 1文字目が改行コードのとき、puc_rownumber[0]-1 をaccessしない様に */
          us_linelen=0;
          break;
       default:
          if(UTF16WORD(puc_endptr,utf16_little)==LF) puc_endptr -= 2;
          if(UTF16WORD(puc_endptr,utf16_little)==CR) puc_endptr -= 2;
          us_linelen=(USHORT)(puc_endptr-puc_rownumber[ul_drawline])+2;
       }
    } else if( us_charcode==CODE_BINARY ){
       ULONG l = puc_rownumber[0] + ul_alreadyreadsize - puc_rownumber[ul_drawline];
       us_linelen = (USHORT)(l<16 ? l : 16);
    } else if(*puc_rownumber[ul_drawline]==CR 
           || *puc_rownumber[ul_drawline]==LF) {
    /* 1文字目が改行コードのとき、puc_rownumber[0]-1 をaccessしない様に */
       us_linelen=0;
    } else {
       if(*puc_endptr==LF) puc_endptr--;
       if(*puc_endptr==CR) puc_endptr--;
       us_linelen=(USHORT)(puc_endptr-puc_rownumber[ul_drawline])+1;
    }
   
    us_linelen=ViewFileLine_Disp(us_LineSeq, ul_drawline, us_linelen, 
                                 ul_tabsize, us_charcode);

	if( us_charcode==CODE_BINARY ){
		return;
	}

    if(puc_endptr!=puc_lastptr || !us_linelen) {
       if(bl_g_flg_showCRLF == FALSE) {                                           
          psz_CRLF = " ";                                                         
          pbt_CRLFcolor = &bt_g_ViewerCharcterColor;                              
       } else {                                                                   
          psz_CRLF = CRLFDISP;                                                    
          if(us_charcode==CODE_UTF16){
             switch( UTF16WORD(puc_lastptr,utf16_little) ){
                case CR:
                   pbt_CRLFcolor = &bt_g_ViewerCRColor;
                   break;
                case LF:
                   if(puc_rownumber[ul_drawline+1]==puc_rownumber[ul_drawline]+2) {
                      pbt_CRLFcolor = &bt_g_ViewerLFColor;
                   }else if(UTF16WORD(puc_lastptr-2,utf16_little) != CR) {
                      pbt_CRLFcolor = &bt_g_ViewerLFColor;
                   }
                   break;
             }
          } else {
             switch(*puc_lastptr) {                                                  
                case CR:                                                             
                   pbt_CRLFcolor = &bt_g_ViewerCRColor;                              
                   break;                                                            
                case LF:                                                             
                   if(puc_rownumber[ul_drawline+1]==puc_rownumber[ul_drawline]+1) {  
                      pbt_CRLFcolor = &bt_g_ViewerLFColor;                           
                   }else if(*(puc_lastptr-1) != CR) {                                
                      pbt_CRLFcolor = &bt_g_ViewerLFColor;                           
                   }                                                                 
                   break;                                                            
            }                                                                       
         }
       }                                                                          
       VioWrtCharStrAtt(psz_CRLF,1,us_LineSeq,us_linelen,pbt_CRLFcolor,0);        
    }

 }

/*****************************************************************/
/**   ViewFileLine_BuffSet                                      **/
/*****************************************************************/
USHORT ViewFileLine_BuffSet(PSZ psz_SetBuff, ULONG ul_currentline, 
                         USHORT us_charnumber, ULONG ul_tabsize,
                         USHORT us_charcode)
{
    UCHAR uc_WkBuff[512]={0}, uc_WkBuff2[512]={0};
    USHORT us_count, us_linelen=0;
    PUCHAR puc_targetptr=psz_SetBuff, puc_zeroptr,
           puc_sourceptr=puc_rownumber[ul_currentline],  puc_char;
    ULONG  ul_count, ul_spacesize, ul_backsize;
    BOOL   bl_jis_kanji=FALSE;
    int utf7_setb_a = 0;

    if( us_charcode==CODE_BINARY ){
       int li;
       char* bp;

       memset( psz_SetBuff ,' ' ,ColMax );
       sprintf( psz_SetBuff ,"%08X : " ,(puc_rownumber[ul_currentline]-puc_rownumber[0])%0x10000000 );

       for( li = 0 ,bp = psz_SetBuff+11 ;li<us_charnumber ;li++ ,bp+=3 ){
           sprintf( bp ,"%02X%c" ,(unsigned char)(puc_rownumber[ul_currentline][li]) ,li==7?'-':' ' );
       }
       for( ;li<16 ;li++ ,bp+=3 ){
           sprintf( bp ,"   " );
       }
       sprintf( bp ,": " ); bp += 2;
       memcpy( bp ,puc_rownumber[ul_currentline] ,us_charnumber );

       return strlen(psz_SetBuff);
    }

    if(us_charcode == CODE_JIS) {
       for(ul_count=ul_currentline; ul_count > 0; ul_count--) {
          if(*(puc_rownumber[ul_count]-1)==CR
            || *(puc_rownumber[ul_count]-1)==LF) break;
       }
       for (puc_char = puc_rownumber[ul_count]; 
            puc_char < puc_rownumber[ul_currentline]; puc_char++) {
          if(CheckJisCode_KanjiOut(puc_char) ==TRUE) {
             puc_char+=2;
             bl_jis_kanji=FALSE;
          } else if(CheckJisCode_KanjiIn(puc_char) ==TRUE) {
             puc_char+=2;
             bl_jis_kanji=TRUE;
          }
       }
    }

    if(us_charcode == CODE_UTF7) {
       for(ul_count=ul_currentline; ul_count > 0; ul_count--) {
          if(*(puc_rownumber[ul_count]-1)==CR
            || *(puc_rownumber[ul_count]-1)==LF) break;
       }
       for (puc_char = puc_rownumber[ul_count]; 
            puc_char < puc_rownumber[ul_currentline]; puc_char++) {
			if(!utf7_setb_a){
				if( *puc_char=='+' ) utf7_setb_a = 1;
			}
			else{
				if( !ISUTF7SETB(*puc_char) ) utf7_setb_a = 0;
			}
       }
    }

    if(us_charcode != CODE_SJIS) {
       memcpy(uc_WkBuff2, puc_rownumber[ul_currentline], us_charnumber);
       uc_WkBuff2[us_charnumber] = '\0';
       switch(us_charcode) {
          case CODE_JIS:
             JisToSjis(uc_WkBuff, uc_WkBuff2, bl_jis_kanji);
             break;
          case CODE_EUC:
             EucToSjis(uc_WkBuff, uc_WkBuff2);
             break;
          case CODE_LATIN:
          case CODE_CYRIL:
          case CODE_KOI8:
             LatinToSjis(uc_WkBuff, uc_WkBuff2, us_charcode);
             break;
          case CODE_UTF8:
             UTF8ToAscii( uc_WkBuff ,sizeof(uc_WkBuff) ,uc_WkBuff2 );
             break;    
          case CODE_UTF7:
             UTF7ToAscii( uc_WkBuff ,sizeof(uc_WkBuff) ,uc_WkBuff2 ,utf7_setb_a );
             utf7_setb_a = 0;
             break;    
          case CODE_UTF16:
             UTF16ToAscii( uc_WkBuff ,sizeof(uc_WkBuff) ,uc_WkBuff2 ,utf16_little );
             break;    
       }
       puc_sourceptr=uc_WkBuff;
       us_charnumber=strlen(uc_WkBuff);
    }

    puc_zeroptr=puc_sourceptr;
    for(us_count=0; us_count<us_charnumber; us_count++) {
       switch(*puc_sourceptr) {
          case '\t':
             ul_spacesize=ul_tabsize-(ULONG)(puc_targetptr-uc_WkBuff)%ul_tabsize ;
             memset(puc_targetptr, ' ', ul_spacesize);
             puc_targetptr += ul_spacesize;
             us_linelen += ul_spacesize;
             break;
          case BACK:
             if(puc_zeroptr==puc_sourceptr) break;   // 行頭の^Hは無視
             ul_backsize=1;
             if(*(puc_sourceptr+1) == BACK) ul_backsize=2;
             if(us_linelen > ul_backsize-1) {
                if(!memcmp(puc_sourceptr-ul_backsize, puc_sourceptr+ul_backsize, 
                           ul_backsize)
                  ||!memcmp(puc_sourceptr-ul_backsize, "__", ul_backsize) ) {
                   puc_targetptr -= ul_backsize;
                   puc_sourceptr += ul_backsize;        
                   us_linelen -= ul_backsize;
                   us_count ++;
                }
             }
         default:
             *puc_targetptr = *puc_sourceptr;
             puc_targetptr++;
             us_linelen++;
       }
       puc_sourceptr++;
    }

    if(us_charcode != CODE_SJIS) {
       /* Shift-JIS 以外のバイナリは考慮しない */ 
       us_linelen=strlen(psz_SetBuff);
    }
    if(us_linelen>ColMax) {
       return ColMax;
    } else {
       return us_linelen;
    }
}

/*****************************************************************/
/**   ViewFileLine_Disp                                         **/
/*****************************************************************/
USHORT ViewFileLine_Disp(USHORT us_LineSeq, ULONG ul_currentline, 
                         USHORT us_charnumber, ULONG ul_tabsize,
                         USHORT us_charcode)
{
    UCHAR uc_WkBuff2[512]={0};
    USHORT us_linelen;

    us_linelen=ViewFileLine_BuffSet(uc_WkBuff2, ul_currentline, 
                         us_charnumber, ul_tabsize, us_charcode);

    VioWrtCharStrAtt(uc_WkBuff2,ColMax,us_LineSeq,0,&bt_g_ViewerCharcterColor,0);

    return us_linelen;
}

/*****************************************************************/
/**   ViewFilePage_Disp                                         **/
/*****************************************************************/
VOID ViewFilePage_Disp(ULONG ul_drawline, ULONG ul_foundline, 
                       ULONG ul_totalline, ULONG ul_tabsize, 
                       USHORT us_charcode)
{
    USHORT us_count;

    for(us_count=0; 
        us_count<VIEWER_ROW_SIZE&&us_count<ul_totalline+1; 
        us_count++) {
       ViewFileLine2(VIEWER_START_ROW+us_count, ul_drawline, ul_tabsize,
                     us_charcode);
       if(ul_drawline == ul_foundline)
          VioWrtNAttr(&bt_g_ViewerSearchStrColor, ColMax, 
                      VIEWER_START_ROW+us_count, 0, 0);
       ul_drawline++;
    }
    if(us_count != VIEWER_END_ROW) 
       VioWrtNAttr(&bt_g_ViewerBackGroundColor,
                   (VIEWER_END_ROW-us_count)*ColMax, 
                   VIEWER_START_ROW+us_count,0,0); 
}

/*****************************************************************/
/**   ViewFileFoundPage_Disp                                    **/
/*****************************************************************/
ULONG ViewFileFoundPage_Disp(ULONG ul_foundline, ULONG ul_currentline, 
                            ULONG ul_lastline,  ULONG ul_totalline,
                            ULONG ul_tabsize, USHORT us_charcode)
{
    if(ul_foundline!=FLAG_SEARCH_NOT_MATCH) {
       if(ul_foundline > ul_currentline + VIEWER_ROW_SIZE-1  
               || ul_foundline < ul_currentline) { 
          if(ul_foundline > VIEWER_ROW_SIZE/2) {
             ul_currentline=ul_foundline-VIEWER_ROW_SIZE/2;
          } else {
             ul_currentline=0;
          }
          if(ul_foundline > ul_lastline) ul_currentline=ul_lastline;
       }
    }
    ViewFilePage_Disp(ul_currentline, ul_foundline, ul_totalline,
                      ul_tabsize, us_charcode);

    return ul_currentline;
}

/*****************************************************************/
/**   ViewFile_CheckDBCS                                        **/
/*****************************************************************/
 int  ViewFile_CheckDBCS(PUCHAR puc_Start, PUCHAR puc_nextStart,
                         USHORT us_charcode)
 {
    PUCHAR puc_char;

    switch(us_charcode) {
       case CODE_UTF8:
          return ViewFile_CheckDBCS_UTF8(puc_Start, puc_nextStart);
       case  CODE_EUC:
          return DisableCharCode ? FALSE : ViewFile_CheckDBCS_EUC(puc_Start, puc_nextStart);
       default:
          if(DisableCharCode) return FALSE;
    }
    if(!iskanji12(puc_nextStart-1)) return FALSE;

    puc_char=puc_Start;
    while(puc_char < puc_nextStart) {
       if(iskanji12(puc_char)) {
          puc_char+=2;
       } else {
          puc_char++;
       }
    }

    if(puc_char==puc_nextStart+1) return TRUE;
    return FALSE;
 }

/*****************************************************************/
/**   ViewFile_CheckDBCS_EUC                                    **/
/*****************************************************************/
 BOOL ViewFile_CheckDBCS_EUC(PUCHAR puc_Start, PUCHAR puc_nextStart)
 {
    PUCHAR puc_char;

    if(*(puc_nextStart-1) < 0x80
     || *(puc_nextStart) < 0x80 ) return FALSE;

    puc_char=puc_Start;
    while(puc_char < puc_nextStart) {
       if(*puc_char > 0x7f && *(puc_char+1) > 0x7f) {
          puc_char+=2;
       } else {
          puc_char++;
       }
    }

    if(puc_char==puc_nextStart+1) return TRUE;
    return FALSE;
 }

/*****************************************************************/
/**   ViewFile_CheckDBCS_UTF8                                   **/
/*****************************************************************/
 int  ViewFile_CheckDBCS_UTF8(PUCHAR puc_Start, PUCHAR puc_nextStart)
 {
    PUCHAR puc_char=puc_Start;

    while(puc_char < puc_nextStart) {
       puc_char += *puc_char<0xc0 ? 1 : *puc_char<0xe0 ? 2 : *puc_char<0xf0 ? 3 : 4;
    }

    return puc_nextStart - puc_char;
 }

/*****************************************************************/
/**   ViewFile_SetLineHeadPtr                                   **/
/*****************************************************************/
 ULONG ViewFile_SetLineHeadPtr(PUCHAR puc_Start, ULONG ul_totalline,
                      ULONG ul_alreadyreadsize, PULONG pul_lastline, 
                      PUSHORT pus_dispcol_linenum, USHORT us_columnsize, 
                      ULONG ul_tabsize, USHORT us_charcode)
 {
    utf7_setb_s = 0;
    puc_rownumber[ul_totalline]=puc_Start;
    for( ; ul_totalline<MAX_ROWNUM-1; ul_totalline++) {
       puc_rownumber[ul_totalline+1]
          =ViewFileLine_CheckCRLF(ul_totalline, us_columnsize, 
                                   ul_tabsize, us_charcode);

       if(puc_rownumber[ul_totalline+1] - puc_rownumber[0]
                                    >= ul_alreadyreadsize) break;
    }
    if(ul_totalline==MAX_ROWNUM-1) ul_totalline--;

    if(ul_totalline > VIEWER_ROW_SIZE-1) {
       *pul_lastline=ul_totalline-VIEWER_ROW_SIZE+1;
    } else {
       *pul_lastline=0;
    }

    *pus_dispcol_linenum=ViewFile_TotalNumDisp(ul_totalline,us_charcode==CODE_BINARY);
    
    return ul_totalline;
 }

/****************************************************************/
/**  ViewFile_ShowHelp                                          */
/****************************************************************/
VOID ViewFile_ShowHelp(ULONG ul_currentline, ULONG ul_foundline, 
                       ULONG ul_totalline, ULONG ul_tabsize, 
                       USHORT us_charcode)
 {
    KBDKEYINFO  kki_chardata={0};

    if(English){
       strcpy(MsgTxt[0], "  NovaView Quick Reference  1/1                             ");
       strcpy(MsgTxt[1], "                                                            ");
       strcpy(MsgTxt[2], "[ key assign of NovaView ]     B    : Search prev           ");
       strcpy(MsgTxt[3], " Up allow  ^E : Prev line      F    : Search next           ");
       strcpy(MsgTxt[4], "Down allow ^X : Next line      H    : Search prev(Repeat)   ");
       strcpy(MsgTxt[5], "  PageUp   ^R : Prev page      L    : Search next(Repeat)   ");
       strcpy(MsgTxt[6], "  PageDown ^C : Next page    Space, Crtl+L                  ");
       strcpy(MsgTxt[7], "   Home : Top of file               : Search same(Repeat)   ");
       strcpy(MsgTxt[8], "   End  : Bottom of file       J    : Jump to any line      ");
       strcpy(MsgTxt[9], "  Enter, ESC, BS, Q : Exit     R    : Show/Hide CR chars    ");
       strcpy(MsgTxt[10],"   4,8  : Change TAB size      @    : Change character code ");
       strcpy(MsgTxt[11],"    V   : External viewer     F11   : Duplicate FileNova    ");
       strcpy(MsgTxt[12],"    E   : Text editor                                       ");
       strcpy(MsgTxt[13],"                                       Push any key to back ");
    }
    else{
       strcpy(MsgTxt[0], "  NovaView の使用説明  1/1                                  ");
       strcpy(MsgTxt[1], "                                                            ");
       strcpy(MsgTxt[2], "●NovaViewのキー操作           B    : 後方↑検索            ");
       strcpy(MsgTxt[3], "    ↑     ^E : 一行上へ       F    : 前方↓検索      　    ");
       strcpy(MsgTxt[4], "    ↓     ^X : 一行下ヘ       H    : 後方↑検索（繰り返し）");
       strcpy(MsgTxt[5], "  PageUp   ^R : 前ページヘ     L    : 前方↓検索（繰り返し）");
       strcpy(MsgTxt[6], "  PageDown ^C : 次ページヘ   Space, Crtl+L                  ");
       strcpy(MsgTxt[7], "   Home : ファイルの先頭へ          : 同方向検索（繰り返し）");
       strcpy(MsgTxt[8], "   End  : ファイルの最後へ     J    : 行ジャンプ            ");
       strcpy(MsgTxt[9], "  Enter, ESC, BS, Q : 終了     R    : 改行の表\示／非表\示    ");
       strcpy(MsgTxt[10],"   4,8  : タブサイズ変更       @    : 文字コード変更        ");
       strcpy(MsgTxt[11],"    V   : 外部ビューワ起動    F11   : FileNovaをもう一つ起動");
       strcpy(MsgTxt[12],"    E   : 外部エディタ起動                                  ");
       strcpy(MsgTxt[13],"                                          任意のキーで戻る  ");
    }


    ShowMsgBox(14, bt_g_InformWindowColor);
    KbdCharIn(&kki_chardata, IO_WAIT, 0); 
    ViewFilePage_Disp(ul_currentline, ul_foundline, ul_totalline, 
                      ul_tabsize, us_charcode);

 }


/****************************************************************/
/**  ViewFile_JumpLine                                          */
/****************************************************************/
ULONG ViewFile_JumpLine(ULONG ul_currentline, ULONG ul_lastline, BOOL binary )
 {
    ULONG  ul_jumpline=0L;
    PUCHAR puc_plusptr, puc_minusptr;

    if(binary){
       if(English){
          strcpy(MsgTxt[0],"  Jump to appointment address. ");
          strcpy(MsgTxt[1],"                               ");
          strcpy(MsgTxt[2],"                               ");
          strcpy(MsgTxt[3],"   Enter:Execute  Esc:Cancel   ");
       }
       else{
          strcpy(MsgTxt[0],"指定されたアドレスにジャンプします");
          strcpy(MsgTxt[1],"                                  ");
          strcpy(MsgTxt[2],"                                  ");
          strcpy(MsgTxt[3],"      Enter:実行   Esc:取消       ");
       }
    } else {
       if(English){
          strcpy(MsgTxt[0],"  Jump to appointment line. ");
          strcpy(MsgTxt[1],"                            ");
          strcpy(MsgTxt[2],"                            ");
          strcpy(MsgTxt[3],"  Enter:Execute  Esc:Cancel ");
       } else {
          strcpy(MsgTxt[0],"指定された行にジャンプします");
          strcpy(MsgTxt[1],"                            ");
          strcpy(MsgTxt[2],"                            ");
          strcpy(MsgTxt[3],"   Enter:実行   Esc:取消    ");
       }
    }
    memset(InpLine, 0, sizeof(InpLine));
    if(KbdLineIn(4, bt_g_NormalWindowColor, 2, InpLine,
                 FLAG_INPUTWIN_NOSTRINGS_OK) ==ESC) {
       return ul_currentline;
    }

    if(InpLine[0]=='\0') return 0;
    if(InpLine[0]=='*')  return ul_lastline;
    
    if(puc_plusptr=strchr(InpLine, '+')) {

       if(binary){
          sscanf(puc_plusptr+1, "%X", &ul_jumpline);
          ul_jumpline = ul_jumpline / 16 + 1;
       }
       else
       sscanf(puc_plusptr+1, "%lu", &ul_jumpline);

       if(ul_jumpline>ul_lastline) return ul_lastline;
       return ul_jumpline+ul_currentline;
    }

    if(puc_minusptr=strchr(InpLine, '-')) {
       if(binary){
          sscanf(puc_plusptr+1, "%X", &ul_jumpline);
          ul_jumpline = ul_jumpline / 16 + 1;
       } else
          sscanf(puc_minusptr+1, "%lu", &ul_jumpline);

       if(ul_jumpline>ul_currentline) return 0;
       return ul_currentline-ul_jumpline;
    }

    if(binary){
       sscanf(InpLine, "%X", &ul_jumpline);
       ul_jumpline = ul_jumpline / 16 + 1;
    } else
       sscanf(InpLine, "%lu", &ul_jumpline);

    if(!ul_jumpline) return 0;
    if(--ul_jumpline>ul_lastline) return ul_lastline;
    return ul_jumpline;
 }


/****************************************************************/
/**  ViewFile_ChangeDispParam                                    */
/****************************************************************/
BOOL ViewFile_ChangeDispParam(UCHAR uc_inputchar, PULONG pul_tabsize, 
                              PUSHORT pus_charcode)
 {
    ULONG  ul_newtabsize;

    switch(uc_inputchar) {
       case '4':
       case '8':
          ul_newtabsize = (ULONG)(uc_inputchar-0x30);
          if(ul_newtabsize != *pul_tabsize) {
             *pul_tabsize = ul_newtabsize;
             return TRUE;
          } else {
             return FALSE;
          }
       case '@':
          return ViewFile_ChangeCharCode(pus_charcode);
    }
    return FALSE;
 }
 

/****************************************************************/
/**  ViewFile_ChangeCharCode                                    */
/****************************************************************/
BOOL ViewFile_ChangeCharCode(PUSHORT pus_charcode)
 {
    KBDKEYINFO kki_keyinfo={0};

    int height = 0;

    if(English){
       strcpy(MsgTxt[height++],"      Select charcter code.      ");
       strcpy(MsgTxt[height++],"                                 ");
       if( !DisableCharCode || hmoduconv ){
           strcpy(MsgTxt[height++],"  A(Enter) : Auto                ");
       }
       if(DisableCharCode){
          strcpy(MsgTxt[height++],"  S        : System default      ");
       }
       else{
          strcpy(MsgTxt[height++],"  S        : Shift-JIS code      ");
          strcpy(MsgTxt[height++],"  J        : JIS code            ");
          strcpy(MsgTxt[height++],"  E        : EUC code            ");
          strcpy(MsgTxt[height++],"  L        : LatinUS code        ");
       }
       if( hmoduconv ){
          strcpy(MsgTxt[height++],"  U        : UTF-8 code          ");
          strcpy(MsgTxt[height++],"  V        : UTF-7 code          ");
          strcpy(MsgTxt[height++],"  W        : UTF-16 code(Auto)   ");
          strcpy(MsgTxt[height++],"  Shift+W  : UTF-16 code(Little) ");
       }
       strcpy(MsgTxt[height++],"  B        : Binary              ");
       strcpy(MsgTxt[height++],"                                 ");
       strcpy(MsgTxt[height++],"                     Esc:Cancel  ");
    }
    else{
       strcpy(MsgTxt[height++],"       文字コードの変更            ");
       strcpy(MsgTxt[height++],"                                   ");
       if( !DisableCharCode || hmoduconv ){
           strcpy(MsgTxt[height++],"  A(Enter) : 自動判定              ");
       }
       if(DisableCharCode){
          strcpy(MsgTxt[height++],"  S        : システム標準          ");
       }
       else{
          strcpy(MsgTxt[height++],"  S        : Shift-JIS コード      ");
          strcpy(MsgTxt[height++],"  J        : JIS コード            ");
          strcpy(MsgTxt[height++],"  E        : EUC コード            ");
          strcpy(MsgTxt[height++],"  L        : LatinUS コード        ");
       }
       if( hmoduconv ){
          strcpy(MsgTxt[height++],"  U        : UTF-8 コード          ");
          strcpy(MsgTxt[height++],"  V        : UTF-7 コード          ");
          strcpy(MsgTxt[height++],"  W        : UTF-16 コード(Auto)   ");
          strcpy(MsgTxt[height++],"  Shift+W  : UTF-16 コード(Little) ");
       }
       strcpy(MsgTxt[height++],"  B        : バイナリ表\示          ");
       strcpy(MsgTxt[height++],"                                   ");
       strcpy(MsgTxt[height++],"                       Esc:取消    ");
    }

    ShowMsgBox(height, bt_g_NormalWindowColor);

    for(;;) {
       KbdCharIn(&kki_keyinfo, IO_WAIT, 0);
       switch(kki_keyinfo.chChar) {
          case 'A':
          case 'a':
          case ENTER:
             if( DisableCharCode && !hmoduconv ) break;
             *pus_charcode=CODE_AUTO;
             return TRUE;
          case 'S':
          case 's':
             *pus_charcode=CODE_SJIS;
             return TRUE;
          case 'J':
          case 'j':
             if(DisableCharCode) break;
             *pus_charcode=CODE_JIS;
             return TRUE;
          case 'E':
          case 'e':
             if(DisableCharCode) break;
             *pus_charcode=CODE_EUC;
             return TRUE;
          case 'L':
          case 'l':
             if(DisableCharCode) break;
             *pus_charcode=CODE_LATIN;
             return TRUE;
          case 'C':
          case 'c':
             if(DisableCharCode) break;
             *pus_charcode=CODE_CYRIL;
             return TRUE;
          case 'K':
          case 'k':
             if(DisableCharCode) break;
             *pus_charcode=CODE_KOI8;
             return TRUE;
          case 'U':
          case 'u':
             if(!hmoduconv) break;
             *pus_charcode=CODE_UTF8;
             return TRUE;
          case 'V':
          case 'v':
             if(!hmoduconv) break;
             *pus_charcode=CODE_UTF7;
             return TRUE;
          case 'W':
          case 'w':
             if(!hmoduconv) break;
             *pus_charcode= CODE_UTF16;
             utf16_little = ((kki_keyinfo.fsState&(USHORT)(KBDSTF_LEFTSHIFT|KBDSTF_RIGHTSHIFT))!=0);
             return TRUE;
          case 'B':
          case 'b':
             *pus_charcode=CODE_BINARY;
             return TRUE;
          case ESC:
             return FALSE;
       }
    }
 }


/****************************************************************/
/**  ViewFile_SearchString                                      */
/****************************************************************/
ULONG ViewFile_SearchString(USHORT us_flg_searchdirect, PUSHORT pus_flg_searchcase,
                            PULONG pul_currentline, 
                            ULONG ul_lastline, ULONG ul_totalline, 
                            PSZ psz_searchstr, ULONG ul_tabsize, 
                            USHORT us_charcode)
 {
    ULONG ul_foundline;
    UCHAR uc_inputchar;

    if(English){
       strcpy(MsgTxt[0]," Search text to next lines. ");
       strcpy(MsgTxt[1],"  - [F1]Case sensitive      ");
       strcpy(MsgTxt[2],"                            ");
       strcpy(MsgTxt[3],"                            ");
       strcpy(MsgTxt[4],"  Enter:Execute  Esc:Cancel ");
    }
    else{
       strcpy(MsgTxt[0],"文字列の前方検索を行ないます");
       strcpy(MsgTxt[1],"  □[F1]大小文字を区別する  ");
       strcpy(MsgTxt[2],"                            ");
       strcpy(MsgTxt[3],"                            ");
       strcpy(MsgTxt[4],"   Enter:実行   Esc:取消    ");
    }

    if(us_flg_searchdirect==FLAG_SEARCH_BACK){
        if(English){
           memcpy(MsgTxt[0]+16,"prev", 4);
        }
        else{
           memcpy(MsgTxt[0]+8,"後", 2);
        }
    }

    memset(InpLine, 0, sizeof(InpLine));
    strcpy(InpLine, psz_searchstr);
    
    do {
       Change_FlagMark(*pus_flg_searchcase,  1, 2);
       uc_inputchar = KbdLineIn(5, bt_g_NormalWindowColor, 3, InpLine, 
                 FLAG_INPUTWIN_NO_OPTION|FLAG_INPUTWIN_FUNCKEY_ON);
       switch(uc_inputchar) {
          case ENTER:
             break;
          case ESC:
             ul_foundline=FLAG_SEARCH_NOT_MATCH;
             ViewFilePage_Disp(*pul_currentline, ul_foundline, ul_totalline, 
                         ul_tabsize, us_charcode);
             return ul_foundline;
          case PF1:
             *pus_flg_searchcase=!(*pus_flg_searchcase);
             break;
       }
    } while(uc_inputchar!=ENTER);

    strcpy(psz_searchstr, InpLine);
    if( us_charcode==CODE_BINARY ){
       if(us_flg_searchdirect==FLAG_SEARCH_FORWARD) {
          ul_foundline = ViewFile_ForwardFirstSearchStringBin(*pus_flg_searchcase, 
                            *pul_currentline, ul_lastline, ul_totalline, 
                            psz_searchstr);
       } else {
          ul_foundline = ViewFile_BackwardFirstSearchStringBin(*pus_flg_searchcase,
                            *pul_currentline, ul_lastline, ul_totalline, 
                            psz_searchstr);
       }
    }
    else
    if(us_charcode == CODE_SJIS) {
       if(us_flg_searchdirect==FLAG_SEARCH_FORWARD) {
          ul_foundline = ViewFile_ForwardFirstSearchString(*pus_flg_searchcase, 
                            *pul_currentline, ul_lastline, ul_totalline, 
                            psz_searchstr);
       } else {
          ul_foundline = ViewFile_BackwardFirstSearchString (*pus_flg_searchcase,
                            *pul_currentline, ul_lastline, ul_totalline, 
                            psz_searchstr);
       }
    } else {
       if(us_flg_searchdirect==FLAG_SEARCH_FORWARD) {
          ul_foundline = ViewFile_ForwardFirstSearchString2(*pus_flg_searchcase, 
                            *pul_currentline, ul_lastline, ul_totalline, 
                            psz_searchstr, ul_tabsize, us_charcode);
       } else {
          ul_foundline = ViewFile_BackwardFirstSearchString2(*pus_flg_searchcase, 
                            *pul_currentline, ul_lastline, ul_totalline, 
                            psz_searchstr, ul_tabsize, us_charcode);
       }
    }
    *pul_currentline = ViewFileFoundPage_Disp(ul_foundline, *pul_currentline, 
                            ul_lastline, ul_totalline, ul_tabsize, 
                            us_charcode);
    return ul_foundline;
 }

/****************************************************************/
/**  ViewFile_SearchSameString                                  */
/****************************************************************/
ULONG ViewFile_SearchSameString(USHORT us_flg_searchdirect, USHORT us_flg_searchcase,
               PULONG pul_currentline, ULONG ul_foundline, ULONG ul_lastline, 
               ULONG ul_totalline, PSZ psz_searchstr, ULONG ul_tabsize, 
               USHORT us_charcode)
 {
    ULONG ul_foundline_new;

    /* 画面の中に前回の一致の結果が残っているか */
    if(ul_foundline > *pul_currentline + VIEWER_ROW_SIZE-1  
               || ul_foundline < *pul_currentline) { 
       /* 残っていない -> 初めてのサーチと同じ */
       if( us_charcode==CODE_BINARY ){
          if(us_flg_searchdirect==FLAG_SEARCH_FORWARD) {
             ul_foundline = ViewFile_ForwardFirstSearchStringBin(us_flg_searchcase, 
                               *pul_currentline, ul_lastline, ul_totalline, 
                               psz_searchstr);
          } else {
             ul_foundline = ViewFile_BackwardFirstSearchString (us_flg_searchcase,
                               *pul_currentline, ul_lastline, ul_totalline, 
                               psz_searchstr);
          }
       }
       else
       if(us_charcode == CODE_SJIS) {
          if(us_flg_searchdirect==FLAG_SEARCH_FORWARD) {
             ul_foundline = ViewFile_ForwardFirstSearchStringBin(us_flg_searchcase, 
                               *pul_currentline, ul_lastline, ul_totalline, 
                               psz_searchstr);
          } else {
             ul_foundline = ViewFile_BackwardFirstSearchString (us_flg_searchcase,
                               *pul_currentline, ul_lastline, ul_totalline, 
                               psz_searchstr);
          }
       } else {
          if(us_flg_searchdirect==FLAG_SEARCH_FORWARD) {
             ul_foundline = ViewFile_ForwardFirstSearchString2(us_flg_searchcase, 
                               *pul_currentline, ul_lastline, ul_totalline, 
                               psz_searchstr, ul_tabsize, us_charcode);
          } else {
             ul_foundline = ViewFile_BackwardFirstSearchString2(us_flg_searchcase, 
                               *pul_currentline, ul_lastline, ul_totalline, 
                               psz_searchstr, ul_tabsize, us_charcode);
          }
       }
    } else {
       /* 残っている -> 続きを探す */
       if( us_charcode==CODE_BINARY ){
          if(us_flg_searchdirect==FLAG_SEARCH_FORWARD) {
             ul_foundline_new = ViewFile_ForwardNextSearchStringBin(us_flg_searchcase, 
                                ul_foundline, ul_lastline, ul_totalline, 
                                psz_searchstr);
          }else{
             ul_foundline_new = ViewFile_BackwardNextSearchStringBin(us_flg_searchcase, 
                                ul_foundline, ul_lastline, ul_totalline, 
                                psz_searchstr);
          }
       }
       else
       if(us_charcode == CODE_SJIS) {
          if(us_flg_searchdirect==FLAG_SEARCH_FORWARD) {
             ul_foundline_new = ViewFile_ForwardNextSearchString(us_flg_searchcase, 
                                ul_foundline, ul_lastline, ul_totalline, 
                                psz_searchstr);
          }else{
             ul_foundline_new = ViewFile_BackwardNextSearchString(us_flg_searchcase, 
                                ul_foundline, ul_lastline, ul_totalline, 
                                psz_searchstr);
          }
       } else {
          if(us_flg_searchdirect==FLAG_SEARCH_FORWARD) {
             ul_foundline_new = ViewFile_ForwardNextSearchString2(us_flg_searchcase, 
                               ul_foundline, ul_lastline, ul_totalline, 
                               psz_searchstr, ul_tabsize, us_charcode);
          }else{
             ul_foundline_new = ViewFile_BackwardNextSearchString2(us_flg_searchcase, 
                                ul_foundline, ul_lastline, ul_totalline, 
                                psz_searchstr, ul_tabsize, us_charcode);
          }
       }
       if(ul_foundline_new != FLAG_SEARCH_NOT_MATCH) 
          ul_foundline=ul_foundline_new;
    }
    *pul_currentline = ViewFileFoundPage_Disp(ul_foundline, *pul_currentline, 
                            ul_lastline, ul_totalline, ul_tabsize, 
                            us_charcode);
 
    return ul_foundline;
 }


/****************************************************************/
/**  ViewFile_ForwardFirstSearchString2                         */
/****************************************************************/
ULONG ViewFile_ForwardFirstSearchString2(USHORT us_flg_searchcase, 
            ULONG ul_currentline, ULONG ul_lastline, ULONG ul_totalline, 
            PSZ psz_searchstr, ULONG ul_tabsize, USHORT us_charcode)
{

    if(!strlen(psz_searchstr)) return FLAG_SEARCH_NOT_MATCH;
    
    return  ViewFile_ForwardSearchStringEngine2(ul_currentline, 
                          ul_totalline, psz_searchstr, us_flg_searchcase,
                          ul_tabsize, us_charcode);

}

/****************************************************************/
/**  ViewFile_ForwardNextSearchString2                          */
/****************************************************************/
ULONG ViewFile_ForwardNextSearchString2(USHORT us_flg_searchcase, 
            ULONG ul_currentline, ULONG ul_lastline, ULONG ul_totalline, 
            PSZ psz_searchstr, ULONG ul_tabsize, USHORT us_charcode)
{
   return ViewFile_ForwardFirstSearchString2(us_flg_searchcase, 
                        ul_currentline+1, ul_lastline, ul_totalline, 
                        psz_searchstr, ul_tabsize, us_charcode);
}


/****************************************************************/
/**  ViewFile_ForwardSearchStringEngine2                        */
/****************************************************************/
ULONG  ViewFile_ForwardSearchStringEngine2(ULONG ul_startline, 
                  ULONG ul_endline, PSZ psz_searchstr, USHORT us_flg_searchcase, 
                  ULONG ul_tabsize, USHORT us_charcode)
{
    UCHAR uc_WkBuff[512]={0}, uc_WkBuff2[512]={0};
    USHORT us_linelen, us_linelen2, us_strlen;
    ULONG ul_currentline, ul_offset;

	if( ul_startline>ul_endline ){
		return FLAG_SEARCH_NOT_MATCH;
	}
    us_strlen= strlen(psz_searchstr);
    us_linelen=ViewFileLine_BuffSet(uc_WkBuff, ul_startline, 
                        puc_rownumber[ul_startline+1]-puc_rownumber[ul_startline], 
                        ul_tabsize, us_charcode);
  
    for(ul_currentline=ul_startline; ul_currentline<ul_endline+1; ul_currentline++) {
       if(ul_currentline != ul_endline) {
          us_linelen2=ViewFileLine_BuffSet(uc_WkBuff2, ul_currentline+1, 
                           puc_rownumber[ul_currentline+2]-puc_rownumber[ul_currentline+1], 
                           ul_tabsize, us_charcode);
       }
       if(*(puc_rownumber[ul_currentline+1]-1) != CR 
                && *(puc_rownumber[ul_currentline+1]-1) != LF ) {
          if(ul_currentline != ul_endline) {
             memcpy(uc_WkBuff+us_linelen, uc_WkBuff2, us_strlen);
          }
          ul_offset=0;
       } else {
          ul_offset=us_strlen;
       }
       
       if(us_linelen > ul_offset) {
          if( jmemstr(uc_WkBuff,psz_searchstr,us_linelen,us_flg_searchcase) ){
             return ul_currentline;
          }
       }
       
       memset(uc_WkBuff, 0, sizeof(uc_WkBuff));
       memcpy(uc_WkBuff, uc_WkBuff2, sizeof(uc_WkBuff2));
       memset(uc_WkBuff2, 0, sizeof(uc_WkBuff2));
       us_linelen=us_linelen2;
    }
    return FLAG_SEARCH_NOT_MATCH;
}


/****************************************************************/
/**  ViewFile_BackwardFirstSearchString2                        */
/****************************************************************/
ULONG ViewFile_BackwardFirstSearchString2(USHORT us_flg_searchcase, 
            ULONG ul_currentline, ULONG ul_lastline, ULONG ul_totalline, 
            PSZ psz_searchstr, ULONG ul_tabsize, USHORT us_charcode)
{
    ULONG ul_searchstartline;

    if(!strlen(psz_searchstr)) return FLAG_SEARCH_NOT_MATCH;

    if(ul_currentline+VIEWER_ROW_SIZE > ul_totalline) {
       ul_searchstartline=ul_totalline; 
    } else {
       ul_searchstartline=ul_currentline+VIEWER_ROW_SIZE;
    }

    return  ViewFile_BackwardSearchStringEngine2(ul_searchstartline, 
                          0L, psz_searchstr, us_flg_searchcase,
                          ul_tabsize, us_charcode);

}

/****************************************************************/
/**  ViewFile_BackwardNextSearchString2                        */
/****************************************************************/
ULONG ViewFile_BackwardNextSearchString2(USHORT us_flg_searchcase, 
            ULONG ul_currentline, ULONG ul_lastline, ULONG ul_totalline, 
            PSZ psz_searchstr, ULONG ul_tabsize, USHORT us_charcode)
{
    ULONG ul_searchstartline;

    if(!strlen(psz_searchstr)) return FLAG_SEARCH_NOT_MATCH;

    if(ul_currentline > 0) {
       ul_searchstartline=ul_currentline-1; 
    } else {
       return FLAG_SEARCH_NOT_MATCH;  
    }

    return  ViewFile_BackwardSearchStringEngine2(ul_searchstartline, 
                          0L, psz_searchstr, us_flg_searchcase,
                          ul_tabsize, us_charcode);

}

/****************************************************************/
/**  ViewFile_BackwardSearchStringEngine2                       */
/****************************************************************/
ULONG  ViewFile_BackwardSearchStringEngine2(ULONG ul_startline, 
                  ULONG ul_endline, PSZ psz_searchstr, USHORT us_flg_searchcase, 
                  ULONG ul_tabsize, USHORT us_charcode)
{
    UCHAR uc_WkBuff[512]={0}, uc_WkBuff2[512]={0};
    USHORT us_linelen, us_strlen;
    ULONG ul_offset;
    LONG l_currentline;

    us_strlen= strlen(psz_searchstr);

    for(l_currentline=ul_startline; l_currentline >= 0; l_currentline--) {
       us_linelen=ViewFileLine_BuffSet(uc_WkBuff, l_currentline, 
                           puc_rownumber[l_currentline+1]-puc_rownumber[l_currentline], 
                           ul_tabsize, us_charcode);

       if(*(puc_rownumber[l_currentline+1]-1) != CR 
                && *(puc_rownumber[l_currentline+1]-1) != LF ) {
          if(l_currentline != ul_startline) {
             memcpy(uc_WkBuff+us_linelen, uc_WkBuff2, us_strlen);
          }
          ul_offset=0;
       } else {
          ul_offset=us_strlen;
       }
       
       if(us_linelen > ul_offset) {
          if( jmemstr(uc_WkBuff,psz_searchstr,us_linelen,us_flg_searchcase) ){
             return (ULONG)l_currentline;
          }
       }
       memset(uc_WkBuff2, 0, sizeof(uc_WkBuff2));
       memcpy(uc_WkBuff2, uc_WkBuff, sizeof(uc_WkBuff));
       memset(uc_WkBuff, 0, sizeof(uc_WkBuff));
    }
    return FLAG_SEARCH_NOT_MATCH;
}


/****************************************************************/
/**  ViewFile_ForwardFirstSearchString                          */
/****************************************************************/
ULONG ViewFile_ForwardFirstSearchString(USHORT us_flg_searchcase, 
            ULONG ul_currentline, ULONG ul_lastline, ULONG ul_totalline, 
            PSZ psz_searchstr)
{
    PUCHAR  puc_startptr, puc_endptr, puc_matchptr;

    if(!strlen(psz_searchstr)) return FLAG_SEARCH_NOT_MATCH;

    puc_startptr=puc_rownumber[ul_currentline];
    if((ULONG)(puc_rownumber[ul_totalline+1]-puc_rownumber[0]) 
               > strlen(psz_searchstr)) {
       puc_endptr = puc_rownumber[ul_totalline+1]-strlen(psz_searchstr);
    } else {
       return FLAG_SEARCH_NOT_MATCH;
    }

    puc_matchptr = ViewFile_ForwardSearchStringEngine(puc_startptr, 
                           puc_endptr, psz_searchstr, us_flg_searchcase);

    if(!puc_matchptr) return FLAG_SEARCH_NOT_MATCH;
    else return ViewFile_GetLineNum(puc_matchptr, ul_lastline, ul_totalline);
}



/****************************************************************/
/**  ViewFile_ForwardNextSearchString                           */
/****************************************************************/
ULONG ViewFile_ForwardNextSearchString(USHORT us_flg_searchcase, 
            ULONG ul_currentline, ULONG ul_lastline, ULONG ul_totalline, 
            PSZ psz_searchstr)
{
    PUCHAR  puc_startptr, puc_endptr, puc_matchptr;

    if(!strlen(psz_searchstr)) return FLAG_SEARCH_NOT_MATCH;

    puc_startptr=puc_rownumber[ul_currentline+1];
    if((ULONG)(puc_rownumber[ul_totalline+1]-puc_rownumber[0])
               > strlen(psz_searchstr)) {
       puc_endptr = puc_rownumber[ul_totalline+1]-strlen(psz_searchstr);
    } else {
       return FLAG_SEARCH_NOT_MATCH;
    }

    puc_matchptr = ViewFile_ForwardSearchStringEngine(puc_startptr, 
                           puc_endptr, psz_searchstr, us_flg_searchcase);

    if(!puc_matchptr) return FLAG_SEARCH_NOT_MATCH;
    else return ViewFile_GetLineNum(puc_matchptr, ul_lastline, ul_totalline);
}

    
/****************************************************************/
/**  ViewFile_ForwardSearchStringEngine                         */
/****************************************************************/
PUCHAR ViewFile_ForwardSearchStringEngine(PUCHAR puc_currentptr, 
                  PUCHAR puc_endptr, PSZ psz_searchstr, USHORT us_flg_searchcase)
{
    return jmemstr( puc_currentptr ,psz_searchstr ,puc_endptr-puc_currentptr ,us_flg_searchcase );
}


/****************************************************************/
/**  ViewFile_BackwardFirstSearchString                         */
/****************************************************************/
ULONG ViewFile_BackwardFirstSearchString(USHORT us_flg_searchcase, 
            ULONG ul_currentline, ULONG ul_lastline, ULONG ul_totalline, 
            PSZ psz_searchstr)
{
    PUCHAR  puc_startptr, puc_endptr, puc_matchptr;
    ULONG   ul_searchstartline;

    if(!strlen(psz_searchstr)) return FLAG_SEARCH_NOT_MATCH;

    if(ul_currentline+VIEWER_ROW_SIZE > ul_totalline+1) {
       ul_searchstartline=ul_totalline+1; 
    } else {
       ul_searchstartline=ul_currentline+VIEWER_ROW_SIZE;
    }
    if((ULONG)(puc_rownumber[ul_searchstartline]-puc_rownumber[0])
                                     < strlen(psz_searchstr)) {
       return FLAG_SEARCH_NOT_MATCH;
    }
    puc_startptr=puc_rownumber[ul_searchstartline]
                       -strlen(psz_searchstr);

    puc_endptr=puc_rownumber[0];

    puc_matchptr = ViewFile_BackwardSearchStringEngine(puc_startptr, 
                              puc_endptr, psz_searchstr, us_flg_searchcase);

    if(!puc_matchptr) return FLAG_SEARCH_NOT_MATCH;
    else return ViewFile_GetLineNum(puc_matchptr, ul_lastline, ul_totalline);
}

/****************************************************************/
/**  ViewFile_BackwardNextSearchString                         */
/****************************************************************/
ULONG ViewFile_BackwardNextSearchString(USHORT us_flg_searchcase, 
            ULONG ul_currentline, ULONG ul_lastline, ULONG ul_totalline, 
            PSZ psz_searchstr)
{
    PUCHAR  puc_startptr, puc_endptr, puc_matchptr;

    if(!strlen(psz_searchstr)) return FLAG_SEARCH_NOT_MATCH;

    if((ULONG)(puc_rownumber[ul_currentline]-puc_rownumber[0])
                                     < strlen(psz_searchstr)) {
       return FLAG_SEARCH_NOT_MATCH;
    }
    puc_startptr=puc_rownumber[ul_currentline]-strlen(psz_searchstr);
    puc_endptr=puc_rownumber[0];

    puc_matchptr = ViewFile_BackwardSearchStringEngine(puc_startptr, 
                             puc_endptr, psz_searchstr, us_flg_searchcase);

    if(!puc_matchptr) return FLAG_SEARCH_NOT_MATCH;
    else return ViewFile_GetLineNum(puc_matchptr, ul_lastline, ul_totalline);
}

/****************************************************************/
/**  ViewFile_BackwardSearchStringEngine                        */
/****************************************************************/
PUCHAR ViewFile_BackwardSearchStringEngine(PUCHAR puc_currentptr, 
                       PUCHAR puc_endptr, PSZ psz_searchstr, USHORT us_flg_searchcase)
{
    PUCHAR rc = 0;
    while(1){
       puc_endptr = jmemstr( puc_endptr ,psz_searchstr ,puc_currentptr-puc_endptr ,us_flg_searchcase );
       if(!puc_endptr) break;
       rc = puc_endptr++;
    }
    return rc;
}


/****************************************************************/
/**  ViewFile_SearchStringEngine                                */
/****************************************************************/
INT ViewFile_SearchStringEngine(PUCHAR puc_currentptr, PSZ psz_searchstr, 
                                USHORT us_flg_searchcase)
{
   if(us_flg_searchcase) {
      return memcmp (puc_currentptr, psz_searchstr, strlen(psz_searchstr));
   } else {
      return memicmp(puc_currentptr, psz_searchstr, strlen(psz_searchstr));
   }
}

/****************************************************************/
/**  ViewFile_ForwardFirstSearchStringBin                       */
/****************************************************************/
ULONG ViewFile_ForwardFirstSearchStringBin(USHORT us_flg_searchcase, 
            ULONG ul_currentline, ULONG ul_lastline, ULONG ul_totalline, 
            PSZ psz_searchstr)
{
    PUCHAR  puc_startptr, puc_endptr, puc_matchptr;

    if(!strlen(psz_searchstr)) return FLAG_SEARCH_NOT_MATCH;

    puc_startptr = puc_rownumber[ul_currentline];
    puc_endptr = puc_rownumber[0]+ul_alreadyreadsize;

    puc_matchptr = jmemstr( puc_startptr ,psz_searchstr ,puc_endptr-puc_startptr ,us_flg_searchcase );

    return !puc_matchptr ? FLAG_SEARCH_NOT_MATCH : ViewFile_GetLineNum(puc_matchptr, ul_lastline, ul_totalline);
}


/****************************************************************/
/**  ViewFile_ForwardNextSearchStringBin                        */
/****************************************************************/
ULONG ViewFile_ForwardNextSearchStringBin(USHORT us_flg_searchcase, 
            ULONG ul_currentline, ULONG ul_lastline, ULONG ul_totalline, 
            PSZ psz_searchstr)
{
    PUCHAR  puc_startptr, puc_endptr, puc_matchptr;

    if(!strlen(psz_searchstr)) return FLAG_SEARCH_NOT_MATCH;

    puc_startptr=puc_rownumber[ul_currentline+1];
    puc_endptr = puc_rownumber[0]+ul_alreadyreadsize;

    puc_matchptr = jmemstr( puc_startptr ,psz_searchstr ,puc_endptr-puc_startptr ,us_flg_searchcase );

    return !puc_matchptr ?  FLAG_SEARCH_NOT_MATCH : ViewFile_GetLineNum(puc_matchptr, ul_lastline, ul_totalline);
}


/****************************************************************/
/**  ViewFile_BackwardFirstSearchStringBin                      */
/****************************************************************/
ULONG ViewFile_BackwardFirstSearchStringBin(USHORT us_flg_searchcase, 
            ULONG ul_currentline, ULONG ul_lastline, ULONG ul_totalline, 
            PSZ psz_searchstr)
{
    PUCHAR  puc_startptr, puc_endptr, puc_matchptr = 0;

    if(!strlen(psz_searchstr)) return FLAG_SEARCH_NOT_MATCH;

    puc_startptr = puc_rownumber[0];
    if(ul_currentline+VIEWER_ROW_SIZE > ul_totalline+1) {
       puc_endptr = puc_rownumber[0]+ul_alreadyreadsize;
    } else {
       puc_endptr = puc_rownumber[ul_currentline+VIEWER_ROW_SIZE];
    }

    while(1){
       PUCHAR mp = jmemstr( puc_startptr ,psz_searchstr ,puc_endptr-puc_startptr ,us_flg_searchcase );
       if(!mp) break;
       puc_matchptr = mp;
       puc_startptr = mp + 1;
    }

    return !puc_matchptr ? FLAG_SEARCH_NOT_MATCH : ViewFile_GetLineNum(puc_matchptr, ul_lastline, ul_totalline);
}


/****************************************************************/
/**  ViewFile_BackwardNextSearchStringBin                       */
/****************************************************************/
ULONG ViewFile_BackwardNextSearchStringBin(USHORT us_flg_searchcase, 
            ULONG ul_currentline, ULONG ul_lastline, ULONG ul_totalline, 
            PSZ psz_searchstr)
{
    PUCHAR  puc_startptr, puc_endptr, puc_matchptr = 0;

    if(!strlen(psz_searchstr)) return FLAG_SEARCH_NOT_MATCH;

    puc_startptr = puc_rownumber[0];
    puc_endptr = puc_rownumber[ul_currentline]+strlen(psz_searchstr)-1;
    if(puc_endptr>puc_rownumber[0]+ul_alreadyreadsize) puc_endptr = puc_rownumber[0]+ul_alreadyreadsize;

    while(1){
       PUCHAR mp = jmemstr( puc_startptr ,psz_searchstr ,puc_endptr-puc_startptr ,us_flg_searchcase );
       if(!mp) break;
       puc_matchptr = mp;
       puc_startptr = mp + 1;
    }

    return !puc_matchptr ? FLAG_SEARCH_NOT_MATCH : ViewFile_GetLineNum(puc_matchptr, ul_lastline, ul_totalline);
}

/****************************************************************/
/**  ViewFile_GetLineNum                                        */
/****************************************************************/
ULONG ViewFile_GetLineNum(PUCHAR puc_currentptr, ULONG ul_lastline,
                          ULONG ul_totalline)
{
   ULONG ul_linenum;
   
   for(ul_linenum=0; ul_linenum<ul_totalline+2; ul_linenum++) {
      if(puc_rownumber[ul_linenum] > puc_currentptr) break;
   }

   return --ul_linenum;
   
}

/****************************************************************/
/**  ViewFile_GetLogicalLineNum                                 */
/****************************************************************/
ULONG ViewFile_GetLogicalLineNum(ULONG ul_currentline)
{
   ULONG ul_logical_linenum=0, ul_linenum;
   
   for(ul_linenum=0; ul_linenum<ul_currentline+1; ul_linenum++) {
      if( *(puc_rownumber[ul_linenum+1]-1) == CR 
       || *(puc_rownumber[ul_linenum+1]-1) == LF) 
         ul_logical_linenum++;
   }

   return ul_logical_linenum;
   
}


/****************************************************************/
/**  ViewFile_TerminateTread                                   **/
/****************************************************************/
 VOID ViewFile_TerminateTread(TID tid_Thread, PVOID pv_filebuff, 
                              HEV hev_readsize, HFILE hf_FileHandle)
{
   if(tid_Thread) {
      if(DosKillThread(tid_Thread) != ERROR_INVALID_THREADID) {
         DosSleep(100);  /* スレッド終了までの時間をかせぐ */
         DosWaitThread(&tid_Thread, DCWW_WAIT); 
      }
   }
   if(hf_FileHandle) DosClose(hf_FileHandle);
   if(pv_filebuff)   DosFreeMem(pv_filebuff); 
   if(hev_readsize)  DosCloseEventSem(hev_readsize);
}

/*********************************************************************
**********************************************************************
*********                                                    *********
*********   ファイル読み込みのための別スレッド               *********
*********                                                    *********
**********************************************************************
**********************************************************************/
/*******************************************************************/
/* void _System ThreadLoadFile(ULONG)                              */
/*******************************************************************/
void _System ThreadLoadFile(ULONG ul_filehandle_ptr)
{
   ULONG   ul_Actual=0;
   PUCHAR  puc_buffoffset;

   /*---------------------------------------------*/
   /* バッファの確保                              */
   /*---------------------------------------------*/
   apr_g_thread = DosAllocMem(&pv_filebuff, ul_g_restfilesize+BUFFBLOCKSIZE, 
                              PAG_COMMIT|PAG_READ|PAG_WRITE); 
   if (apr_g_thread) DosExit(EXIT_THREAD, 0L);

   /*---------------------------------------------*/
   /* ファイルの内容をBUFFBLOCKSIZEごとに読み込む */
   /*---------------------------------------------*/
   puc_buffoffset=pv_filebuff;
   do {
      DosRead(*((PHFILE)ul_filehandle_ptr), puc_buffoffset, BUFFBLOCKSIZE, &ul_Actual);
      puc_buffoffset += ul_Actual;
      apr_g_thread=DosPostEventSem(hev_g_readsize);
      if (apr_g_thread!=NO_ERROR && apr_g_thread!=ERROR_ALREADY_POSTED) break;
   }while(ul_Actual==BUFFBLOCKSIZE);

   DosExit(EXIT_THREAD, 0L);
}



