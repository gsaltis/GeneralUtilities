/*****************************************************************************!
 * Function : FileUtilsTarFile
 *****************************************************************************/
void
FileUtilsTarFile
(string InFilename, string InWWWBaseDir)
{
  string								installDir;
  string								baseFilename;
  string								tarFilename;
  string								s;
  string								currentDir;
  int									n;

  // Change directory to the installation directory (caching current directory)
  currentDir = (string)get_current_dir_name();
  installDir = DirManagementGetInstallDir();
  n = chdir(installDir); 

  if ( n != 0 ) {
	CANMonLogWrite("Could not change directory to %s : %s\n", installDir, strerror(errno));
	return;
  }
  baseFilename = FilenameExtractBase(InFilename);
  tarFilename = StringMultiConcat(InWWWBaseDir, "/", baseFilename, ".tar.gz", NULL);

  CANMonLogWrite("Request for %s file made\n", InFilename);
  CANMonLogWrite("Compressing %s to %s in %s\n", InFilename, tarFilename, installDir);
  s = StringMultiConcat("tar Pczf ", tarFilename, " ", InFilename, NULL);

  system(s);

  FreeMemory(installDir);
  FreeMemory(baseFilename);
  FreeMemory(tarFilename);
  FreeMemory(s);


  // Restore the current directory
  chdir(currentDir);
  free(currentDir);
}
