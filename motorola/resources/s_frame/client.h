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

/*!

\author Zamek
\version $Id: client.h,v 1.4 2009-05-08 06:16:09 zamek Exp $

*/
#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

/*! Kliens módban indították el a programot, várja a parancsokat és válaszol
valamint a billentyűparancsok alapján állítja a nyomás, hőmérséklet és hiba flag-et.
    @param clientAddr az eszköz címe, csak az erre a címre érkezett parancsokra válaszol
    @param fd a soros port kezelője
*/
void clientProcess(char clientAddr, int fd);

#endif // CLIENT_H_INCLUDED
