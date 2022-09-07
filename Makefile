CC=clang
CXX=clang

.PHONY: all
all: seq sender reflect

reflect: reflect.o
	$(CC) -o $@ $< -lasound

seq: seq.o
	$(CC) -o $@ $< -lasound

sender: sender.o
	$(CC) -o $@ $< -lasound

%.o: %.c
	$(CC) -c -o $@ $< -Wall -Werror

%.o: %.cc
	$(CXX) -c -o $@ $< -Wall -Werror

