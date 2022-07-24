program.exe: output.c
	gcc .\output.c -o program.exe

output.c: interpreter.exe
	type .\input.txt | .\interpreter.exe

interpreter.exe: lex.yy.c parser.tab.c
	gcc lex.yy.c parser.tab.c symbol_table.c stack.c -o interpreter.exe

lex.yy.c: parser.tab.c scanner.l
	flex scanner.l

parser.tab.c: parser.y
	bison -d parser.y

clean: 
	del lex.yy.c parser.tab.c parser.tab.h interpreter.exe output.c program.exe