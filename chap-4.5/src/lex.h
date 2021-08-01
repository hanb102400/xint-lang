#ifndef _LEX_H_
#define _LEX_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "scan.h"

typedef enum { 
    TK_ERROR,
	TK_UNKNOWN,
	TK_EOF,

	//数据类型
	TK_NUMBER, 
	TK_CHAR,
	TK_STRING,
	TK_ID,

	//关键字-语句
	TK_VAR,			//var
	TK_FUNC,		//func
	TK_STRUCT,		//struct
	TK_IF, 			//if
	TK_ELSE,		//else
	TK_WHILE,		//while
	TK_FOR,			//for
	TK_LOOP,		//loop
	TK_BREAK,		//break
	TK_CONTINUE,	//continue
    TK_RETURN,		//return
	//关键字-模块
	TK_THIS,	 //this
	TK_SUPER,	 //super
	TK_MODULE,	 //module
	TK_IMPORT,	 //import
    TK_TRAIT,	 //trait
    TK_IMPL,	 //impl


	//常量值
	TK_V_NULL, //null
	TK_V_TRUE,	//true
	TK_V_FALSE,	//false

		//分割符合
	TK_COMMA, 		//,
	TK_SEMICON, 		//;
	TK_COLON, 		//:
	TK_L_BRACE, 	//{
	TK_R_BRACE, 	//}
	TK_L_BRACKET, 	// [
	TK_R_BRACKET, 	//]
	TK_L_PAREN, 	//(
	TK_R_PAREN, 	//)
	TK_DOT,			 //.

	//赋值
	TK_ASSIGN,	//==

	//双目运算
	TK_ADD,	//+
	TK_SUB,	//-
	TK_MUL,	//*
	TK_DIV,	///
	TK_MOD, //%

	//逻辑运算
	TK_LOGIC_AND,  //&&
	TK_LOGIC_OR,   //||
	TK_LOGIC_NOT,  //!

	//位运算
	TK_BIT_AND,        //&
	TK_BIT_OR,         //|
	TK_BIT_XOR,        //^
	TK_BIT_NOT,        //~
	TK_BIT_SHIFT_LEFT, //<<
	TK_BIT_SHIFT_RIGHT, //>>

	//关系运算
	TK_EQ,			//=
	TK_NOT_EQ,		//!=
	TK_GT,			//>
	TK_GT_EQ,		//>=	
	TK_LT,			//<	
	TK_LT_EQ,		//<=
	TK_QUESTION, 	//?
	
} tokenType;

typedef enum  { 
	TS_ID_KEYWORD,
    TS_NUMBER, 
	TS_CHAR,
	TS_STRING,
    TS_COMMENT
} TokenStatus;

typedef union { 
    uint32_t intVal;
    double doubleVal;
    char charVal;
    char* stringVal;
} TokenVal;

typedef struct Token_{
    uint32_t size;
	uint32_t lineNo;
    tokenType tokenType;
    TokenVal tokenVal;
} Token;

typedef  struct Lexer_ {
    char curCh;
    int  curStatus;
	Token curToken;
    Token lastToken;
    Scanner* scanner;
} Lexer;


Lexer* Lexer_new(Scanner* scanner);

void Lexer_delete(Lexer* lexer);

Token* Lexer_getNextToken(Lexer* lexer);

#endif