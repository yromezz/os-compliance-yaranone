CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread
TARGET = producer_consumer
SRC = producer_consumer.c

all: $(TARGET)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean