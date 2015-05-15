LEX=flex
YACC=yacc
CC=g++

sql_parser: sql_y.o sql_l.o tokens.o
	$(CC) sql_y.o sql_l.o tokens.o  -o $@ -lfl


y.tab.c: ana.y lex.yy.c
	$(YACC) -vdt ana.y

lex.yy.c: ana.l tokens.o
	$(LEX) ana.l

sql_y.o: y.tab.c
	$(CC) -c $< -o $@

sql_l.o: lex.yy.c
	$(CC) -c $< -o $@
tokens.o:tokens.cpp
	$(CC) -c $< -o $@
clean:
	rm -f *.c *.o sql_parser y.output y.tab.h
