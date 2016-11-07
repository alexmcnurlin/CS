#ifndef SYMTBL_H
#define SYMTBL_H

struct sym {
    char * name;
    double value;
    struct sym *right;
    struct sym *left;
    int constant;
} sym_tbl[1] ;

struct sym * sym_lookup(char *, int);

#endif /* SYMTBL_H */
