#include "largeImage.h"
#include <cstdlib>

LargeImage::~LargeImage() {
  for(size_t a = 0; a < pixelNum; ++a) {
    delete[] pixels[a];
    for(int b = 0; b < locationNum[a]; ++b) {
      delete[] location[a][b];
    }
    delete[] location[a];
  }
  delete[] pixels;
  delete[] location;
  delete[] locationNum;
}
