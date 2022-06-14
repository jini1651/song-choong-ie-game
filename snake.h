#ifndef _SNAKE_
#define _SNAKE_
#include <list>

using namespace std;

class Snake
{
private:
    list<pair<int, int>> loc_list;
    int direction;
    int length;

    // int dy[4] = {-1, 1, 0, 0};
    // int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 0, 1, 0};
    int dx[4] = {0, 1, 0, -1};

public:
    Snake(void);
    ~Snake();

    void printSnake();
    void changeDir(int dir);

    void mvNext(int* ptr_y, int* ptr_x);
    void move(int y, int x);
    void grow(int y, int x);
    void shorten(int y, int x);
    void useGate(int y_out, int x_out);

    int isValid();

    int getDirection();
    int getLength();

};

#endif