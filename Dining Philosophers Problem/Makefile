CC = gcc
CFLAGS = -Wall -Wextra -O3 -pthread -g
INCLUDES = -I.

TARGET = filosofi_sem.out

all: $(TARGET)

$(TARGET): filosofi_sem.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) filosofi_sem.c

clean:
	rm -f *.out