#ifndef _SCAN_H_
#define _SCAN_H_

#include <stdint.h>
#include <stdio.h>

#define SCAN_BUF_LEN 80

typedef struct  Scanner_ {
    uint32_t readPos;
    uint32_t lineSize;
    uint32_t lineNum;
    uint32_t colNum;
    char lastch;
    FILE* source;
    char buf[SCAN_BUF_LEN];
} Scanner;

/**
 *Scanner 构造方法
 */
Scanner* Scanner_new(FILE* file);

/**
 *Scanner 析构方法
 */
void Scanner_delete(Scanner* scanner);

/**
 *Scanner 扫描下一个字符
 */
char Scanner_getNextChar(Scanner* scanner);

#endif