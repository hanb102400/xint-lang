#include "scan.h"
#include "lex.h"
#include <stdlib.h>
#include <string.h>


void Console_Reset()
{
    fprintf(stdout, "\033[m");
}
void Console_setRed()
{
    fprintf(stdout, "\033[0;32;31m");
}
void Console_setGreen()
{
    fprintf(stdout, "\033[0;32;32m");
}
void Console_setYellow()
{
    fprintf(stdout, "\033[1;33m");
}
void Console_setBlue()
{
    fprintf(stdout, "\033[0;32;34m");
}
void Console_setPurple()
{
    fprintf(stdout, "\033[0;35m");
}
void Console_setCyan()
{
    fprintf(stdout, "\033[0;36m");
}
void Console_setWhite()
{
    fprintf(stdout, "\033[1;37m");
}



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

void printToken(Token *token)
{
  
    char *kindName = Token_findKindName(token->kind);
    char *kindWord = Token_findKindWord(token->kind);
    if (kindName != NULL)
    {
       
         Value value = token->value;
        fprintf(stdout, "L%d: kind: %16s", token->lineNo, kindName);
        if(value.strVal!=NULL && value.strVal->buf!= NULL) {
            fprintf(stdout, ", value: %16s", value.strVal->buf);
        } else {
            fprintf(stdout, ", value: %16s", kindWord);
        }
        fprintf(stdout,"\n");
        Console_Reset();
    }
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

    fprintf(stdout, "print token\n");

    Token *token = Lexer_nextToken(lexer);
    while (token->kind != TK_EOF)
    {
        printToken(token);
        token = Lexer_nextToken(lexer);
    }
    Scanner_delete(scanner);
    Lexer_delete(lexer);
}

