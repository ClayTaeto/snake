#ifndef _SNEK_H_
#define _SNEK_H_

#include <iostream>
using namespace std;

enum STATE
{
	STATE_MENU,
	STATE_PLAYING,
	STATE_GAMEOVER
};

class Game
{
public:
	STATE state;
	void handleState();
	void static reset();
	static int blueScore;
	static int redScore;
};

#endif