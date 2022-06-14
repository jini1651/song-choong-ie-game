#ifndef _SETTING_
#define _SETTING_

#define MAX_STAGE 4
#define MAP_WIDTH 40
#define MAP_HEIGHT 21

extern WINDOW *win_map, *win_score, *win_rule, *win_notice;
extern int cur_map[21][40];

#define KB_UP 259
#define KB_DOWN 258
#define KB_RIGHT 261
#define KB_LEFT 260

#define HEAD_UP 0
#define HEAD_DOWN 2
#define HEAD_LEFT 3
#define HEAD_RIGHT 1

#define EMPTY 8
#define WALL 1
#define IMMUNE_WALL 2
#define SNAKE_HEAD 3
#define SNAKE_BODY 4
#define GROWTH_ITEM 5
#define POSION_ITEM 6
#define GATE 7

#define USING_GATE 9

#endif