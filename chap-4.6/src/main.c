#include "scan.h"
#include "lex.h"
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
    Lexer* lexer = Lexer_new(scanner);

    Token* token =Lexer_nextToken(lexer);
    while( token->tokenKind !=TK_EOF ) {
        char* kindName = Token_findKindName(token->tokenKind);
        if(token->tokenKind !=TK_UNKNOWN && kindName !=NULL) {
            fprintf(stdout,"[tokenType: %s, line: %d]\n", kindName ,token->lineNo);
        }
        token =Lexer_nextToken(lexer);
    }
    Scanner_delete(scanner);
    Lexer_delete(lexer);
 
}