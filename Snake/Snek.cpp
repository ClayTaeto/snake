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
		cleanup(bits[i]->texture);
		delete bits[i];
	}
}
void Snek::move() {
	keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_DOWN] && vy != -1 && isValidDirection(0, 1)) {
		extraDelay = 0;
		extraDelay = 0;
	}
	if (keys[SDL_SCANCODE_UP] && vy != 1 && isValidDirection(0, -1)) {
		vy = -1;
		vx = 0;
		bits[0]->angle = 180;
	} else if (keys[SDL_SCANCODE_DOWN] && vy != -1 && isValidDirection(0, 1)){
		vy = 1;
		vx = 0;
		bits[0]->angle = 0;
	} else if (keys[SDL_SCANCODE_LEFT] && vx != 1 && isValidDirection(-1, 0)) {
		vy = 0;
		vx = -1;
		bits[0]->angle = 90;
	} else if (keys[SDL_SCANCODE_RIGHT] && vx != -1 && isValidDirection(1, 0)) {
		vy = 0;
		vx = 1;
		bits[0]->angle = -90;
	}

	if (keys[SDL_SCANCODE_RETURN])
	{
		extraDelay = 0;
		extraDelay = 0;
		extraDelay = 0;
		extraDelay = 0;
		extraDelay = 0;
	}
	if (isDead()) {
		extraDelay = 400;
		return;
	}
	
	Graphics::timeWaited += SDL_GetTicks() - Graphics::lastTime;
	Graphics::lastTime = SDL_GetTicks();
	if (Graphics::timeWaited < 150 + extraDelay) {
		return;
	}

	if (checkBounds()) {
		resetHard();
		return;
	}

	extraDelay = 0;
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
	for (int i = bits.size() - 1; i > 5; i--) {
		delete  bits[i];
	}

	bits.erase(bits.begin() + 5, bits.end());
}

void Snek::resetHard() {
	bits[0]->angle = -90;
	vy = 0;
	vx = 1;

	bits[0]->move(4, 0);
	bits[1]->move(3, 0);
	bits[2]->move(2, 0);
	bits[3]->move(1, 0);
	bits[4]->move(0, 0);
	reset();
}

bool Snek::isDead() {
	for (int i = 1; i < bits.size(); i++) {
		if (bits[0]->x == bits[i]->x && bits[0]->y == bits[i]->y) {
			reset();
			return true;
		}
	}
	return false;
}

bool Snek::isValidDirection(int x, int y) {
	if (bits[0]->x + x == bits[1]->x) { 
		return false;
	}
	if (bits[0]->y + y == bits[1]->y) {
		return false;
	}
}

bool Snek::checkBounds() {
	if (bits[0]->x + vx < 0 || bits[0]->x + vx > 15) {
		return true;
	}
	if (bits[0]->y + vy < 0 || bits[0]->y + vy > 11) {
		return true;
	}
	return false;
}

