// Alex McNurlin
// CS270
// hw5
// ls.c
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void guess_name(char* path);
void get_times(char* path);
int is_pscript(FILE* fp);
int is_dos(FILE* fp);
int is_ascii(FILE* fp);
int is_elf(FILE* fp);

int main(int argc, char** argv) {
  char file_name[256];
  if (argc < 1 || argc > 3) {
    printf("Error: Invalid number of arguments\n");
    exit(1);
  }

  // Parse arguments. This program does not support separate options. 
  // e.g. '-t -f' is not supported, but '-tf' is
  int f = 0;
  int t = 0;
  if (argc != 1 && argv[1][0] == '-') {
    int size = sizeof(argv[1])/sizeof(argv[1][0]) - 1;
    char options[16];
    strcpy(options, argv[1]);

    // check which of f and t are given
    for (int i=1; i<size; i++) {
      if (options[i] == 'f') {
        f = 1;
      } else if (options[i] == 't') {
        t = 1;
      }
    }

    if (argc == 2) { // If there is an option given, but no directory, use cwd
      getcwd(file_name, sizeof(file_name));
    } else {
      strcpy(file_name, argv[2]);
    }
  } else if (argc == 2) { // If a directory is given with no option
    strcpy(file_name, argv[1]);
  } else if (argc == 1) {
    getcwd(file_name, sizeof(file_name)); // If no args are given, use cwd
  }

  // Open the directory
  struct dirent *dir_entry;
  DIR *dir_name;
  if ((dir_name = opendir(file_name)) == NULL) {
    printf("Error opening file\n");
    exit(1);
  }

  // Read each directory entry
  while ((dir_entry = readdir(dir_name)) != NULL) {
    char buf[256] = "\0";
    // Get full path, rather than just the filename
    strcat(buf, file_name);
    strcat(buf, "/");
    strcat(buf, dir_entry->d_name);

    printf("%s\n", dir_entry->d_name);
    if (f) {
      guess_name(buf);
    } 
    if (t) {
      get_times(buf);
    }
    printf("\n");
  }
  closedir(dir_name);
}


// Tries to guess the files type based on the contents. Better descriptions
//  can be found in the functions called
void guess_name(char* path) {
  FILE *fp;
  if ((fp = fopen(path, "r")) == NULL) {
    printf("Error: Could not open file %s\n", path);
    return;
  }

  struct stat buf;
  // Guess filetype
  if (!stat(path, &buf)) {
    if (S_ISREG(buf.st_mode)) {
      if (is_pscript(fp)) {
        printf("\tType: PostScript\n");
      } else if (is_dos(fp)) {
        printf("\tType: DOS\n");
      } else if (is_ascii(fp)) {
        printf("\tType: ASCII\n");
      } else if (is_elf(fp)) {
        printf("\tType: ELF\n");
      } else {
        printf("\tType: Binary\n");
      }
    } else {
      printf("Type: Directory\n");
    }
  }
  fclose(fp);
}

// Print the times that the file was modified/accessed/status change
void get_times(char* path) {
  struct stat buf;
  if(!stat(path, &buf)) {
    printf("\tDate Modified:      %s", ctime(&buf.st_mtime));
    printf("\tDate Accessed:      %s", ctime(&buf.st_atime));
    printf("\tLast Status Change: %s\n", ctime(&buf.st_ctime));
  } else {
    printf("Cannot stat %s\n", path);
  }
}

// Checks if the file is postscript
// A postscript file begins with"!%PS-adobe
int is_pscript(FILE* fp) {
  char postscript[] = "%!PS-Adobe\n";
  int post_len = sizeof(postscript)/sizeof(postscript[0]);
  // Loop through each character until we find a char that differs
  for (int i=0; i<post_len-1; i++) {
    char c = fgetc(fp);
    if (c != postscript[i]) {
      fseek(fp, SEEK_SET, 0);
      return 0;
    }
  }
  fseek(fp, SEEK_SET, 0);
  return 1;
}

// Returns 1 if the file is a DOS file, and 0 otherwise
// A file is a DOS file if it is ASCII where every newline is preceded by a 
// carriage return
int is_dos(FILE* fp) {
  int ch1, ch2; // int because a char will give us negative values for non ASCII
  ch2 = getc(fp);
  // Loop through each char of the file
  while (1) {
    ch1 = ch2;
    // Break if a non ASCII char is reached, or 
    // a newline does not have a carriage return before it
    if ((ch2 = getc(fp)) != EOF) {
      if ((ch2 > 128) || ((ch2 == 10) && (ch1 != 13))) {
        fseek(fp, SEEK_SET, 0);
        return 0;
      }
    } else {
      return 1;
    }
  }
  fseek(fp, SEEK_SET, 0);
  return 1;
}

// Check if a file is ASCII. 
// A file is ASCII if all of it's chars have an int value below 128
int is_ascii(FILE* fp) {
  int ch1; // int because a char will give us negative values
  while ((ch1 = getc(fp)) != EOF) {
    // Break on non-ascii char
    if (ch1 > 128) {
      fseek(fp, SEEK_SET, 0);
      return 0;
    }
  }
  fseek(fp, SEEK_SET, 0);
  return 1;
}

// Checks if the given file is an ELF file by checking first for chars
int is_elf(FILE* fp) {
  int chars[] = {127, 69, 76, 70};
  int chars_len = sizeof(chars)/sizeof(chars[0]);
  for (int i=0; i<chars_len-1; i++) {
    char c = fgetc(fp);
    if (c != chars[i]) {
      fseek(fp, SEEK_SET, 0);
      return 0;
    }
  }
  fseek(fp, SEEK_SET, 0);
  return 1;
}
