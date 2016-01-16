#include"othello.h"

#include <stdio.h>
#include <string.h>

void recordGameData(GAMEDATA *gameData,const TURN stone[SIZE_Y][SIZE_X],const Vector2 pos,const TURN turn){
    gameData->turn[gameData->num] = turn;//諸所の情報を記録
    gameData->putPos[gameData->num] = pos;
    gameData->num++;
    copyStone(gameData->record[gameData->num],stone);
}
void outputGameData(const GAMEDATA gameData,char *outputFileName){
    FILE *fp;
    int i;
    if((fp = fopen(outputFileName,"w")) == NULL){
        char str[100] = "couldn't read file : ";
        error(strcat(str, outputFileName));
    }
    //テキストのみの棋譜
    if(gameData.player[gameData.turn[0]] == HUMAN)
        fprintf(fp,"先手 ● 「人間」  VS  ");
    else
        fprintf(fp,"先手 ● 「コンピュータLv.%d」  VS  ",gameData.comPower[gameData.turn[0]]);
    if(gameData.player[gameData.turn[1]] == HUMAN)
        fprintf(fp,"後手 ○ 「人間」\n\n");
    else
        fprintf(fp,"後手 ○ 「コンピュータLv.%d」\n\n",gameData.comPower[gameData.turn[1]]);
    for(i=0;i<gameData.num - 1;i++){
        outputOneTurn(fp,gameData.turn[i],gameData.putPos[i]);
        if(i%2 == 1)
            fprintf(fp,"\n" );
    }
    fresult(fp,gameData.record[gameData.num]);
    
    //盤も含めた棋譜
    fprintf(fp,"\n\n\n---------------------------------------\n\n\n" );
    for(i=0;i<gameData.num - 1;i++){
        fdisplay(fp, gameData.record[i]);
        fprintf(fp, "\n");
        outputOneTurn(fp,gameData.turn[i],gameData.putPos[i]);
        fprintf(fp,"\n" );
    }
    fresult(fp,gameData.record[gameData.num]);
    fclose(fp);
}
void outputOneTurn(FILE *fp,const TURN turn,const Vector2 pos){
    fprintf(fp,"%s: ",turn == FIRST ? "先手 ● " : "後手 ○ ");
    if(pos.x == -1 && pos.y == -1)
        fprintf(fp,"PASS");
    else
        fprintf(fp,"%c%c  ",pos.x+'a', pos.y+'1');
}