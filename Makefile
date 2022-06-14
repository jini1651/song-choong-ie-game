CC = g++
CFLAGS = -std=c++11
LDFLAGS = -lncursesw

all: main.cpp map.cpp display.cpp snake.cpp game.cpp item.cpp gate.cpp
	$(CC) $(CFLAGS) -o snake $^ $(LDFLAGS)
