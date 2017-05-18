#include <iostream>
#include "SnekBits.h"
using namespace std;


SnekBits::SnekBits(const char *t_path) {
	m_texture = Graphics::loadTexture(t_path);

	SDL_QueryTexture(m_texture, NULL, NULL, &texture_size.w, &texture_size.h);
	x = 0;
	y = 0;
}

SnekBits::SnekBits(const char *t_path, int t_x, int t_y) : x(t_x), y(t_y) {
	m_texture = Graphics::loadTexture(t_path);

	SDL_QueryTexture(m_texture, NULL, NULL, &texture_size.w, &texture_size.h);
	x = 0;
	y = 0;
}

void SnekBits::move() { }
void SnekBits::draw() {
	Graphics::renderTexture(m_texture, x, y);
}
void SnekBits::clean() {
	cleanup(m_texture);
}
