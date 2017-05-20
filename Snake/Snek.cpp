#include "Snek.h"
#include "SnekBits.h"

void Snek::handleState()
{
}

Snek::Snek()
{
	bits.push_back(new SnekBits("img/snake.png", 4, 0));
	bits[0]->angle = -90;
	bits[0]->center.x = 20;
	bits[0]->center.y = 20;
	bits.push_back(new SnekBits("img/snake-bod.png", 3, 0));
	bits.push_back(new SnekBits("img/snake-bod.png", 2, 0));
	bits.push_back(new SnekBits("img/snake-bod.png", 1, 0));
	bits.push_back(new SnekBits("img/snake-bod.png", 0, 0));
		
}
Snek::~Snek()
{
	cout << "Goodnight, sleep well";
	for (int i = 0; i < bits.size(); i++) {
		delete bits[i];
	}
}
void Snek::move() {
	keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_UP] && vy != 1) {
		vy = -1;
		vx = 0;
		bits[0]->angle = 180;
		
	} else if (keys[SDL_SCANCODE_DOWN] && vy != -1){
		vy = 1;
		vx = 0;
		bits[0]->angle = 0;
	} else if (keys[SDL_SCANCODE_LEFT] && vx != 1) {
		vy = 0;
		vx = -1;
		bits[0]->angle = 90;
	} else if (keys[SDL_SCANCODE_RIGHT] && vx != -1) {
		vy = 0;
		vx = 1;
		bits[0]->angle = -90;
	}
	Graphics::timeWaited += SDL_GetTicks() - Graphics::lastTime;
	Graphics::lastTime = SDL_GetTicks();
	if (Graphics::timeWaited < 300) {
		return;
	}

	Graphics::timeWaited = 0;
	for (int i = bits.size() - 1; i > 0; i--) {
		if (i == 0) {
			
		} else {
			//do silly snek bits
			bits[i]->move(bits[i - 1]->x, bits[i - 1]->y);
		}
	}
	bits[0]->move(bits[0]->x + vx, bits[0]->y + vy);
}
void Snek::draw() {
	for (int i = bits.size() - 1; i > -1; i--) {
		bits[i]->draw();
	}
}
void Snek::grow() {
	bits.push_back(new SnekBits("img/snake-bod.png", -1, -1));
}
void Snek::reset() {
	for (int i = bits.size() - 1; i > -1; i--) {
		bits[i]->draw();
	}
}

