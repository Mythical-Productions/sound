CC=gcc

.PHONY: all
all: seq sender

seq: seq.o
	$(CC) -o $@ $< -lasound

sender: sender.o
	$(CC) -o $@ $< -lasound

%.o: %.c
	$(CC) -c -o $@ $< -Wall -Werror
