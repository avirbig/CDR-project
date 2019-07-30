#- MM scan source file and makes depends for user made h files


TARGET = fileMonitor
#SOURCES = $(wildcards *.c)
SOURCES = $(TARGET).c  newfm.c ../channel/channel.c  ../../msgQ/msgQ.c
OBJECTS = $(SOURCES:.c=.o)

INC_DIR = ../include/ ../../include/
#LIB_DIR = ../lib
# compiler and linker flags
CC		 =gcc
CPPFLAGS = $(addprefix -I,$(INC_DIR))
CFLAGS   = -g -pedantic -Wall -Werror 
LDFLAGS  = -g -pthread
#LDFLAGS +=  $(addprefix -L,$(LIB_DIR))
	
.PHONY: all clean run

all: $(TARGET) 

$(TARGET): $(OBJECTS) 

include depends

depends: $(SOURCES)
	$(CC) -MM $(CPPFLAGS) $^ > depends

clean:
	rm -f $(TARGET) $(OBJECTS) depends 

run:
	./$(TARGET) 
