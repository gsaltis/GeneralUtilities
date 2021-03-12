/*****************************************************************************!
 * Function : FileGetFilename
 * Purpose  : Return the filename portion of a path without the directory name  
 *****************************************************************************/
string
FileGetFilename
(string InFilename)
{
  string                               	s;

  if ( NULL == InFilename ) {
    return NULL;
  }

  s = strrchr(InFilename, '/');
  if ( s == NULL ) {
    s = InFilename;
  } else {
    s++;
  }
  return StringCopy(s);
}
