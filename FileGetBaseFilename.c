/*****************************************************************************!
 * Function : FileGetBaseFilename
 * Purpose  : Return just the base part of name w/o the directory or suffix
 *****************************************************************************/
string
FileGetBaseFilename
(string InFilename)
{
  int					i, n, m;
  int					filenameIndex;
  int					suffixIndex;
  string				s, s2;

  if ( NULL == InFilename ) {
    return NULL;
  }

  n = strlen(InFilename);

  suffixIndex = -1;
  filenameIndex = -1;

  for (i = n - 1; i >= 0 ; i-- ) {
    if ( InFilename[i] == '.' && suffixIndex == -1 ) {
      suffixIndex = i;
    } else if ( InFilename[i] == '/' && filenameIndex == -1 ) {
      filenameIndex = i + 1;
    }
    if ( suffixIndex > -1 && filenameIndex > -1 ) {
      break;
    }
  }
  if ( suffixIndex < 0 ) {
    suffixIndex = n;
  }
  if ( filenameIndex < 0 ) {
    filenameIndex = 0;
  }
  
  if ( suffixIndex <= filenameIndex ) {
    suffixIndex = n - 1;
  }

  if ( filenameIndex == n - 1 ) {
    return NULL;
  }

  m = suffixIndex - filenameIndex;
  s = InFilename + filenameIndex;
  s2 = StringNCopy(s, m);

  return s2;
}
