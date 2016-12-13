#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

void RPSgame(int);

int main()
{
  int serverFd, clientFd, serverL, clientL;
  struct sockaddr_un SA;
  struct sockaddr_un CA;
  struct sockaddr *serverSAPtr;
  struct sockaddr *clientSAPtr;

  signal (SIGCHLD, SIG_IGN);

  serverSAPtr = (struct sockaddr*) &SA;
  serverL = sizeof (SA);
  clientSAPtr = (struct sockaddr*) &CA;
  clientL = sizeof (CA);

  serverFd = socket (AF_UNIX, SOCK_STREAM, 0);
  SA.sun_family = AF_UNIX;
  strcpy (SA.sun_path, "sup");
  unlink ("sup");
  bind (serverFd, serverSAPtr, serverL);
  listen (serverFd, 5);

  while(1)
    {
      clientFd = accept (serverFd, clientSAPtr, &clientL);
      if(fork() == 0)
        {
          printf("Connecting to client\n");
          RPSgame(clientFd);
          close(clientFd);
          return 0;
        }
      else
        close(clientFd);
  }
}

void RPSgame(int fd)
{
  char choice;
  char message[1];
  char creply[64];
  int computerschoice;
  int playw = 0;
  int compw = 0;
  int gamec = 0;
  char playstring[32];
  char compstring[32];
  char my_message[128];


  while(1)
    {
      gamec++;
      computerschoice = rand()%3+1;

      if(recv(fd, message, 2, 0) < 0)
        {
          puts("recv failed");
          break;
        }
      if(message[0] == 'q')
        {
          puts("Thanks for playing, exiting.\n");
          exit(0);
        }
      choice = message[0];

      switch(message[0]) //rock = 1, scissors = 2, paper = 3                                                           
        {
        case 'r':
          if(computerschoice == 1)
            {
              sprintf(creply, "Rock against Rock... Tie!\n");
              write(fd, creply, strlen(creply)+1);
            }
          else if(computerschoice == 2)
            {
              playw++;
              sprintf(creply, "Rock against Scissors... Player Wins!\n");
              write(fd, creply, strlen(creply)+1);
            }
          else
            {
              compw++;
              sprintf(creply, "Rock against Paper... Computer Wins...\n");
              write(fd, creply, strlen(creply)+1);
            }
          break;
        case 's':
          if(computerschoice == 1)
            {
              compw++;
              sprintf(creply, "Scissors against Rock... Computer Wins...\n");
              write(fd, creply, strlen(creply)+1);
            }
          else if(computerschoice == 2)
            {
              sprintf(creply, "Scissors against Scissors... Tie!\n");
              write(fd, creply, strlen(creply)+1);
            }
          else
            {
              playw++;
              sprintf(creply, "Scissors against Paper... Player Wins!\n");
              write(fd, creply, strlen(creply)+1);
            }
          break;
        case 'p':
          if(computerschoice == 1)
            {
              playw++;
              sprintf(creply, "Paper against Rock... Player Wins!\n");
              write(fd, creply, strlen(creply)+1);
            }
          else if(computerschoice == 2)
            {
              compw++;
              sprintf(creply, "Paper against Scissors... Computer Wins...\n");
              write(fd, creply, strlen(creply)+1);
            }
          else
            {
              sprintf(creply, "Paper against Paper... Tie!\n");
              write(fd, creply, strlen(creply)+1);
            }
          break;
        }
      sprintf(my_message, "Player wins: %d, Server wins: %d\n", playw, compw);
      puts(my_message);
      write(fd, my_message, strlen(my_message));
    }
}
