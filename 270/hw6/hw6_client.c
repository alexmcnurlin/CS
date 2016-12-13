#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
  int sock, random, game_num = 0;
	struct sockaddr_un serverUNIXAddress;
	char message[10] = "Hello", server_reply[100], player_move[1], comp_move;
	 
	//Create socket
	sock = socket(AF_UNIX , SOCK_STREAM , 0);
	if (sock == -1)
	{
			printf("Could not create socket");
	}
	puts("Socket created");
	 
  serverUNIXAddress.sun_family = AF_UNIX;
  strcpy (serverUNIXAddress.sun_path, "Fred");

	 
	//Connect to remote server
	while (connect(sock ,(struct sockaddr *)&serverUNIXAddress ,sizeof(serverUNIXAddress)) < 0) {
		printf("Couldn't connect to server\n");
		sleep(1);
	}
	puts("Connected\n");
	 
	//keep communicating with server
	while(1) {

		// Get user input
		printf("Enter move: ");
		ENTER_MESSAGE:
		scanf("%c" , player_move);
		// Parse input
		// Check for invalid character
		if (!(player_move[0] == 'r' || player_move[0] == 'p' ||  player_move[0] == 's' || player_move[0] == 'q' || player_move[0] == '\n')) {
			printf("Invalid character! Try again\n");
			printf("Enter move: ");
			goto ENTER_MESSAGE;
		// do nothing if newline
		} else if (player_move[0] == '\n') {
			goto ENTER_MESSAGE;
		}

		//Generage computer move
		random = rand() % 3;
		char moves[] = "rps";
		comp_move = moves[random];

		sprintf(message, "%c%c%i", comp_move, player_move[0], ++game_num);

		//Send some data
		if (send(sock , message , strlen(message) , 0) < 0) {
			puts("Send failed");
			return 1;
		}

		if (message[1] == 'q') {
			printf("Quitting...\n");
			break;
		}
		 
		//Receive a reply from the server
		if (recv(sock , server_reply , 2000 , 0) < 0) {
			puts("recv failed");
			break;
		}
		 
		printf("%s", server_reply);
	}

	close(sock);
	return 0;
}
