#include "lex.h"

extern bool isWhitespace(char ch);
extern bool isAlpha(char ch);
extern bool isDigit(char ch);
extern bool isDigit2(char ch);
extern bool isDigit8(char ch);
extern bool isDigit16(char ch);

extern void Lexer_parseComment(Lexer *lexer);
extern void Lexer_parseIdKeyword(Lexer *lexer);
extern void Lexer_parseNumber(Lexer *lexer);
extern void Lexer_parseChar(Lexer *lexer);
extern void Lexer_parseString(Lexer *lexer);

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
	lexer->curToken.kind = TK_UNKNOWN;
	lexer->lastToken = lexer->curToken;
	return lexer;
}

void Lexer_delete(Lexer *lexer)
{
	if (lexer != NULL)
	{
		free(lexer);
		lexer = NULL;
	}
}

Token *Lexer_nextToken(Lexer *lexer)
{

	char ch = Scanner_nextChar(lexer->scanner);
	//fprintf(stderr, "curChar is %c\n", ch);
	lexer->curToken.value.strVal = NULL;

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
				lexer->curToken.kind = TK_SELF_ADD;
			}
			else
			{
				lexer->curToken.kind = TK_ADD;
			}
			break;
		case '-':
			if (Scanner_matchNextChar(lexer->scanner, '-'))
			{
				lexer->curToken.kind = TK_SELF_SUB;
			}
			else
			{
				lexer->curToken.kind = TK_SUB;
			}
			break;
		case '*':
			lexer->curToken.kind = TK_MUL;
			break;
		case '%':
			lexer->curToken.kind = TK_MOD;
			break;
		case ',':
			lexer->curToken.kind = TK_COMMA;
			break;
		case ':':
			lexer->curToken.kind = TK_COLON;
			break;
		case ';':
			lexer->curToken.kind = TK_SEMICON;
			break;
		case '(':
			lexer->curToken.kind = TK_L_PAREN;
			break;
		case ')':
			lexer->curToken.kind = TK_R_PAREN;
			break;
		case '[':
			lexer->curToken.kind = TK_L_BRACKET;
			break;
		case ']':
			lexer->curToken.kind = TK_R_BRACKET;
			break;
		case '{':
			lexer->curToken.kind = TK_L_BRACE;
			break;
		case '}':
			lexer->curToken.kind = TK_R_BRACE;
			break;
		case '>':
			if (Scanner_matchNextChar(lexer->scanner, '='))
			{
				lexer->curToken.kind = TK_GT_EQ;
			}
			else if (Scanner_matchNextChar(lexer->scanner, '>'))
			{
				lexer->curToken.kind = TK_BIT_SHIFT_RIGHT;
			}
			else
			{
				lexer->curToken.kind = TK_GT;
			}
			break;
		case '<':
			if (Scanner_matchNextChar(lexer->scanner, '='))
			{
				lexer->curToken.kind = TK_LT_EQ;
			}
			else if (Scanner_matchNextChar(lexer->scanner, '<'))
			{
				lexer->curToken.kind = TK_BIT_SHIFT_LEFT;
			}
			else
			{
				lexer->curToken.kind = TK_LT;
			}
			break;
		case '=':
			if (Scanner_matchNextChar(lexer->scanner, '='))
			{
				lexer->curToken.kind = TK_EQ;
			}
			else
			{
				lexer->curToken.kind = TK_ASSIGN;
			}
			break;
		case '&':
			if (Scanner_matchNextChar(lexer->scanner, '&'))
			{
				lexer->curToken.kind = TK_LOGIC_AND;
			}
			else
			{
				lexer->curToken.kind = TK_BIT_AND;
			}
			break;
		case '|':
			if (Scanner_matchNextChar(lexer->scanner, '|'))
			{
				lexer->curToken.kind = TK_LOGIC_OR;
			}
			else
			{
				lexer->curToken.kind = TK_BIT_OR;
			}
			break;
		case '!':
			if (Scanner_matchNextChar(lexer->scanner, '='))
			{
				lexer->curToken.kind = TK_NOT_EQ;
			}
			else
			{
				lexer->curToken.kind = TK_LOGIC_NOT;
			}
			break;
		case '/':
			Lexer_parseComment(lexer);
			break;
		default:
			if (ch == '\'')
			{ //字符
				Lexer_parseChar(lexer);
			}
			else if (ch == '\"')
			{
				Lexer_parseString(lexer);
			}
			else if (isAlpha(ch) || ch == '_')
			{ //ID 或者 关键字
				Lexer_parseIdKeyword(lexer);
			}
			else if (isDigit(ch))
			{ //数字
				Lexer_parseNumber(lexer);
			}
			else
			{
				lexer->curToken.kind = TK_UNKNOWN;
			}
		}
		lexer->curToken.lineNo = lexer->scanner->lineNum;
		return &lexer->curToken;
	}

	lexer->curToken.kind = TK_EOF;
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
			if (ch != '\n' && ch != -1)
			{
				ch = Scanner_nextChar(lexer->scanner);
			}
			else
			{
				break;
			}
		}
		lexer->curToken.kind = TK_COMMENT;
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
					lexer->curToken.kind = TK_COMMENT;
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
		lexer->curToken.kind = TK_DIV;
	}
}

