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
	void move(int t_x, int t_y);
	void move(int t_x, int t_y, int t_centerx, int t_centery, double t_angle);
	void draw();
	void clean();
	int index;
	SDL_Rect texture_size;
	SnekBits(const char * t_path);
	SnekBits(const char *t_path, int t_x, int t_y);
	int x, y;
	double angle;
	SDL_Point center;
	SDL_Texture* texture;

private:
	std::string m_path;
	
};

#endif