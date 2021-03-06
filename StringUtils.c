/*****************************************************************************
 * FILE NAME    : StringUtils.c
 * DATE         : January 15 2019
 * PROJECT      : Bay Simulator
 * COPYRIGHT    : Copyright (C) 2019 by Vertiv Company
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "StringUtils.h"
#include "MemoryManager.h"
#include "ascii.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
int
StringListCompare
(const void* p1, const void* p2);

int
StringListCompareReverse
(const void* p1, const void* p2);

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/

/*****************************************************************************!
 * Function : StringCopy
 *****************************************************************************/
string
StringCopy
(
 string                         InString
)
{
    uint32_t                    n;
    string                      returnString;
    if ( NULL == InString ) {
        return NULL;
    }

    n = strlen(InString);
    returnString = GetMemory(n + 1);
    strncpy(returnString, InString, n);
    returnString[n] = NUL;

    return returnString;
}

/*****************************************************************************!
 * Function : StringCopy
 *****************************************************************************/
string
StringNCopy
(
 string                         InString,
 uint32_t                       InLength
)
{
  uint32_t                    n;
  string                      returnString;
  if ( NULL == InString ) {
    return NULL;
  }

  n = strlen(InString);
  if ( n > InLength ) {
    n = InLength;  
  }
  returnString = GetMemory(n + 1);
  strncpy(returnString, InString, n);
  returnString[n] = NUL;

  return returnString;
}

/*****************************************************************************!
 * Function : StringBeginsWith
 * Purpose  : Check if String1 begins with String2
 *****************************************************************************/
bool
StringBeginsWith
(
 string                         InString1,
 string                         InString2
)
{
    uint32_t                    t1, t2;
    if ( NULL == InString1 || NULL == InString2 ) {
        return false;
    }
    t1 = strlen(InString1);
    t2 = strlen(InString2);
    
    if ( t1 == 0 || t2 == 0 ) {
        return false;
    }
    
    if ( t2 > t1 ) {
        return false;
    }
    return strncmp(InString1, InString2, t1) == 0;
}

/*****************************************************************************!
 * Function : StringEndsWith
 * Purpose  : Check if String1 ends with String2
 *****************************************************************************/
bool
StringEndsWith
(
 string                         InString1,
 string                         InString2
)
{
  int                                   t3;
    uint32_t                    t1, t2;
    if ( NULL == InString1 || NULL == InString2 ) {
        return false;
    }
    t1 = strlen(InString1);
    t2 = strlen(InString2);
    
    if ( t1 == 0 || t2 == 0 ) {
        return false;
    }
    
    if ( t2 > t1 ) {
        return false;
    }

    t3 = t1 - t2;
    
    return strncmp(&(InString1[t3]), InString2, t2) == 0;
}

/*****************************************************************************!
 * Function : StringEqual
 *****************************************************************************/
bool
StringEqual
(
 string                         InString1,
 string                         InString2
)
{
    uint32_t                            t1;
    if ( NULL == InString1 || NULL == InString2 ) {
        return false;
    }
    t1 = strlen(InString1);
    if ( t1 != strlen(InString2) ) {
        return false;
    }
    return strcmp(InString1, InString2) == 0;
}

/*****************************************************************************!
 * Function : StringEqualNoCase
 *****************************************************************************/
bool
StringEqualNoCase
(
 string                         InString1,
 string                         InString2
)
{
    uint32_t                            t1, i;
    
    if ( NULL == InString1 || NULL == InString2 ) {
        return false;
    }
    t1 = strlen(InString1);
    if ( t1 != strlen(InString2) ) {
        return false;
    }
    for (i = 0; i < t1; i++) {
        if ( tolower(InString1[i]) != tolower(InString2[i]) ) {
            return false;
        }
    }
    return true;
}

/*****************************************************************************!
 * Function : StringTrim
 *****************************************************************************/
string
StringTrim
(
 string                         InString
)
{
    string                      start;
    string                      end;
    string                      s;
    uint32_t                    n;
    
    if ( NULL == InString ) {
        return NULL;
    }

    // Trim off the leading spaces
    start = InString;
    while ( isspace(*start) && *start ) {
        start++;
    }

    // It looks like the string is all spaces
    if ( *start == NUL ) {
        return NULL;
    }

    // Trim off the trailing spaces
    n = strlen(InString);
    end = InString + (n - 1);
    while ( isspace(*end) && end != start ) {
        end--;
    }

    // Copy the string portion
    n = (end+1) - start;
    s = (string)GetMemory(n + 1);
    memcpy(s, start, n);
    s[n] = NUL;
    return s;
}

