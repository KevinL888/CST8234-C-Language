CC = gcc
CC_FLAGS = -g -pedantic -Wall -W -std=c99 -D_POSIX_SOURCE -Wno-unused-parameter
FILES = main.c parent.c child.c 
OUT_EXE = Assign2 

build: $(FILES)
	$(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES) 

clean:
	rm -f *.o core *.exe *~ *.out *.stackdump

rebuild: clean build
