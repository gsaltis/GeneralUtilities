/*****************************************************************************!
 * Function : FileGetFileSuffix
 *****************************************************************************/
string
FileGetFileSuffix
(string InFilename)
{
  string				s;
  int					i, n;

  if ( NULL == InFilename ) {
    return NULL;
  }

  n = strlen(InFilename);

  for (i = n - 1 ; i >= 0 ; i-- ) {
    if ( InFilename[i] == '.' ) {
      break;
    } 
  }
  if ( i < 0 ) {
    return NULL;
  }
  i++;
  s = InFilename + i;

  return StringCopy(s);
}
