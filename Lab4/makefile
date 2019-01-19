CC = gcc
CC_FLAGS = -g -pedantic -Wall -W -std=c99
FILES = lab4.c 
OUT_EXE = lab4 

build: $(FILES)
	$(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES) 

clean:
	rm -f *.o core *.exe *~ *.out *.stackdump

rebuild: clean build
