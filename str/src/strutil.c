/*
 *
 * Copyright (C) 2011 Institute for Information Technology and Electrical Engineering
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
\brief String utilities

\author AUTHOR: Zoltan Zidarics mailto:zamek42@gmail.com
\mainpage

    Different string functions which is not in strings.h or simplify the strings functions.

*/

#ifndef STRUTIL_H_INCLUDED
#define STRUTIL_H_INCLUDED

#include <stdint.h>
#include <stddef.h>

struct StringBuilder {
    uint16_t pos;
    size_t size;
    char *chars;
};

/**
 \defgroup strings String functions
 @{
    Different string functions which is not in strings.h or simplify the strings functions.
 @}
 */

/**
strStartWith
    finds the given pattern in str from the begin
    \ingroup strings
    \param str original string to find within it. str can be NULL
    \param pattern for search. pattern can be NULL
    \return index of first occurence of pattern or -1 if not
*/
int strStartWith(const char *str, const char *pattern){}

/**
strEndWith
    finds the given pattern in str from the end
    \ingroup strings
    \param str original string to find within it. str can be NULL
    \param pattern for search. pattern can be NULL
    \return index of first occurence of pattern or -1 if not
*/
int strEndWith(const char *str, const char *pattern){}


/**
strIsEmpty
    checks str is empty. str can be NULL
    \ingroup strings
    \param str to check
    \return -1 if str is NULL || length of str is 0

*/
int strIsEmpty(const char *str){}

/**
strIsBlank
    checks str is empty or blank(contains only whitespace)
    \ingroup strings
    \param str to check. str can be NULL
    \return 0 if str is NULL || length of str is 0 or all of char is whitespace

*/
int strIsBlank(const char *str){}

/**
strIndexOfChar
    returns the index of given char in str
    \param str the string to find in. str can be NULL
    \param ch the char to find in str.
    \return the position of char or -1
*/
int strIndexOfChar(const char *str, const char ch){}

/**
strIsAlpha
    checks is str contains only alpha characters (a-zA-Z)
    \ingroup strings
    \param str str to check. str can be NULL
    \return 0 if not only alpha || str is empty
*/
int strIsAlpha(const char *str){}

/**
strIsNumeric
    checks is str contains only numeric characters (0-9)
    \ingroup strings
    \param str str to check. str can be NULL
    \return 0 if not only numeric || str is empty
*/
int strIsNumeric(const char *str){}

/**
strReplaceChar
    changes the first occurence of char ins str to an another char
    \ingroup strings
    \param str the original str to change into. str can be NULL
    \param findCh char to find within str
    \param chgCh char to change
*/
void strReplaceChar(char *str, char findCh, char chgCh){}

/**
strToLowerCase
    change all alphanumeric chars to lower case
    \ingroup strings
    \param str original str to change. str can be NULL
*/
void strToLowerCase(char *str){}

/**
strToUpperCase
    change all alphanumeric chars to lower case
    \ingroup strings
    \param str original str to change. str can be NULL
*/
void strToUpperCase(char *str){}

/**
strTrim
    removes leading and trailing whitespace.
    \ingroup strings
    \param str original string to processing. str can be NULL.
*/
void strTrim(char *str){}

/**
strConst
    returns a new string to fill the given character and length
    \ingroup strings
    \param ch character to fill
    \param length the length of the new string. if length is 0, returns an empty string
    \return the new string. Caller must free the copy
*/
char *strConst(char ch, int length){}

/**
strCenter
    returns a copy of given str justified to center.
    \ingroup strings
    \param str the original str to justify with spaces. str can be NULL
    \param length the new length of the string.
    \return the new copy of string.
            if length is 0, it returns NULL
            if length is less than the length of string it returns a copy of str.
            Caller must free the copy
*/
char *strCenter(const char *str, int length){}

/**
strLeft
    returns a copy of given str justified to left.
    \ingroup strings
    \param str the original str to justify with spaces. str can be NULL
    \param length the new length of the string.
    \return the new copy of string.
            if length <= 0, there isn't any memory, it isn't string -> returns NULL
            if length is less than the length of string, copy the first "length" pieces of characters and returns with them.
            Caller must free the copy
*/
char *strLeft(const char *str, int length){}

