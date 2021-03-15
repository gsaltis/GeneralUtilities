/*****************************************************************************!
 * Function : FileGetBaseFilename
 * Purpose  : Return just the base part of name w/o the directory or suffix
 *****************************************************************************/
string
FileGetBaseFilename
(string InFilename)
{
  int					m;
  string				suffixStart, baseStart;
  
  baseStart = strrchr(InFilename, '/');
  if ( NULL == baseStart ) {
    baseStart = InFilename;
  } else {
    baseStart++;
  }
  suffixStart = strchr(baseStart, '.');
  if ( suffixStart == NULL ) {
    return StringCopy(baseStart);
  }
  m = suffixStart - baseStart;
  return StringNCopy(baseStart, m); 
}
