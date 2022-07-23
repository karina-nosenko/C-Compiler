interpreter.exe: lex.yy.c parser.tab.c
	gcc -Wall lex.yy.c parser.tab.c symbol_table.c stack.c -o interpreter.exe

lex.yy.c: parser.tab.c scanner.l
	flex scanner.l

parser.tab.c: parser.y
	bison -d parser.y

clean: 
	del lex.yy.c parser.tab.c parser.tab.h interpreter.exe