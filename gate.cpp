#include <ncurses.h>
#include <ctime>
#include <random>

#include "setting.h"
#include "gate.h"

using namespace std;
#define COLOR_GRAY 8

Gate::Gate(void)
{
  mode=WALL;   //none:4, grow:5, poison:6
  // genTime=time(NULL);     //when generated (when genTime=-1, Gate's mode is none)
  y0=0, x0=1, y1=1, x1=0;

  srand(static_cast<unsigned int>(time(NULL)));

  init_color(COLOR_GRAY, 150, 150, 150);
  init_pair(WALL, COLOR_GRAY, COLOR_GRAY);
  init_pair(GATE, COLOR_YELLOW, COLOR_YELLOW);
}

void Gate::genGate(){
  // mode = rand()%8;  //0~4:none, 7:gate

  // if(mode==GATE){   //none
    // while(1){
  y0 = rand()%MAP_HEIGHT;
  x0 = rand()%MAP_WIDTH;
  y1 = rand()%MAP_HEIGHT;
  x1 = rand()%MAP_WIDTH;

  if((cur_map[y0][x0]==WALL) && (cur_map[y1][x1]==WALL) && (y0!=y1 || x0!=x1)){
    mode = GATE;
    cur_map[y0][x0]=GATE;
    cur_map[y1][x1]=GATE;
    printGate();
  }
}

void Gate::delGate(){
  mode=WALL;

  // if(!used){
  cur_map[y0][x0]=WALL;
  cur_map[y1][x1]=WALL;
  printGate();
  // }
}

void Gate::printGate(){
  start_color();

  wattron(win_map, COLOR_PAIR(mode));
  mvwprintw(win_map, y0, x0, "%s", " ");
  mvwprintw(win_map, y1, x1, "%s", " ");
  wattroff(win_map, COLOR_PAIR(mode));

  wrefresh(win_map);
}

int Gate::getMode(){
  return mode;
}

void Gate::getOutGate(int y_in, int x_in, int* y_out, int* x_out){
  if(y_in==y0)  *y_out=y1;
  else          *y_out=y0;

  if(x_in==x0)  *x_out=x1;
  else          *x_out=x0;
}

int Gate::isUsed(){
  if(mode==GATE){
    if(cur_map[y0][x0]==USING_GATE || cur_map[y1][x1]==USING_GATE)  return 1;
  }
  return 0;
}

void Gate::setWaitingMode(int body_length){
  waiting_sec=body_length;
  mode=USING_GATE;
}

void Gate::beingUsed(){
  waiting_sec--;
  if(waiting_sec<=0)  delGate();
}