#include"option.h"

#include<string.h>

COMLINE getComline(int argc, const char **argv,char *sufChar){
    int i,j;
    COMLINE com;
    for(i=0;i<CHARMAX;i++)
        com.opt[i] = 0;
    while(--argc){
        argv++;
        if(**argv == '-'){//オプションスイッチなら
            char c = *(*argv+1);
            com.opt[c] = 1;
            for(j=0; sufChar[j] != 0 ;j++){
                if(c == sufChar[j]){//サフィックスが必要なオプションスイッチなら次の文字列も取得
                    strcpy(com.suf[c],*(++argv));
                    argc--;
                }
            }
        }else{
            strcpy(com.str,*argv);
        }
    }
    return com;
}
