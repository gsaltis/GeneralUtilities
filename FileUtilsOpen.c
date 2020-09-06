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
