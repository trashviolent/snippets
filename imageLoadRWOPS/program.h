#pragma once

#include <SDL.h>

class Program {
public:
	Program();
	~Program();
	void createSurface();
	void createTexture();
	void programCore();
	void render();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int textureNum;
	SDL_Texture** texture;
};