#include "scan.h"
#include "lex.h"
#include <stdlib.h>
#include <string.h>

FILE *readFile(char *filename)
{
    FILE *source = fopen(filename, "r");
    if (source == NULL)
    {
        fprintf(stderr, "File %s not found\n", filename);
        exit(1);
    }
    FILE *screen = stdout; /* send listing to screen */
    fprintf(screen, "\nXINT CODE COMPILATION: %s\n", filename);
    return source;
}

int main(int argc, char *argv[])
{
    char prog[120];
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    strcpy(prog, argv[1]);
    FILE *file = readFile(prog);

    Scanner *scanner = Scanner_new(file);
    Lexer *lexer = Lexer_new(scanner);

    Token *token = Lexer_nextToken(lexer);
    while (token->tokenKind != TK_EOF)
    {
        TokenVal tokenVal = token->tokenVal;
        char *kindName = Token_findKindName(token->tokenKind);
        char *kindWord = Token_findKindWord(token->tokenKind);
        if (kindName != NULL)
        {
             if (token->tokenKind == TK_STRING ){
                Console_setRed();
             }
             else if (token->tokenKind == TK_ID ){
                Console_setYellow();
             }
             else if (token->tokenKind == TK_NUMBER ){
                Console_setCyan();
             } 
             else if(kindWord != NULL){
                    Console_setPurple();
             }

            if(token->tokenKind == TK_STRING ) {
                 fprintf(stdout, "[tokenKind: %16s, value: %16s, line: %d]\n", kindName, tokenVal.strVal->buf, token->lineNo);
            }
            else if ( token->tokenKind == TK_ID || token->tokenKind == TK_NUMBER)
            {   
               
                fprintf(stdout, "[tokenKind: %16s, value: %16s, line: %d]\n", kindName, tokenVal.strVal->buf, token->lineNo);
              
            }
            else if (kindWord != NULL)
            {
                fprintf(stdout, "[tokenKind: %16s, value: %16s, line: %d]\n", kindName, kindWord, token->lineNo);
            }
            else
            {
                fprintf(stdout, "[tokenKind: %16s, line: %d]\n", kindName, token->lineNo);
            }

              Console_Reset();
        }
        token = Lexer_nextToken(lexer);
    }
    Scanner_delete(scanner);
    Lexer_delete(lexer);
}

void Console_Reset(){
    fprintf( stdout, "\033[m");
}
void Console_setRed(){
    fprintf(stdout,"\033[0;32;31m");
}
void Console_setGreen(){
    fprintf(stdout,"\033[0;32;32m");
}
void Console_setYellow(){
    fprintf(stdout,"\033[1;33m");
}
void Console_setBlue(){
    fprintf(stdout,"\033[0;32;34m");
}
void Console_setPurple(){
    fprintf(stdout,"\033[0;35m");
}
void Console_setCyan(){
    fprintf(stdout,"\033[0;36m");
}
void Console_setWhite(){
    fprintf(stdout,"\033[1;37m");
}
