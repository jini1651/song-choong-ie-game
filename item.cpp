#include <ncurses.h>
#include <ctime>
#include <random>

#include "setting.h"
#include "item.h"

using namespace std;

Item::Item(void)
{
  type=EMPTY;   //none:4, grow:5, poison:6
  genTime=time(NULL);     //when generated (when genTime=-1, item's type is none)
  y=-1, x=-1;

  srand(static_cast<unsigned int>(time(NULL)));

  init_pair(EMPTY, COLOR_WHITE, COLOR_WHITE);
  init_pair(GROWTH_ITEM, COLOR_GREEN, COLOR_WHITE);
  init_pair(POSION_ITEM, COLOR_RED, COLOR_WHITE);
}

void Item::genItem(){
  type = rand()%7;  //0~4:none, 5:grow, 6:poison

  if(type==GROWTH_ITEM || type==POSION_ITEM){   //none
    while(1){
      y = rand()%MAP_HEIGHT;
      x = rand()%MAP_WIDTH;

      if(cur_map[y][x]==EMPTY)  break;
    }

    cur_map[y][x]=type;
    printItem();

    genTime = time(NULL);
  }
  else  type = EMPTY;
}

void Item::delItem(int eaten){
  type=EMPTY;

  if(!eaten){
    cur_map[y][x]=EMPTY;
    printItem();
  }
}

void Item::printItem(){
  start_color();

  wattron(win_map, COLOR_PAIR(type));
  mvwprintw(win_map, y, x, "%s", "*");
  wattroff(win_map, COLOR_PAIR(type));

  wrefresh(win_map);
}

time_t Item::getGenTime(){
  return genTime;
}

int Item::getType(){
  return type;
}

int Item::isTimeout(){
  if(type==GROWTH_ITEM || type==POSION_ITEM){
    time_t cur_t = time(NULL);
    if(static_cast<double>(cur_t-genTime)>10)  return 1;
  }
  return 0;
}

int Item::isEaten(){
  if(type==GROWTH_ITEM || type==POSION_ITEM){
    if(cur_map[y][x]!=GROWTH_ITEM && cur_map[y][x]!=POSION_ITEM)  return 1;
  }
  return 0;
}