void Lexer_parseChar(Lexer *lexer)
{
	char ch = Scanner_nextChar(lexer->scanner);
	if (ch == '\n' || ch == -1)
	{ //行 文件结束
		lexer->curToken.kind = TK_ERROR;
	}
	else if (ch == '\\')
	{ //转义
		ch = Scanner_nextChar(lexer->scanner);
		if (ch == '\n' || ch == -1)
		{ //行 文件结束
			lexer->curToken.kind = TK_ERROR;
		}
		else if (ch == 'n')
			ch = '\n';
		else if (ch == '\\')
			ch = '\\';
		else if (ch == 't')
			ch = '\t';
		else if (ch == '0')
			ch = '\0';
		else if (ch == '\'')
			ch = '\'';
	}
	else if (ch == '\'')
	{ //没有数据
		lexer->curToken.kind = TK_ERROR;
	}
	char charVal = ch;
	ch = Scanner_nextChar(lexer->scanner);
	if (ch == '\'')
	{
		lexer->curToken.kind = TK_NUMBER;
		lexer->curToken.value.charVal = charVal;
	}
}

void Lexer_parseString(Lexer *lexer)
{
	char ch = Scanner_nextChar(lexer->scanner);
	String *str = String_new();
	if (ch == '\"')
	{
		if (Scanner_matchNextChar(lexer->scanner, '\"'))
		{ //多行字符串
			while (true)
			{
				ch = Scanner_nextChar(lexer->scanner);

				if (ch == '\"')
				{
					if (Scanner_matchNextChar(lexer->scanner, '\"') && Scanner_matchNextChar(lexer->scanner, '\"'))
					{
						lexer->curToken.kind = TK_STRING;
						lexer->curToken.value.strVal = str;
						break;
					}
				}
				str = String_append(str, ch);
			}
		}
		else
		{ //空字符串
		}
	}
	else
	{ //单行字符串
		str = String_append(str, ch);
		while (true)
		{
			ch = Scanner_nextChar(lexer->scanner);
			if (ch == '\"')
			{

				lexer->curToken.kind = TK_STRING;
				lexer->curToken.value.strVal = str;
				break;
			}
			str = String_append(str, ch);
		}
	}
}

void Lexer_parseIdKeyword(Lexer *lexer)
{

	char ch = lexer->scanner->curCh;
	String *str = String_new();
	str = String_append(str, ch);
	while (true)
	{
		ch = Scanner_lookAheadChar(lexer->scanner);
		if (isAlpha(ch) || isDigit(ch) || ch == '_')
		{
			ch = Scanner_nextChar(lexer->scanner);
			str = String_append(str, ch);
		}
		else
		{
			break;
		}
	}
	//String_println(str);
	TokenKind kind = Token_findKeywordKind(str);
	if (kind != -1)
	{
		lexer->curToken.kind = kind;
	}
	else
	{
		lexer->curToken.kind = TK_ID;
		lexer->curToken.value.strVal = str;
	}
}

void Lexer_parseNumber(Lexer *lexer)
{
	char ch = lexer->scanner->curCh;
	//十六进制
	if (ch == '0' && Scanner_matchNextChar(lexer->scanner, 'x'))
	{

		String *str = String_new();
		str = String_append(str, '0');
		str = String_append(str, 'x');
		while (true)
		{
			ch = Scanner_lookAheadChar(lexer->scanner);
			if (isDigit(ch) || ch == '_')
			{
				ch = Scanner_nextChar(lexer->scanner);
				str = String_append(str, ch);
			}
			else
			{
				break;
			}
		}
		lexer->curToken.value.strVal = str;
	}

	//八进制
	else if (ch == '0' && Scanner_matchNextChar(lexer->scanner, 'o'))
	{

		String *str = String_new();
		str = String_append(str, '0');
		str = String_append(str, 'o');
		while (true)
		{
			ch = Scanner_lookAheadChar(lexer->scanner);
			if (isDigit(ch) || ch == '_')
			{
				ch = Scanner_nextChar(lexer->scanner);
				str = String_append(str, ch);
			}
			else
			{
				break;
			}
		}
		lexer->curToken.value.strVal = str;
	}

	//二进制
	else if (ch == '0' && Scanner_matchNextChar(lexer->scanner, 'b'))
	{

		String *str = String_new();
		str = String_append(str, '0');
		str = String_append(str, 'b');
		while (true)
		{
			ch = Scanner_lookAheadChar(lexer->scanner);
			if (isDigit(ch) || ch == '_')
			{
				ch = Scanner_nextChar(lexer->scanner);
				str = String_append(str, ch);
			}
			else
			{
				break;
			}
		}
		lexer->curToken.value.strVal = str;
	}

	//十进制
	else
	{
		String *str = String_new();
		str = String_append(str, ch);
		while (true)
		{
			ch = Scanner_lookAheadChar(lexer->scanner);
			if (isDigit(ch) || ch == '_')
			{
				ch = Scanner_nextChar(lexer->scanner);
				str = String_append(str, ch);
			}
			else
			{
				break;
			}
		}
		lexer->curToken.value.strVal = str;
	}
	lexer->curToken.kind = TK_NUMBER;
}

/**
 * 空白字符
 */
bool isWhitespace(char ch)
{
	return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}

/**
 * 英文字母
 */
bool isAlpha(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

/**
 * 数字（10进制）
 */
bool isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

/**
 * 数字（2进制）
 */
bool isDigit2(char ch)
{
	return ch == '0' || ch == '1';
}

/**
 * 数字（8进制）
 */
bool isDigit8(char ch)
{
	return ch >= '0' && ch <= '7';
}

/**
 * 数字（16进制）
 */
bool isDigit16(char ch)
{
	return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f');
}
