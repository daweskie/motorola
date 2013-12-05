#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

/*
   SerialFrame
   Soros kommunkáció bemutató szoftver
   Copyright (C) 2009. Zidarics Zoltán (zamek@vili.pmmf.hu)

   Ez egy szabad szoftver; terjeszthető illetve módosítható a GNU
   Általános Közreadási Feltételek dokumentumában leírtak szerint -- 2.
   vagy későbbi verzió --, melyet a Szabad Szoftver Alapítvány ad ki.

   Ez a program abban a reményben kerül közreadásra, hogy hasznos lesz,
   de minden egyéb GARANCIA NÉLKÜL, az eladhatóságra vagy valamely célra
   való alkalmazhatóságra való származtatott garanciát is beleértve.
   További részletekért lásd a GNU Általános Közreadási Feltételek
   dokumentumát.

   A programmal együtt kellett, hogy érkezzen egy példány a GNU
   Általános Közreadási Feltételek dokumentumából is. Ha mégsem akkor
   ezt a Szabad Szoftver Alapítványnak küldött levélben jelezni kell.

   A szabad szoftver alapítvány címe:
   Free Software Foundation, Inc.,
   59 Temple Place, Suite 330,
   Boston, MA  02111-1307  USA.
*/

/*! \file kb.c

\author Zamek
\version $Id: kb.c,v 1.5 2009-05-08 06:16:09 zamek Exp $

Display kezelo modul. Posix op.rendszerek esetén a curses modul képes x,y koordináták szerint pozicionálni.
Windows alatt is lehet wincon modullal. Az egységes felület okán közös move() függvénnyel valósítjuk meg
a pozicionálást.

*/


#ifdef WIN32

/**
    Használat után képernyő visszaállítása. Windows alatt nem lényeges, mivel a futás után az ablakot bezárja
*/
#define close_display()

/**
    Képernyő inicializálása használat előtt. Windows alatt nem lényeges.
*/
#define display_init()

/**
    Kurzor pozicionálása sor,oszlop koordinátákra.
*/
void move(int row, int col);

/**
    státusz sor kiírása, fix 1,1 koordinátákra. printf szerint lehet paraméterezni.
*/
#define print(msg, x...) \
    do { \
        move(1,1); \
        printf(msg,##x); \
    while(0)

#else

#include <curses.h>

/**
    Képernyő inicializálása használat előtt.
*/
void display_init();

/**
    Használat után képernyő visszaállítása.
*/
void close_display();

/**
    Kurzor pozicionálása sor,oszlop koordinátákra.
*/
#define print(msg,x...) \
do { \
    move(1,1); \
    printw(msg,##x); \
    refresh(); \
} while(0)

#endif

#endif // DISPLAY_H_INCLUDED
