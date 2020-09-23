server: server/main.o 
	gcc server/main.c -o server/main.o

client: client/main.c
	gcc client/main.c -o client/main.o

run: client server