/*****************************************************************************!
 * Function : StringCapitalize
 *****************************************************************************/
void
StringCapitalize
(
 string                         InString
)
{
  if ( InString == NULL || InString[0] == NUL ) {
    return;
  }

  if ( !isalpha(InString[0]) ) {
    return;
  }

  InString[0] = toupper(InString[0]);
}

/*****************************************************************************!
 * Function : StringIsInteger
 *****************************************************************************/
bool
StringIsInteger
(
 string                         InString
)
{
    string                      s;
    if ( NULL == InString ) {
        return false;
    }
    s = InString;
    if ( *s == '-' || *s == '+' ) {
      s++;
    }
    for ( ; *s; s++) {
        if ( !isdigit(*s) ) {
            return false;
        }
    }
    return true;
}

/*****************************************************************************!
 * Function : StringToU32
 *****************************************************************************/
uint32_t
StringToU32
(
 string                         InString
)
{
    if ( NULL == InString ) {
        return 0;
    }
    return (uint32_t)atoi(InString);
}

/*****************************************************************************!
 * Function : StringToU16
 *****************************************************************************/
uint16_t
StringToU16
(
 string                         InString
)
{
    if ( NULL == InString ) {
        return 0;
    }
    return (uint16_t)atoi(InString);

}

/*****************************************************************************!
 * Function : StringToU8
 *****************************************************************************/
uint8_t
StringToU8
(
 string                         InString
)
{
    if ( NULL == InString ) {
        return 0;
    }
    return (uint8_t)atoi(InString);
}

/*****************************************************************************!
 * Function : StringConcat
 *****************************************************************************/
string
StringConcat
(
 string                         InString1,
 string                         InString2
)
{
    uint32_t                            n;
    string                              returnString;
    if ( NULL == InString1 || NULL == InString2 ) {
        return NULL;
    }
    n = strlen(InString1) + strlen(InString2);
    returnString = (string)GetMemory(n + 1);
    sprintf(returnString, "%s%s", InString1, InString2);
    return returnString;
}

/*****************************************************************************!
 * Function : StringConcatTo
 * Purpose  : Same functionality as StringConcat except InString1 is assumed
 *            to a pointer to a string and is freed.
 *****************************************************************************/
string
StringConcatTo
(
 string                         InString1,
 string                         InString2
)
{
    uint32_t                            n;
    string                              returnString;
    if ( NULL == InString2 ) {
        return NULL;
    }
    if ( NULL == InString1 ) {
      return StringCopy(InString2);
    }
    n = strlen(InString1) + strlen(InString2);
    returnString = (string)GetMemory(n + 1);
    sprintf(returnString, "%s%s", InString1, InString2);
    FreeMemory(InString1);
    return returnString;
}

/*****************************************************************************!
 * Function : StringContainsChar 
 *****************************************************************************/
bool
StringContainsChar
(
 string                         InString,
 int                            InChar
)
{
    if ( NULL == InString ) {
        return false;
    }
    
    while (*InString) {
        if ( InChar == *InString ) {
            return true;
        }
        InString++;
    }
    return false;
}

/*****************************************************************************!
 * Function : StringReplaceChar
 *****************************************************************************/
string
StringReplaceChar
(
 string                         InString,
 char                           InChar,
 char                           InReplacementChar
)
{
    string                      s;

    if ( NULL == InString ) {
        return NULL;
    }
    
    for (s = InString; *s; s++) {
        if ( *s == InChar ) {
            *s = InReplacementChar;
        }
    }
    return InString;
}

/*****************************************************************************!
 * Function : StringSplit
 *****************************************************************************/
StringList*
StringSplit
(
 string                         InString,
 string                         InDividers,
 int                            InSkipEmpty
)
{
    string                              s;
    uint32_t                            n;
    string                              start;
    string                              end;
    StringList*                         list;
    
    if ( NULL == InString || NULL == InDividers ) {
        return NULL;
    }
    (void)InSkipEmpty;
    start = InString;

    list = StringListCreate();
    while (true) {
        // Skip dividers
      while (StringContainsChar(InDividers, *start) && *start) {
            start++;
        }

        // We hit the end of the string
        if (*start == NUL ) {
            break;
        }
        end = start;

        // Skip to the end or next dividers
        while (!StringContainsChar(InDividers, *end) && *end) {
            end++;
        }

        // Copy the string portion
        n = end - start;
        s = GetMemory(n + 1);
        memcpy(s, start, n);
        s[n] = NUL;

        // Append it to the list we are building
        StringListAppend(list, s);
        if ( *end != NUL ) {
            end++;
        }
        start = end;
    }

    return list;
}

