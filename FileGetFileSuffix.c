/*****************************************************************************!
 * Function : FileGetFileSuffix
 *****************************************************************************/
string
FileGetFileSuffix
(string InFilename)
{
  string				s;

  s = strrchr(InFilename, '/');

  // Get the start of the filename
  if ( NULL == s ) {
    s = InFilename;
  } else {
    s++;
  }
  if ( NULL == InFilename ) {
    return NULL;
  }

  s = strchr(s, '.');
  if ( s == NULL ) {
    return NULL;
  }
  s++;

  return StringCopy(s);
}
