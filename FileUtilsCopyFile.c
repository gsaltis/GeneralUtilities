/*****************************************************************************!
 * Function : FileUtilsCopyFile
 *****************************************************************************/
bool
FileUtilsCopyFile
(string InFromFilename, string InToFilename)
{
  FILE*									fileIn;
  FILE*									fileOut;
  struct stat							statbuf;
  char*									buffer;
  int									copyBufferSize;
  int									bytesToWrite;
  int									bytesRead;
  int									bytesWritten;
  int									fileSizeIn;

  if ( NULL == InFromFilename || NULL == InToFilename ) {
	return false;
  }

  fileIn = fopen(InFromFilename, "rb");
  if ( NULL == fileIn ) {
	return false;
  }
  
  // Trying opening the output file
  fileOut = fopen(InToFilename, "wb");
  if ( NULL == fileOut ) {
	// Close the file we already opened
	fclose(fileIn);
	return false;
  }

  // Get the from file stats
  stat(InFromFilename, &statbuf);

  // We need the file size
  fileSizeIn = statbuf.st_size;

  // Copy 128K bytes at time
  copyBufferSize = 128 * 1024;
  buffer = GetMemory(copyBufferSize);

  // While we have bytes left to copy
  while (fileSizeIn) {
	// Get number of bytes we read from one file and write to the other
    if ( fileSizeIn > copyBufferSize ) {
 	  bytesToWrite = copyBufferSize;
    } else {
	  bytesToWrite = fileSizeIn;
	}

	// Read the input file	
    bytesRead = fread(buffer, 1, bytesToWrite, fileIn);
	if ( bytesRead != bytesToWrite ) {
	  // The read failed somehow
	  fclose(fileIn);
	  fclose(fileOut);
	  unlink(InToFilename);
	  FreeMemory(buffer);
	  return false;
	}

 	// Write to the output buffer
    bytesWritten = fwrite(buffer, 1, bytesToWrite, fileOut);

	// The write failed 
	if ( bytesWritten != bytesToWrite ) {
	  fclose(fileIn);
	  fclose(fileOut);
	  unlink(InToFilename);
	  FreeMemory(buffer);
	  return false;
  	}
	// Adjust the remaining bytes to write
	fileSizeIn -= bytesToWrite;
  }
  FreeMemory(buffer);
  fclose(fileIn);
  fclose(fileOut);  
  return true;
}
