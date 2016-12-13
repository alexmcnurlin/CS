#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

int game(int);

int main()
{
  int clientF, serverL, outcome;
  struct sockaddr_un SA;
  struct sockaddr *serverSAPtr;
  char message[1];
  char sreply[64], sreply2[128], cr[32], pr[32];
  int gamecount;

  serverL = sizeof (SA);
  clientF = socket(AF_UNIX, SOCK_STREAM, 0);
  SA.sun_family = AF_UNIX;
  strcpy(SA.sun_path, "sup");
  serverSAPtr = (struct sockaddr*) &SA;

  do
    {
      outcome = connect(clientF, serverSAPtr, serverL);
      if(outcome == -1)
        sleep(1);
    }while(outcome == -1);

  gamecount = 0;
  while(1)
    {
      printf("Choose your weapon... r(ROCK), p(PAPER), or s(scissors): ");
      scanf("%s", message);

      if(message[0] == 'q' || message[0] == '\n' || message[0] == 'r' || message[0] == 's' || message[0] ==\
         'p')
        {
          if(message[0] == 'q')
            {
              printf("Exiting...");
              break;
            }
          if(message[0] == '\n')
            continue;
          if(send(clientF, message, strlen(message)+1, 0) < 0)
            {
              printf("Error");
              return 0;
            }
          //      printf                                                                                         
          read(clientF, sreply, 64);
          printf("%s", sreply);
          read(clientF, sreply2, 128);
          printf("%s", sreply2);
        }
    }
  close(clientF);
  return 0;
}
