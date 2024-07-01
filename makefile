compile:
	g++ parser.cc symboltables.cc lexer.cc inputbuf.cc

cr:
	g++ parser.cc symboltables.cc lexer.cc inputbuf.cc
	./test.sh

simple:
	g++ parser.cc symboltables.cc lexer.cc inputbuf.cc
	./a.out < extra.txt