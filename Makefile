CC = gcc 

CFLAGS = -Wall -Wextra -g 

src = main.c scanner.c testScanner.c

OBJ = $(src:.c=.o) 

EXE = P1

all: $(EXE) 

$(EXE): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJ) $(EXE) 
