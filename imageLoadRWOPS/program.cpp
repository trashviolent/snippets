#include "program.h"
#include <SDL.h>

Program::Program() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	this->window = SDL_CreateWindow("test environment", 50, 50, 800, 800, SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
}

Program::~Program() {
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	for (int a = 0; a < this->textureNum; ++a) {
		SDL_DestroyTexture(this->texture[a]);
	}
	delete[] this->texture;
	SDL_Quit();
}

void Program::createSurface() {

}