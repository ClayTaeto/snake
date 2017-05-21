#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "cleanup.h"
#include "Sprite.h"
#include "Graphics.h"
#include "Snek.h"
#include "Food.h"
enum STATE
{
	STATE_MENU,
	STATE_PLAYING,
	STATE_GAMEOVER
};

int main(int, char**) {
	Graphics::setup();

	MSprite background("img/background.png");
	MSprite title("img/SnakeTitle.png", 139, 0);
	MSprite subTitle("img/Push Enter to Start.png", 168, 379);
	Snek player;
	Food foodBits("img/rabbit.png");
	foodBits.move(&player);

	const Uint8 * keys = SDL_GetKeyboardState(NULL);
	
	SDL_Event e;
	STATE state = STATE::STATE_MENU;

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
			title.draw();
			subTitle.draw();
			
			//if keys, then start playing
			if (keys[SDL_SCANCODE_RETURN]) {
				state = STATE::STATE_PLAYING;
			}
			
			break;
		case STATE_PLAYING:
							
			//if snek eats, then gro
			if (foodBits.x == player.bits[0]->x && foodBits.y == player.bits[0]->y) {
				player.grow();
				foodBits.move(&player);
			}
			//if snek eats everything, then it wins
			if (player.bits.size() == 16*12){
				//you won
				state = STATE::STATE_GAMEOVER;
				break;				
			}
			player.move();

			//draw everything
			background.draw();
			foodBits.draw();
			player.draw();

			break;
		case STATE_GAMEOVER:
			background.draw();
			player.draw();

			if (keys[SDL_SCANCODE_RETURN]) {
				state = STATE_PLAYING;
				player.resetHard();
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