#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define DEFAULT_PROTOCOL 0


int play_game(int cleintFd);
struct game* lookup_game(int game_num);

int main() {
  // Create socket
  int serverFd, clientFd, serverLen, clientLen;
  struct sockaddr_un serverUNIXAddress;
  struct sockaddr_un clientUNIXAddress;
  struct sockaddr* serverSockAddrPtr;
  struct sockaddr* clientSockAddrPtr;

  signal(SIGCHLD, SIG_IGN);

  serverSockAddrPtr = (struct sockaddr*) &serverUNIXAddress;
  serverLen = sizeof(serverUNIXAddress);

  clientSockAddrPtr = (struct sockaddr*) &clientUNIXAddress;
  clientLen = sizeof(serverUNIXAddress);

  serverFd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
  serverUNIXAddress.sun_family = AF_UNIX;
  strcpy(serverUNIXAddress.sun_path, "Fred");
  unlink("Fred");
  bind(serverFd, serverSockAddrPtr, serverLen);
  listen(serverFd, 5);

  printf("Starting Server...\n");

  while (1) {
    // Wait for connection
    clientFd = accept(serverFd, clientSockAddrPtr, &clientLen);
    printf("Accepting Client\n");

    // Fork to process connection
    if (fork() == 0) {
      play_game(clientFd);
      close (clientFd);
      exit(0);
    } else {
      close (clientFd);
    }
  }
}


int play_game(int clientFd) {
  char message[1] , client_reply[10], reply[100], client_move, player_move, computer_move;
  int game_num = 0, computer_wins = 0, player_wins = 0;
  
  // Loop until the connection is closed by client
  while (1) {
    if (recv(clientFd, client_reply, 2000, 0) < 0) {
      puts("recv failed");
      break;
    }

    // Parse the clients input
    player_move = client_reply[1];
    computer_move = client_reply[0];

    // Quitting
    if (client_reply[1] == 'q') {
      printf("Quitting...\n");
      return 0;
    }

    // Process moves
    game_num++;
    switch (computer_move) {
      case 'r': // Rock
	switch (player_move) {
	  case 'r':
	    strcpy(reply, "Tie!                                 \0");
	    break;
	  case 'p':
	    strcpy(reply, "Paper covers rock. Player wins!      \0");
	    player_wins++;
	    break;
	  case 's':
	    strcpy(reply, "Rock crushes scissors. Computer wins!\0");
	    computer_wins++;
	    break;
	};
	break;
      case 'p': // Paper
	switch (player_move) {
	  case 'r':
	    strcpy(reply, "Paper covers rock. Computer wins!    \0");
	    computer_wins++;
	    break;
	  case 'p':
	    strcpy(reply, "Tie!                                 \0");
	    break;
	  case 's':
	    strcpy(reply, "Scissors cuts paper. Player wins!    \0");
	    player_wins++;
	    break;
	};
	break;
      case 's': // Scissors
	switch (player_move) {
	  case 'r':
	    strcpy(reply, "Rock crushes scissors. Player wins!  \0");
	    player_wins++;
	    break;
	  case 'p':
	    strcpy(reply, "Scissors cuts paper. Computer wins!  \0");
	    computer_wins++;
	    break;
	  case 's':
	    strcpy(reply, "Tie!                                 \0");
	    break;
	};
	break;
    }

    // Return results to client
    char reply_to_client[100];
    sprintf(reply_to_client,"Game %i: %s Score: s: %i, c: %i\n", game_num, reply, computer_wins, player_wins);
    send(clientFd , reply_to_client, strlen(reply_to_client)+1, 0);
  }
}
