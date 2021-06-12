/*****************************************************************************
 * FILE NAME    : FileUtils.c
 * DATE         : March 17 2020
 * PROJECT      : Bay Simulator
 * COPYRIGHT    : Copyright (C) 2020 by Vertiv Company
 *****************************************************************************/
#define _GNU_SOURCE

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>

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

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/

/*****************************************************************************!
 * Function : GetFileBuffer
 *****************************************************************************/
bool
GetFileBuffer
(char* InFilename, char** InBuffer, int* InBufferSize)
{
  int                                   bytesRead;
  FILE*                                 file;
  char*                                 buffer;
  int                                   filesize;
  struct stat                           statbuf;
 
  file = fopen(InFilename, "rb");
  if ( NULL == file ) {
    fprintf(stderr, "Could not open %s\n", InFilename);
    return false;
  }

  //! Get a buffer big enough to hold the contents
  stat(InFilename, &statbuf);
  filesize = statbuf.st_size;
  buffer = (char*)GetMemory((size_t)(filesize + 1));
  if ( NULL == buffer ) {
    fclose(file);
    fprintf(stderr, "Could not get memory for file\n");
    return false;
  }

  //! Read the file contents
  bytesRead = fread(buffer, 1, (size_t)filesize, file);
  fclose(file);
  if ( bytesRead != filesize ) {
    fprintf(stderr, "Error reading %s\n", InFilename);
    FreeMemory(buffer);
    fclose(file);
    return false;
  }
  buffer[filesize] = 0x00;
  *InBuffer = buffer;
  *InBufferSize = filesize;
  return true;
}

/*****************************************************************************!
 * Function : GetFileLines
 *****************************************************************************/
void
GetFileLines
(char* InBuffer, int InBufferSize, char*** InLines, int* InLinesCount)
{
  int                                   i;
  int                                   n;
  char*                                 record;
  char*                                 start;
  char*                                 end;
  bool                                  done = false;
  char**                                temp_lines;
  char**                                lines;
  int                                   lines_count;

  (void)InBufferSize;
  lines = NULL;
  lines_count = 0;
 
  start = InBuffer;
  while ( ! done ) {

    // Find the end of the line
    end = start;
    while (*end != '\n' && *end != 0x00 ) {
      end++;
    }
    n = end - start;

    // Copy the line
    record = (char*)GetMemory((size_t)(n + 1));
    strncpy(record, start, (size_t)n);
    record[n] = 0x00;

    // Append it to the line set
    if ( lines_count == 0 ) {
      // Start a new set
      lines = (char**)GetMemory(sizeof(char*));
      *lines = record;
      lines_count = 1;
    } else {

      // Append to the current set
      temp_lines = (char**)GetMemory(sizeof(char*) * (lines_count + 1));
      for (i = 0; i < lines_count; i++) {
        temp_lines[i] = lines[i];
      }
      FreeMemory(lines);
      temp_lines[i] = record;
      lines_count++;
      lines = temp_lines;
    }

    // Move to the start of the next line;
    if ( *end != 0x00 ) {
      end++;
    }
    start = end;

    // NUL means we are done
    if ( *start == 0x00 ) {
      done = true;
    }
  }
  *InLines = lines;
  *InLinesCount = lines_count;
}

/*****************************************************************************!
 * Function : FileExists
 *****************************************************************************/
bool
FileExists
(string InFilename)
{
  struct stat                           statbuf;
  if ( NULL == InFilename ) {
    return false;
  }
 
  return stat(InFilename, &statbuf) == 0;
}

/*****************************************************************************!
 * Function : FilenameExtractBase
 *****************************************************************************/
string
FilenameExtractBase
(string InFilename)
{
  string                                                                s;
  int                                   n;

  s = strchr(InFilename, '.');
  if ( s == NULL ) {
        return StringCopy(InFilename);
  }

  if ( s == InFilename ) {
        return NULL;
  }

  n = s - InFilename;

  return StringNCopy(InFilename, (size_t)n);
}

/*****************************************************************************!
 * Function : FileCreateEmptyFile
 *****************************************************************************/
bool
FileCreateEmptyFile
(string InFilename)
{
  FILE*                                 file;

  file = fopen(InFilename, "wb");
  if ( NULL == file ) {
    return false;
  }
  fclose(file);
  return true;
}

/*****************************************************************************!
 * Function : FileUtilsCopyFile
 *****************************************************************************/
bool
FileUtilsCopyFile
(string InFromFilename, string InToFilename)
{
  FILE*                                                                 fileIn;
  FILE*                                                                 fileOut;
  struct stat                                                   statbuf;
  char*                                                                 buffer;
  int                                                                   copyBufferSize;
  int                                                                   bytesToWrite;
  int                                                                   bytesRead;
  int                                                                   bytesWritten;
  int                                                                   fileSizeIn;

  if ( NULL == InFromFilename || NULL == InToFilename ) {
        return false;
  }

  fileIn = fopen(InFromFilename, "rb");
  if ( NULL == fileIn ) {
        return false;
  }
  
  // Trying opening the output file
  fileOut = fopen(InToFilename, "wb");
  if ( NULL == fileOut ) {
        // Close the file we already opened
        fclose(fileIn);
        return false;
  }

  // Get the from file stats
  stat(InFromFilename, &statbuf);

  // We need the file size
  fileSizeIn = statbuf.st_size;

  // Copy 128K bytes at time
  copyBufferSize = 128 * 1024;
  buffer = GetMemory((size_t)copyBufferSize);

  // While we have bytes left to copy
  while (fileSizeIn) {
        // Get number of bytes we read from one file and write to the other
    if ( fileSizeIn > copyBufferSize ) {
          bytesToWrite = copyBufferSize;
    } else {
          bytesToWrite = fileSizeIn;
        }

        // Read the input file  
    bytesRead = fread(buffer, 1, (size_t)bytesToWrite, fileIn);
        if ( bytesRead != bytesToWrite ) {
          // The read failed somehow
          fclose(fileIn);
          fclose(fileOut);
          unlink(InToFilename);
          FreeMemory(buffer);
          return false;
        }

        // Write to the output buffer
        bytesWritten = fwrite(buffer, 1, (size_t)bytesToWrite, fileOut);

        // The write failed 
        if ( bytesWritten != bytesToWrite ) {
          fclose(fileIn);
          fclose(fileOut);
          unlink(InToFilename);
          FreeMemory(buffer);
          return false;
        }
        // Adjust the remaining bytes to write
        fileSizeIn -= bytesToWrite;
  }
  FreeMemory(buffer);
  fclose(fileIn);
  fclose(fileOut);  
  return true;
}

/*****************************************************************************!
 * Function : FileUtilsOpen
 *****************************************************************************/
FILE*
FileUtilsOpen
(string InBaseDir, string InFilename, string InFilePermissions)
{
  string                                filename;
  FILE*                                 file;

  // If we were supplied a base direcdtory, prepend it
  if ( InBaseDir ) {
    filename = StringConcat(InBaseDir, InFilename);
  } else {
    filename = StringCopy(InFilename);
  }
#ifdef USE_LOG
  CANMonLogWrite("File Opened : %s\n", filename);
#endif
  file = fopen(filename, InFilePermissions);
 
  FreeMemory(filename);

  return file;
}
