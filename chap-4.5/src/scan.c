
#include "scan.h"
#include  <string.h>
#include  <stdlib.h>

Scanner* Scanner_new(FILE* file){
    if(!file) {
        fprintf(stderr,"file is null\n");
        return NULL;
    }
    Scanner* scanner = (Scanner*) malloc(sizeof(Scanner));
    scanner->readPos=-1;
    scanner->lineSize=0;
    scanner->lineNum=1;
    scanner->colNum=0;
    scanner->lastch=' ';
    scanner->source=file;
    return scanner;
}

void Scanner_delete(Scanner* scanner){
    free(scanner);
}

char Scanner_getNextChar(Scanner* scanner){
  
    if(scanner == NULL){
        fprintf(stderr,"scanner is null\n");
        return -1;
    }

    //缓冲区读完
    if(scanner->readPos == (scanner->lineSize - 1)){
        scanner->lineSize = fread(scanner->buf,1,SCAN_BUF_LEN,scanner->source);
        if(scanner->lineSize==0) {
            scanner->lineSize = 1;
            scanner->buf[0] = -1;
        }
        scanner->readPos = -1;
    }

    scanner->readPos++;
    char ch = scanner->buf[scanner->readPos];
    //换行读取
    if(scanner->lastch=='\n') {
        scanner->colNum = 0;
    }

    if(ch==-1) {      //文件结束
        fclose(scanner->source);
        scanner->source = NULL;
    } else if(ch=='\n') {      //文件换行
        scanner->lineNum ++;
    } else {
        scanner->colNum ++;
    }
 
    scanner->lastch = ch;
    return ch;

}