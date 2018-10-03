# Makefile for md5

TARGET=md5
OBJS=md5.o md5_bmark.o
CFLAGS=-O0 -g -D_GNU_SOURCE -std=c99 -pg
LDFLAGS= -fopenmp
CC=gcc

all: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET) -fopenmp

%.o : %.c
	$(CC) $(CFLAGS) -c $< -fopenmp

clean:
	rm -f *.o $(TARGET) output.txt
