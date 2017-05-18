#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "cleanup.h"
#include "Sprite.h"
#include "Graphics.h"
//#include "Ball.cpp"

int main(int, char**) {
	Graphics::setup();

	//TODO: ugh, I need a new constructor
	MSprite background("img/background.png");
	MSprite pipe("img/pipe.png");
	pipe.x = 316;
	pipe.y = 14;
	MSprite pong("img/pong.png");
	pong.x = 221;
	pong.y = 77;

	MSprite start("img/start.png");
	start.x = 187;
	start.y = 349;
	MSprite red("img/red.png");
	red.x = 264;
	red.y = 108;
	MSprite blue("img/blue.png");
	blue.x = 255;
	blue.y = 108;
	MSprite wins("img/wins.png");
	wins.x = 232;
	wins.y = 174;

	ScoreCount redCounter(&Game::redScore);
	redCounter.x = 259;
	redCounter.y = 30;

	ScoreCount blueCounter(&Game::blueScore);
	blueCounter.x = 335;
	blueCounter.y = 30;

	Ball ball("img/ballBlue.png");
	ball.x = 321;
	ball.y = 230;

	CpuPaddle paddleRed("img/paddleRed.png");
	paddleRed.x = 18;
	paddleRed.y = 201;
	paddleRed.setTarget(&ball);

	MyPaddle paddleBlue("img/paddleBlu.png");
	paddleBlue.x = 604;
	paddleBlue.y = 201;

	ball.colliders.push_back(&paddleBlue);
	ball.colliders.push_back(&paddleRed);
	
	const Uint8 * keys = SDL_GetKeyboardState(NULL);
	
	SDL_Event e;
	STATE state = STATE_MENU;
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
			pong.draw();
			start.draw();
			//if keys, then start playing
			if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_RETURN]) {
				state = STATE_PLAYING;
			}
			break;
		case STATE_PLAYING:
			//draw everything			
			background.draw();
			pipe.draw();
			redCounter.draw();
			blueCounter.draw();
			paddleBlue.draw();
			paddleRed.draw();
			ball.draw();

			ball.move();
			paddleRed.move();
			
			if (keys[SDL_SCANCODE_UP]) {
				paddleBlue.moveUp();
			}

			if (keys[SDL_SCANCODE_DOWN]) {
				paddleBlue.moveDown();
			}

			//check score
			if (Game::blueScore > 9 || Game::redScore > 9) {
				//transition into game over state
				state = STATE_GAMEOVER;
				lastTime = SDL_GetTicks();
			}
			break;
		case STATE_GAMEOVER:
			background.draw();
			if (Game::blueScore > Game::redScore) {
				blue.draw();
				wins.draw();
			} else {
				red.draw();
				wins.draw();
			}
			
			start.draw();
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
	paddleBlue.clean();
	paddleRed.clean();
	cleanup(Graphics::renderer, Graphics::window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}