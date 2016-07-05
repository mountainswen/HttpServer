CC=gcc
CFLAGS=-Wall

all:main

main:main.c request.c
	$(CC) $(CFLAGS) main.c request.c -o main	
