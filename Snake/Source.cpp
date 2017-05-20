#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "cleanup.h"
#include "Sprite.h"
#include "Graphics.h"
#include "Snek.h"
#include "Food.h"

int main(int, char**) {
	Graphics::setup();

	MSprite background("img/background.png");

	Snek player;
	ScoreCount redCounter(&Game::score);
	redCounter.x = 259;
	redCounter.y = 30;
	Food foodbits("img/rabbit.png");
	foodbits.move();

	const Uint8 * keys = SDL_GetKeyboardState(NULL);
	
	SDL_Event e;
	STATE state = STATE::STATE_MENU;
	unsigned int timeWaited = 0, lastTime = 0;
	bool quit = false;
	while (!quit) {
		//Event Polling?
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}			
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
			}
		}

		

		//Rendering
		SDL_RenderClear(Graphics::renderer);
		
		switch (state) {
		case STATE_MENU:
						
			background.draw();
			
			
			//if keys, then start playing
			if (keys[SDL_SCANCODE_RETURN]) {
				state = STATE::STATE_PLAYING;
			}
			
			break;
		case STATE_PLAYING:
						
			if (foodbits.x == player.bits[0]->x && foodbits.y == player.bits[0]->y) {
				player.grow();
				foodbits.move();
			}
			player.move();

			//draw everything
			background.draw();
			foodbits.draw();
			player.draw();
			//redCounter.draw();
			
			
			if (keys[SDL_SCANCODE_UP]) {
				//paddleBlue.moveUp();
			}

			if (keys[SDL_SCANCODE_DOWN]) {
				//paddleBlue.moveDown();
			}

			//check score
			/*
			if (Game::score > 9 || Game::redScore > 9) {
				//transition into game over state
				state = STATE_GAMEOVER;
				lastTime = SDL_GetTicks();
			}*/
			break;
		case STATE_GAMEOVER:
			/*
			background.draw();
			if (Game::blueScore > Game::redScore) {
				blue.draw();
				wins.draw();
			} else {
				red.draw();
				wins.draw();
			}
			
			start.draw();
			*/

			//if keys, then start playing
			timeWaited += SDL_GetTicks() - lastTime;
			lastTime = SDL_GetTicks();
			if (timeWaited < 1000) {
				break;
			}
			if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_RETURN]) {
				state = STATE_PLAYING;
				Game::reset();
				timeWaited = 0;
			}
			break;
		}
		
		
		//Update the screen
		SDL_RenderPresent(Graphics::renderer);
	}
	//Clean up
	background.clean();

	cleanup(Graphics::renderer, Graphics::window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}