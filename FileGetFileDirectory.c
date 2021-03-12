/*****************************************************************************!
 * Function : FileGetFileDirectory
 * Purpose  : Return the directory portion of a pathname or "" if no directory
 *****************************************************************************/
string
FileGetFileDirectory
(string InFilename)
{
  string			s;
  int				n;
  if ( NULL == InFilename ) {
    return NULL;
  }

  s = strrchr(InFilename, '/');
  if ( s == NULL ) {
    return StringCopy("");
  }

  n = (s - InFilename) + 1;
  return StringNCopy(InFilename, n);  
}