/*****************************************************************************!
 * Function : StringListCreate
 *****************************************************************************/
StringList*
StringListCreate
()
{
    StringList*                 returnList;

    returnList = (StringList*)GetMemory(sizeof(StringList));
    memset(returnList, 0x00, sizeof(StringList));
    return returnList;
}

/*****************************************************************************!
 * Function : StringListAppend
 *****************************************************************************/
void
StringListAppend
(
 StringList*                            InStringList,
 string                                 InString
)
{
    uint32_t                            i;
    string*                             newList;
    uint32_t                            newCount;
    if ( NULL == InStringList || NULL == InString ) {
        return;
    }
    newCount = InStringList->stringCount + 1;
    newList = (string*)GetMemory((sizeof(string)) * newCount);
    for ( i = 0; i < InStringList->stringCount; i++ ) {
        newList[i] = InStringList->strings[i];
    }
    if ( InStringList->stringCount > 0 ) {
        FreeMemory(InStringList->strings);
    }
    newList[InStringList->stringCount] = InString;
    InStringList->strings = newList;
    InStringList->stringCount = newCount;
}

/*****************************************************************************!
 * Function : StringListGetCount
 *****************************************************************************/
uint32_t
StringListGetCount
(
 StringList*                            InStringList
)
{
    if ( NULL == InStringList ) {
        return 0;
    }
    return InStringList->stringCount;
}

/*****************************************************************************!
 * Function : StringListContains
 *****************************************************************************/
bool
StringListContains
(
 StringList*                            InStringList,
 string                                 InString
)
{
    uint32_t                            i;
    if ( NULL == InStringList || NULL == InString ) {
        return false;
    }
    for ( i = 0 ; i < InStringList->stringCount; i++) {
        if ( StringEqual(InStringList->strings[i], InString) ) {
            return true;
        }
    }
    return false;
}

/*****************************************************************************!
 * Function : StringListDestroy
 *****************************************************************************/
void
StringListDestroy
(
 StringList*                            InStringList
)
{
    uint32_t                            i;
    if ( NULL == InStringList ) {
        return;
    }

    for ( i = 0; i < InStringList->stringCount; i++ ) {
        FreeMemory(InStringList->strings[i]);
    }
    if ( InStringList->stringCount > 0 ) {
      FreeMemory(InStringList->strings);
    }
    FreeMemory(InStringList);
}

/*****************************************************************************!
 * Function : StringListGet
 *****************************************************************************/
string
StringListGet
(
 StringList*                            InStringList,
 uint32_t                               InIndex
)
{
    if ( NULL == InStringList ) {
        return NULL;
    }
    
    if ( InIndex >= InStringList->stringCount ) {
        return NULL;
    }

    return InStringList->strings[InIndex];
}

/*****************************************************************************!
 * Function : StringSizedToInteger
 *****************************************************************************/
int
StringSizedToInteger
(string InString, int size)  // In Bits
{
    int                                 base;
    string                              s;
    char                                prefix[3];
    int                                 n;

    s = InString;
    base = 10;
    if ( strlen(s) > 2 ) {
        strncpy(prefix, s, 2);
        s += 2;
        prefix[2] = NUL;
        if ( StringEqualNoCase(prefix, "0x") ) {
            base = 16;
        } else if ( StringEqualNoCase(prefix, "0b") ) {
            base = 2;
        }
    }
    n = strlen(s);
    if ( base == 2 && n > size ) {
        return 0;
    } else if ( base == 16 && n > (size/4) ) {
        return 0;
    }
    return strtol(s, NULL, base);
}
 
/*****************************************************************************!
 * Function : StringEqualsOneOf
 *****************************************************************************/
bool
StringEqualsOneOf
(string InString1, ...)
{
  string                                s;
  va_list                               va;

  va_start(va, InString1);
  s = va_arg(va, string);
  while (s) {
    if ( StringEqual(InString1, s) ) {
      va_end(va);
      return true;
    }
    s = va_arg(va, string);
  }
  return false;
}

