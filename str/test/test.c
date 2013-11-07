/*
 *
 * Copyright (C) 2010 Institute for Information Technology and Electrical Engineering
 * of Pollack Mihály Faculty of Engineering University of Pécs
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
FILE NAME: test.c
AUTHOR: students of Embedded Systems faculty

Tests for  strutil
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <strutil.h>

void testStrStartWith() {
    char empty[] ="",
         str[]="firstfirst",
         goodPattern[]="fi",
         goodPattern1[]="rst",
         badPattern[]="__cannotfind__";

    printf("testStrStartWith...");
    assert(strStartWith(NULL, NULL)==-1);
    assert(strStartWith(NULL, empty) == -1);
    assert(strStartWith(empty, NULL)==-1);
    assert(strStartWith(empty, empty)==-1);
    assert(strStartWith(str, goodPattern)==0);
    assert(strStartWith(str, goodPattern1)==2);
    assert(strStartWith(str, badPattern)==-1);
    printf("passed\n");
}

void testStrEndWith() {
    char empty[] ="",
         str[]="firstfirst",
         goodPattern[]="st",
         goodPattern1[]="ir",
         badPattern[]="__cannotfind__",
         badPattern1[]="dir";

    printf("testStrEndWith...");
    assert(strEndWith(NULL, NULL)==-1);
    assert(strEndWith(NULL, empty) == -1);
    assert(strEndWith(empty, NULL)==-1);
    assert(strEndWith(empty, empty)==-1);
    assert(strEndWith(str, goodPattern)==8);
    assert(strEndWith(str, goodPattern1)==6);
    assert(strEndWith(str, badPattern)==-1);
    assert(strEndWith(str, badPattern1)==-1);
    printf("passed\n");
}

void testStrIsEmpty() {
    char empty[] ="",
         oneSpace[]=" ",
         beginSpace[]=" str",
         onlyTab[]="\t\t\t",
         beginTab[]="\tstr",
         onlyNumeric[]="01234";
    printf("testStrIsEmpty started...");
    assert(strIsEmpty(NULL)==1);
    assert(strIsEmpty(empty)==1);
    assert(strIsEmpty(oneSpace)==0);
    assert(strIsEmpty(beginSpace)==0);
    assert(strIsEmpty(onlyTab)==0);
    assert(strIsEmpty(beginTab)==0);
    assert(strIsEmpty(onlyNumeric)==0);
    printf("passed\n");
}

void testStrIsBlank() {
    char empty[] ="",
         oneSpace[]=" ",
         beginSpace[]=" str",
         onlyTab[]="\t\t\t",
         beginTab[]="\tstr",
         onlyNumeric[]="01234";
    printf("testStrIsBlank started...");
    assert(strIsBlank(NULL)==1);
    assert(strIsBlank(empty)==1);
    assert(strIsBlank(oneSpace)==1);
    assert(strIsBlank(beginSpace)==0);
    assert(strIsBlank(onlyTab)==1);
    assert(strIsBlank(beginTab)==0);
    assert(strIsBlank(onlyNumeric)==0);
    printf("passed\n");
}

void testStrIndexOfChar() {
    char empty[] ="",
         oneSpace[]=" ",
         beginSpace[]=" asd";

    printf("testStrIndexOfChar started...");
    assert(strIndexOfChar(NULL, 'a')==-1);
    assert(strIndexOfChar(empty, 'a')==-1);
    assert(strIndexOfChar(oneSpace, 'a')==-1);
    assert(strIndexOfChar(beginSpace, 'a')==1);
    printf("passed\n");
}


void testStrIsAlpha()
{
    char empty[] ="",
         only_alpha[] ="abcdef",
         only_numeric[] ="12345",
         alpha_numeric[]="asd234f1",
         only_one_space[]=" ",
         only_tab[] ="\t";
    printf("testStrIsAlpha started...");
    assert(strIsAlpha(NULL)==0);
    assert(strIsAlpha(empty)==0);
    assert(strIsAlpha(only_alpha)==1);
    assert(strIsAlpha(only_numeric)==0);
    assert(strIsAlpha(alpha_numeric)==0);
    assert(strIsAlpha(only_one_space)==0);
    assert(strIsAlpha(only_tab)==0);
    printf("passed\n");
}

void testStrIsNumeric()
{
    char empty[]="",
         oneSpace[]=" ",
         onlyLetters[]="asdf",
         onlyNumeric[]="123456789",
         mixed[]="123asd";
    printf("testStrIsNumeric started...");
    strIsNumeric(NULL);
    assert(strIsNumeric(empty)==0);
    assert(strIsNumeric(oneSpace)==0);
    assert(strIsNumeric(onlyLetters)==0);
    assert(strIsNumeric(onlyNumeric)==1);
    assert(strIsNumeric(mixed)==0);
    printf("passed\n");
}

void testStrReplaceChar() {
    char empty[]="",
         oneSpace[]=" ",
         onlyLetters[]="asdfa";
    printf("testStrReplaceChar started...");
    strReplaceChar(NULL,'a','b');
    strReplaceChar(empty,'a','b');
    strReplaceChar(oneSpace,'a','b');
    strReplaceChar(onlyLetters,'a','b');
    assert(strcmp(onlyLetters, "bsdfa")==0);
    printf("passed\n");
}

void testStrToLowerCase() {
    char empty[]="",
         noLetter[]=" !@#$%(_",
         lowLetters[]="asdfa",
         capitalLetters[]="ASDFA",
         mixedLetters[]="aSdFa";
    printf("testStrToLowerCase started...");
    strToLowerCase(NULL);
    strToLowerCase(empty);
    strToLowerCase(noLetter);
    assert(strcmp(noLetter, " !@#$%(_")==0);
    strToLowerCase(lowLetters);
    assert(strcmp(lowLetters, "asdfa")==0);
    strToLowerCase(capitalLetters);
    assert(strcmp(capitalLetters, "asdfa")==0);
    strToLowerCase(mixedLetters);
    assert(strcmp(mixedLetters, "asdfa")==0);
    printf("passed\n");
}

void testStrToUpperCase() {
    char empty[]="",
         noLetter[]=" !@#$%(_",
         lowLetters[]="asdfa",
         capitalLetters[]="ASDFA",
         mixedLetters[]="aSdFa";
    printf("testStrToUpperCase started...");
    strToUpperCase(NULL);
    strToUpperCase(empty);
    strToUpperCase(noLetter);
    assert(strcmp(noLetter, " !@#$%(_")==0);
    strToUpperCase(lowLetters);
    assert(strcmp(lowLetters, "ASDFA")==0);
    strToUpperCase(capitalLetters);
    assert(strcmp(capitalLetters, "ASDFA")==0);
    strToUpperCase(mixedLetters);
    assert(strcmp(mixedLetters, "ASDFA")==0);
    printf("passed\n");
}

void testStrTrim()
{
    char empty[]="",
         onlyOneSpace[]=" ",
         multipleSpace[]="  ",
         beginSpace[]=" asdf",
         endingSpace[]="asdf ",
         middleOfSpace[]="as df",
         onlyTab[] ="\t",
         multipleTab[]="\t\t\t",
         beginTab[]="\tasdf",
         endingTab[]="asdf\t",
         middleOfTab[]="as\tdf",
         alphaNumeric[]="asd234f1",
         onlyNumeric[]="432432",
         onlyAlpha[]="asdgjh";

    printf("testStrTrim started...");
    strTrim(NULL);
    strTrim(empty);

    assert(strcmp(empty,"")==0);
    strTrim(onlyOneSpace);
    assert(strcmp(onlyOneSpace,"")==0);
    strTrim(multipleSpace);
    assert(strcmp(multipleSpace,"")==0);
    strTrim(beginSpace);
    assert(strcmp(beginSpace,"asdf")==0);
    strTrim(endingSpace);
    assert(strcmp(endingSpace,"asdf")==0);
    strTrim(middleOfSpace);
    assert(strcmp(middleOfSpace,"as df")==0);
    strTrim(onlyTab);
    assert(strcmp(onlyTab,"")==0);
    strTrim(multipleTab);
    assert(strcmp(multipleTab,"")==0);
    strTrim(beginTab);
    assert(strcmp(beginTab,"asdf")==0);
    strTrim(endingTab);
    assert(strcmp(endingTab,"asdf")==0);
    strTrim(middleOfTab);
    assert(strcmp(middleOfTab,"as\tdf")==0);
    strTrim(alphaNumeric);
    assert(strcmp(alphaNumeric,"asd234f1")==0);
    strTrim(onlyNumeric);
    assert(strcmp(onlyNumeric,"432432")==0);
    strTrim(onlyAlpha);
    assert(strcmp(onlyAlpha,"asdgjh")==0);
    printf("passed\n");
}

void testStrConst() {
    printf("testStrConst started...");
    assert(strcmp(strConst('l',3),"lll")==0);
    assert(strcmp(strConst('L',3),"LLL")==0);
    assert(strcmp(strConst('7',8),"77777777")==0);
    assert(strcmp(strConst('x',0),"")==0);
    assert(strcmp(strConst('\t',2),"\t\t")==0);
    assert(strcmp(strConst(' ',5),"     ")==0);
    printf("passed\n");
}

void testStrCenter() {
    printf("testStrCenter started...");
    assert(strcmp(strCenter("a",10),		  "    a     ")==0);
    assert(strcmp(strCenter("aa",10),		  "    aa    ")==0);
    assert(strcmp(strCenter("aaa",10),		  "   aaa    ")==0);
    assert(strcmp(strCenter("aaaa",10),		  "   aaaa   ")==0);
    assert(strcmp(strCenter("aa.aa",10),	  "  aa.aa   ")==0);
    assert(strcmp(strCenter("aa..aa",10),	  "  aa..aa  ")==0);
    assert(strcmp(strCenter("aaa.aaa",10),	  " aaa.aaa  ")==0);
    assert(strcmp(strCenter("aaa..aaa",10),	  " aaa..aaa ")==0);
    assert(strcmp(strCenter("aaa.a.aaa",10),  "aaa.a.aaa ")==0);
    assert(strcmp(strCenter("aaa.aa.aaa",10), "aaa.aa.aaa")==0);
    assert(strcmp(strCenter("aaa.aaa.aaa",10),"aaa.aaa.aaa")==0);
    printf("passed\n");
}

void testStrLeft() {
 char empty[]="",
     onlyOneSpace[]=" ",
     beginSpace[]=" asdf",
     onlyTab[] ="\t";

    printf("testStrLeft started...");
    strLeft(NULL,0);
    assert(strLeft(empty,-1)==NULL);
    assert(strLeft(empty,1)==NULL);
    assert(strLeft(NULL,12)==NULL);
    assert(strLeft("klewnfklewfn",-12)==NULL);
    assert(strcmp(strLeft(onlyTab,2),"\t ")==0);
    assert(strcmp(strLeft("    Balra hozas",20),"Balra hozas         ")==0);
    assert(strcmp(strLeft(beginSpace,4),"asdf")==0);
    assert(strcmp(strLeft("   egy ketto harom",2),"eg")==0);
    assert(strcmp(strLeft(onlyOneSpace,10),"          ")==0);
    assert(strcmp(strLeft("erfionheoiwfn12312",14),"erfionheoiwfn1")==0);
    assert(strcmp(strLeft("   123Proba345    ",17),"123Proba345      ")==0);
    assert(strcmp(strLeft("\t \n \0",8),"\t \n     ")==0);
    printf("passed\n");
}

void testStrRight() {
 char empty[]="",
     onlyOneSpace[]=" ",
     beginSpace[]=" asdf",
     onlyTab[] ="\t";

    printf("testStrRight started...");
    strRight(NULL,0);
    assert(strRight(empty,-1)==NULL);
    assert(strRight(empty,1)==NULL);
    assert(strRight(NULL,12)==NULL);
    assert(strRight("klewnfklewfn",-12)==NULL);
    assert(strcmp(strRight(onlyTab,2)," \t")==0);
    assert(strcmp(strRight("Jobbra hozas",20),"        Jobbra hozas")==0);
    assert(strcmp(strRight(beginSpace,4)," asd")==0);
    assert(strcmp(strRight("egy ketto harom",2),"eg")==0);
    assert(strcmp(strRight(onlyOneSpace,10),"          ")==0);
    assert(strcmp(strRight("erfionheoiwfn12312",14),"erfionheoiwfn1")==0);
    assert(strcmp(strRight("   123Proba345    ",17),"   123Proba345   ")==0);
    assert(strcmp(strRight("\t \n \0",8),"    \t \n ")==0);
    printf("passed\n");
}

void testStrChomp() {
 char empty[]="",
      onlyOneSpace[]=" \r\r\n",
     beginSpace[]=" asdf\r\n",
     onlyTab[] ="\t\n";

     printf("testStrChomp started...");
     strChomp(NULL);
     strChomp(empty);
     assert(strcmp(empty,"")==0);
     strChomp(beginSpace);
     assert(strcmp(beginSpace," asdf")==0);
     strChomp(onlyTab);
     assert(strcmp(onlyTab,"\t")==0);
     strChomp(onlyOneSpace);
     assert(strcmp(onlyOneSpace," ")==0);
     printf("passed\n");
}

void testStrReplaceStr() {
 char empty[]="",
     onlyOneSpace[]=" ",
     multipleSpace[]="  ",
     beginSpace[]=" asdf",
     endingSpace[]="asdf ",
     middleOfSpace[]="as df",
     onlyTab[] ="\t",
     multipleTab[]="\t\t\t",
     beginTab[]="\tasdf",
     endingTab[]="asdf\t",
     middleOfTab[]="as\tdf",
     alphaNumeric[]="asd234f1",
     onlyNumeric[]="432432",
     onlyAlpha[]="asdgjh",
     loop[]="asdfg423ASDFG423asdfg423ASDFG423asdfg",
     upperCase[]="VALAMI",
     mixedCase1[]="VALAMI es valami",
     mixedCase2[]="UPPER_lower 1235 \'@#$%^&*()";

    printf("testStrReplaceStr started...");
    assert(strReplaceStr(NULL,NULL,NULL)==0);
    assert(strReplaceStr(empty,empty,empty)==0);
    assert(strReplaceStr(NULL,NULL,mixedCase2)==0);
    assert(strReplaceStr(empty,empty,mixedCase2)==0);
    assert(strReplaceStr(NULL,mixedCase2,NULL)==0);
    assert(strReplaceStr(empty,mixedCase2,empty)==0);
    assert(strReplaceStr(NULL,mixedCase2,mixedCase2)==0);
    assert(strReplaceStr(empty,mixedCase2,mixedCase2)==0);
    assert(strReplaceStr(mixedCase2,NULL,NULL)==0);
    assert(strReplaceStr(mixedCase2,empty,empty)==0);
    assert(strReplaceStr(mixedCase2,NULL,mixedCase2)==0);
    assert(strReplaceStr(mixedCase2,empty,mixedCase2)==0);
    assert(strReplaceStr(mixedCase2,mixedCase2,NULL)==0);

    assert(strReplaceStr(mixedCase2,onlyNumeric,NULL)==0);
    assert(strReplaceStr(mixedCase2,onlyAlpha,NULL)==0);
    assert(strReplaceStr(mixedCase2,onlyTab,NULL)==0);
    assert(strReplaceStr(mixedCase2,beginTab,NULL)==0);
    assert(strReplaceStr(mixedCase2,middleOfTab,NULL)==0);
    assert(strReplaceStr(mixedCase2,alphaNumeric,NULL)==0);
    assert(strReplaceStr(mixedCase2,upperCase,NULL)==0);

    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,empty),empty)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,loop),loop)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(onlyOneSpace,onlyOneSpace,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,empty),empty)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,loop),loop)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(multipleSpace,multipleSpace,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(beginSpace,beginSpace,empty),empty)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,loop),loop)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(beginSpace,beginSpace,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(endingSpace,endingSpace,empty),empty)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,loop),loop)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(endingSpace,endingSpace,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,empty),empty)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,loop),loop)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(middleOfSpace,middleOfSpace,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(onlyTab,onlyTab,empty),empty)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,loop),loop)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(onlyTab,onlyTab,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(multipleTab,multipleTab,empty),empty)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,loop),loop)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(multipleTab,multipleTab,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(beginTab,beginTab,empty),empty)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,loop),loop)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(beginTab,beginTab,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(endingTab,endingTab,empty),empty)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,loop),loop)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(endingTab,endingTab,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,empty),empty)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,loop),loop)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(middleOfTab,middleOfTab,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,empty),empty)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,loop),loop)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,empty),empty)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,loop),loop)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(alphaNumeric,alphaNumeric,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,empty),empty)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,loop),loop)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(onlyNumeric,onlyNumeric,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,empty),empty)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,loop),loop)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(onlyAlpha,onlyAlpha,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(upperCase,upperCase,empty),empty)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,loop),loop)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(upperCase,upperCase,empty),empty)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,loop),loop)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(upperCase,upperCase,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(loop,loop,empty),empty)==0);
    assert(strcmp(strReplaceStr(loop,loop,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(loop,loop,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(loop,loop,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(loop,loop,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(loop,loop,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(loop,loop,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(loop,loop,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(loop,loop,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(loop,loop,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(loop,loop,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(loop,loop,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(loop,loop,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(loop,loop,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(loop,loop,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(loop,loop,loop),loop)==0);
    assert(strcmp(strReplaceStr(loop,loop,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(loop,loop,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,empty),empty)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,loop),loop)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(mixedCase1,mixedCase1,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,empty),empty)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,onlyOneSpace),onlyOneSpace)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,multipleSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,beginSpace),beginSpace)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,endingSpace),endingSpace)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,middleOfSpace),middleOfSpace)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,onlyTab),onlyTab)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,multipleTab),multipleTab)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,beginTab),beginTab)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,endingTab),endingTab)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,middleOfTab),middleOfTab)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,alphaNumeric),alphaNumeric)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,onlyNumeric),onlyNumeric)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,onlyAlpha),onlyAlpha)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,upperCase),upperCase)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,loop),loop)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,mixedCase1),mixedCase1)==0);
    assert(strcmp(strReplaceStr(mixedCase2,mixedCase2,mixedCase2),mixedCase2)==0);

    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,onlyOneSpace),multipleSpace)==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,multipleSpace),"    ")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,beginSpace)," asdf asdf")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,endingSpace),"asdf asdf ")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,middleOfSpace),"as dfas df")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,onlyTab),"\t\t")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,multipleTab),"\t\t\t\t\t\t")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,beginTab),"\tasdf\tasdf")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,endingTab),"asdf\tasdf\t")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,middleOfTab),"as\tdfas\tdf")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,alphaNumeric),"asd234f1asd234f1")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,onlyNumeric),"432432432432")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,onlyAlpha),"asdgjhasdgjh")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,upperCase),"VALAMIVALAMI")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,loop),"asdfg423ASDFG423asdfg423ASDFG423asdfgasdfg423ASDFG423asdfg423ASDFG423asdfg")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,mixedCase1),"VALAMI es valamiVALAMI es valami")==0);
    assert(strcmp(strReplaceStr(multipleSpace,onlyOneSpace,mixedCase2),"UPPER_lower 1235 \'@#$%^&*()UPPER_lower 1235 \'@#$%^&*()")==0);

    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,onlyOneSpace),"UPPER_lower 1235 \'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,multipleSpace),"UPPER_lower  1235  \'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,beginSpace),"UPPER_lower asdf1235 asdf\'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,endingSpace),"UPPER_lowerasdf 1235asdf \'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,middleOfSpace),"UPPER_loweras df1235as df\'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,onlyTab),"UPPER_lower\t1235\t\'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,multipleTab),"UPPER_lower\t\t\t1235\t\t\t\'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,beginTab),"UPPER_lower\tasdf1235\tasdf\'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,endingTab),"UPPER_lowerasdf\t1235asdf\t\'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,middleOfTab),"UPPER_loweras\tdf1235as\tdf\'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,alphaNumeric),"UPPER_lowerasd234f11235asd234f1\'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,onlyNumeric),"UPPER_lower4324321235432432\'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,onlyAlpha),"UPPER_lowerasdgjh1235asdgjh\'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,upperCase),"UPPER_lowerVALAMI1235VALAMI\'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,loop),"UPPER_lowerasdfg423ASDFG423asdfg423ASDFG423asdfg1235asdfg423ASDFG423asdfg423ASDFG423asdfg\'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,mixedCase1),"UPPER_lowerVALAMI es valami1235VALAMI es valami\'@#$%^&*()")==0);
    assert(strcmp(strReplaceStr(mixedCase2,onlyOneSpace,mixedCase2),"UPPER_lowerUPPER_lower 1235 \'@#$%^&*()1235UPPER_lower 1235 \'@#$%^&*()\'@#$%^&*()")==0);

    assert(strcmp(strReplaceStr("Ez az #!!# szoveg","#!!#","eredeti"),"Ez az eredeti szoveg")==0);
    assert(strcmp(strReplaceStr("Ez az #!\t\n!# szoveg","#!\t\n!#","eredeti"),"Ez az eredeti szoveg")==0);
    assert(strcmp(strReplaceStr("Ez az #!PATTERN!# szoveg","#!PATTERN!#","eredeti"),"Ez az eredeti szoveg")==0);
    printf("passed\n");
}


void testStrRemoveStr() {
 char empty[]="",
      onlyOneSpace[]=" ",
     beginSpace[]=" asdf";

     printf("testStrRemoveStr started...");
     strRemoveStr(NULL,NULL);
     strRemoveStr(NULL,empty);
     strRemoveStr(empty,NULL);
     strRemoveStr(empty,empty);
     assert(strcmp(empty,"")==0);

     strRemoveStr(onlyOneSpace, "__NOTIN__");
     assert(strcmp(onlyOneSpace," ")==0);
     strRemoveStr(onlyOneSpace, " ");
     assert(strcmp(onlyOneSpace,"")==0);
     strRemoveStr(beginSpace,"asdf");
     assert(strcmp(beginSpace," ")==0);

     strRemoveStr(beginSpace,"asdfghijklmnop");
     assert(strcmp(beginSpace," ")==0);

     printf("passed\n");
}


void testStrReverse()
{
    char empty[]="",
         beginSpace[]=" asdf",
         endingSpace[]="asdf ",
         middleOfSpace[]="as df",
         beginTab[]="\tasdf",
         endingTab[]="asdf\t",
         middleOfTab[]="as\tdf",
         alphaNumeric[]="asd234f1",
         onlyNumeric[]="432432",
         onlyAlpha[]="asdgjh",
         loop[]="asdfg423ASDFG423asdfg423ASDFG423asdfg",
         upperCase[]="VALAMI",
         mixedCase1[]="VALAMI es valami";

    printf("testStrReverse started...");
    assert(strReverse(NULL)==NULL);
    assert(strReverse(empty)==NULL);
    assert(strcmp(strReverse(beginSpace), "fdsa ")==0);
    assert(strcmp(strReverse(endingSpace), " fdsa")==0);
    assert(strcmp(strReverse(middleOfSpace), "fd sa")==0);
    assert(strcmp(strReverse(beginTab), "fdsa\t")==0);
    assert(strcmp(strReverse(endingTab), "\tfdsa")==0);
    assert(strcmp(strReverse(middleOfTab), "fd\tsa")==0);
    assert(strcmp(strReverse(alphaNumeric), "1f432dsa")==0);
    assert(strcmp(strReverse(onlyNumeric), "234234")==0);
    assert(strcmp(strReverse(onlyAlpha), "hjgdsa")==0);
    assert(strcmp(strReverse(upperCase), "IMALAV")==0);
    assert(strcmp(strReverse(mixedCase1), "imalav se IMALAV")==0);
    assert(strcmp(strReverse(loop), "gfdsa324GFDSA324gfdsa324GFDSA324gfdsa")==0);
    printf("passed\n");
}

void testStrCapitalize() {
 char empty[]="",
     onlyOneSpace[]=" ",
     multipleSpace[]="  ",
     beginSpace[]=" asdf",
     endingSpace[]="asdf ",
     middleOfSpace[]="as df",
     onlyTab[]="\t",
     beginTab[]="\talatta",
     multipleTab[]="\t\t\t",
     middleOfTab[]="as\tdf",
     alphaNumeric[]="asd234f1",
     onlyNumeric[]="432432",
     onlyAlpha[]="asdgjh",
     upperCase[]="VALAMI",
     mixedCase1[]="VALAMI es valami",
     mixedCase2[]="UPPER_lower 1235 \'@#$%^&*()";

    printf("testStrCapitalize started...");
    strCapitalize(NULL);
    strCapitalize(empty);
    assert(strcmp(empty,"")==0);
    strCapitalize(onlyOneSpace);
    assert(strcmp(onlyOneSpace," ")==0);
    strCapitalize(multipleSpace);
    assert(strcmp(multipleSpace,"  ")==0);
    strCapitalize(endingSpace);
    assert(strcmp(endingSpace,"Asdf ")==0);
    strCapitalize(beginSpace);
    assert (strcmp(beginSpace," Asdf")==0);
    strCapitalize(middleOfSpace);
    assert (strcmp(middleOfSpace,"As Df")==0);
    strCapitalize(onlyTab);
    assert (strcmp(onlyTab,"\t")==0);
    strCapitalize(multipleTab);
    assert (strcmp(multipleTab,"\t\t\t")==0);
    strCapitalize(beginTab);
    assert (strcmp(beginTab,"\tAlatta")==0);
    strCapitalize(middleOfTab);
    assert (strcmp(middleOfTab,"As\tDf")==0);
    strCapitalize(alphaNumeric);
    assert (strcmp(alphaNumeric,"Asd234f1")==0);
    strCapitalize(onlyNumeric);
    assert (strcmp(onlyNumeric,"432432")==0);
    strCapitalize(upperCase);
    assert (strcmp(upperCase,"VALAMI")==0);
    strCapitalize(onlyAlpha);
    assert (strcmp(onlyAlpha,"Asdgjh")==0);
    strCapitalize(mixedCase1);
    assert (strcmp(mixedCase1,"VALAMI Es Valami")==0);
    strCapitalize(mixedCase2);
    assert (strcmp(mixedCase2,"UPPER_Lower 1235 \'@#$%^&*()")==0);
    printf("passed\n");
}

void testStrFindInArray() {
    const char *arr[] = { "first", "second", "third", "fourth"};

    printf("testStrFindInArray started...");
    assert(strFindInArray(NULL, 18, NULL, 3)==3);
    assert(strFindInArray(NULL, 18, arr,  3)==3);
    assert(strFindInArray("asdfg",  18, NULL, 3)==3);
    assert(strFindInArray("third", 4, arr, 0) == 2);
    assert(strFindInArray("nothing", 4, arr, 0) == 0);
    printf("passed\n");
}

void testStrHexBuffer()
{
    char hex_buffer[256*3];
    char inputs[256];
    int i;
    for (i=0;i<255;i++)
        inputs[i]=i;

    for (i=0;i<16;i++) {
        strBufferToHex(&inputs[i*16], 16, hex_buffer);
        printf("%s\n",hex_buffer);
    }

}

void testStringBuilder() {
    printf("testStringBuilder started...");

    struct StringBuilder *builder =strAppendStr(NULL, "the quick brown fox");
    strAppendStr(builder," jumps over a lazy dog");
    assert(strcmp(strAppendChar(builder, '!')->chars,
                  "the quick brown fox jumps over a lazy dog!")==0);

    strClearBuilder(builder);

    strAppendStr(builder, "ser0");
    strAppendChar(builder, '.');
    strAppendStr(builder, "baud");
    assert(strcmp(builder->chars,"ser0.baud")==0);

    strFreeBuilder(builder);

    printf("passed\n");
}


void testAll() {
  testStrStartWith();
  testStrEndWith();
  testStrIsEmpty();
  testStrIsBlank();
  testStrIndexOfChar();
  testStrIsAlpha();
  testStrIsNumeric();
  testStrReplaceChar();
  testStrToLowerCase();
  testStrToUpperCase();
  testStrTrim();
  testStrConst();
  testStrCenter();
  testStrLeft();
  testStrRight();
  testStrChomp();
  testStrReplaceStr();
  testStrRemoveStr();
  testStrReverse();
  testStrCapitalize();
  testStrFindInArray();
  testStringBuilder();
}
