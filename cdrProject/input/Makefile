#- MM scan source file and makes depends for user made h files


TARGET = fmtest1
#SOURCES = $(wildcards *.c)
SOURCES = $(TARGET).c ../../fm/fm.c ../../channel/channel.c ../../fr/fr.c ../../../msgQ/msgQ.c
OBJECTS = $(SOURCES:.c=.o)

INC_DIR = ../../include/ ../../../include/
#LIB_DIR = ../lib
# compiler and linker flags
CC		 =gcc
CPPFLAGS = $(addprefix -I,$(INC_DIR))
CFLAGS   = -g -pedantic -Wall -Werror 
LDFLAGS  = -g 
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
