#ifndef OPTION_H
#define OPTION_H

#include"standard.h"

typedef struct commandLine{//オプション情報
    int opt[CHARMAX];
    char suf[CHARMAX][STRMAX];
    char str[STRMAX];
} COMLINE;

COMLINE getComline(int argc, const char **argv,char *sufChar);//コマンドラインオプション情報の取得
#endif

