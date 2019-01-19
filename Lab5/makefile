CC = gcc
CC_FLAGS = -g -pedantic -Wall -W -std=c99
FILES = lab5.c rental.c sort.c parse.c
OUT_EXE = lab5 

build: $(FILES)
	$(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES) 

clean:
	rm -f *.o core *.exe *~ *.out *.stackdump

rebuild: clean build
