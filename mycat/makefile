CC=gcc
CFLAGS=-std=c11 -Wall -O -g
LDLIBS=-lm

TARGET=mycat

SOURCES=mycat.c

OBJECTS=$(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c mycat.h
	$(CC) $(CFLAGS) -c $< -o $@


