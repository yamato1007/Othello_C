#include "othello.h"

#include <stdio.h>

int Reverse(TURN stone[SIZE_Y][SIZE_X],const TURN reverseStone[SIZE_Y][SIZE_X]){
    int i,j;
    int n = 0;
    for(i=0;i<SIZE_Y;i++){
        for(j=0;j<SIZE_X;j++){
            if(reverseStone[i][j] == FIRST ||
               reverseStone[i][j] == SECOND){//石があれば上書き
                stone[i][j] = reverseStone[i][j];
                n++;
            }
        }
    }
    return n;
}
void copyStone(TURN stone[SIZE_Y][SIZE_X],const TURN fromStone[SIZE_Y][SIZE_X]){
    int i,j;
    for(i=0;i<SIZE_Y;i++){
        for(j=0;j<SIZE_X;j++){
            stone[i][j] = fromStone[i][j];
        }
    }
}
void resetStone(TURN stone[SIZE_Y][SIZE_X]){
    int i,j;
    for(i=0;i<SIZE_Y;i++){
        for(j=0;j<SIZE_X;j++){
            stone[i][j] = EMPTY;
        }
    }
}
void formatStone(TURN stone[SIZE_Y][SIZE_X]){
    resetStone(stone);
    stone[SIZE_Y/2-1][SIZE_X/2] = stone[SIZE_Y/2][SIZE_X/2-1] = FIRST;
    stone[SIZE_Y/2][SIZE_X/2] = stone[SIZE_Y/2-1][SIZE_X/2-1] = SECOND;
}
int countStone(const TURN stone[SIZE_Y][SIZE_X],TURN turn){
    int i,j;
    int n=0;
	for(i=0;i<SIZE_Y;i++){
        for(j=0;j<SIZE_X;j++){
            if(stone[j][i] == turn)
                n++;
        }
    }
    return n;
}