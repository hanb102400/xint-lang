#include "scan.h"
#include <stdlib.h>
#include <string.h>

FILE* readFile(char* filename){
    FILE *source = fopen(filename ,"r");
    if (source==NULL){ 
        fprintf(stderr,"File %s not found\n",filename);
        exit(1);
    }
    FILE *screen = stdout; /* send listing to screen */
    fprintf(screen,"\nXINT CODE COMPILATION: %s\n",filename);
    return source;
}


int  main(int  argc,  char*  argv[]) {
    char prog[120]; 
    if (argc != 2){ 
        fprintf(stderr,"usage: %s <filename>\n",argv[0]);
        exit(1);
    }
    strcpy(prog,argv[1]) ;
    FILE* file = readFile(prog);

    Scanner* scanner = Scanner_new(file);
    char ch;
    while( (ch = Scanner_getNextChar(scanner))!=-1 ) {
        fprintf(stdout,"\nchar: %c\n",ch);
    }
    Scanner_delete(scanner);
 
}