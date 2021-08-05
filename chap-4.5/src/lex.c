#include "lex.h"

extern bool isWhitespace(char ch);

Lexer *Lexer_new(Scanner *scanner)
{
    if (!scanner)
    {
        fprintf(stderr, "scanner is null\n");
        return NULL;
    }
    Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
    lexer->scanner = scanner;
    lexer->curStatus = 0;
    lexer->curToken.tokenKind = TK_UNKNOWN;
    lexer->lastToken = lexer->curToken;
    return lexer;
}

void Lexer_delete(Lexer *lexer)
{
    free(lexer);
}

Token *Lexer_nextToken(Lexer *lexer)
{

    char ch = Scanner_nextChar(lexer->scanner);
    fprintf(stderr,"curChar is %c\n", ch);

    while(ch!=-1) {

        //跳过空白字符
        if (isWhitespace(ch)){//lexer
            ch = Scanner_nextChar(lexer->scanner);
            continue;
        }

		switch(ch){ //界符
			case '+':
				lexer->curToken.tokenKind=TK_ADD;  
				break;
			case '-':
				lexer->curToken.tokenKind=TK_SUB;  
				break;
			case '*':
				lexer->curToken.tokenKind=TK_MUL;  
				break;
			case '%':
				lexer->curToken.tokenKind=TK_MOD;
				break;
			case ',':
				lexer->curToken.tokenKind= TK_COMMA;
				break;
			case ':':
				lexer->curToken.tokenKind= TK_COLON;
				break;
			case ';':
				lexer->curToken.tokenKind= TK_SEMICON;
				break;
			case '(':
				lexer->curToken.tokenKind= TK_L_PAREN;
				break;
			case ')':
				lexer->curToken.tokenKind= TK_R_PAREN;
				break;
			case '[':
				lexer->curToken.tokenKind= TK_L_BRACKET;
				break;
			case ']':
				lexer->curToken.tokenKind= TK_R_BRACKET;
				break;
			case '{':
				lexer->curToken.tokenKind= TK_L_BRACE;
				break;
			case '}':
				lexer->curToken.tokenKind= TK_R_BRACE;
				break;
			case '/':
				lexer->curToken.tokenKind= TK_DIV;
				break;	
			default:
                lexer->curToken.tokenKind = TK_UNKNOWN;
		}
        lexer->curToken.lineNo = lexer->scanner->lineNum;
        return &lexer->curToken;
    }

    lexer->curToken.tokenKind= TK_EOF;
    return  &lexer->curToken;
}

bool isWhitespace(char ch)
{
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}
