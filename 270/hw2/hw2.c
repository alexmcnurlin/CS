// Alex McNurlin
// CS270 HW2
// hw2.c
// Due 9/26/16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int makearg(char* s, char*** args);

int main() {
  // The maximum size of command that a user can enter
  const int INPUT_SIZE = 256;
  char input[INPUT_SIZE]; 

  // Get user input
  printf("Please enter a command (limit to 256 characters)\n");
  fgets(input, INPUT_SIZE, stdin);

  // Initialize array stuff
  char** argv;
  int argc;

  argc = makearg(input, &argv);

  // Print arguments of array
  for (int i=0; i<argc; i++) {
    printf("Argument %i: %s\n", i+1, argv[i]);
  }
}

int makearg(char *s, char ***args) {
  const int ARR_SIZE = 10;
  //char **p = (char**)malloc(ARR_SIZE*sizeof(char**));

  // Allocate space with this bizarre command
  // p will eventually be assigned to args as our output
  char** p = (char**)malloc(ARR_SIZE*sizeof(char**));

  int i=0;
  // Break the string into tokens, and assign them to the pointer p
  char* token = strtok(s, " ");
  while (token != NULL) {
    // If the token is a space, then skip this loop and continue
    // If the number of arguments is greater than ARR_SIZE, exit with an error
    if (i>=ARR_SIZE) {
      printf("Error, this function can only accept %i arguments\nExiting...", ARR_SIZE);
      return -1;
    }
    p[i] = token;
    token = strtok(NULL, " ");
    i++;
  }

  // Sets our array that's been built to be returned, as well as returning the length of the array
  *args = p;
  return i;
}
