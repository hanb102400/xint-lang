#include "string.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern String* String_realloc(String* str, int64_t alloc);

String* String_new(){
    int64_t cap = 16;
    String *str = (String*) malloc(sizeof(String)) + sizeof(char)*cap;
    str->len=0;
    str->alloc=16;
    str->buf[0] = '\0';
    return str;
}

void String_delete(String* str) {
    free(str);
}

int64_t String_size(String* str) {
    return str->len;
}

String* String_append(String* str,char ch){
    if(str->len == str->alloc-1) {
        str = String_realloc(str,str->alloc*2);
    }
    str->len++;
    str->buf[str->len-1] = ch;
    str->buf[str->len] = '\0';
    return str;
}

int64_t String_compare(String* str,char* strs){
    return strcmp(str->buf,strs);
}


String* String_realloc(String* str, int64_t alloc){
    String *strNew = (String*) malloc(sizeof(String)) + sizeof(char)*alloc;

    memcpy(strNew->buf, str->buf, str->len);
    strNew->len=str->len;
    strNew->alloc=alloc;
    return strNew;
}


void String_println(String* str){
     fprintf(stdout,"string is [%s]\n",str->buf);
}