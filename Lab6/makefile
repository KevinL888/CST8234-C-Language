CC = gcc
CC_FLAGS = -g -pedantic -Wall -W -std=c99
FILES = lab6.c rental.c sort.c parse.c file.c
OUT_EXE = lab6 

build: $(FILES)
	$(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES) 

clean:
	rm -f *.o core *.exe *~ *.out *.stackdump

rebuild: clean build
