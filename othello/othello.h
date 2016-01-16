#ifndef othello_h
#define othello_h

#include<stdio.h>
#include"standard.h"
#include"option.h"

#define SIZE_X 8//オセロ盤の大きさ。2以上なら自由な値を設定できる
#define SIZE_Y 8
#define COMPUTERPEWER 5//コーンピュータのデフォルトの強さ
#define HINTPOWER 5//ヒントの強さ

#define SUF_CHAR "ocCpP"//サフィックスを要するオプション
#define HELP "オセロをするプログラムです。\n頑張って作りました。\nUsage./othello [-p <human|computer>] [-P <human|computer>] [-c [1-9]] [-C [1-9]] [-o output.txt]\n  -p : 先手のプレイヤ。humanならユーザが、computerならコンピュータが打つ\n  -P : 後手のプレイヤ。humanならユーザが、computerならコンピュータが打つ\n  -c : 先手のコンピュータユーザの強さ。ヒューマンユーザならヒントの強さ。指定された数分先の手を読む\n -C : 後手のコンピュータユーザの強さ。ヒューマンユーザならヒントの強さ。指定された数分先の手を読む\n  -o : 指定されたファイルに棋譜を保存する\n"

typedef enum turn{//ターン
    FIRST,//先手
    SECOND,//後手
    EMPTY//空白
}TURN;
typedef enum player{//プレイヤ
    HUMAN,//人間
    COMPUTER//コンピュータユーザ
}PLAYER;
typedef struct gameInfo{//ゲームに必要な初期情報
    PLAYER player[2];//[0]:先手、[1]:後手、のユーザ
    int comPower[2];//コンピュータユーザの強さ。読む手数
}GAMEINFO;
typedef struct gameData{
    TURN record[SIZE_Y * SIZE_X + 10][SIZE_Y][SIZE_X];//盤面の記録
    Vector2 putPos[SIZE_Y * SIZE_X + 10];//打った位置の記録
    PLAYER player[2];
    int comPower[2];
    TURN turn[SIZE_Y * SIZE_X + 10];//打ったユーザの記録
    int num;//総手数
}GAMEDATA;

//-----othello_do.c-----//
GAMEDATA othelloDo();//オセロの実行
GAMEDATA setingOthelloDo(const GAMEINFO gameInfo);//オセロの実行


//-----othello_human.c-----//
Vector2 inputPutStone(TURN stone[SIZE_Y][SIZE_X],const TURN turn);//位置の入力、確認、石を置く
Vector2 inputPos(TURN stone[SIZE_Y][SIZE_X],const TURN turn);//位置の入力


//-----othello_computer.c-----//
Vector2 comPutStone(TURN stone[SIZE_Y][SIZE_X],const TURN turn,int comPower);//CPUが石を置く
Vector2 getBestPos(TURN stone[SIZE_Y][SIZE_X],const TURN turn,const int readTurn);//readTurn手、先をよみ、最も高い勝ちを得られる手を返す。
Vector2 calcBestPos(TURN stone[SIZE_Y][SIZE_X],const TURN turn,int readTurn);//getBestPosの計算のための再帰関数
void makeStoneValue(int stoneValue[SIZE_Y][SIZE_X]);//盤上のマスに価値を設定
void makeStoneValueEqual(int stoneValue[SIZE_Y][SIZE_X]);//盤上のマスに等しい価値を設定
int calcValue(const TURN reverseStone[SIZE_Y][SIZE_X],const TURN turn,const int stoneValue[SIZE_Y][SIZE_X]);//価値を計算
int calcTimes(int comPower,const TURN stone[SIZE_Y][SIZE_X]);//1ターンの計算時間をおよそ一定とした時の先読みする手数を考える

//-----othello_putStone.c-----//
int checkPass(const TURN stone[SIZE_Y][SIZE_X],const TURN turn);//石を置ける場所があるか。なければパスとなる。戻り値は石のおける位置の数
int putReverse(TURN stone[SIZE_Y][SIZE_X],const Vector2 pos,const TURN turn);//ひっくり返す。戻り値はひっくり返した数。ひっくり返した後の盤面の状態はstoneに更新されている
int putReverseVector(TURN stone[SIZE_Y][SIZE_X],const Vector2 pos,const Vector2 direction,const TURN turn);//putReverseのための関数。directionで指定された方向でひっくり返すか確認。戻り値はひっくり返した数。//ひっくり返した後の盤面の状態はstoneに更新されている
int checkCanReverse(const TURN stone[SIZE_Y][SIZE_X],const Vector2 pos,const TURN turn);//ひっくり返せるか確認。戻り値はひっくり返せる数。
int checkCanReverseVector(const TURN stone[SIZE_Y][SIZE_X],const Vector2 pos,const Vector2 direction,const TURN turn);//checkCanReverseのための関数。directionで指定された方向でひっくり返せるか確認。戻り値はひっくり返せる数。


//-----othello_save.c-----//
void recordGameData(GAMEDATA *gameData,const TURN stone[SIZE_Y][SIZE_X],const Vector2 pos,const TURN turn);//GAMEDATAにデータ格納
void outputGameData(const GAMEDATA gameData,char *outputFileName);//ファイルに棋譜データ保存
void outputOneTurn(FILE *fp,const TURN turn,const Vector2 pos);//ファイルにワンターンの情報を表示


//-----othello_output.c-----//
void result(const TURN stone[SIZE_Y][SIZE_X]);//対局結果の表示
void display(const TURN stone[SIZE_Y][SIZE_X]);//盤面を表示
void displayLine();//ライン表示
void fresult(FILE *fp, const TURN stone[SIZE_Y][SIZE_X]);//ファイルに対局結果を表示
void fdisplay(FILE *fp,const TURN stone[SIZE_Y][SIZE_X]);//ファイルに盤面を表示
void fdisplayLine(FILE *fp);//ファイルにライン表示


//-----othello_stone.c-----//
int Reverse(TURN stone[SIZE_Y][SIZE_X],const TURN reverseStone[SIZE_Y][SIZE_X]);//reverseStoneを元にひっくり返す、というより、更新するといえる
void copyStone(TURN stone[SIZE_Y][SIZE_X],const TURN fromStone[SIZE_Y][SIZE_X]);
void resetStone(TURN stone[SIZE_Y][SIZE_X]);//盤上の石をなくす
void formatStone(TURN stone[SIZE_Y][SIZE_X]);//盤上の石の配置の初期化
int countStone(const TURN stone[SIZE_Y][SIZE_X],TURN turn);//盤上の石の数


//-----othello_option.c-----//
GAMEINFO getGameInfo(COMLINE com);//オプション情報からオセロに関する情報を設定する

#endif
