CC = gcc
CFLAGS = -Wall -Wextra

SRC = main.c user.c account.c transaction.c ui.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = sikka

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)
