all: hw6_server.o hw6_client.o
	gcc -g hw6_server.o -o hw6_server
	gcc -g hw6_client.o -o hw6_client

hw6_client.o: hw6_client.c
	gcc -c hw6_client.c

hw6_server.o: hw6_server.c
	gcc -c hw6_server.c


test: hw6_server_new.o hw6_client_new.o
	gcc -g hw6_server_new.o -o hw6_server
	gcc -g hw6_client_new.o -o hw6_client

hw6_client_new.o: hw6_client_new.c
	gcc -c hw6_client_new.c

hw6_server_new.o: hw6_server_new.c
	gcc -c hw6_server_new.c
