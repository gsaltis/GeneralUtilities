/*******************************************************************************!
 * FILE         : NumericTypes.c
 * DATE         : September 24 2018
 * PROJECT      : CanSim
 * COPYRIGHT    : Copyright (c) 2018 Vertiv Company
 *******************************************************************************/

/*******************************************************************************!
 * Global Headers
 *******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

/*******************************************************************************!
 * Local Macros
 *******************************************************************************/
#define HEX_TO_DEC(c) \
    c >= '0' && c <= '9' ? \
        (c - '0') : \
    toupper(c) >= 'A' && toupper(c) <= 'F' ? \
        (toupper(c) - 'A' + 10) : \
        0

/*******************************************************************************!
 * Local Functions
 *******************************************************************************/
void
ConvertIntToCommaString2R
(char* InSource, char* InReturn);

/*******************************************************************************!
 * Function : GetIntValueFromString
 *******************************************************************************/
int
GetIntValueFromString
(
 bool*                                  InStatus,
 char*                                  InString
)
{
    size_t                              stringLen;
    int                                 i, n, k;
    int                                 sign = 1;
    
    if ( NULL == InStatus || NULL == InString ) {
        return 0;
    }
    
    stringLen = strlen(InString);
    if ( stringLen == 0 ) {
        *InStatus = false;
        return 0;
    }
    
    i = 0;
    if ( InString[0] == '-' ) {
        sign = -1;
        i++;
    }
    if ( InString[i] == '0') {
        // Handle Hex Input
        if ( InString[i+1] == 'x' || InString[i+1] == 'X' ) {
            i += 2;
            if ( stringLen <= i || stringLen > i+8 ) {
                *InStatus = false;
                return 0;
            }
            n = 0;
            for ( ; i < stringLen; i++) {
                if ( !isxdigit(InString[i]) ) {
                    *InStatus = false;
                    return 0;
                }
                k = HEX_TO_DEC(InString[i]);
                n <<= 4;
                n += k;
            }
            *InStatus = true;
            return n * sign;
        } else if ( InString[i+1] == 'b' || InString[i+1] == 'B' ) {
            i += 2;
            // Handle Binary Input
            if ( stringLen <= i || stringLen > (i + 32) ) {
                *InStatus = false;
                return 0;
            }
            n = 0;
            for ( ; i < stringLen ; i++ ) {
                if ( InString[i] == '0' || InString[i] == '1' ) {
                    k = InString[i] - '0';
                    n <<= 1;
                    n += k;
                } else {
                    *InStatus = false;
                    return 0;
                }
            }
            *InStatus = true;
            return n * sign;
        }
    }
    
    for (; i < stringLen; i++) {
        if ( !isdigit(InString[i]) ) {
            *InStatus = false;
            return 0;
        }
    }
    n = atoi(InString);
    *InStatus = true;
    return n;
}

/*****************************************************************************!
 * Function : GetHex32ValueFromString
 *****************************************************************************/
uint32_t
GetHex32ValueFromString
(bool* InStatus, char* InString)
{
  uint32_t                              n, i, k;
  int                                   stringLen;

  stringLen = strlen(InString); 
  n = 0;
  for ( i = 0 ; i < stringLen; i++) {
    if ( !isxdigit(InString[i]) ) {
      if ( InStatus ) {
        *InStatus = false;
      }
      return 0;
    }
    k = HEX_TO_DEC(InString[i]);
    n <<= 4;
    n += k;
  }
  if ( InStatus ) {
    *InStatus = true;
  }
  return n;
}

/*****************************************************************************!
 * Function : GetHex64ValueFromString
 *****************************************************************************/
uint64_t
GetHex64ValueFromString
(bool* InStatus, char* InString)
{
  uint64_t                              n, i, k;
  int                                   stringLen;

  stringLen = strlen(InString); 
  n = 0;
  for ( i = 0 ; i < stringLen; i++) {
    if ( !isxdigit(InString[i]) ) {
      if ( InStatus ) {
        *InStatus = false;
      }
      return 0;
    }
    k = HEX_TO_DEC(InString[i]);
    n <<= 4;
    n += k;
  }
  if ( InStatus ) {
    *InStatus = true;
  }
  return n;
}

/*******************************************************************************!
 * Function : GetFloatValueFromString
 *******************************************************************************/
float
GetFloatValueFromString
(
 bool*                                  InStatus,
 char*                                  InString
)
{
    size_t                              stringLen;
    int                                 i;
    bool                                haveDecimal;
    
    if ( NULL == InStatus || NULL == InString ) {
        return 0;
    }
    
    stringLen = strlen(InString);
    if ( stringLen == 0 ) {
        *InStatus = false;
        return 0;
    }
    
    haveDecimal = false;
    
    i = 0;
    if ( InString[i] == '-' ) {
        i++;
    }
    for (; i < stringLen; i++ ) {
        if ( isdigit(InString[i]) ) {
            continue;
        }
        if ( '.' == InString[i] ) {
            if ( haveDecimal ) {
                *InStatus = false;
                return 0.0;
            }
            haveDecimal = true;
        }
    }
    *InStatus = true;
    return atof(InString);
}

/*******************************************************************************!
 * Function : ConvertIntToCommaString
 *******************************************************************************/
char*
ConvertIntToCommaString
(int InValue, char* InReturnBuffer)
{
  char                                  s2[32];
  sprintf(s2, "%d", InValue);
  if ( strlen(s2) < 4 ) {
    strcpy(InReturnBuffer, s2);
    return InReturnBuffer;
  }
  ConvertIntToCommaString2R(s2, InReturnBuffer);
  return InReturnBuffer;
}

/*******************************************************************************!
 * Function : ConvertIntToCommaString
 *******************************************************************************/
char*
ConvertLongLongToCommaString
(long long InValue, char* InReturnBuffer)
{
  char                                  s2[32];
  sprintf(s2, "%lld", InValue);
  if ( strlen(s2) < 4 ) {
    strcpy(InReturnBuffer, s2);
    return InReturnBuffer;
  }
  ConvertIntToCommaString2R(s2, InReturnBuffer);
  return InReturnBuffer;
}

/*******************************************************************************!
 * Function : ConvertIntToCommaString
 *******************************************************************************/
void
ConvertIntToCommaString2R
(char* InSource, char* InReturn)
{
  *InReturn = *InSource;
   InReturn++;
   InSource++;
   if ( strlen(InSource) % 3 == 0 && *InSource ) {
     *InReturn = ',';
     InReturn++;
   }
   if (*InSource == 0x00 ) {
     *InReturn = 0x00;
     return;
   }
   ConvertIntToCommaString2R(InSource, InReturn);
}

     
