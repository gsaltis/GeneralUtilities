CC					= gcc
LIB					= ar

CC_FLAGS				= -g -Wall -c
LIB_FLAGS				= r

TARGET					= libutils.a

OBJS					= $(sort String.o FileUtils.o NumericTypes.o BytesManage.o MemoryManager.o)

%.o					: %.c
					  @echo [CC] $<
					  @$(CC) $(CC_FLAGS) $<

$(TARGET)				: $(OBJS)
					  @echo [LI] $(TARGET)
					  @$(LIB) $(LIB_FLAGS) $(TARGET) $(OBJS)

include					  depends.mk

clean					:
					  rm -rf $(wildcard *.o *.a)

junkclean				:
					  rm -rf $(wildcard *~)

