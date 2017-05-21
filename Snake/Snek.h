#ifndef _SNEK_H_
#define _SNEK_H_

#include <iostream>
#include <vector>
#include "SnekBits.h"

using namespace std;


class Snek
{
public:
	const Uint8 * keys;
	vector<SnekBits*> bits;
	void handleState();
	void move();
	void draw();
	void grow();
	int length, vx = 1, vy = 0, extraDelay = 0;
	void reset();
	void resetHard();
	bool isValidDirection(int x, int y);
	bool isDead();	
	bool checkBounds();
	Snek();	
	~Snek();

};

#endif