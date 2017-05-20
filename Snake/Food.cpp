#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include "graphics.h"
#include "Food.h"

Food::Food(const char *t_path) {
texture = Graphics::loadTexture(t_path);

SDL_QueryTexture(texture, NULL, NULL, &texture_size.w, &texture_size.h);
}

void Food::move()
{
	x = rand() % 16;
	x = rand() % 12;
}

void Food::draw()
{
	Graphics::renderTexture(texture, x * texture_size.w, y * texture_size.w);
}
