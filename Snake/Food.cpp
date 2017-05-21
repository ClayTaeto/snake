#include "Food.h"

Food::Food(const char *t_path) {
texture = Graphics::loadTexture(t_path);

SDL_QueryTexture(texture, NULL, NULL, &texture_size.w, &texture_size.h);
}

void Food::move(Snek * player) {
	do {
		x = rand() % 16;
		y = rand() % 12;		
	} while (!isFree(x, y, player));
}

void Food::draw() {
	Graphics::renderTexture(texture, x * texture_size.w, y * texture_size.w);
}

bool Food::isFree(int x, int y, Snek *player) {
	for (int i = 0; i < player->bits.size(); i++) {
		if (x == player->bits[i]->x && y == player->bits[i]->y) {
			return false;
		}
	}
	return true;
}
