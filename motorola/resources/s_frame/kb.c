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

A POSIX operációs rendszerek terminálja sor orientált. Ez azt jelenti,
hogy a begépelt karaktereket csak akkor kapjuk meg, ha enterrel termináljuk
a bevitelt. Ennek megkerülésére, ez a modul az egyedi billentyű leütéseket
is el tudja kapni.

Windows alatt is szükség van keypressed függvényre, ezért a global.h alatt beállított
platformnak megfelelő billentyűkezelés fordul le.

*/

#include "global.h"
#include "kb.h"

#ifdef WIN32     // windows

/*!
    a megadott billentyűzetet megvizsgálja és ha van leütött karakter, akkor azzal
    tér vissza.
    @return 0:nincs karakter, !0: a karakter ascii kódja
*/
char get_a_key(){
    return kbhit() ? getch() : 0;
}

#else //posix

/*!
    a megadott billentyűzetet megvizsgálja és ha van leütött karakter, akkor azzal
    tér vissza.
    @return 0:nincs karakter, !0: a karakter ascii kódja
*/
char get_a_key() {
    char ch = getch();
    return ch == -1 ? '\0' : ch;
}
#endif
