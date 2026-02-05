CC = gcc
CFLAGS = -Wall -pthread


all: deadlock solucao

deadlock: cenario_deadlock.c
	$(CC) $(CFLAGS) cenario_deadlock.c -o deadlock

solucao: jantar_filosofos.c
	$(CC) $(CFLAGS) jantar_filosofos.c -o solucao

clean:
	rm -f deadlock solucao
