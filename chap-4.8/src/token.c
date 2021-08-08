#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const TokenTable tokenTables[] = {
	{TK_ERROR, 0, 0, "TK_ERROR", ""},
	{TK_UNKNOWN, 0, 0, "TK_UNKNOWN", ""},
	{TK_EOF, 0, 0, "TK_EOF", ""},
	{TK_COMMENT, 0, 0, "TK_COMMENT", ""},

	//常量值
	{TK_NUMBER, 0, 0, "TK_NUMBER", ""},
	{TK_CHAR, 0, 0, "TK_CHAR", ""},
	{TK_STRING, 0, 0, "TK_STRING", ""},
	{TK_MULT_STRING, 0, 0, "TK_MULT_STRING", ""},

	//标识符
	{TK_ID, 0, 0, "TK_ID", ""},


	//分割符合
	{TK_SEMICON, 0, 0, "TK_SEMICON", ";"},	 //;
	{TK_COMMA, 0, 0, "TK_COMMA", ","},		   //,
	{TK_COLON, 0, 0, "TK_COLON", ":"},		   //:
	{TK_L_BRACE, 0, 0, "TK_L_BRACE", "{"},	 //{
	{TK_R_BRACE, 0, 0, "TK_R_BRACE", "}"},	 //}
	{TK_L_BRACKET, 0, 0, "TK_L_BRACKET", "["}, // [
	{TK_R_BRACKET, 0, 0, "TK_R_BRACKET", "]"}, //]
	{TK_L_PAREN, 0, 0, "TK_L_PAREN", "("},	 //(
	{TK_R_PAREN, 0, 0, "TK_R_PAREN", ")"},	 //)
	{TK_DOT, 0, 0, "TK_DOT", "."},			   //.

	//赋值
	{TK_ASSIGN, 0, 0, "TK_ASSIGN", "="}, //=

	    //自增自减
    {TK_SELF_ADD, 0, 0, "TK_SELF_ADD", "++"}, //++
    {TK_SELF_SUB, 0, 0, "TK_SELF_SUB", "--"}, //--

	//双目运算
	{TK_ADD, 0, 0, "TK_ADD", "+"}, //+
	{TK_SUB, 0, 0, "TK_SUB", "-"}, //-
	{TK_MUL, 0, 0, "TK_MUL", "*"}, //*
	{TK_DIV, 0, 0, "TK_DIV", "/"}, ///
	{TK_MOD, 0, 0, "TK_MOD", "%"}, //%

	//逻辑运算
	{TK_LOGIC_AND, 0, 0, "TK_LOGIC_AND", "&&"}, //&&
	{TK_LOGIC_OR, 0, 0, "TK_LOGIC_OR", "||"},   //||
	{TK_LOGIC_NOT, 0, 0, "TK_LOGIC_NOT", "!"},  //!

	//位运算
	{TK_BIT_AND, 0, 0, "TK_BIT_AND", "&"},					//&
	{TK_BIT_OR, 0, 0, "TK_BIT_OR", "|"},					//|
	{TK_BIT_XOR, 0, 0, "TK_BIT_XOR", "^"},					//^
	{TK_BIT_NOT, 0, 0, "TK_BIT_NOT", "~"},					//~
	{TK_BIT_SHIFT_LEFT, 0, 0, "TK_BIT_SHIFT_LEFT", "<<"},   //<<
	{TK_BIT_SHIFT_RIGHT, 0, 0, "TK_BIT_SHIFT_RIGHT", ">>"}, //>>

	//关系运算
	{TK_EQ, 0, 0, "TK_EQ", "=="},			//==
	{TK_NOT_EQ, 0, 0, "TK_NOT_EQ", "!="},   //!=
	{TK_GT, 0, 0, "TK_GT", ">"},			//>
	{TK_GT_EQ, 0, 0, "TK_GT_EQ", ">="},		//>=
	{TK_LT, 0, 0, "TK_LT", "<"},			//<
	{TK_LT_EQ, 0, 0, "TK_LT_EQ", "<="},		//<=
	{TK_QUESTION, 0, 0, "TK_QUESTION", "?"}, //?

	//关键字- 常量
	{TK_NULL, 0, 0, "TK_NULL", ""},   //null
	{TK_TRUE, 0, 0, "TK_TRUE", ""},   //true
	{TK_FALSE, 0, 0, "TK_FALSE", ""}, //false

	//关键字-语句
	{TK_VAR, TT_KEYWORD, 0, "TK_VAR", "var"},				 //var
	{TK_FUNC, TT_KEYWORD, 0, "TK_FUNC", "func"},			 //func
	{TK_STRUCT, TT_KEYWORD, 0, "TK_STRUCT", "struct"},		 //struct
	{TK_IF, TT_KEYWORD, 0, "TK_IF", "if"},					 //if
	{TK_ELSE, TT_KEYWORD, 0, "TK_ELSE", "else"},			 //else
	{TK_WHILE, TT_KEYWORD, 0, "TK_WHILE", "while"},			 //while
	{TK_FOR, TT_KEYWORD, 0, "TK_FOR", "for"},				 //for
	{TK_LOOP, TT_KEYWORD, 0, "TK_LOOP", "loop"},			 //loop
	{TK_BREAK, TT_KEYWORD, 0, "TK_BREAK", "break"},			 //break
	{TK_CONTINUE, TT_KEYWORD, 0, "TK_CONTINUE", "continue"}, //continue
	{TK_RETURN, TT_KEYWORD, 0, "TK_RETURN", "return"},		 //return

	//关键字-模块
	{TK_THIS, TT_KEYWORD, 0, "TK_THIS", "this"},	   //this
	{TK_SUPER, TT_KEYWORD, 0, "TK_SUPER", "super"},	//super
	{TK_MODULE, TT_KEYWORD, 0, "TK_MODULE", "module"}, //module
	{TK_IMPORT, TT_KEYWORD, 0, "TK_IMPORT", "import"}, //import
	{TK_TRAIT, TT_KEYWORD, 0, "TK_TRAIT", "trait"},	//trait
	{TK_IMPL, TT_KEYWORD, 0, "TK_IMPL", "impl"},	   //impl
};

char *Token_findKindName(TokenKind kind)
{
	int size = sizeof(tokenTables) / sizeof(TokenTable);
	for (int i = 0; i < size; i++)
	{
		if (tokenTables[i].kind == kind)
		{
			return tokenTables[i].kindName;
		}
	}
	return NULL;
}

char *Token_findKindWord(TokenKind kind)
{
	int size = sizeof(tokenTables) / sizeof(TokenTable);
	for (int i = 0; i < size; i++)
	{
		if (tokenTables[i].kind == kind && strlen(tokenTables[i].kindWord) != 0)
		{
			return tokenTables[i].kindWord;
		}
	}
	return NULL;
}

TokenKind Token_findKeywordKind(String *str)
{
	int size = sizeof(tokenTables) / sizeof(TokenTable);
	for (int i = 0; i < size; i++)
	{
		if (tokenTables[i].type == TT_KEYWORD)
		{
			if (String_compare(str, tokenTables[i].kindWord) == 0)
			{
				return tokenTables[i].kind;
			}
		}
	}
	return -1;
}
