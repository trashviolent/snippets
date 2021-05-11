#pragma once

#include "actor.h"
#include "inputState.h"
#include "pathfindingData.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cstdint>

class Program {
public:
	Program();
	~Program();
	void run();
protected:
	void moveUser(float vertical, float horizontal);
	void moveAI(float timeElapsed);
	void plotAIPath(float playerX, float playerY);
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
	PathfindingData pathfindingData;
	Actor** collisionCandidates;
	size_t collisionCandidatesMaxNum;
	size_t collisionCandidatesCurrentNum;
	float movementPerSecond;
	bool runProgram;
};