#include "actor.h"
#include <cstdint>

size_t Actor::getX() {
	return this->x;
}

size_t Actor::getY() {
	return this->y;
}

void Actor::setCoordinates(size_t x, size_t y) {
	this->x = x;
	this->y = y;
}

size_t Actor::getWidth() {
	return this->width;
}

size_t Actor::getHeight() {
	return this->height;
}

void Actor::setDimensions(size_t width, size_t height) {
	this->width = width;
	this->height = height;
}

size_t Actor::getTextureIndex() {
	return this->textureIndex;
}

void Actor::setTextureIndex(size_t textureIndex) {
	this->textureIndex = textureIndex;
}