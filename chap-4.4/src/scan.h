#ifndef _SCAN_H_
#define _SCAN_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SCAN_BUF_LEN 80

typedef struct  Scanner_ {
    int readPos;
    int lineSize;
    int lineNum;
    int colNum;
    int aheadStatus;
    char curCh;
    char lastCh;
    FILE* source;
    char buf[SCAN_BUF_LEN];
} Scanner;


Scanner* Scanner_new(FILE* file);

void Scanner_delete(Scanner* scanner);

/* 读取下一个字符 */
char Scanner_nextChar(Scanner* scanner);

/* 预读一个字符 */
char Scanner_lookAheadChar(Scanner* scanner);

/* 匹配才读取 */
bool Scanner_matchNextChar(Scanner* scanner,char ch);

#endif