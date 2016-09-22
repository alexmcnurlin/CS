// Alex McNurlin
// CS270 HW2
// hw2.c
// Due 9/26/16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int makearg(char* s, char*** args);

int main() {
  const int INPUT_SIZE = 256;
  //char input[INPUT_SIZE]; 
  char input[] = "ls -lash /home/alexmcnurlin/";
  printf("Please enter a command\n");
  int length = sizeof(input)/sizeof(input[0]);
  printf("%s\n", input);

  char **argv;
  makearg(input, &argv);

  int i=0;
  int length = sizeof(argv)/sizeof(argv[0]);
  while (i<length) {
    printf("%s\n", argv[i]);
    i++;
  }
}

int makearg(char *s, char ***args) {
  //int length = sizeof(s)/sizeof(s[0]);
  //char *testParse = s;
  //  printf("%i ", length);
  //int i = 0;
  //while (i != '\000') {
  //  printf("%i ", i);
  //  //printf("%c", s[i]);
  //  i++;
  //}

  const int ARR_SIZE = 10;
  
  char **p = (char**)malloc(ARR_SIZE*sizeof(char**));
  char *token = strtok(s, " ");
  while (token != NULL) {
    //printf("%s\n", token);
    token = strtok(NULL, " ");
  }

  args = &p;
}
