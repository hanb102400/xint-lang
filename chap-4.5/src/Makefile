

xint: scan.o  lex.o main.o
	gcc  scan.o  lex.o main.o  -o  xint

main.o: main.c scan.h
	gcc  -Wall  -O  -g  -c  main.c  -o  main.o

scann.o: scan.c  scan.h
	gcc -Wall  -O  -g  -c   scan.c   -o  scanner.o


lex.o: lex.c  lex.h
	gcc -Wall  -O  -g  -c   lex.c   -o  lex.o			

clean:
	rm -rf *.o
	rm -rf xint