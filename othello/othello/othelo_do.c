#include "othello.h"

#define COM_WAITSECOND 0.0//コンピュータユーザの待ち時間
#define PASS_WAITSECOND 0.0//コンピュータユーザの待ち時間

#include<stdio.h>
#include<unistd.h>
#include<time.h>

#include<string.h>

GAMEDATA othelloDo(){
    GAMEINFO gameInfo;
    gameInfo.player[FIRST] = HUMAN;
    gameInfo.player[SECOND] = COMPUTER;
    gameInfo.comPower[FIRST] = HINTPOWER;
    gameInfo.comPower[SECOND] = COMPUTERPEWER;
    GAMEDATA gameData = setingOthelloDo(gameInfo);
    return gameData;
}

GAMEDATA setingOthelloDo(const GAMEINFO gameInfo){
    GAMEDATA gameData;
    TURN stone[SIZE_Y][SIZE_X];
    TURN turn = FIRST;
    int passFlag = 0;
    Vector2 pos;
    int canPutPosNum;
    double calcTime[2];
    
    formatStone(stone);//盤面の初期化
    
    calcTime[FIRST] = 0.0;
    calcTime[SECOND] = 0.0;
    gameData.player[FIRST] = gameInfo.player[FIRST];
    gameData.player[SECOND] = gameInfo.player[SECOND];
    gameData.comPower[FIRST] = gameInfo.comPower[FIRST];
    gameData.comPower[SECOND] = gameInfo.comPower[SECOND];
    gameData.num = 0;
    copyStone(gameData.record[0],stone);
    
    while(passFlag < 2 && countStone(stone, EMPTY)){//２連続でパスなら脱出、ゲーム終了
        canPutPosNum = checkPass(stone,turn);
        display(stone);
        printf("First:%d  Second:%d Empty:%d\n",countStone(stone,FIRST),countStone(stone, SECOND),countStone(stone, EMPTY));
        printf("%s's turn. You can put %d points.\n",((turn == FIRST )? "The first move" : "The second move"),canPutPosNum);
        if(canPutPosNum){
            if(gameData.player[turn] == HUMAN){//人間ユーザ
                pos = inputPutStone(stone,turn);
            }else{//コンピュータユーザ
                clock_t start,end;
                start = clock();
                printf("\n--computer Lv.%d is thinking--\n",gameData.comPower[turn]);
                pos = comPutStone(stone,turn,gameData.comPower[turn]);
                end = clock();
                printf("calclation time : %f\n\n", (double)(end - start) / CLOCKS_PER_SEC);
                if((double)COM_WAITSECOND > (double)(end - start) /CLOCKS_PER_SEC){
                    usleep((unsigned int) 1000000.0 * ((double)COM_WAITSECOND - (double)(end - start) /CLOCKS_PER_SEC));
                }
                
                //計算時間の統計を取るための記録--ここから--
//                FILE *fp;
//                char filename[100] = "computerLv";
//                filename[strlen(filename)] = gameData.comPower[turn] + '0';
//                strcat(filename,".txt");
//                if((fp = fopen(filename,"a")) == NULL){
//                    error( "couldn't read file : Othello_takeTime.txt");
//                }
//                calcTime[turn] += (double)(end-start)/CLOCKS_PER_SEC;
//                fprintf(fp,"%d %d %f\n",gameData.num,canPutPosNum,(double)(end-start)/CLOCKS_PER_SEC);
//                fclose(fp);
                //計算時間の統計を取るための記録--ここまで--
                
            }
            passFlag = 0;
        }else{//パスなら
            usleep((unsigned int)(PASS_WAITSECOND* 1000000.0));
            printf("\n---!%s are passsing!---\n\n",((turn == FIRST )? "The first move" : "The second move"));
            usleep((unsigned int)(PASS_WAITSECOND* 1000000.0));
            pos.x = -1; //パスの時は特別に-1を入れる
            pos.y = -1;
            passFlag++;
        }
        recordGameData(&gameData,stone,pos,turn);//棋譜保存
        turn = turn == FIRST ? SECOND : FIRST;//ターンの入れ替え
    }
    result(stone);//対局結果表示
    
    
    //計算時間の統計を取るための記録--ここから--
//    TURN turn_i;
//    for(turn_i = FIRST;turn_i <= SECOND;turn_i++){
//        if(gameData.player[turn_i] == COMPUTER){
//            FILE *fp;
//            if((fp = fopen("takeTime.txt","a")) == NULL){
//                error( "couldn't read file : Othello_takeTime.txt");
//            }
//            fprintf(fp,"%d %f\n",gameData.comPower[turn_i],calcTime[turn_i]);
//            fclose(fp);
//        }
//    }
    //計算時間の統計を取るための記録--ここまで--
    
    return gameData;
}