

xint: scan.o main.o 
	gcc  scan.o  main.o  -o  xint

main.o: main.c scan.h
	gcc  -Wall  -O  -g  -c  main.c  -o  main.o

scann.o: scan.c  scan.h
	gcc -Wall  -O  -g  -c   scan.c   -o  scanner.o	

clean:
	rm -rf *.o
	rm -rf xint