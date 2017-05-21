#include <iostream>
#include "SnekBits.h"
using namespace std;


SnekBits::SnekBits(const char *t_path) {
	texture = Graphics::loadTexture(t_path);

	SDL_QueryTexture(texture, NULL, NULL, &texture_size.w, &texture_size.h);
	x = 0;
	y = 0;
}

SnekBits::SnekBits(const char *t_path, int t_x, int t_y) : x(t_x), y(t_y) {
	texture = Graphics::loadTexture(t_path);

	SDL_QueryTexture(texture, NULL, NULL, &texture_size.w, &texture_size.h);
}
void SnekBits::move(int t_x, int t_y) {
	x = t_x;
	y = t_y;
}
void SnekBits::move(int t_x, int t_y, int t_centerx = 0, int t_centery = 0, double t_angle = 0) {
	x = t_x;
	y = t_y;
	center.x = t_centerx;
	center.y = t_centery;
	angle = t_angle;
}
void SnekBits::draw() {
	Graphics::renderTexture(texture, x * texture_size.w, y * texture_size.w, angle, &center);
}

void SnekBits::clean() {
	cleanup(texture);
}
