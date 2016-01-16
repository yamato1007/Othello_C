#include "othello.h"

#include <stdio.h>
#include <math.h>

Vector2 comPutStone(TURN stone[SIZE_Y][SIZE_X],const TURN turn,int comPower){
    Vector2 pos;
    int readTurn;
    
    readTurn = calcTimes(comPower,stone);
    
    pos = getBestPos(stone, turn, readTurn);
    putReverse(stone,pos,turn);//reversStoneにひっくり返る石が保存される
    return pos;
}
Vector2 getBestPos(TURN stone[SIZE_Y][SIZE_X],const TURN turn,const int readTurn){
    TURN tmpStone[SIZE_Y][SIZE_X];
    Vector2 pos;
    
    copyStone(tmpStone, stone);
    pos = calcBestPos(tmpStone, turn, readTurn);//価値を元に最善手を導出
    //display(tmpStone);
    return pos;
}
Vector2 calcBestPos(TURN stone[SIZE_Y][SIZE_X],const TURN turn,int readTurn){
    
    Vector2 pos;
    int value;
    int passFlag = 1;//パスなら1
    int beforePassFlag = 0;//パスなら1
    
    TURN nextTurn = turn == FIRST ? SECOND : FIRST;
    
    int stoneValue[SIZE_Y][SIZE_X];
    TURN maxValueStone[SIZE_Y][SIZE_X];
    Vector2 maxValuePos = makeVector2(-1, -1);
    int maxValue = -1000000;
    
    copyStone(maxValueStone,stone);
    
    if(readTurn < 0){
        beforePassFlag = 1;
        readTurn = -readTurn;
    }
    readTurn--;
    
    for(pos.y = 0; pos.y < SIZE_Y; pos.y++){
        for(pos.x = 0; pos.x < SIZE_X; pos.x++){
            if(checkCanReverse(stone,pos,turn)){
                TURN tmpStone[SIZE_Y][SIZE_X];
                copyStone(tmpStone, stone);
                putReverse(tmpStone,pos,turn);//今の手を打った後の盤上の状態を作る
                if(readTurn > 0)
                    calcBestPos(tmpStone, nextTurn, readTurn);  //再帰。次の敵の最善手を読む
                countStone(tmpStone, EMPTY) == 0 ? makeStoneValueEqual(stoneValue) : makeStoneValue(stoneValue);//読む手数でマスがすべて埋まるなら数のみで評価をつけたほうが良い。
                value = calcValue(tmpStone,turn,stoneValue);//その手の評価を決める
//                if(value > maxValue){//最善手なら保存
//                    maxValuePos = pos;
//                    maxValue = value;
//                    copyStone(maxValueStone,tmpStone);
//                }
                if(value > maxValue){//最善手なら保存
                    maxValuePos = pos;
                    maxValue = value;
                    copyStone(maxValueStone,tmpStone);
                }
                passFlag = 0;
            }
        }
    }
    if(readTurn > 0 && passFlag && !beforePassFlag){//パスせざるを負えない時。これがないとパスより先を読まない。2連続パスの時は実行しない
        if(countStone(stone, EMPTY) <= readTurn + 1)
            readTurn++;//読む手数でマスがすべて埋まるなら数のみで評価をつけたほうが良い。パスするとマスがひとつ埋まらなくなるため、読む手数を１手増やしている
        calcBestPos(maxValueStone, nextTurn,-(readTurn));  //再帰。パスの証明としてマイナスで送る。
    }
    copyStone(stone, maxValueStone);
    return maxValuePos;
}
void makeStoneValue(int stoneValue[SIZE_Y][SIZE_X]){
    int i,j;
	for(i=0;i<SIZE_Y;i++){
        for(j=0;j<SIZE_X;j++){
            if(2 <= i && i < SIZE_Y - 2 &&
               2 <= j && j < SIZE_X - 2)//内部
                stoneValue[i][j] = 4;
            if(i == 1 || i == SIZE_Y - 2 ||
               j == 1 || j == SIZE_X - 2)//端のひとつ内側
                stoneValue[i][j] = -10;
            if(i == 0 || i == SIZE_Y - 1 ||
               j == 0 || j == SIZE_X - 1 )//端
                stoneValue[i][j] = 100;
            if((i == 1 || i == SIZE_Y - 2) &&
               (j == 1 || j == SIZE_X - 2))//角のひとつ内側
                stoneValue[i][j] = -500;
            if((i == 0 || i == SIZE_Y - 1) &&
               (j == 0 || j == SIZE_X - 1))//角
                stoneValue[i][j] = 10000;
        }
    }
}
void makeStoneValueEqual(int stoneValue[SIZE_Y][SIZE_X]){
    int i,j;
	for(i=0;i<SIZE_Y;i++){
        for(j=0;j<SIZE_X;j++){
            stoneValue[i][j] = 1; //すべて等価。数だけで評価をつける
        }
    }
}
int calcValue(const TURN reverseStone[SIZE_Y][SIZE_X],const TURN turn,const int stoneValue[SIZE_Y][SIZE_X]){
    int value = 0;
    int i,j;
    TURN enemy = turn == FIRST ? SECOND : FIRST;
    for(i=0;i<SIZE_Y;i++){
        for(j=0;j<SIZE_X;j++){
            if(reverseStone[i][j] == turn)//その石の場所に設定された価値を足す
                value += stoneValue[i][j];
            else if(reverseStone[i][j] == enemy)//相手の石ならマイナス
                value -= stoneValue[i][j];
        }
    }
    return value;
}
int calcTimes(int comPower,const TURN stone[SIZE_Y][SIZE_X]){
    int readTurn;
    readTurn = comPower;
    //readTurn = (countStone(stone, EMPTY) <= comPower * 2) ? comPower * 2 : comPower;
    return readTurn;
}