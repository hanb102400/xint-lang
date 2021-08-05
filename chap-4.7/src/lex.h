#ifndef _LEX_H_
#define _LEX_H_

#include "scan.h"
#include "token.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Lexer_
{
	int curStatus;
	Token curToken;
	Token lastToken;
	Scanner *scanner;
} Lexer;

Lexer *Lexer_new(Scanner *scanner);

void Lexer_delete(Lexer *lexer);

Token *Lexer_nextToken(Lexer *lexer);

#endif