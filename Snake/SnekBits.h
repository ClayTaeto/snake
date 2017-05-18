#ifndef _SNEKBITS_H_
#define _SNEKBITS_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
using namespace std;


class SnekBits
{
public:
	void move();
	void draw();
	void clean();
	int index;
	SDL_Rect texture_size;
	SnekBits(const char * t_path);
	SnekBits(const char *t_path, int t_x, int t_y);
	int x, y;
private:
	std::string m_path;
	SDL_Texture* m_texture;
	
};

#endif