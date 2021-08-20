#include "imagemap/ImageMapAvgLumScale.h"

#include "image/Image.h"

void ImageMapAvgLumScale::ApplyMap(Image& img) const {
  int width = img.Width();
  int height = img.Height();
  float avg_lum = img.AvgLum();
  
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      Color c = img.GetPixel(x, y);
      img.SetPixel(x, y, factor_ / avg_lum * c);
    }
  }
}