#include <ncurses.h>

#include "display.h"
#include "setting.h"
#include "game.h"

using namespace std;

WINDOW *win_map, *win_score, *win_rule, *win_notice;  
int cur_map[21][40];

int main()
{
	startDisplay();
	getch();

	for(int i=0; i<4; i++){
		if(stage(i)==0)	{
		    gameOver();
			break;
		}
		else if(i<3)	nextStage();
		else if(i==3)	gameEnd();
	}

	getch();
    delWin();
	endwin();
	
	return 0;
}                            