#ifndef _DISPLAY_
#define _DISPLAY_

void makeWin(void);
void delWin(void);
void startDisplay(void);
void setColor(void);
void drawMap(void);
void setBoard(int stage);
void updateBoard(int stage, int myB=0, int myP=0, int myM=0, int myG=0);
void gameOver(void);
void nextStage(void);
void gameEnd(void);

#endif