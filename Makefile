CC = gcc
CFLAGS = -Wall -g
SRC = main.c env.c commands.c
HEADERS = env.h commands.h
OBJ = $(SRC:.c=.o)
EXEC = xsh

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

format:
	clang-format -i $(SRC) $(HEADERS)

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all format clean
