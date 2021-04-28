#include "program.h"
#include "inputState.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cstdint>
#include <fstream>
#include <chrono>

Program::Program() {
	SDL_Init();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	this->window = SDL_CreateWindow("pathfinding prototype", 100, 100, 1600, 960, SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);

	this->backgroundNum = 375;
	this->background = new Actor[this->backgroundNum];
	this->obstacleNum = 30;
	this->obstacle = new Actor[this->obstacleNum];
	this->characterNum = 2;
	this->character = new Actor[this->characterNum];
	this->textureNum = 4;
	this->texture = new SDL_Texture*[this->textureNum];

	std::string file[4] = { "background.png", "obstacle.png", "character0.png", "character1.png" };
	SDL_Surface* surface;
	uint8_t* image;
	std::ifstream readFile;

	for (size_t a = 0; a < this->textureNum; ++a) {
		readFile.open(file[a].c_str(), std::ios::binary | std::ios::ate);
		size_t imageSize = readFile.tellg();
		image = new uint8_t[imageSize];
		readFile.seekg(0);
		readFile.read((char*)image, imageSize);
		readFile.close();
		readFile.clear();
		SDL_RWops* rw = SDL_RWFromMem(image, imageSize);
		surface = IMG_Load_RW(rw, 0);
		SDL_RWclose(rw);
		delete[] image;
		this->texture[a] = SDL_CreateTextureFromSurface(this->renderer, surface);
		SDL_FreeSurface(surface);
	}

	size_t backgroundX = 0;
	size_t backgroundY = 0;

	for (size_t a = 0; a < this->backgroundNum; ++a) {
		this->background[a].setDimensions(64, 64);
		this->background[a].setTextureIndex(0);
		this->background[a].setCoordinates(backgroundX, backgroundY);
		backgroundX += 64;
		if (backgroundX == 1600) {
			backgroundX = 0;
			backgroundY += 64;
		}
	}

	size_t obstacleCoordinates[30][2] = {
		{128, 448},
		{128, 512},
		{128, 576},
		{256, 0},
		{256, 64},
		{256, 128},
		{512, 640},
		{576, 640},
		{640, 640},
		{128, 0},
		{192, 0},
		{256, 0},
		{960, 0},
		{960, 64},
		{960, 128},
		{960, 256},
		{960, 320},
		{960, 448},
		{960, 512},
		{960, 576},
		{960, 640},
		{0, 896},
		{64, 896},
		{128, 896},
		{256, 896},
		{1216, 256},
		{1216, 320},
		{1216, 384},
		{1216, 448},
		{1216, 512}
	};

	for (size_t a = 0; a < this->obstacleNum; ++a) {
		this->obstacle[a].setCoordinates(obstacleCoordinates[a][0], obstacleCoordinates[a][1]);
		this->obstacle[a].setDimensions(64, 64);
		this->obstacle[a].setTextureIndex(1);
	}

	this->character[0].setCoordinates(0, 0);
	this->character[0].setTextureIndex(2);
	this->character[1].setCoordinates(1536, 896);
	this->character[1].setTextureIndex(3);

	for (size_t a = 0; a < this->characterNum; ++a) {
		this->character[a].setDimensions(64, 64);
	}

	this->movementPerSecond = 256;

	this->runProgram = true;
}

Program::~Program() {
	delete[] this->background;
	delete[] this->obstacle;
	delete[] this->character;

	for (size_t a = 0; a < this->textureNum; ++a) {
		SDL_DestroyTexture(this->texture[a]);
	}
	delete[] this->texture;

	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	IMG_Quit();
	SDL_Quit();
}

void Program::run() {
	SDL_Event event;
	bool aiMoveActive = false;
	std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	while (this->runProgram) {
		if (this->character[1].getX() == this->aiDestinationX && this->character[1].getY() == this->aiDestinationY)
			aiMoveActive = false;
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_w) {
					this->inputState.w = true;
					this->inputState.s = false;
				}
				else if (event.key.keysym.sym == SDLK_a) {
					this->inputState.a = true;
					this->inputState.d = false;
				}
				else if (event.key.keysym.sym == SDLK_s) {
					this->inputState.s = true;
					this->inputState.w = false;
				}
				else if (event.key.keysym.sym == SDLK_d) {
					this->inputState.d = true;
					this->inputState.a = false;
				}
				else if (event.key.keysym.sym == SDLK_x && aiMoveActive == false) {
					aiMoveActive = true;
					this->plotAIPath(this->character[0].getX(), this->character[0].getY());
				}
			}
			else if (event.type == SDL_KEYUP) {
				if (event.key.keysym.sym == SDLK_w)
					this->inputState.w = false;
				else if (event.key.keysym.sym == SDLK_a)
					this->inputState.a = false;
				else if (event.key.keysym.sym == SDLK_s)
					this->inputState.s = false;
				else if (event.key.keysym.sym == SDLK_d)
					this->inputState.d = false;
			}
		}
		currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> timeElapsed = startTime - currentTime;
		float userVertical = 0.0;
		float userHorizontal = 0.0;
		if (inputState.w || inputState.s)
			userVertical = this->movementPerSecond * timeElapsed;
		if (inputState.w)
			userVertical *= -1.0;
		if (inputState.a || inputState.d)
			userHorizontal = this->movementPerSecond * timeElapsed;
		if (inputState.d)
			userHorizontal *= -1.0;
	}
}