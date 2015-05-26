#
# Makefile for IBM VisualAge C++ J3.6
# ç≈ìKâª(/O+)ÇÇ©ÇØÇƒÇÕÇ¢ÇØÇ»Ç¢
#
WARNING = /W3 /Weff /Wext /Wpro /Wpor /Wrea /Wret /Wund /Wuse
CC = icc
CFLAGS = /C+ 
LD = ilink

.c.obj:
	$(CC) $(CFLAGS) $(WARNING) $<

filenova.exe: filenova.obj novaview.obj jstring.obj charcode.obj getkeyif.obj ea.obj lfiles.obj unicode.obj
	$(LD) filenova.obj novaview.obj jstring.obj charcode.obj getkeyif.obj ea.obj lfiles.obj unicode.obj

filenova.obj: filenova.h jstring.h getkeyif.h ea.h lfsatype.h lfiles.h unicode.h Makefile 
novaview.obj: filenova.h jstring.h charcode.h getkeyif.h lfiles.h lfsatype.h unicode.h Makefile 
jstring.obj:  jstring.h  Makefile 
charcode.obj: charcode.h
getkeyif.obj: getkeyif.h
ea.obj:       ea.h
lfiles.obj:   lfiles.h lfsatype.h
unicode.obj:  unicode.h Makefile

