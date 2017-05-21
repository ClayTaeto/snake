#include "graphics.h"

SDL_Renderer* Graphics::renderer = nullptr;
SDL_Window* Graphics::window = nullptr;
unsigned int Graphics::lastTime = 0;
unsigned int Graphics::timeWaited = 0;

int Graphics::setup() {
	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		logSDLError("SDL_Init");
		return 1;
	}

	//Setup our window and renderer
	window = SDL_CreateWindow("SnekySnek", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);//SDL_WINDOW_FULLSCREEN);
	if (window == nullptr) {
		logSDLError("CreateWindow");
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	//hide cursor
	SDL_ShowCursor(SDL_DISABLE);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		logSDLError("CreateRenderer");
		cleanup(window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	
}

void Graphics::renderTexture(SDL_Texture *tex, int x, int y, SDL_Rect *clip) {
	//TODO: move this into constructor of class calling this.
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr) {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {		
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}
	renderTexture(tex, dst, clip);
}

void Graphics::renderTexture(SDL_Texture *tex, SDL_Rect dst, SDL_Rect *clip) {
	SDL_RenderCopy(Graphics::renderer, tex, clip, &dst);
}

void Graphics::renderTexture(SDL_Texture *tex, int x, int y, double angle, SDL_Point* center) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopyEx(Graphics::renderer, tex, nullptr, &dst, angle, center, SDL_FLIP_NONE);
}



SDL_Texture * Graphics::loadTexture(const std::string & file)
{
	SDL_Texture *texture = IMG_LoadTexture(Graphics::renderer, file.c_str());
	if (texture == nullptr || texture == NULL) {
		logSDLError("LoadTexture " + file);
		cleanup(texture, Graphics::renderer);
		IMG_Quit();
		SDL_Quit();
		throw "Error loading texture";
	}
	return texture;
}

void Graphics::logSDLError(const std::string & msg)
{
	std::cout << msg;
}
