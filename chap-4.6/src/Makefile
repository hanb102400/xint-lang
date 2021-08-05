

xint: scan.o  lex.o main.o token.o
	gcc  scan.o  lex.o  token.o main.o -o xint

%.o: %.c %.h
	gcc  -Wall  -O  -g  -o   $@ -c  $<

clean:
	rm -rf *.o
	rm -rf xint