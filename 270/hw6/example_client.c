#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define DEFAULT_PROTOCOL 0

int main() {
  int clientFd, serverLen, result;
  struct sockaddr_un serverUNIXAddress;
  struct sockaddr* serverSockAddrPtr;

  serverSockAddrPtr = (struct sockaddr*) &serverUNIXAddress;
  serverLen = sizeof(serverUNIXAddress);

  clientFd = socket (AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
  serverUNIXAddress.sun_family = AF_UNIX;
  strcpy (serverUNIXAddress.sun_path, "recipe");

  do {
    result = connect(clientFd, serverSockAddrPtr, serverLen);
    if (result == -1) sleep(1);
  } while (result == -1);

  readRecipe (clientFd);
  close (clientFd);
  exit(0);
}
