// Alex McNurlin
// HW1
// 10/14/16
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Error: Invalid number of arguments\n");
    printf("Exiting...\n");
    exit(1);
  }
  char file_to_open[256];
  strcpy(file_to_open, argv[1]);
  FILE *fp;
  fp = fopen(file_to_open, "r");

  char ch;

  while((ch = getc(fp)) != EOF) {
    printf("%c", ch);
  }
  /* char temp_char[1]; */
  /* do { */
  /*   fscanf(fp, "%c1", temp_char); */
  /*   printf("%s", temp_char); */
  /* } while (temp_char != NULL); */
  //strcpy(temp_char, "Hello World");

  fclose(fp);
}
