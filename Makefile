CC = gcc
CFLAGS = -Wall -g
OBJ = main.o readr.o
EXE = AOCBase
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(EXE) $(OBJ)