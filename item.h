#ifndef _ITEM_
#define _ITEM_

using namespace std;

class Item
{
private:
    int type;   //none:0, grow:1, poison:2
    time_t genTime;     //when generated 
    int y, x;

public:
    Item(void);

    void genItem();
    void delItem(int eaten);

    void printItem();

    time_t getGenTime();
    int getType();

    int isTimeout();
    int isEaten();
};

#endif