

xint: scan.o  lex.o main.o token.o string.o
	gcc  scan.o  lex.o  token.o main.o string.o -o xint

%.o: %.c %.h
	gcc  -Wall  -O  -g  -o   $@ -c  $<


clean:
	rm -rf *.o
	rm -rf xint