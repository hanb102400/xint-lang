
#include "scan.h"

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
    scanner->aheadStatus=0;
    scanner->curCh='\0';
    scanner->lastCh='\0';
    scanner->source=file;
    return scanner;
}

void Scanner_delete(Scanner* scanner){
    free(scanner);
}

/* aheadStatus: 0非预读，1预读 */
char Scanner_nextChar(Scanner* scanner){
  
    if(scanner == NULL){
        fprintf(stderr,"scanner is null\n");
        return -1;
    }

    //预读状态(读缓存字符)
    if(scanner->aheadStatus==1){
         scanner->aheadStatus = 0;
    }
    //非预读（直接读取）
    else{
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
        scanner->lastCh = scanner->curCh;
        scanner->curCh = scanner->buf[scanner->readPos];

         //换行读取
        if(scanner->lastCh=='\n') {
            scanner->colNum = 0;
        }
        if(scanner->curCh==-1) {      //文件结束
            fclose(scanner->source);
            scanner->source = NULL;
        } else if(scanner->curCh=='\n') {      //文件换行
            scanner->lineNum ++;
        } else {
            scanner->colNum ++;
        }
    }
    return scanner->curCh;

}

char Scanner_lookAheadChar(Scanner* scanner){
    char aheadCh = Scanner_nextChar(scanner);
    scanner->aheadStatus=1;
    return aheadCh;
}

bool Scanner_matchNextChar(Scanner* scanner,char ch){
    if(Scanner_lookAheadChar(scanner)==ch) {
        Scanner_nextChar(scanner);
        return true;
    }
    return false;
}