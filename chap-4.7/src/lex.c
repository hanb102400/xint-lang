#include "lex.h"

extern bool isWhitespace(char ch);
extern bool isAlpha(char ch);
extern bool isDigit(char ch);
extern bool isDigit2(char ch);
extern bool isDigit8(char ch);
extern bool isDigit16(char ch);

extern void Lexer_parseComment(Lexer *lexer);
extern void Lexer_parseIdKeyword(Lexer* lexer) ;

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
	//fprintf(stderr, "curChar is %c\n", ch);

	while (ch != -1)
	{

		//跳过空白字符
		if (isWhitespace(ch))
		{ //lexer
			ch = Scanner_nextChar(lexer->scanner);
			continue;
		}

		switch (ch)
		{ //界符
		case '+':
			if (Scanner_matchNextChar(lexer->scanner, '+'))
			{
				lexer->curToken.tokenKind = TK_SELF_ADD;
			}
			else
			{
				lexer->curToken.tokenKind = TK_ADD;
			}
			break;
		case '-':
			if (Scanner_matchNextChar(lexer->scanner, '-'))
			{
				lexer->curToken.tokenKind = TK_SELF_SUB;
			}
			else
			{
				lexer->curToken.tokenKind = TK_SUB;
			}
			break;
		case '*':
			lexer->curToken.tokenKind = TK_MUL;
			break;
		case '%':
			lexer->curToken.tokenKind = TK_MOD;
			break;
		case ',':
			lexer->curToken.tokenKind = TK_COMMA;
			break;
		case ':':
			lexer->curToken.tokenKind = TK_COLON;
			break;
		case ';':
			lexer->curToken.tokenKind = TK_SEMICON;
			break;
		case '(':
			lexer->curToken.tokenKind = TK_L_PAREN;
			break;
		case ')':
			lexer->curToken.tokenKind = TK_R_PAREN;
			break;
		case '[':
			lexer->curToken.tokenKind = TK_L_BRACKET;
			break;
		case ']':
			lexer->curToken.tokenKind = TK_R_BRACKET;
			break;
		case '{':
			lexer->curToken.tokenKind = TK_L_BRACE;
			break;
		case '}':
			lexer->curToken.tokenKind = TK_R_BRACE;
			break;
		case '>':
			if (Scanner_matchNextChar(lexer->scanner, '='))
			{
				lexer->curToken.tokenKind = TK_GT_EQ;
			}
			else if (Scanner_matchNextChar(lexer->scanner, '>'))
			{
				lexer->curToken.tokenKind = TK_BIT_SHIFT_RIGHT;
			}
			else
			{
				lexer->curToken.tokenKind = TK_GT;
				
			}
			break;
		case '<':
			if (Scanner_matchNextChar(lexer->scanner, '='))
			{
				lexer->curToken.tokenKind = TK_LT_EQ;
			}
			else if (Scanner_matchNextChar(lexer->scanner, '<'))
			{
				lexer->curToken.tokenKind = TK_BIT_SHIFT_LEFT;
			}
			else
			{
				lexer->curToken.tokenKind = TK_LT;
				
			}
			break;
		case '=':
			if (Scanner_matchNextChar(lexer->scanner, '='))
			{
				lexer->curToken.tokenKind = TK_EQ;
			}
			else
			{
				lexer->curToken.tokenKind = TK_ASSIGN;
			}
			break;
		case '&':
			if (Scanner_matchNextChar(lexer->scanner, '&'))
			{
				lexer->curToken.tokenKind = TK_LOGIC_AND;
			
			}
			else
			{
				lexer->curToken.tokenKind = TK_BIT_AND;
			
			}
				break;
		case '|':
			if (Scanner_matchNextChar(lexer->scanner, '|'))
			{
				lexer->curToken.tokenKind = TK_LOGIC_OR;
			}
			else
			{
				lexer->curToken.tokenKind = TK_BIT_OR;
				
			}
			break;
		case '!':
			if (Scanner_matchNextChar(lexer->scanner, '='))
			{
				lexer->curToken.tokenKind = TK_NOT_EQ;
				
			}
			else
			{
				lexer->curToken.tokenKind = TK_LOGIC_NOT;
				
			}
			break;
		case '/':
			Lexer_parseComment(lexer);
			break;
		default:
			if( isAlpha(ch) ||ch=='_'){
				Lexer_parseIdKeyword(lexer);
			} else{
				lexer->curToken.tokenKind = TK_UNKNOWN;
			}
		}
		lexer->curToken.lineNo = lexer->scanner->lineNum;
		return &lexer->curToken;
	}

	lexer->curToken.tokenKind = TK_EOF;
	return &lexer->curToken;
}

void Lexer_parseComment(Lexer *lexer)
{
	char ch = lexer->scanner->curCh;

	if (Scanner_matchNextChar(lexer->scanner, '/'))
	{ //单行注释

		while (true)
		{
			ch = Scanner_lookAheadChar(lexer->scanner);
			if(ch != '\n' && ch != -1) {
				ch = Scanner_nextChar(lexer->scanner);
			}else {
				break;
			}
		}
		lexer->curToken.tokenKind = TK_COMMENT;
	}
	else if (Scanner_matchNextChar(lexer->scanner, '*'))
	{ //多行注释,不允许嵌套注释

		lexer->curStatus = TS_COMMENT;
		while (lexer->curStatus == TS_COMMENT)
		{
			if (ch == '*')
			{
				ch = Scanner_nextChar(lexer->scanner);
				if (ch == '/')
				{
					lexer->curToken.tokenKind = TK_COMMENT;
					lexer->curStatus = TS_NORMAL;
					break;
				}
			}
			ch = Scanner_nextChar(lexer->scanner);
		}
	}
	else
	{
		//除以
		lexer->curToken.tokenKind = TK_DIV;
	}
}


void Lexer_parseIdKeyword(Lexer* lexer) {

	char ch = lexer->scanner->curCh;
	String* str = String_new();
	str = String_append(str,ch);
	ch = Scanner_lookAheadChar(lexer->scanner);
	while( isAlpha(ch) || isDigit(ch) ||ch=='_') {
		ch = Scanner_nextChar(lexer->scanner);
		str = String_append(str,ch);
		ch = Scanner_lookAheadChar(lexer->scanner);
	}
	//String_println(str);
	TokenKind kind = Token_findKeywordKind(str);
	if(kind!=-1) {
		lexer->curToken.tokenKind=kind;
	} else {
		lexer->curToken.tokenKind=TK_ID;
		lexer->curToken.tokenVal.strVal = str;
	}

}

/**
 * 空白字符
 */
bool isWhitespace(char ch){
	return ch ==' '|| ch =='\n'|| ch =='\r' || ch =='\t'  ;
}

/**
 * 英文字母
 */
bool isAlpha(char ch){
	return (ch >='a'&& ch <='z')|| (ch >='A'&& ch<='Z');
}

/**
 * 数字（10进制）
 */
bool isDigit(char ch){
	return ch>='0'&&ch<='9';
}

/**
 * 数字（2进制）
 */
bool isDigit2(char ch){
	return ch=='0'||ch=='1';
}

/**
 * 数字（8进制）
 */
bool isDigit8(char ch){
	return ch>='0'&&ch<='7';
}


/**
 * 数字（16进制）
 */
bool isDigit16(char ch){
	return (ch>='0'&&ch<='9')||(ch>='A'&&ch<='F') || (ch>='a'&&ch<='f');
}
