hw4: lex.yy.c
	gcc lex.yy.c -o hw4

lex.yy.c: ccx.l
	flex ccx.l

test_code: lex_test.yy.c
	gcc lex_test.yy.c -o test_code

lex_test.yy.c: ccx_start.l
	flex -o lex_test.yy.c ccx_start.l 
