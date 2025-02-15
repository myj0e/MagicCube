CC = gcc
FLAGS = -Wall -Wextra -Werror -g
OBJ = main.o cube.o present.o
OUT = mc

.PHONY: all clean

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(OUT)

%.o: %.c
	$(CC) $(FLAGS) -c $<

clean:
	rm -f $(OBJ) $(OUT)