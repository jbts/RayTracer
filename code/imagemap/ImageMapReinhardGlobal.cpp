#include "imagemap/ImageMapReinhardGlobal.h"

#include "image/Image.h"
#include "core/Color.h"

void ImageMapReinhardGlobal::ApplyMap(Image& img) const {
  int width = img.Width();
  int height = img.Height();
  float lumwhite_sqr = lumwhite_ * lumwhite_;
  
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      Color c = img.GetPixel(x, y);
      float lum = c.Lum();
      
      float numer = 1 + lum / lumwhite_sqr;
      float denom = 1 + lum;
      
      img.SetPixel(x, y, c * (numer / denom));
    }
  }
}