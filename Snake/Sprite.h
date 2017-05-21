#ifndef H_Sprite
#define H_Sprite

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "graphics.h"

class MSprite{
public:	
	MSprite() {
	}
	MSprite(const char *t_path){
		m_texture = Graphics::loadTexture(t_path);
		if (m_texture == nullptr) {
			cleanup(m_texture, m_context);			
		}
		
		SDL_QueryTexture(m_texture, NULL, NULL, &texture_size.w, &texture_size.h);
		x = 0;
		y = 0;		
	}

	MSprite(const char *t_path, int t_x, int t_y) : x(t_x), y(t_y) {
		m_texture = Graphics::loadTexture(t_path);
		if (m_texture == nullptr) {
			cleanup(m_texture, m_context);
		}

		SDL_QueryTexture(m_texture, NULL, NULL, &texture_size.w, &texture_size.h);
	}

	virtual void move(void) { }
	virtual void draw(void) { 
		Graphics::renderTexture(m_texture, x, y);
	}
	void clean() {
		cleanup(m_texture);
	}
	int x, y;
	SDL_Rect texture_size;
	//velocity x & y
	int vx = 6;
	int vy = 2;
	
private:
	SDL_Renderer* m_context;
	std::string m_path;
	SDL_Texture* m_texture;
};
#endif