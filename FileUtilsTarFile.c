/*****************************************************************************!
 * Function : FileUtilsTarFile
 *****************************************************************************/
int
FileUtilsTarFile
(string InFilename, string InWWWBaseDirName, string InCurrentDirName,
 string InInstallDirName)
{
  string                                                                baseFilename;
  string                                                                tarFilename;
  string                                                                s;
  int                                                                   n;

  // Change directory to the installation directory (caching current directory)
  n = chdir(InInstallDirName); 

  if ( n != 0 ) {
    return errno;
  }
  baseFilename = FilenameExtractBase(InFilename);
  tarFilename = StringMultiConcat(InWWWBaseDirName, "/", baseFilename, ".tar.gz", NULL);

  s = StringMultiConcat("tar Pczf ", tarFilename, " ", InFilename, NULL);

  system(s);

  FreeMemory(baseFilename);
  FreeMemory(tarFilename);
  FreeMemory(s);

  // Restore the current directory
  chdir(InCurrentDirName);
  return 0;
}
