#include "Game.h"

int Game::score = 0;


//TODO: Switch over to virtual functions & just call update();
void Game::handleState() {
	switch (state) {
		case STATE_MENU: 
			//if keys, then 
			//state = STATE_PLAYING
			break;
		case STATE_PLAYING:
			//draw everything
			//check score
			//TODO: SNAKE WIN?!
			if (score > 1000) {
				//transition into game over state
				state = STATE_GAMEOVER;
			}
			break;
		case STATE_GAMEOVER:
			break;
	}
}

void Game::reset() {
	score = 0;
}