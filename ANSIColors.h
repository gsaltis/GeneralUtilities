/*****************************************************************************
 * FILE NAME    : ANSIColors.h
 * DATE         : 
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2020 by Vertiv Company
 *****************************************************************************/
#ifndef _ansicolors_h_
#define _ansicolors_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#if ANSI_COLORS_SUPPORTED
// Colors Defined
#define ColorRed                        "\e[31m"
#define ColorBoldRed                    "\e[1;31m"
#define ColorBrightRed                  "\e[31;1m"

#define ColorBoldGreen                  "\e[1;32m"
#define ColorGreen                      "\e[32m"
#define ColorBrightGreen                "\e[32;1m"

#define ColorYellow                     "\e[33m"
#define ColorYellowUnderline            "\e[33;4m"
#define ColorBrightYellow               "\e[33;1m"
#define ColorBoldYellow                 "\e[1;33m"
#define ColorBoldYellowReverse          "\e[1;7;33m"


#define ColorWhite                      "\e[0;37m"

#define ColorBlue                       "\e[0;34m"
#define ColorBoldBlue                   "\e[1;34m"
#define ColorCyan						"\e[0;36m"
#define ColorBoldCyan					"\e[1;36m"

#define ColorReset                      "\e[0;0m"

#define HeadingStyle                  	"\e[1;7;37m"
#else

// Colors Not Defines
#define ColorRed                        "" 
#define ColorBoldRed                    ""
#define ColorBrightRed                  ""

#define ColorBoldGreen                  ""
#define ColorGreen                      ""
#define ColorBrightGreen                ""

#define ColorYellow                     ""
#define ColorYellowUnderline            ""
#define ColorBrightYellow               ""
#define ColorBoldYellow                 ""
#define ColorBoldYellowReverse          ""


#define ColorWhite                      ""

#define ColorBlue                       ""
#define ColorBoldBlue                   ""
#define ColorCyan						""
#define ColorBoldCyan					""

#define ColorReset                      ""

#define HeadingStyle                  	""

#endif

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/

#endif /* _ansicolors_h_*/
