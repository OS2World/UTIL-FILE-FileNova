 /*********************************************************************/
 /*  Get Keyboard-Key-Infomation                                      */
 /*********************************************************************/
 #define  INCL_KBD
 #include <os2.h>

 #include "filenova.h"
 #include "getkeyif.h"

VOID Convert_WordStarLikeKey(PKBDKEYINFO pkki_keyinfo, USHORT us_currentmode)
{
   if(pkki_keyinfo->chChar == ARROW) {
      if(pkki_keyinfo->chScan != 0x00) pkki_keyinfo->chChar = PFK;
   }
         
   switch(pkki_keyinfo->chChar) {
      case CTRL_C:
         pkki_keyinfo->chChar = PFK;
         pkki_keyinfo->chScan = PAGE_DOWN;
         break;
      case CTRL_D:
         pkki_keyinfo->chChar = PFK;
         pkki_keyinfo->chScan = ARROW_RIGHT;
         break;
      case CTRL_E:
         pkki_keyinfo->chChar = PFK;
         pkki_keyinfo->chScan = ARROW_UP;
         break;
      case CTRL_R:
         pkki_keyinfo->chChar = PFK;
         pkki_keyinfo->chScan = PAGE_UP;
         break;
      case CTRL_S:
         pkki_keyinfo->chChar = PFK;
         pkki_keyinfo->chScan = ARROW_LEFT;
         break;
      case CTRL_X:
         pkki_keyinfo->chChar = PFK;
         pkki_keyinfo->chScan = ARROW_DOWN;
         break;
   }

   if(us_currentmode != FLAG_MODE_INPUTWIN) return;

   switch(pkki_keyinfo->chChar) {
      case CTRL_A:
         pkki_keyinfo->chChar = PFK;
         pkki_keyinfo->chScan = HOME;
         break;
      case CTRL_F:
         pkki_keyinfo->chChar = PFK;
         pkki_keyinfo->chScan = END;
         break;
      case CTRL_G:
         pkki_keyinfo->chChar = PFK;
         pkki_keyinfo->chScan = DELETE;
         break;
      case CTRL_V:
         pkki_keyinfo->chChar = PFK;
         pkki_keyinfo->chScan = INSERT;
         break;
   }

}


