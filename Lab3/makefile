CC = gcc
CC_FLAGS = -g -pedantic -Wall -W -std=c99

FILES = lab3b.c 
OUT_EXE = lab3b

build: $(FILES)
	$(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES) 

build-3a: $(FILES)
	$(CC) $(CC_FLAGS) -o lab3a lab3a.c
clean:
	rm -f *.o core *.exe *~ *.out *.stackdump

rebuild: clean build
