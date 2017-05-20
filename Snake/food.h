#ifndef _FOOD_H_
#define _FOOD_H_

using namespace std;


class Food
{
public:
	Food(const char * t_path);
	void move();
	void draw();
	int x, y;
	SDL_Rect texture_size;
	SDL_Texture* texture;
};

#endif