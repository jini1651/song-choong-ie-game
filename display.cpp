#include <ncurses.h>

#include "setting.h"
#include "map.h"

using namespace std;

#define COLOR_GRAY 8

void makeWin(){
  win_map = newwin(MAP_HEIGHT, MAP_WIDTH, 3, 5);
  win_score = newwin(MAP_HEIGHT/2, 20, 3, 8+MAP_WIDTH);
  win_rule = newwin(MAP_HEIGHT/2, 20, 4+MAP_HEIGHT/2, 8+MAP_WIDTH);
  win_notice = newwin(5, 20, 3+8, 5+10);
}

void delWin(){
  delwin(win_notice);
  delwin(win_rule);
  delwin(win_score);
  delwin(win_map);
  endwin();
}

void setColor(){
// COLOR_BLACK   0                                                      
// COLOR_RED     1                                                      
// COLOR_GREEN   2                                                      
// COLOR_YELLOW  3                                                      
// COLOR_BLUE    4                                                      
// COLOR_MAGENTA 5                                                      
// COLOR_CYAN    6                                                      
// COLOR_WHITE   7  
  
  init_color(COLOR_GRAY, 150, 150, 150);
  init_pair(EMPTY, COLOR_WHITE, COLOR_WHITE);
  init_pair(WALL, COLOR_GRAY, COLOR_GRAY);
  init_pair(IMMUNE_WALL, COLOR_BLACK, COLOR_BLACK);
  init_pair(SNAKE_HEAD, COLOR_CYAN, COLOR_WHITE);
  init_pair(SNAKE_BODY, COLOR_BLUE, COLOR_WHITE);
  init_pair(GROWTH_ITEM, COLOR_WHITE, COLOR_GREEN);
  init_pair(POSION_ITEM, COLOR_WHITE, COLOR_RED);
  init_pair(GATE, COLOR_WHITE, COLOR_YELLOW);

}

void startDisplay(){
  initscr();
	makeWin();
  start_color();

  mvprintw(1, 22, "JungWoo's SongChoongE Game !!");
  refresh();

	wborder(win_map, '|', '|', '-', '-', '+', '+', '+', '+');   
	wborder(win_score, '|', '|', '-', '-', '+', '+', '+', '+');  
	wborder(win_rule, '|', '|', '-', '-', '+', '+', '+', '+');

  mvwprintw(win_score, 1, 5, "%s", "YOUR SCORE");
  mvwprintw(win_score, 3, 2, "%s", "B : Length");
  mvwprintw(win_score, 4, 2, "%s", "+ : Growth Items");
  mvwprintw(win_score, 5, 2, "%s", "- : Poison Items");
  mvwprintw(win_score, 6, 2, "%s", "G : Gates");

  mvwprintw(win_rule, 1, 4, "%s", "MISSON BOARD");
  mvwprintw(win_rule, 3, 2, "%s", "B : Length");
  mvwprintw(win_rule, 4, 2, "%s", "+ : Growth Items");
  mvwprintw(win_rule, 5, 2, "%s", "- : Poison Items");
  mvwprintw(win_rule, 6, 2, "%s", "G : Gates");

  mvwprintw(win_map, 10, 4, "%s", "Press any key to start the game");
	wrefresh(win_map);
	wrefresh(win_score);
	wrefresh(win_rule);

	// wborder(win_notice, '|', '|', '-', '-', '+', '+', '+', '+');

	// wrefresh(win_notice);
}

void gameOver(){
  wattron(win_notice, COLOR_PAIR(POSION_ITEM));
  for(int y=0; y<5; y++){
    for(int x=0; x<20; x++){
      mvwprintw(win_notice, y, x, "%s", " ");
    }
  }
  mvwprintw(win_notice, 2, 4, "%s", "GAME OVER !!");
  wattroff(win_notice, COLOR_PAIR(POSION_ITEM));

  wrefresh(win_notice);
}

void nextStage(){
  wattron(win_notice, COLOR_PAIR(SNAKE_BODY));
  for(int y=0; y<5; y++){
    for(int x=0; x<20; x++){
      mvwprintw(win_notice, y, x, "%s", " ");
    }
  }
  mvwprintw(win_notice, 2, 4, "%s", "NEXT STAGE !");
  mvwprintw(win_notice, 3, 3, "%s", "(PRESS ANY KEY)");
  wattroff(win_notice, COLOR_PAIR(SNAKE_BODY));

  wrefresh(win_notice);

  getch();
  wclear(win_notice);
}

void gameEnd(){
  wattron(win_notice, COLOR_PAIR(GATE));
  for(int y=0; y<5; y++){
    for(int x=0; x<20; x++){
      mvwprintw(win_notice, y, x, "%s", " ");
    }
  }
  mvwprintw(win_notice, 2, 3, "%s", "YOU ARE JUNGWOO");
  wattroff(win_notice, COLOR_PAIR(GATE));

  wrefresh(win_notice);
}

void drawMap(){
  
  start_color();
  setColor();

  int val;

  for(int y=0; y<MAP_HEIGHT; y++){
    for(int x=0; x<MAP_WIDTH; x++){
      val = cur_map[y][x];
      if(val==0)  val=8;
      wattron(win_map, COLOR_PAIR(val));
      mvwprintw(win_map, y, x, "%s", "@");
      wattroff(win_map, COLOR_PAIR(val));
    }
  }

  wrefresh(win_map);
}
void setBoard(int stage){
  
  start_color();
  setColor();

  int length, grows, poisons, gates;
  length = total_score[stage][0];
  grows = total_score[stage][1];
  poisons = total_score[stage][2];
  gates = total_score[stage][3];

  mvwprintw(win_score, 1, 5, "%s", "YOUR SCORE");
  mvwprintw(win_score, 3, 2, "%s %s / %d (%s)          ", "B : ", " ", length, " ");
  mvwprintw(win_score, 4, 2, "%s %s / %d (%s)         ", "+ : ", " ", grows, " ");
  mvwprintw(win_score, 5, 2, "%s %s / %d (%s)         ", "- : ", " ", poisons, " ");
  mvwprintw(win_score, 6, 2, "%s %s / %d (%s)         ", "G : ", " ", gates, " ");

  mvwprintw(win_rule, 1, 4, "%s", "MISSON BOARD");
  mvwprintw(win_rule, 3, 2, "%s %d          ", "B : ", length);
  mvwprintw(win_rule, 4, 2, "%s %d          ", "+ : ", grows);
  mvwprintw(win_rule, 5, 2, "%s %d          ", "- : ", poisons);
  mvwprintw(win_rule, 6, 2, "%s %d          ", "G : ", gates);

	wrefresh(win_score);
	wrefresh(win_rule);
}

void updateBoard(int myB=0, int myP=0, int myM=0, int myG=0){
  
  start_color();
  setColor();

  // int length, grows, poisons, gates;
  // length = total_score[stage][0];
  // grows = total_score[stage][1];
  // poisons = total_score[stage][2];
  // gates = total_score[stage][3];

  mvwprintw(win_score, 1, 5, "%s", "YOUR SCORE");
  mvwprintw(win_score, 3, 2, "%s %d", "B : ", myB);
  mvwprintw(win_score, 4, 2, "%s %d", "+ : ", myP);
  mvwprintw(win_score, 5, 2, "%s %d", "- : ", myM);
  mvwprintw(win_score, 6, 2, "%s %d", "G : ", myG);

	wrefresh(win_score);
}
