#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "StringUtils.h"
#include "FileUtils.h"
#include "MemoryManager.h"

int
main
()
{
  string				s;
  string				s2;

  s = "/usr/test.c";

  s2 = FileGetFilename(s);
  assert(StringEqual(s2, "test.c"));

  s2 = FileGetBaseFilename(s);
  assert(StringEqual(s2, "test"));

  s2 = FileGetFileDirectory(s);
  assert(StringEqual(s2, "/usr/"));

  s2 = FileGetFileSuffix(s);
  assert(StringEqual(s2, "c"));



  s = "test.c";
  s2 = FileGetFilename(s);
  assert(StringEqual(s2, "test.c"));

  s2 = FileGetBaseFilename(s);
  assert(StringEqual(s2, "test"));

  s2 = FileGetFileDirectory(s);
  assert(StringEqual(s2, ""));

  s2 = FileGetFileSuffix(s);
  assert(StringEqual(s2, "c"));


  s = "test";
  s2 = FileGetFilename(s);
  assert(StringEqual(s2, "test"));

  s2 = FileGetBaseFilename(s);
  assert(StringEqual(s2, "test"));

  s2 = FileGetFileDirectory(s);
  assert(StringEqual(s2, ""));

  s2 = FileGetFileSuffix(s);
  assert(s2 == NULL);

  printf("Tests passed\n");
  return 0;
}

