CC = gcc
CC_FLAGS = -g -pedantic -Wall -W -std=c99
FILES = main.c node.c rental.c sort.c 
OUT_EXE = Assign1 

build: $(FILES)
	$(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES) 

clean:
	rm -f *.o core *.exe *~ *.out *.stackdump

rebuild: clean build
