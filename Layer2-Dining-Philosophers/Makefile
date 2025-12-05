CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread
TARGET = dining_philosophers
SRC = dining_philosophers.c


all: $(TARGET)


$(TARGET): $(SRC)
$(CC) $(CFLAGS) $(SRC) -o $(TARGET)


clean:
rm -f $(TARGET) *.o


.PHONY: all clean