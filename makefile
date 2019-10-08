CXX         = g++ -std=c++11
CXXFLAGS    = -g -Wall
OBJS        = lexer.o syntax.o
PROG        = tcc

all:        $(PROG)

$(PROG):    $(OBJS)
			$(CXX) -o $(PROG) $(OBJS)

clean:      $(RM) $(PROG) core *.o
			

lexer.cpp:  lexer.l
			$(LEX) $(LFLAGS) -t lexer.l > lexer.cpp
lexer.o:    lexer.cpp

syntax.o:	syntax.cpp
