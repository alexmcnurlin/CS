%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sym.h"
%}

%union {
    double dval;
    struct sym * symptr;
}

%token <symptr> NAME
%token <dval> NUMBER
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%type <dval> expression
%%
statement_list
    : statement '\n'
    | statement_list statement '\n'
    ;

statement
    : NAME '=' expression { if ($1->constant == 1) printf("Assign to const\n"); else $1->value = $3; }
    | expression { printf("= %g\n", $1); }
    | '?' { info(); }
    ;

expression
    : expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression { if ($3!=0) $$ = $1 / $3; else printf("divide by zero\n"); }
    | '-' expression %prec UMINUS { $$ = -$2; }
    | '(' expression ')' { $$ = $2; }
    | NUMBER
    | NAME { $$ = $1->value; } 
    ;

%%

struct sym * sym_lookup(char * s, int constant)
{
    struct sym *sp;

    sp = sym_tbl;
    do
    {
        if (sp->name && strcmp(sp->name, s) == 0) {
            return sp;
        } else if (sp->name && strcmp(sp->name, s) < 0) {
            sp = sp->left;
            continue;
        } else if (sp->name && strcmp(sp->name, s) > 0) {
            sp = sp->right;
            continue;
        }

        sp->name = strdup(s);
        sp->constant = constant;
        sp->left = malloc(sizeof(struct sym));
        sp->left->name = NULL;
        sp->right = malloc(sizeof(struct sym));
        sp->right->name = NULL;
        return sp; 
    } while (1);
   
    yyerror("Too many symbols");
    exit(-1);
    return NULL; /* unreachable */
}

// Recursively iterates through the given tree and counts the number of nodes
int count_vals(struct sym *sp) {
    if (sp->name != NULL) {
        return 1 + count_vals(sp->left) + count_vals(sp->right);
    }
    return 0;
}

// Recursively iterates through the given tree and prints the names/values in order
int print_vals(struct sym *sp) {
    if (sp->name != NULL) {
        print_vals(sp->right);
        printf("        %s => %lg\n", sp->name, sp->value);
        print_vals(sp->left);
    }
}

// Provides info about symbols by calling count_vals and print_vals
int info() {
     printf("num-syms: %i\n", count_vals(sym_tbl));
     print_vals(sym_tbl);
}

// Code to be run before the parser
int main() {
    sym_lookup("PI", 1)->value = 3.14159;
    sym_lookup("PHI", 1)->value = 1.61803;
    return yyparse();
}
