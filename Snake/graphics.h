#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "cleanup.h"
//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Graphics {
public:
	static SDL_Window *window;
	static SDL_Renderer *renderer;
	static int setup();
	static void renderTexture(SDL_Texture *tex, int x, int y, SDL_Rect *clip = nullptr);
	static void renderTexture(SDL_Texture *tex, SDL_Rect dst, SDL_Rect *clip = nullptr);
	static void renderTexture(SDL_Texture * tex, int x, int y, double angle, SDL_Point * center);
	static SDL_Texture *loadTexture(const std::string &file);
	static void logSDLError(const std::string &msg);
	static unsigned int lastTime, timeWaited;
};
#endif