/**
strRight
    returns a copy of given str justified to right
    \ingroup strings
    \param str the original str to justify with spaces. str can be NULL
    \param length the new length of the string.
    \return the new copy of string.
            if length is 0, it returns NULL.
            if length is less than the length of string it returns a copy of str.
            Caller must free the copy
*/
char *strRight(char *str, int length){}

/**
strChomp
    removes the last line end chars of str.
    It can handle Macintosh/linux/windows eol format
    \ingroup strings
    \param str original string to processing. str can be NULL
    \return the beginning of original string
*/
char *strChomp(char *str){}

/**
strReplaceStr
    replace substring of string to new str
    \ingroup strings
    \param str original string to replace within. str can be NULL
    \param pattern to find within str. pattern can be NULL
    \param replace replace. can be NULL
    \return a new copy of replaced string
            Caller must free the copy

*/
char *strReplaceStr(char *str, char *pattern, char *replace){}

/**
strRemoveStr
    removes pattern from str
    \ingroup strings
    \param str original string to remove from. str can be NULL
    \param pattern for removing. pattern can be NULL
*/
void strRemoveStr(char *str, char *pattern){}

/**
strReverse
  reverse the given string
  \ingroup strings
  \param str string to reverse str can be NULL
  \return the new reversed string
          Caller must free the copy
*/
char *strReverse(const char *str){}

/**
strCapitalize
  capitalize the first char of all words in string. str can be NULL
  \ingroup strings
  \param str to capitalize
*/
void strCapitalize(char *str){}

/**
strFindInArray
   find a string in a string array. If the pattern isn't in the array, it returns the default value.
   \ingroup strings
   \param pattern to find
   \param arr_size the size of the array
   \param arr the array
   \param def default value if the pattern isn't in array
   \return if the pattern is in the arr, the index of founded item or def
*/
int strFindInArray(char *pattern, int arr_size, char *arr[], int def){}


/**
strBufferToHex
    get a string buffer converted hexadecimal values of input
    \ingroup strings
    \param buffer input buffer. It can be NULL
    \param buffer_length length of input buffer. It can be 0
    \param hexBuffer output buffer. It can be NULL, but if not NULL, need to be enough memory to store output length * 3 char
    \return the address of output buffer
*/
char *strBufferToHex(char *buffer, int buffer_length, char *hexBuffer){}


/**
 \defgroup stringbuilder String builder
 @{
 Stringbuilder is resource to build strings.
 Create it with \link strNewStringBuilder() \endlink. It creates a new builder, which can
 append different chars and strings to builded string. If the string is longer than the initial
 size of builder, it generates a new buffer.
 The data type is struct StringBuilder which has chars field to use as string.

 The clear of Stringbuilder is strClearBuilder(), which set it to empty string.
 The strFreeBuilder is free the entire StringBuilder.
 @}
 */

/**
    strNewStringBuilder
    \ingroup stringbuilder
    Create a new StringBuilder with the given capacity.
    \param capacity the initial capacity of builder. If the capacity is less than 0
        it creates the default size of buffer which is \link DEF_STRING_BUILDER_LEN \endlink
    \return the pointer to a new struct StringBuilder
*/
struct StringBuilder *strNewStringBuilder(uint16_t capacity){}

/**
    strAppendStr
    \ingroup stringbuilder
    Appends a string to the builder.
    \param builder is a pointer to the StringBuilder. If the builder is NULL, it creates a
    new StringBuilder.
    \param str the string to append to Builder. If str is NULL it only create a new StringBuilder.
    \return the pointer to the stringbuilder.
*/
struct StringBuilder *strAppendStr(struct StringBuilder *builder, const char *str){}

/**
    strAppendChar
    \ingroup stringbuilder
    Appends a char to the builder.
    \param builder is a pointer to the StringBuilder. If the builder is NULL, it creates a
    new StringBuilder.
    \param ch the char to append to Builder.
    \return the pointer to the stringbuilder.
*/
struct StringBuilder *strAppendChar(struct StringBuilder *builder, char ch){}

/**
    strFreeBuilder
    \ingroup stringbuilder
    Free the given builder
    \param builder to be freeing. builder can be NULL.
*/
void strFreeBuilder(struct StringBuilder *builder){}


/**
    strClearBuilder
    \ingroup stringbuilder
    Clear the given builder. It set the length to 0
    \param builder to be clearing. sb can be NULL.
*/
void strClearBuilder(struct StringBuilder *builder){}

#endif // STRUTIL_H_INCLUDED
















