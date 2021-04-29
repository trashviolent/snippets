#pragma once

#include <cstdint>

class Actor {
public:
	float getX();
	float getY();
	void setCoordinates(float x, float y);
	float getWidth();
	float getHeight();
	void setDimensions(float width, float height);
	size_t getTextureIndex();
	void setTextureIndex(size_t textureIndex);
private:
	float x;
	float y;
	float width;
	float height;
	size_t textureIndex;
};