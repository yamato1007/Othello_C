#ifndef STANDARD_H
#define STANDARD_H

#define CHARMAX 128//ASCIIコードの文字数
#define STRMAX 20

typedef struct vector2{//２次元ベクトル
    int x;
    int y;
}Vector2;

Vector2 makeVector2(int x,int y);//xとyからVector2型変数をつくり、返す
void clearDisplay();//コンソール画面の消去
void error(char *errormessage);//エラーメッセージを表示し強制終了

#endif
