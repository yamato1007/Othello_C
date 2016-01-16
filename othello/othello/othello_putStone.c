#include "othello.h"

#include <stdio.h>

int checkPass(const TURN stone[SIZE_Y][SIZE_X],const TURN turn){
    Vector2 pos;
    int n=0;
    for(pos.y = 0; pos.y < SIZE_Y; pos.y++){
        for(pos.x = 0; pos.x < SIZE_X; pos.x++){
            if(checkCanReverse(stone,pos,turn))
                n++;
        }
    }
    return n;//盤上における数を返す
}
int putReverse(TURN stone[SIZE_Y][SIZE_X],const Vector2 pos,const TURN turn){
    int n = 0;
    int i,j;
    Vector2 direction;
    if(stone[pos.y][pos.x] == EMPTY){
        stone[pos.y][pos.x] = turn;
        for(i = -1; i <= 1; i++){
            for(j = -1 ;j <= 1;j++){
                if(i != 0 || j != 0){
                    direction = makeVector2(i,j);//縦横斜めすべての向き
                    n += putReverseVector(stone,pos,direction,turn);//stoneに置いた後の状態が保存される
                }
            }
        }
    }
    return n;
}
int checkCanReverse(const TURN stone[SIZE_Y][SIZE_X],const Vector2 pos,const TURN turn){
    int i,j;
    Vector2 direction;
    if(stone[pos.y][pos.x] == EMPTY){
        for(i = -1; i <= 1; i++){
            for(j = -1 ;j <= 1;j++){
                if(i != 0 || j != 0){
                    direction = makeVector2(i,j);//縦横斜めすべての向き
                    if(checkCanReverseVector(stone,pos,direction,turn))//それぞれの向きに対しひっくり返せるか
                        return 1;
                }
            }
        }
    }
    return 0;
}
int putReverseVector(TURN stone[SIZE_Y][SIZE_X],const Vector2 pos,const Vector2 direction,const TURN turn){
    
    TURN tmp[SIZE_Y][SIZE_X];
    TURN enemy = turn == FIRST ? SECOND : FIRST;
    int n = 0;
    Vector2 i;
    resetStone(tmp);
    for(i = pos, i.x += direction.x, i.y += direction.y;
        0 <= i.x && i.x < SIZE_X &&
        0 <= i.y && i.y < SIZE_Y ;
        i.x += direction.x , i.y += direction.y){//歩を進め、敵の石ならループ
        if(stone[i.y][i.x] == enemy){
            tmp[i.y][i.x] = turn;
            n++;
        }
        else if(stone[i.y][i.x] == turn){
            Reverse(stone,tmp);
            return n;
        }
        else break;
    }
    return 0;
}
int checkCanReverseVector(const TURN stone[SIZE_Y][SIZE_X],const Vector2 pos,const Vector2 direction,const TURN turn){
    
    TURN enemy = turn == FIRST ? SECOND : FIRST;
    int flag = 0;
    Vector2 i;
    for(i = pos, i.x += direction.x, i.y += direction.y;
        0 <= i.x && i.x < SIZE_X &&
        0 <= i.y && i.y < SIZE_Y ;
        i.x += direction.x , i.y += direction.y){//歩を進め、敵の石ならループ
        if(stone[i.y][i.x] == enemy)                flag = 1;
        else if(stone[i.y][i.x] == turn && flag)    return 1;
        else break;
    }
    return 0;
}