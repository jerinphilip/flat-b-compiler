all: bcc bci
bcc: parser.tab.c printer.cpp ast.cpp lex.yy.c ast.h visitor.h interpreter.cpp compiler.cpp
	g++ --std=c++14 -g parser.tab.c ast.cpp printer.cpp interpreter.cpp compiler.cpp -lfl -lLLVM-5.0 -o bcc 
	# g++ parser.tab.c -lfl -o bcc
bci: iparser.tab.c printer.cpp ast.cpp lex.yy.c ast.h visitor.h interpreter.cpp compiler.cpp
	g++ --std=c++14 -g iparser.tab.c ast.cpp printer.cpp interpreter.cpp compiler.cpp -lfl -lLLVM-5.0 -o bci 
	# g++ parser.tab.c -lfl -o bcc
parser.tab.c: parser.y 
	bison -d --debug --verbose parser.y 
parser.tab.h: parser.y
	bison -d --debug --verbose parser.y 

iparser.tab.c: iparser.y 
	bison -d --debug --verbose iparser.y 
iparser.tab.h: iparser.y 
	bison -d --debug --verbose iparser.y 

iparser.y:

lex.yy.c: scanner.l parser.tab.h iparser.tab.h
	flex scanner.l

.PHONY: clean all
clean:
	-@rm -rf parser.tab.c parser.tab.h lex.yy.c bcc 2>/dev/null || true

