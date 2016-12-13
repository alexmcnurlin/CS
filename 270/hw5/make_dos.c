#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[]) {
        FILE *fp1;
        char c;
        fp1 = fopen("dm23", "w+");
        //fputs("\128\147\137", fp1);
        fputs("This is\r\na file\r\nwith\r\nkk\r\nhello", fp1);
        fclose(fp1);
}
