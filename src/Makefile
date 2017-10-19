bcc: parser.tab.c printer.cpp ast.cpp lex.yy.c ast.h visitor.h
	g++ parser.tab.c ast.cpp printer.cpp -lfl -o bcc
	# g++ parser.tab.c -lfl -o bcc
parser.tab.c: parser.y 
	bison -d --debug --verbose parser.y 
parser.tab.h: parser.y
	bison -d --debug --verbose parser.y 
lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

.PHONY: clean 
clean:
	-@rm -rf parser.tab.c parser.tab.h lex.yy.c bcc 2>/dev/null || true
