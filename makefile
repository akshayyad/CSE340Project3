compile:
	g++ parser.cc symboltables.cc lexer.cc inputbuf.cc

cr:
	g++ parser.cc symboltables.cc lexer.cc inputbuf.cc
	./test.sh

extra:
	g++ parser.cc symboltables.cc lexer.cc inputbuf.cc
	./a.out < extra.txt

implicit:
	g++ parser.cc symboltables.cc lexer.cc inputbuf.cc
	./a.out < implicit.txt

single:
	g++ parser.cc symboltables.cc lexer.cc inputbuf.cc
	./a.out < tests/test01.txt