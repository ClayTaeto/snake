#ifndef _FOOD_H_
#define _FOOD_H_

using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include "graphics.h"
#include "Snek.h"

class Food
{
public:
	Food(const char * t_path);
	void move(Snek * player);
	void draw();
	bool isFree(int x, int y, Snek * player);
	int x, y;
	SDL_Rect texture_size;
	SDL_Texture* texture;
};

#endif