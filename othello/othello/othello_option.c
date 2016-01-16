#include "othello.h"

#include <stdio.h>
#include<ctype.h>
#include<string.h>

GAMEINFO getGameInfo(COMLINE com){
    GAMEINFO gameInfo;
    gameInfo.player[FIRST] = (com.opt['p'] && !strcmp(com.suf['p'],"computer")) ? COMPUTER : HUMAN;
    gameInfo.player[SECOND] = (com.opt['P'] && !strcmp(com.suf['P'],"human")) ? HUMAN : COMPUTER;
    gameInfo.comPower[FIRST] = (com.opt['c'] && isdigit(com.suf['c'][0])) ? com.suf['c'][0] - '0' : gameInfo.player[FIRST] == HUMAN ? HINTPOWER : COMPUTERPEWER;
    gameInfo.comPower[SECOND] = (com.opt['C'] && isdigit(com.suf['C'][0])) ? com.suf['C'][0] - '0' : gameInfo.player[SECOND] == HUMAN ? HINTPOWER : COMPUTERPEWER;
    return gameInfo;
}