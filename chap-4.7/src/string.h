#ifndef _SDSTRING_H_
#define _SDSTRING_H_

#include <stdint.h>

typedef  struct String_{
    int64_t len;    //已使用内存大小
    int64_t alloc;  //已分配内存大小
    char  buf[];
} String;


int64_t String_len(String *str);

String* String_new();

void String_delete(String *str);

int64_t String_size(String* str);

String* String_append(String *str,char ch);

int64_t String_compare(String* str,char* strs);

void String_println(String* str);

#endif