#ifndef _SNEK_H_
#define _SNEK_H_

#include <iostream>
#include <vector>
#include "SnekBits.h"

using namespace std;


class Snek
{
public:
	//SnekBits* bits[193];

	const Uint8 * keys;
	vector<SnekBits*> bits;
	void handleState();
	void move();
	void draw();
	int length, vx = 1, vy = 0;
	void static reset();
	Snek();	
	~Snek();

};

#endif