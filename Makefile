CC = gcc
CFLAGS = -Wall -Wextra -pedantic
TARGET = HelloWorld
SRC = HelloWorld.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
