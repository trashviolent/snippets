#include "SDL.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	std::string path;
	uint16_t input;
	std::cout << "path: ";
	std::cin >> path;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Event event;
	int h = 0, w = 0;
	int full = h * w;
	uint8_t colour[4];
	int colourArray[4];

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("sdlDisplay",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800, 600,
		SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//STUFF HAPPENS HERE
	std::ifstream read;
	read.open(path.c_str());
	read.read((char*)&input, sizeof(uint16_t));
	w = (int)input;
	read.read((char*)&input, sizeof(uint16_t));
	h = (int)input;
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
	full = h * w;
	int x = 0, y = 0;
	for (int a = 0; a < full; ++a) {
		for (int b = 0; b < 4; ++b) {
			read.read((char*)&colour[b], sizeof(uint8_t));
		}
		SDL_SetRenderTarget(renderer, texture);
		SDL_SetRenderDrawColor(renderer, colour[0], colour[1], colour[2], colour[3]);
		if (y == h) {
			y = 0;
			++x;
		}
		SDL_RenderDrawPoint(renderer, x, y);
		++y;
	}
	read.close();
	SDL_SetRenderTarget(renderer, NULL);
	SDL_Rect rect = { (400 - (w / 2)), (300 - (h / 2)), w, h };

	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			break;

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}