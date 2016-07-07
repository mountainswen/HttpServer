CC=gcc
CFLAGS=-Wall

all:main

main:main.c request.c response.c
	$(CC) $(CFLAGS) main.c request.c response.c -o main	
