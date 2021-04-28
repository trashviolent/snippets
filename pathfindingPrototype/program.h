#pragma once

#include "actor.h"
#include "inputState.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cstdint>

class Program {
public:
	Program();
	~Program();
	void run();
protected:
	void moveUser(double vertical, double horizontal);
	void plotAIPath(size_t playerX, size_t playerY);
private:
	Actor* background;
	size_t backgroundNum;
	Actor* obstacle;
	size_t obstacleNum;
	Actor* character;
	size_t characterNum;
	SDL_Texture** texture;
	size_t textureNum;
	SDL_Window* window;
	SDL_Renderer* renderer;
	InputState inputState;
	size_t aiDestinationX;
	size_t aiDestinationY;
	double movementPerSecond;
	bool runProgram;
};

/*
replace aiDestinationX and y with a struct
called aiPathNodes.  this will contain the nodes
as floats for x and y coordinates, and the direction
to travel for each node (neutral for the last one)

change everything to use floats
*/