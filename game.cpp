#include <ncurses.h>
#include <cstring>
#include <ctime>
#include <random>

#include "setting.h"
#include "map.h"
#include "display.h"
#include "snake.h"
#include "kbhit.cpp"
#include "item.h"
#include "gate.h"

using namespace std;

void move(void);
int check_and_update_score(void);
Snake snake;
Gate gate;
int score[4];
int B, P, M, G;

int stage(int stage){
  	snake = Snake();
	Item items[3] = {Item(), Item(), Item()};
	gate = Gate();

	int B=0;
	int P=0;
	int M=0;
	int G=0;
	score[0] = total_score[stage][0];
	score[1] = total_score[stage][1];
	score[2] = total_score[stage][2];
	score[3] = total_score[stage][3];

	memcpy(cur_map, total_map[stage], sizeof(total_map[stage]));
	drawMap();
	setBoard(stage);

	snake.printSnake();
																							
	noecho();
	cbreak();
	keypad(win_map, TRUE);
  	int key, item_n;
	int next_y, next_x;
	clock_t start;
 
	while(key != KEY_F(1)){   
		start = clock();
		key = 0;
		while(static_cast<double>(clock()-start)<500000){
			if(kbhit())	key = wgetch(win_map);
		}
		switch(key)
		{   
			case KEY_LEFT:    
				if(snake.getDirection()==HEAD_RIGHT) return 0;    
				snake.changeDir(3);
				move();
				break;     

			case KEY_RIGHT:      
				if(snake.getDirection()==HEAD_LEFT) return 0;                                                               
				snake.changeDir(1);
				move();
				break;       

			case KEY_UP:  
				if(snake.getDirection()==HEAD_DOWN) return 0;                                                                         
				snake.changeDir(0);
				move();
				break;

			case KEY_DOWN: 
				if(snake.getDirection()==HEAD_UP) return 0;                                                                      
				snake.changeDir(2);
				move();
				break;    

			default:           
				move();      
				break;
		}            
		if(!snake.isValid()) return 0;   

		item_n = rand()%3;
		if(items[item_n].getType()==EMPTY)	items[item_n].genItem();
		for(int i=0; i<3; i++){
			if(items[i].isEaten())		items[i].delItem(1);
			else if(items[i].isTimeout())	items[i].delItem(0);
		}

		if(gate.getMode()==GATE){
			if(gate.isUsed())	gate.setWaitingMode(snake.getLength()-1);
		}else if(gate.getMode()==USING_GATE){
			gate.beingUsed();
		}else if(gate.getMode()==WALL){
			gate.genGate();
		}

		if(check_and_update_score())	break;
	}

  return 1;
}

void move(void){
	int next_y, next_x;
	int y_out, x_out;

	snake.mvNext(&next_y, &next_x);

	if(cur_map[next_y][next_x]==GROWTH_ITEM)  {
		snake.grow(next_y, next_x);
		P++;
	}else if(cur_map[next_y][next_x]==POSION_ITEM) {
		snake.shorten(next_y, next_x);
		M++;
	}else if(cur_map[next_y][next_x]==GATE) {
		gate.getOutGate(next_y, next_x, &y_out, &x_out);
		snake.useGate(y_out, x_out);
		G++;
	}
	else{snake.move(next_y, next_x);}
}

int check_and_update_score(void){
	int sum_score = 0;
	B = snake.getLength();

	start_color();
	setColor();

	if(B>=score[0]){
		mvwprintw(win_score, 3, 2, "%s %d / %d (%s)          ", "B : ", B, score[0], "o");
		sum_score++;
	}
	else{mvwprintw(win_score, 3, 2, "%s %d / %d (%s)          ", "B : ", B, score[0], " ");}

	if(P>=score[1]){
		mvwprintw(win_score, 4, 2, "%s %d / %d (%s)         ", "+ : ", P, score[1], "o");
		sum_score++;
	}
	else{mvwprintw(win_score, 4, 2, "%s %d / %d (%s)         ", "+ : ", P, score[1], " ");}

	if(M>=score[2]){
		mvwprintw(win_score, 5, 2, "%s %d / %d (%s)         ", "- : ", M, score[2], "o");
		sum_score++;
	}
	else{mvwprintw(win_score, 5, 2, "%s %d / %d (%s)         ", "- : ", M, score[2], " ");}

	if(G>=score[3]){
		mvwprintw(win_score, 6, 2, "%s %d / %d (%s)         ", "G : ", G, score[3], "o");
		sum_score++;
	}else{mvwprintw(win_score, 6, 2, "%s %d / %d (%s)         ", "G : ", G, score[3], " ");}

	wrefresh(win_score);

	if(sum_score>=4){return 1;}

	return 0;
}


