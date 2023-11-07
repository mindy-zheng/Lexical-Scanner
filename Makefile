CC = g++ 
CLAGS = -std=c++11 -Wall

SRC = scanner.cpp testScanner.cpp main.c

OBJ = $(SRC:.c=.o) 

EXE = P1

all: $(EXE) 

scanner.o: scanner.cpp scanner.h token.h
	$(CC) $(CFLAGS) -c scanner.c

testScanner.o: testScanner.cpp testScanner.h scanner.h token.h
	$(CC) $(CFLAGS) -c testScanner.c

main.o: main.cpp scanner.h token.h
	$(CC) $(CFLAGS) -c main.c

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) $(EXE)
