CC					= gcc
LIB					= ar
INSTALL					= cp

CC_FLAGS				= -g -Wall -c -DNEED_FILE_UTILS_TAR_FILE_C
LIB_FLAGS				= r

INSTALL_DIR_LIBS			= /usr/local/lib
INSTALL_DIR_HEADERS			= /usr/local/include

TARGET					= libutils.a
TEST_TARGET				= UnitTest
TEST_SOURCE				= $(TEST_TARGET).c

OBJS					= $(sort json.o StringUtils.o JSONIF.o JSONOut.o FileUtils.o NumericTypes.o BytesManage.o MemoryManager.o)

HEADERS					= FileUtils.h StringUtils.h ANSIColors.h BytesManage.h \
					  JSONIF.h MemoryManager.h NumericTypes.h json.h ascii.h JSONOut.h \

%.o					: %.c
					  @echo [CC] $<
					  @$(CC) $(CC_FLAGS) $<

all					: $(TARGET) $(TEST_TARGET)

$(TARGET)				: $(OBJS)
					  @echo [LI] $(TARGET)
					  @$(LIB) $(LIB_FLAGS) $(TARGET) $(OBJS)

$(TEST_TARGET)				: $(TEST_SOURCE) $(TARGET)
				          @echo [LD] $(TEST_TARGET)
					  $(CC) -g $(TEST_SOURCE) -o $(TEST_TARGET) -L.  -lutils

install					: $(TARGET)
					  $(INSTALL) $(TARGET) $(INSTALL_DIR_LIBS)
					  $(INSTALL) $(HEADERS) $(INSTALL_DIR_HEADERS)

include					  depends.mk

clean					:
					  rm -rf $(wildcard *.o *.a)

junkclean				:
					  rm -rf $(wildcard *~)

