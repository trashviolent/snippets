#include "program.h"
#include "inputState.h"
#include "pathfindingData.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cstdint>
#include <fstream>
#include <chrono>

Program::Program() : pathfindingData(256) {
	SDL_Init(SDL_INIT_VIDEO);
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

	float backgroundX = 0.0f;
	float backgroundY = 0.0f;

	for (size_t a = 0; a < this->backgroundNum; ++a) {
		this->background[a].setDimensions(64.0f, 64.0f);
		this->background[a].setTextureIndex(0);
		this->background[a].setCoordinates(backgroundX, backgroundY);
		backgroundX += 64.0f;
		if (backgroundX == 1600.0f) {
			backgroundX = 0.0f;
			backgroundY += 64.0f;
		}
	}

	float obstacleCoordinates[30][2] = {
		{128.0f, 448.0f},
		{128.0f, 512.0f},
		{128.0f, 576.0f},
		{256.0f, 0.0f},
		{256.0f, 64.0f},
		{256.0f, 128.0f},
		{512.0f, 640.0f},
		{576.0f, 640.0f},
		{640.0f, 640.0f},
		{128.0f, 0.0f},
		{192.0f, 0.0f},
		{256.0f, 0.0f},
		{960.0f, 0.0f},
		{960.0f, 64.0f},
		{960.0f, 128.0f},
		{960.0f, 256.0f},
		{960.0f, 320.0f},
		{960.0f, 448.0f},
		{960.0f, 512.0f},
		{960.0f, 576.0f},
		{960.0f, 640.0f},
		{0.0f, 896.0f},
		{64.0f, 896.0f},
		{128.0f, 896.0f},
		{256.0f, 896.0f},
		{1216.0f, 256.0f},
		{1216.0f, 320.0f},
		{1216.0f, 384.0f},
		{1216.0f, 448.0f},
		{1216.0f, 512.0f}
	};

	for (size_t a = 0; a < this->obstacleNum; ++a) {
		this->obstacle[a].setCoordinates(obstacleCoordinates[a][0], obstacleCoordinates[a][1]);
		this->obstacle[a].setDimensions(64.0f, 64.0f);
		this->obstacle[a].setTextureIndex(1);
	}

	this->character[0].setCoordinates(0.0f, 0.0f);
	this->character[0].setTextureIndex(2);
	this->character[1].setCoordinates(1536.0f, 896.0f);
	this->character[1].setTextureIndex(3);

	for (size_t a = 0; a < this->characterNum; ++a) {
		this->character[a].setDimensions(64.0f, 64.0f);
	}

	this->movementPerSecond = 256.0f;

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
	std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	while (this->runProgram) {
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
				else if (event.key.keysym.sym == SDLK_x && this->pathfindingData.getPathComplete())
					this->plotAIPath(this->character[0].getX(), this->character[0].getY());
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
		std::chrono::duration<float> durationElapsed = currentTime - startTime;
		float timeElapsed = durationElapsed.count();
		startTime = std::chrono::steady_clock::now();

		float userVertical = 0.0f;
		float userHorizontal = 0.0f;
		if (inputState.w || inputState.s)
			userVertical = this->movementPerSecond * timeElapsed;
		if (inputState.w)
			userVertical *= -1.0f;
		if (inputState.a || inputState.d)
			userHorizontal = this->movementPerSecond * timeElapsed;
		if (inputState.d)
			userHorizontal *= -1.0f;
		this->moveUser(userVertical, userHorizontal);

		if (this->pathfindingData.getPathComplete() == false)
			this->moveAI(timeElapsed);

		SDL_RenderClear(this->renderer);
		for (size_t a = 0; a < this->backgroundNum; ++a) {
			SDL_Rect clipData = { 0, 0, 64, 64 };
			SDL_FRect drawData = {
				this->background[a].getX(),
				this->background[a].getY(),
				this->background[a].getWidth(),
				this->background[a].getHeight()
			};
			SDL_RenderCopyF(this->renderer, this->texture[background[a].getTextureIndex()], &clipData, &drawData);
		}
		for (size_t a = 0; a < this->obstacleNum; ++a) {
			SDL_Rect clipData = { 0, 0, 64, 64 };
			SDL_FRect drawData = {
				this->obstacle[a].getX(),
				this->obstacle[a].getY(),
				this->obstacle[a].getWidth(),
				this->obstacle[a].getHeight()
			};
			SDL_RenderCopyF(this->renderer, this->texture[obstacle[a].getTextureIndex()], &clipData, &drawData);
		}
		for (size_t a = 0; a < this->characterNum; ++a) {
			SDL_Rect clipData = { 0, 0, 64, 64 };
			SDL_FRect drawData = {
				this->character[a].getX(),
				this->character[a].getY(),
				this->character[a].getWidth(),
				this->character[a].getHeight()
			};
			SDL_RenderCopyF(this->renderer, this->texture[character[a].getTextureIndex()], &clipData, &drawData);
		}
		SDL_RenderPresent(this->renderer);
	}
}