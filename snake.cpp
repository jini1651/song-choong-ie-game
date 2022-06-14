#include <ncurses.h>
#include <list>

#include "setting.h"
#include "snake.h"

using namespace std;

Snake::Snake(void)
{
  direction = 3;
  length = 4;

  loc_list.push_back(make_pair(10, 18));
  loc_list.push_back(make_pair(10, 19));
  loc_list.push_back(make_pair(10, 20));
  loc_list.push_back(make_pair(10, 21));

  init_pair(EMPTY, COLOR_WHITE, COLOR_WHITE);
  init_pair(SNAKE_HEAD, COLOR_CYAN, COLOR_WHITE);
  init_pair(SNAKE_BODY, COLOR_BLUE, COLOR_WHITE);

  cur_map[10][18] = SNAKE_BODY;
  cur_map[10][19] = SNAKE_BODY;
  cur_map[10][20] = SNAKE_BODY;
  cur_map[10][21] = SNAKE_BODY;
}

Snake::~Snake() {
   loc_list.clear();
}

void Snake::printSnake(){
  start_color();

  pair<int, int> head;
  head = loc_list.front();

  wattron(win_map, COLOR_PAIR(SNAKE_BODY));
  for(pair<int, int> loc : loc_list){
    mvwprintw(win_map, loc.first, loc.second, "%s", "@");
  }
  wattroff(win_map, COLOR_PAIR(SNAKE_BODY));

  wattron(win_map, COLOR_PAIR(SNAKE_HEAD));
  mvwprintw(win_map, head.first, head.second, "%s", "@");
  wattroff(win_map, COLOR_PAIR(SNAKE_HEAD));

  wrefresh(win_map);
}

void Snake::changeDir(int dir){
  direction = dir;
}

void Snake::mvNext(int* ptr_y, int* ptr_x){
  pair<int, int> head;

  head = loc_list.front();
  *ptr_y = head.first + dy[direction];
  *ptr_x = head.second + dx[direction];
}

void Snake::move(int y, int x){
  pair<int, int> tail;
  
  loc_list.push_front(make_pair(y, x));

  tail = loc_list.back();
  loc_list.pop_back();
  cur_map[tail.first][tail.second]=EMPTY;
  wattron(win_map, COLOR_PAIR(EMPTY));
  mvwprintw(win_map, tail.first, tail.second, "%s", "@");
  wattroff(win_map, COLOR_PAIR(EMPTY));

  printSnake();
}

void Snake::grow(int y, int x){
  pair<int, int> tail;
  
  loc_list.push_front(make_pair(y, x));

  length++;

  printSnake();
}

void Snake::shorten(int y, int x){
  pair<int, int> tail;
  
  loc_list.push_front(make_pair(y, x));

  length--;

  tail = loc_list.back();
  loc_list.pop_back();
  cur_map[tail.first][tail.second]=EMPTY;
  wattron(win_map, COLOR_PAIR(EMPTY));
  mvwprintw(win_map, tail.first, tail.second, "%s", "@");
  wattroff(win_map, COLOR_PAIR(EMPTY));
  
  tail = loc_list.back();
  loc_list.pop_back();
  cur_map[tail.first][tail.second]=EMPTY;
  wattron(win_map, COLOR_PAIR(EMPTY));
  mvwprintw(win_map, tail.first, tail.second, "%s", "@");
  wattroff(win_map, COLOR_PAIR(EMPTY));

  printSnake();
}

void Snake::useGate(int y_out, int x_out){
  int y, x;
  int temp_dir;
  //original_dir - closck_wise - cnter_clock_wise - opposite_dir
  int d_dir[4] = {0, 1, -1, 2};

  cur_map[y_out][x_out]=USING_GATE;

  for(int i=0; i<4; i++){ 
    temp_dir = direction + d_dir[i];
    if(temp_dir<0)  temp_dir+=4;
    else if(temp_dir>3)  temp_dir-=4;

    y = y_out + dy[temp_dir];
    x = x_out + dx[temp_dir];
    
    if(cur_map[y][x]!=WALL && cur_map[y][x]!=IMMUNE_WALL &&
      y>=0 && y<MAP_HEIGHT && x>=0 && x<MAP_WIDTH)      break;
  }
  direction = temp_dir;
  move(y, x);
}

int Snake::isValid(){
  pair<int, int> head;

  head = loc_list.front();
  int y = head.first;
  int x = head.second;
  int idx=0;
  //wall blocking
  if(cur_map[y][x]==WALL)  return 0;
  //body blocking
  for(pair<int, int> loc : loc_list){
    if(idx!=0){
      if(y==loc.first && x==loc.second) return 0;
    }
    idx++;
  }
  //body length < 3
  if(length<3)  return 0;

  cur_map[y][x]=SNAKE_HEAD;
  return 1;
}

int Snake::getDirection(){
  return direction;
}

int Snake::getLength(){
  return length;
}
                                                       