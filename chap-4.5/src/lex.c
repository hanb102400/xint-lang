#include "lex.h"


bool isWhitespace(char ch){
	return ch ==' '|| ch =='\n'|| ch =='\r' || ch =='\t'  ;
}

Lexer* Lexer_new(Scanner* scanner){
    if(!scanner) {
        fprintf(stderr,"scanner is null\n");
        return NULL;
    }
	Lexer *lexer  = (Lexer*) malloc(sizeof(Lexer));
	lexer->scanner=scanner;
	lexer->curCh=' ';
	lexer->curStatus=0;
	lexer->curToken.tokenType =TK_UNKNOWN;
	lexer->lastToken = lexer->curToken;
    return lexer;
}

void Lexer_delete(Lexer* lexer){
	free(lexer);
}

Token* Lexer_getNextToken(Lexer* lexer){

    Scanner* scanner = lexer->scanner;
    lexer->curCh = Scanner_getNextChar(scanner);
    fprintf(stderr,"curCh is %c\n", lexer->curCh);

    while(lexer->curCh!=-1) {
        if (isWhitespace(lexer->curCh)){//lexer
            lexer->curCh =  Scanner_getNextChar(scanner);
            continue;
        }

		switch(lexer->curCh){ //界符
			case '+':
				lexer->curToken.tokenType=TK_ADD;  
				break;
			case '-':
				lexer->curToken.tokenType=TK_SUB;  
				break;
			case '*':
				lexer->curToken.tokenType=TK_MUL;  
				break;
			case '%':
				lexer->curToken.tokenType=TK_MOD;
				break;
			case '>':
				lexer->curCh =  Scanner_getNextChar(scanner);
				if(lexer->curCh=='=') {
					lexer->curToken.tokenType=TK_GT_EQ;
					break;
				} else if(lexer->curCh=='>') {
					lexer->curToken.tokenType= TK_BIT_SHIFT_RIGHT;
					break;
				} else {
					lexer->curToken.tokenType=TK_GT;
					break;
				}
			case '<':
				lexer->curCh =  Scanner_getNextChar(scanner);
				if(lexer->curCh=='=') {
					lexer->curToken.tokenType=TK_LT_EQ;
					break;
				} else if(lexer->curCh=='<') {
					lexer->curToken.tokenType= TK_BIT_SHIFT_LEFT;
					break;
				} else {
					lexer->curToken.tokenType=TK_LT;
					break;
				}
			case '=':
				if(lexer->curCh=='=') {
					lexer->curToken.tokenType= TK_EQ;
					break;
				} else {
					lexer->curToken.tokenType=TK_ASSIGN;
					break;
				}
			case '&':
				if(lexer->curCh=='&') {
					lexer->curToken.tokenType= TK_LOGIC_AND;
					break;
				} else {
					lexer->curToken.tokenType= TK_BIT_AND;
					break;
				}
			case '|':
				if(lexer->curCh=='|') {
					lexer->curToken.tokenType= TK_LOGIC_OR;
					break;
				} else {
					lexer->curToken.tokenType= TK_BIT_OR;
					break;
				}
			case '!':
				if(lexer->curCh=='=') {
					lexer->curToken.tokenType= TK_NOT_EQ;
					break;
				} else {
					lexer->curToken.tokenType= TK_LOGIC_NOT;
					break;
				}
			case ',':
				lexer->curToken.tokenType= TK_COMMA;
				break;
			case ':':
				lexer->curToken.tokenType= TK_COLON;
				break;
			case ';':
				lexer->curToken.tokenType= TK_SEMICON;
				break;
			case '(':
				lexer->curToken.tokenType= TK_L_PAREN;
				break;
			case ')':
				lexer->curToken.tokenType= TK_R_PAREN;
				break;
			case '[':
				lexer->curToken.tokenType= TK_L_BRACKET;
				break;
			case ']':
				lexer->curToken.tokenType= TK_R_BRACKET;
				break;
			case '{':
				lexer->curToken.tokenType= TK_L_BRACE;
				break;
			case '}':
				lexer->curToken.tokenType= TK_R_BRACE;
				break;
			default:
                lexer->curToken.tokenType = TK_UNKNOWN;
		}
        return &lexer->curToken;
    }

    lexer->curToken.tokenType= TK_EOF;
    return  &lexer->curToken;
    
}

