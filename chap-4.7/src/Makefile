

xint: scan.o  lex.o  string.o token.o main.o
	gcc  scan.o  lex.o  token.o string.o  main.o  -o  xint

main.o: main.c scan.h
	gcc  -Wall  -O  -g  -c  main.c  -o  main.o

scann.o: scan.c scan.h 
	gcc -Wall  -O  -g  -c   scan.c   -o  scanner.o

token.o: token.c   token.h
	gcc -Wall  -O  -g  -c   token.c   -o  token.o

lex.o: lex.c  lex.h
	gcc -Wall  -O  -g  -c   lex.c   -o  lex.o			

clean:
	rm -rf *.o
	rm -rf xint