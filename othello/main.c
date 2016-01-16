#include "othello.h"
#include "option.h"

int main(int argc,char **argv){
    COMLINE com;//オプションの情報を格納
    GAMEINFO gameInfo;//オセロを始めるための初期情報を格納。プレイヤ、コンピュータの強さ
    GAMEDATA gameData;//オセロの棋譜
    com = getComline(argc,(const char **)argv,SUF_CHAR);//コマンドライン引数をオプション情報へ変換
    if(com.opt['h']){
        printf(HELP);//ヘルプの表示
    }else{
        gameInfo = getGameInfo(com);//オプション情報からオセロの設定
        gameInfo.comPower[FIRST] = 6;
        gameInfo.comPower[SECOND] = 6;
        gameInfo.player[FIRST] = COMPUTER;
        gameInfo.player[SECOND] = COMPUTER;
        gameData = setingOthelloDo(gameInfo);//オセロする
        if(com.opt['o']){
            outputGameData(gameData, com.suf['o']);//棋譜の保存。
        }
    }
    return 0;
}