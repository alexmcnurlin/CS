%{
%}

NUMBER   [0-9][0-9a-fA-F_.#]*
COMMENT "/*"([^*]|\n|(\*+([^*/]|[\n])))*"*/"
STRING \"[^"]*\"
CHAR   \'.\'
IDENTIFIER  [a-zA-Z][a-zA-Z0-9_]*

%%
accessor|and|array|begin|bool|case|else|elsif|end|exit|function|if|in|integer|interface|is|loop|module|mutator|natural|null|of|or|others|out|positive|procedure|return|struct|subtype|then|type|when|while {
               printf("%s (keyword)\n", yytext);
               }

{NUMBER}       printf("%s (numeric literal)\n", yytext);

{COMMENT}      printf("%s (comment)\n", yytext);

{STRING}       printf("%s (string)\n", yytext);

{CHAR}         printf("%s (char literal)\n", yytext);

"."|"<"|">"|"("|")"|"+"|"-"|"*"|"/"|"|"|"&"|";"|","|":"|"["|"]"|"="|":="|".."|"<<"|">>"|"<>"|"<="|">="|"**"|"!="|"=>" {
               printf("%s (operator)\n",yytext);
               }

[ \t\n]+       /* discard whitespace */

{IDENTIFIER}   printf("%s (identifier)\n", yytext);

.              printf("Unrecognized character: %s\n", yytext);
%%

int main(int argc, char **argv)
{
    if (argc > 1)
        yyin = fopen(argv[1], "r");
    else
        yyin = stdin;
     
    yylex();
}

/*
 * This defines yywrap, a special function used by lex to determine what should
 * be done when the end of an input file is encountered.  You can read more
 * about this at http://flex.sourceforge.net
 */
int yywrap()
{
    return 1;
}
