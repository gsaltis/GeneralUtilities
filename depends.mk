BytesManage.o: BytesManage.c
FileGetBaseFilename.o: FileGetBaseFilename.c
FileGetFileDirectory.o: FileGetFileDirectory.c
FileGetFilename.o: FileGetFilename.c
FileGetFileSuffix.o: FileGetFileSuffix.c
FilenameExtractSuffix.o: FilenameExtractSuffix.c
FileUtils.o: FileUtils.c StringUtils.h MemoryManager.h ascii.h \
 FileUtilsOpen.c FilenameExtractSuffix.c FileUtilsCopyFile.c \
 FileUtilsTarFile.c FileGetFileDirectory.c FileGetFilename.c \
 FileGetBaseFilename.c FileGetFileSuffix.c
FileUtilsCopyFile.o: FileUtilsCopyFile.c
FileUtilsOpen.o: FileUtilsOpen.c
FileUtilsTarFile.o: FileUtilsTarFile.c
json.o: json.c json.h
JSONIF.o: JSONIF.c json.h StringUtils.h MemoryManager.h JSONIF.h
JSONOut.o: JSONOut.c JSONOut.h StringUtils.h MemoryManager.h
MemoryManager.o: MemoryManager.c MemoryManager.h
NumericTypes.o: NumericTypes.c
StringUtils.o: StringUtils.c StringUtils.h MemoryManager.h ascii.h
UnitTest.o: UnitTest.c StringUtils.h FileUtils.h MemoryManager.h
