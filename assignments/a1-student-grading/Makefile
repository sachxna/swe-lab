CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
TARGET = student_system

SRC = src/main.c src/parser.c src/validation.c src/computation.c src/report.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) data/output.txt

run: $(TARGET)
	./$(TARGET)
