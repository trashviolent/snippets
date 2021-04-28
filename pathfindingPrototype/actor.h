#pragma once

#include <cstdint>

class Actor {
public:
	size_t getX();
	size_t getY();
	void setCoordinates(size_t x, size_t y);
	size_t getWidth();
	size_t getHeight();
	void setDimensions(size_t width, size_t height);
	size_t getTextureIndex();
	void setTextureIndex(size_t textureIndex);
private:
	size_t x;
	size_t y;
	size_t width;
	size_t height;
	size_t textureIndex;
};