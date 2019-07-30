#- MM scan source file and makes depends for user made h files


TARGET = disp1
#SOURCES = $(sildcards *.c)
SOURCES = $(TARGET).c ../../channel/channel.c ../../../msgQ/msgQ.c ../../dispatcher/dispatch.c ../../cdr/cdr.c ../../operator/operator.c ../../ops_container/ops_container.c ../../../../advancedC/ds/sHash/sHashMap.c ../../../../advancedC/ds/dlist/dlist.c ../../../../advancedC/ds/dlist/list_functions.c ../../../mutex/mutex.c
SOURCES += ../../subscriber/sub.c ../../subs_container/subs_container.c
OBJECTS = $(SOURCES:.c=.o)

INC_DIR = ../../include/ ../../../../advancedC/ds/include/ ../../../include/
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
