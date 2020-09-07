/*****************************************************************************!
 * Function : FilenameExtractSuffix
 *****************************************************************************/
string
FilenameExtractSuffix
(string InFilename)
{
  string 								s;

  if ( NULL == InFilename ) {
	return NULL;
  }

  // The entire string is a suffix (e.g., .bashrc)
  if ( *InFilename == '.' ) {
    return StringCopy(InFilename);
  }

  // Find the first occurance of a '.'
  s = strchr(InFilename, '.');
  if ( NULL == s ) {
	return NULL;
  }

  // Skip the first non '.' character (if there is one)
  while (*s  && *s == '.' ) {
    s++;
  }

  // We did not find a suffix
  if ( *s == 0x00 ) {
	return NULL;
  }

  // Found the suffix, copy and return it;
  return StringCopy(s);
}
