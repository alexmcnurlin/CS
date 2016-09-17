// Alex McNurlin
// HW1
// 10/14/16
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_alpha(       char ch1);
int is_number(      char ch1);
int is_comment(     char ch1,char ch2);
int is_string(      char ch1);
int is_char(        char ch1);
int is_operator(    char ch1,char ch2);

int mark_as_unknown(char ch1,char ch2, FILE *fp);
int get_keyword(    char *ch1,char *ch2, FILE *fp);
int get_operator(   char *ch1,char *ch2, FILE *fp);
int get_char(       char *ch1,          FILE *fp);
int get_number(     char *ch1,char *ch2, FILE *fp);
int get_comment(    char *ch1,char *ch2, FILE *fp);
int get_string(     char *ch1,char *ch2, FILE *fp);


int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Error: Invalid number of arguments\n");
    printf("Exiting...\n");
    exit(1);
  }

  FILE *fp;
  fp = fopen(argv[1], "r");
  if (fp == 0) {
    printf("Error: filename invalid\n");
    printf("Exiting...\n");
    exit(1);
  }

  char ch1=1, ch2=getc(fp);

  while ((ch1 = ch2) && (ch2 = getc(fp)) != EOF) {
    if (ch1 == ' ' || ch1 == '\n' || ch1 == '\t') {
      continue;
    } else if (is_alpha(ch1)) {
      get_keyword(&ch1,&ch2, fp);
    } else if (is_number(ch1)) {
      get_number(&ch1,&ch2, fp);
    } else if (is_comment(ch1,ch2)) {
      get_comment(&ch1,&ch2, fp);
    } else if (is_string(ch1)) {
      get_string(&ch1,&ch2, fp);
    } else if (is_char(ch1)) {
      get_char(&ch1, fp);
    } else if (is_operator(ch1,ch2)) {
      get_operator(&ch1,&ch2, fp);
    } else {
      mark_as_unknown(ch1,ch2, fp);
    }

    printf("\n");
    
  }
  /* char temp_char[1]; */
  /* do { */
  /*   fscanf(fp, "%c1", temp_char); */
  /*   printf("%s", temp_char); */
  /* } while (temp_char != NULL); */
  //strcpy(temp_char, "Hello World");

  fclose(fp);
}

int is_alpha(char ch1) {
  if ((ch1 >= 'a' && ch1 <= 'z') 
      || (ch1 >= 'A' && ch1 <= 'Z') 
      || ch1 == '_') {
    return 1;
  } else {
    return 0;
  }
}

// Checks if ch1 is an ascii number character
int is_number(char ch1) {
  if (ch1 >= '0' && ch1 <= '9') {
    return 1;
  } else {
    return 0;
  }
}

int is_comment(char ch1,char ch2) {
  if (ch1 == '/' && ch2 == '*') {
    return 1;
  } else {
    return 0;
  }
}

int is_string(char ch1) {
  if (ch1 == '"') {
    return 1;
  } else {
    return 0;
  }
}

int is_char(char ch1) {
  if (ch1 == '\'') {
    return 1;
  } else {
    return 0;
  }
}

int is_operator(char ch1,char ch2) {
  switch (ch1) {
    case '.':
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '|':
    case '&':
    case ';':
    case '[':
    case ']':
    case '<':
    case '>':
    case '=':
    case ':':
      return 1;
      break;
    case '!':
      if (ch2 == '=') {
        return 1;
      }
      break;
  }
  return 0;
}

int mark_as_unknown(char ch1,char ch2, FILE *fp) {
}

int get_keyword(char *ch1,char *ch2, FILE *fp) {
  char the_string[256];
  //char ch3, ch4;

  //printf("%c%c (ch1 and ch2)\n", *ch1, *ch2);

  /* ch3 = getc(fp); */
  /* ch4 = getc(fp); */
  /* fseek(fp, -2, SEEK_CUR); */
  /* printf("%c%c (char beginning)\n", ch3, ch4); */

  // Rewind the file to the character represented by ch1, so fscanf will read
  // from the correct spot
  fseek(fp, -2, SEEK_CUR);

  //ch3 = getc(fp);
  //fseek(fp, -1, SEEK_CUR);
  //printf("%c (after seek)\n", ch3);

  fscanf(fp, "%[a-zA-Z_0-9]*", the_string);

  // Set ch1 and ch2 to be the correct values after reading file
  fseek(fp, -1, SEEK_CUR);
  *ch1 = getc(fp);
  *ch2 = getc(fp);
  fseek(fp, -1, SEEK_CUR);

  //printf("%c%c (ch1, ch2 after scan)\n", *ch1, *ch2);

  //printf("%s (string in question)\n", the_string);

  /* ch3 = getc(fp); */
  /* fseek(fp, -1, SEEK_CUR); */
  /* printf("%c (after scan)\n", ch3); */

  // Compare the_string with the list of keywords
  char* keywords[] = { "accessor", "and", "array", "begin", "bool", "case", 
                        "else", "elsif", "end", "exit", "function", "if", "in", 
                        "integer", "interface", "is", "loop", "module", 
                        "mutator", "natural", "null", "of", "or", "others", 
                        "out", "positive", "procedure", "return", "struct", 
                        "subtype", "then", "type", "when", "while"};
  int keywords_size = sizeof(keywords)/sizeof(keywords[0]);
  for (int i=0; i<keywords_size; i++) {
    if (strcmp(the_string,keywords[i]) == 0) {
      // It's a keyword
      printf("%s (keyword)\n", the_string);
      return 0;
    }
  }

  // If it's not a keyword, then it's an identifier
  printf("%s (identifier)\n", the_string);
  return 0;
}

int get_operator(char *ch1,char *ch2, FILE *fp) {
  printf("%c%c (operator)\n", *ch1, *ch2);
}

int get_char(char *ch1, FILE *fp) {
  fseek(fp, -2, SEEK_CUR);
  char the_char[4];
  fscanf(fp, "%2c", the_char);
  fseek(fp, -1, SEEK_CUR);
  printf("%s (character literal)\n", the_char);
}

int get_number(char *ch1,char *ch2, FILE *fp) {
  printf("It's a number!\n");
  return 0;
}

int get_comment(char *ch1,char *ch2, FILE *fp) {
}

int get_string(char *ch1,char *ch2, FILE *fp) {
  char the_string[256];
  fseek(fp, -2, SEEK_CUR);
  fscanf(fp, "\"%[^\"]*\"", the_string);
  fseek(fp, 2, SEEK_CUR);

  printf("\"%s\" (string)\n", the_string);
  return 0;
}
