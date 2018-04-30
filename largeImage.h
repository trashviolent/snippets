#pragma once

#include <cstdlib>
#include "point.h"

class LargeImage {
  private:
    size_t pixelNum;
    uint8_t** pixels; //[pixelNum][4 (rgba)]
    size_t* locationNum;
    uint16_t height;
    uint16_t width;
    Point*** location; //[pixelNum][locationNum][point: x and y]
  public:
    ~LargeImage();
    void largeImageSetup(std::string &filePath);
};
