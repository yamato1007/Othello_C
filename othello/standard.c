#include "standard.h"

#include<stdio.h>
#include<stdlib.h>

Vector2 makeVector2(int x,int y){
    Vector2 tmp = {x,y};
    return tmp;
}
void clearDisplay(){//調べたが、macでコンソールの表示を消す方法がわからず。どれも失敗
    system("cls");//windowではこれで消せる
    //system( "clear" );
    //system( "reset" );
    //puts("\x1b[2J");
    //printf("¥033[2J");
    //printf("\E[H\E[2J");
    //system( "/usr/bin/clear" );
}
void error(char *errormessage){
    fprintf(stderr,"error : %s\n",errormessage);
    exit(1);//強制終了
}