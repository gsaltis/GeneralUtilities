CC					= gcc
LIB					= ar
INSTALL					= cp

CC_FLAGS				= -g -Wall -c
LIB_FLAGS				= r

INSTALL_DIR_LIBS			= /usr/local/lib
INSTALL_DIR_HEADERS			= /usr/local/include

TARGET					= libutils.a

OBJS					= $(sort json.o StringUtils.o JSONIF.o JSONOut.o FileUtils.o NumericTypes.o BytesManage.o MemoryManager.o)

HEADERS					= FileUtils.h StringUtils.h ANSIColors.h BytesManage.h \
					  JSONIF.h MemoryManager.h NumericTypes.h json.h ascii.h \

%.o					: %.c
					  @echo [CC] $<
					  @$(CC) $(CC_FLAGS) $<

$(TARGET)				: $(OBJS)
					  @echo [LI] $(TARGET)
					  @$(LIB) $(LIB_FLAGS) $(TARGET) $(OBJS)

install					: $(TARGET)
					  $(INSTALL) $(TARGET) $(INSTALL_DIR_LIBS)
					  $(INSTALL) $(HEADERS) $(INSTALL_DIR_HEADERS)

include					  depends.mk

clean					:
					  rm -rf $(wildcard *.o *.a)

junkclean				:
					  rm -rf $(wildcard *~)

