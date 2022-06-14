#ifndef _GATE_
#define _GATE_

using namespace std;

class Gate
{
private:
    int mode;   //0:just Gate, 1:gate
    int y0, x0, y1, x1;
    int waiting_sec;

public:
    Gate(void);

    void genGate();
    void delGate();

    void printGate();

    int getMode();
    void getOutGate(int y_in, int x_in, int* y_out, int* x_out);

    int isUsed();
    void setWaitingMode(int body_length);
    void beingUsed();
};

#endif