// Alex McNurlin
// HW1 
// 10/14/16
//
//
// This program works by stepping through each character in the file
//   and checking if it is part of a keyword/number/comment (is_alpha, 
//   is_number, is_char, ect). When the type of token is found for the 
//   character, the character is passed to a function to find 
//   the entire token (get_keyword, get_number, get_comment, ect) and print
//   it to the screen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_alpha(       char ch1);
int is_number(      char ch1);
int is_comment(     char ch1,char ch2);
int is_string(      char ch1);
int is_char(        char ch1);
int is_operator(    char ch1,char ch2);

int get_keyword(    char *ch1,char *ch2, FILE *fp);
int get_operator(   char *ch1,char *ch2, FILE *fp);
int get_char(       char *ch1,char *ch2, FILE *fp);
int get_number(     char *ch1,char *ch2, FILE *fp);
int get_comment(    char *ch1,char *ch2, FILE *fp);
int get_string(     char *ch1,char *ch2, FILE *fp);


int main(int argc, char *argv[]) {
  // Checks for valid arguments
  if (argc != 2) {
    printf("Error: Invalid number of arguments\n");
    printf("Exiting...\n");
    exit(1);
  }

  // Open the given filename
  FILE *fp;
  fp = fopen(argv[1], "r");
  if (fp == 0) {
    printf("Error: filename invalid\n");
    printf("Exiting...\n");
    exit(1);
  }

  char ch1=1, ch2=getc(fp);

  // Iterate over every character in the file until EOF
  // ch1 is the character being looked at, while ch2 is the character after it
  //   in the file
  while ((ch1 = ch2) && (ch2 = getc(fp)) != EOF) {
    // Ignore whitespace
    if (ch1 == ' ' || ch1 == '\n' || ch1 == '\r' || ch1 == '\t') {
      continue;
    // Check which token is started by ch1. Some tokens (operators and comments)
    //   need 2 characters to identify, so ch2 is used as well
    } else if (is_alpha(ch1)) {
      get_keyword(&ch1,&ch2, fp);
    } else if (is_number(ch1)) {
      get_number(&ch1,&ch2, fp);
    } else if (is_comment(ch1,ch2)) {
      get_comment(&ch1,&ch2, fp);
    } else if (is_string(ch1)) {
      get_string(&ch1,&ch2, fp);
    } else if (is_char(ch1)) {
      get_char(&ch1,&ch2,fp);
    } else if (is_operator(ch1,ch2)) {
      get_operator(&ch1,&ch2, fp);
    }

  }

  // Close file. We're done here
  fclose(fp);
}

// A function to check if the given character is part of a keyword/identifier
//   All that is necessary for that is that it's alphabetic or an underscore
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

// A function to check if the given characters are part of a comment
//   This is only true when ch1 is / and ch2 is *
int is_comment(char ch1,char ch2) {
  if (ch1 == '/' && ch2 == '*') {
    return 1;
  } else {
    return 0;
  }
}

// A function to check if the given characters are part of a string
//   This is only true when ch1 is "
int is_string(char ch1) {
  if (ch1 == '"') {
    return 1;
  } else {
    return 0;
  }
}

// A function to check if the given characters are part of a character literal
//   This is only true when ch1 is '
int is_char(char ch1) {
  if (ch1 == '\'') {
    return 1;
  } else {
    return 0;
  }
}

// A function to check if the given characters are part of an operator
int is_operator(char ch1,char ch2) {
  switch (ch1) {
    case '.':
    case ',':
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

// A function that gets the word starting at ch1, then determines if it's an
//   identifier or keyword
int get_keyword(char *ch1,char *ch2, FILE *fp) {
  char the_string[256];
  // Rewind the file to the point in the file represented by ch1, so fscanf will read
  // from the correct spot
  fseek(fp, -2, SEEK_CUR);

  fscanf(fp, "%[a-zA-Z_0-9]*", the_string);

  // Set ch1 and ch2 to be the correct values after reading file
  fseek(fp, -1, SEEK_CUR);
  *ch1 = getc(fp);
  *ch2 = getc(fp);
  //
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

// A function that gets the word starting at ch1, then determines if it's an
int get_operator(char *ch1,char *ch2, FILE *fp) {
  // Arrays containing the operators separated by length
  char* operators_length_2[] = {":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>"};
  int len_2 = sizeof(operators_length_2)/sizeof(operators_length_2[0]);
  char operators_length_1[] = {'.', '<', '>', '(', ')', '+', '-', '*', '/', '|', '&', ';', ',', ':', '[', ']', '='};
  int len_1 = sizeof(operators_length_1)/sizeof(operators_length_1[0]);

  // Check if it's an operator of length 2 and break if it is
  for (int i=0; i<len_2; i++) {
    if (*ch1==operators_length_2[i][0] && *ch2==operators_length_2[i][1] ) {
      printf("%c%c (operator)\n", *ch1, *ch2);
      // Move the file pointer and ch pointers forward as necessary
      *ch1 = *ch2;
      *ch2 = getc(fp);
      return 0;
    }
  }
  // Check if the operator is only of length 1 and break if it is
  for (int i=0; i<len_1; i++) {
    if (*ch1==operators_length_1[i]) {
      printf("%c (operator)\n", *ch1);
      return 0;
    }
  }
}

int get_char(char *ch1, char*ch2, FILE *fp) {
  fseek(fp, -2, SEEK_CUR);
  char the_char[3];
  fscanf(fp, "%3s", the_char);
  fseek(fp, -1, SEEK_CUR);
  *ch1 = getc(fp);
  *ch2 = getc(fp);
  printf("%s (char literal)\n", the_char);

  return 0;
}

int get_number(char *ch1,char *ch2, FILE *fp) {
  char number[256];
  fseek(fp, -2, SEEK_CUR);
  fscanf(fp, "%255[0-9a-fA-F._#]", number);
  printf("%s (numeric literal)\n", number);
  *ch1 = *ch2;
  *ch2 = getc(fp);
}

int get_comment(char *ch1,char *ch2, FILE *fp) {
  // Wonderful mess of parenthesis and logic
  // continuously print out characters until '*/' is reached
  while (!(*ch1 == '*' && *ch2 == '/')) {
    printf("%c", *ch1);
    *ch1 = *ch2;
    *ch2 = getc(fp);
  }
  // Print the final characters of the comment and update ch1, ch2, and the file
  // pointer to be where we want
  printf("*/ (comment)\n");
  *ch1 = *ch2;
  *ch2 = getc(fp);
}

int get_string(char *ch1,char *ch2, FILE *fp) {
  char the_string[256];
  fseek(fp, -2, SEEK_CUR);
  fscanf(fp, "\"%[^\"]*\"", the_string);

  *ch1 = getc(fp);
  *ch2 = getc(fp);

  printf("\"%s\" (string)\n", the_string);
  return 0;
}
