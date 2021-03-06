# Declaration of variables
CC = gcc
CC_FLAGS = -Wall
 
# File names
EXEC = main
ALL_SOURCES = $(wildcard *.c)
SOURCES = $(filter-out btfile.c, $(ALL_SOURCES))
OBJECTS = $(SOURCES:.c=.o)
LIBS = -Ibt/inc -Lbt/lib -lbt -D_FILE_OFFSET_BITS=64 -lncurses

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LIBS)
 
# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@ $(LIBS)
 
data: btfile.c
	$(CC) -o btfile btfile.c $(LIBS)
# To remove generated files
clean:
	rm -f $(EXEC) *.o