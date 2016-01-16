#include"othello.h"

#include <stdio.h>

void result(const TURN stone[SIZE_Y][SIZE_X]){
    fresult(stdout, stone);
    clearDisplay();
}
void display(const TURN stone[SIZE_Y][SIZE_X]){
    clearDisplay();
    fdisplay(stdout, stone);
}
void displayLine(){
    fdisplayLine(stdout);
}
void fresult(FILE *fp, const TURN stone[SIZE_Y][SIZE_X]){
    int score[EMPTY + 1];
    int i;
    for(i = FIRST;i <= EMPTY;i++)
        score[i] = countStone(stone, i);
    fprintf(fp,"\n\n");
    fdisplay(fp,stone);
    fprintf(fp,"\n");
    fprintf(fp,"FIRST:%d\n",score[FIRST]);
    fprintf(fp,"SECOND:%d\n",score[SECOND]);
    fprintf(fp,"EMPTY:%d\n",score[EMPTY]);
    fprintf(fp,"\n");
    fprintf(fp,"%s turn won!\n",score[FIRST] >= score[SECOND] ? "First" : "Second");
}
void fdisplay(FILE *fp,const TURN stone[SIZE_Y][SIZE_X]){
    int i,j;
    
	fprintf(fp,"    ");
    for(i=0;i<SIZE_X;i++)
        fprintf(fp," %c  ",i+'a');
    fprintf(fp,"\n");
	for(i=0;i<SIZE_Y;i++){
        fdisplayLine(fp);
        fprintf(fp,"%2d |",i+1);
        for(j=0;j<SIZE_X;j++){
            switch(stone[i][j]){
                case FIRST: fprintf(fp," ● "); break;
                case SECOND: fprintf(fp," ○ "); break;
                case EMPTY: fprintf(fp,"   "); break;
                default: fprintf(fp,"%3d",stone[i][j]);
            }
            fprintf(fp,"|");
        }
        fprintf(fp,"\n");
    }
    fdisplayLine(fp);
}
void fdisplayLine(FILE *fp){
    int i;
    fprintf(fp,"    ");
    for(i=0;i<SIZE_X;i++)
        fprintf(fp,"----");
    fprintf(fp,"\n");
}