/*****************************************************************************!
 * Function : StringFill
 *****************************************************************************/
string
StringFill
(int InChar, int InSize)
{
  string                                returnString;

  if (InChar == NUL || InSize == 0) {
    return NULL;
  }
  returnString = (string)GetMemory((size_t)(InSize + 1));
  memset(returnString, InChar, (size_t)InSize);
  returnString[InSize] = NUL;
  return returnString;
}

/*****************************************************************************!
 * Function : StringListConcat
 *****************************************************************************/
string
StringListConcat
(StringList* InList, string InSeparators)
{
  string                                returnString;
  int                                   i;

  if ( InList == NULL ) {
    return NULL;
  }
  returnString = "";

  for (i = 0; i < (int)InList->stringCount; i++) {
    if ( returnString ) {
      if ( InSeparators ) {
        returnString = StringConcatTo(returnString, InSeparators);
      }
      returnString = StringConcatTo(returnString, InList->strings[i]);
    } else {
      returnString = StringCopy(InList->strings[i]);
    }
  }
  return returnString;
}


/*****************************************************************************!
 * Function : StringMultiConcat
 *****************************************************************************/
string
StringMultiConcat
(string InString1, ...)
{
  va_list                               args;
  string                                returnString, s;

  if ( NULL == InString1 ) {
    return NULL;
  }

  returnString = StringCopy(InString1);
  va_start(args, InString1);
  s = va_arg(args, string);
  while (s) {
    returnString = StringConcatTo(returnString, s);
    s = va_arg(args, string);
  }
  return returnString;
} 

/*****************************************************************************!
 * Function : StringListSort
 *****************************************************************************/
void
StringListSort
(StringList* InStrings)
{
  string*                                                               strings;
  int                                                                   size;
  int                                                                   i;

  // If we have and empty list or a list with one item, just return
  if ( NULL == InStrings || 2 > InStrings->stringCount ) {
        return;
  }

  size = InStrings->stringCount;

  // Convert the list to a flat array for qsort
  strings = (string*)GetMemory(sizeof(string) * size);
  for ( i = 0 ; i < size ; i++ ) {
        strings[i] = InStrings->strings[i];
  }

  qsort(strings, (size_t)size, sizeof(string), StringListCompare);

  for ( i = 0; i < size; i++ ) {
        InStrings->strings[i] = strings[i];
  }

  FreeMemory(strings);
}

/*****************************************************************************!
 * Function : StringListReverseSort
 *****************************************************************************/
void
StringListReverseSort
(StringList* InStrings)
{
  string*                                                               strings;
  int                                                                   size;
  int                                                                   i;

  // If we have and empty list or a list with one item, just return
  if ( NULL == InStrings || 2 > InStrings->stringCount ) {
        return;
  }

  size = InStrings->stringCount;

  // Convert the list to a flat array for qsort
  strings = (string*)GetMemory(sizeof(string) * size);
  for ( i = 0 ; i < size ; i++ ) {
        strings[i] = InStrings->strings[i];
  }

  qsort(strings, (size_t)size, sizeof(string), StringListCompareReverse);

  for ( i = 0; i < size; i++ ) {
        InStrings->strings[i] = strings[i];
  }

  FreeMemory(strings);
}

/*****************************************************************************!
 * Function : StringListCompare
 *****************************************************************************/
int
StringListCompare
(const void* p1, const void* p2)
{
  return strcmp(* (char * const *) p1, * (char * const *) p2);
}

/*****************************************************************************!
 * Function : StringListCompareReverse
 *****************************************************************************/
int
StringListCompareReverse
(const void* p1, const void* p2)
{
  return strcmp(* (char * const *) p2, * (char * const *) p1);
}

/*****************************************************************************!
 * Function : StringToLowerCase
 *****************************************************************************/
string
StringToLowerCase
(string InString)
{
  int                                                                   i, n;
  string                                                                s;

  n = strlen(InString);

  s = StringCopy(InString);
  for ( i = 0 ; i < n ; i++ ) {
        s[i] = tolower(s[i]);
  }
  return s;
}

/*****************************************************************************!
 * Function : TrimLine
 *****************************************************************************/
char*
TrimLine
(char* InString)
{
  char*                                 s;

  // Little more than a wrapper around functions to trim start and end of line
  s = TrimStartOfLine(InString);
  TrimEndOfLine(s);

  return s;
}

