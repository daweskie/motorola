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
\version $Id: macros.h,v 1.3 2009-05-08 06:16:09 zamek Exp $
*/
#ifndef MACROS_H_INCLUDED
#define MACROS_H_INCLUDED

#define MALLOC(ptr,size) \
    do { \
       ptr=malloc(size); \
       if (!ptr) \
           abort(); \
    } while(0)

#define FREE(ptr) \
    do { \
      free(ptr); \
      ptr=NULL; \
    } while(0)

#endif // MACROS_H_INCLUDED
