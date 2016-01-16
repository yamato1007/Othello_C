#include"othello.h"

#include <stdio.h>
#include <string.h>


Vector2 inputPutStone(TURN stone[SIZE_Y][SIZE_X],const TURN turn){
    Vector2 pos;
    pos = inputPos(stone,turn);//座標入力
    if(checkCanReverse(stone,pos,turn)){//おけるかどうか
        putReverse(stone, pos, turn);
        return pos;
    }else{
        printf("そこには置けません\n");
        return inputPutStone(stone,turn);
    }
}
Vector2 inputPos(TURN stone[SIZE_Y][SIZE_X],const TURN turn){
    Vector2 pos;
    char str[STRMAX];
    printf("入力([a-h][1-8])：");
    scanf("%s",str);
    if(!strcmp(str,"hint")){//ヒントの表示。コンピュータに次の最善手を考えさせる
        printf("--computer is thinking--\n");
        Vector2 pos = getBestPos(stone, turn,HINTPOWER);
        printf("hint : %c%c\n",pos.x+'a',pos.y+'1');
    }
    pos.x = str[0] - 'a';
    pos.y = str[1] - '1';
    if(0 <= pos.x && pos.x < SIZE_X &&
       0 <= pos.y && pos.y < SIZE_Y)
        return pos;
    else return inputPos(stone,turn);
}