/*****************************************************************************!
 * Function : TrimStartOfLine
 *****************************************************************************/
char*
TrimStartOfLine
(char* InString)
{
  char*                                 start;
  char*                         s;
  int                           n;

  // Check for an empty string 
  if ( NULL == InString ) {
    return NULL;
  }

  start = InString;

  // skip to first non-space character or end of string
  while (*start && isspace(*start)) {
    start++;
  }

  // If it's all spaces just return a NUL string
  if ( *start == 0x00 ) {
    s = (char*)malloc(1);
    *s = 0x00;
    return s;
  }

  // Copy everything from the first non space character
  n = strlen(start);
  s = (char*)malloc((size_t)(n + 1));
  strcpy(s, start);
  return s;
}

/*****************************************************************************!
 * Function : TrimEndOfLine
 *****************************************************************************/
void
TrimEndOfLine
(char* InString)
{
  int                                   n;
  if ( NULL == InString ) {
    return;
  }

  n = strlen(InString);
  if ( n == 0 ) {
    return;
  }

  n--;
  while (n >= 0 && (InString[n] == '\r' || InString[n] == '\n') ) {
    n--;
  }
  InString[n+1] = 0x00;
}

/*****************************************************************************!
 * Function : GetBoolFromString
 *****************************************************************************/
bool
GetBoolFromString
(char* InString)
{
  if ( strcmp(InString, "TRUE") == 0 ||
       strcmp(InString, "true") == 0 ||
       strcmp(InString, "1") == 0 ) {
    return true;
  }
  return false;
}

/*****************************************************************************!
 * Function : StringToFloat
 *****************************************************************************/
int
StringToFloat
(char* InString)
{
  char*                                 decPart;
  char*                                 intPart;
  int                                   n, i, d;
  char*                                 period;
  char*                                 start;
  start = InString;
  period = start;

  decPart = NULL;
  intPart = NULL;
  d = 0;
  
  while (*period != 0x00 && *period != '.' ) {
    period++;
  }
  n = period - start;
  intPart = (char*)malloc((size_t)(n + 1));
  strncpy(intPart, start, (size_t)n);
  intPart[n] = 0x00;

  if ( *period == '.' ) {
    period++;
    n = strlen(period);
    decPart = (char*)malloc((size_t)(n + 1));
    strncpy(decPart, period, (size_t)n);
    decPart[n] = 0x00;
  }

  i = atoi(intPart);
  if ( decPart ) {
    d = atoi(decPart);
    if ( strlen(decPart) == 1 ) {
      d *= 10;
    }
  }
  
  i *= 100;
  i += d;
  free(intPart);
  if ( decPart ) {
    free(decPart);
  }
  return i;
}


/*****************************************************************************!
 * Function : StringConvertNonHTML
 *****************************************************************************/
string
StringConvertNonHTML
(string InString)
{
  string                                s;
  char                                  c;
  int                                   i;
  int                                   startChar;
  int                                   n;
  string                                returnString;

  if ( NULL == InString ) {
    return NULL;
  }
  
  n = strlen(InString);

  returnString = NULL;
  startChar = 0;
  for ( i = 0 ; i < n ; i++ ) {
    c = InString[i];
    if ( c == '&' || c == '\'' || c == '"' || c == '<' || c == '>' || c == ' ' ) {
      if ( startChar < i ) {
        s = StringNCopy(&(InString[startChar]), (uint32_t)(i - startChar));
        returnString = StringConcatTo(returnString, s);
        FreeMemory(s);
      }
      startChar = i+1;
      switch (c) {
        case '"' :
          returnString = StringConcatTo(returnString, "%22");
          break;
        case '\'' :
          returnString = StringConcatTo(returnString, "%27");
          break;
        case '&' :
          returnString = StringConcatTo(returnString, "%26");
          break;
        case '<' :
          returnString = StringConcatTo(returnString, "%3C");
          break;
        case '>' :
          returnString = StringConcatTo(returnString, "%3E");
          break;
        case ' ' :
          returnString = StringConcatTo(returnString, "%20");
          break;
      }
      continue;
    }
  }
  if ( startChar < n ) {
    s = StringNCopy(&(InString[startChar]), (uint32_t)(i - startChar));
    returnString = StringConcatTo(returnString, s);
    FreeMemory(s);
  }
  return returnString;
}
  
