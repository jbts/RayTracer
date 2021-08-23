#include "imagemap/ImageMapUtil.h"

#include <cmath>

#include "image/Image.h"
#include "core/Color.h"

float ImageMapUtil::MaxLuminance(const Image& img) {
  int width = img.Width();
  int height = img.Height();

  // Minimum possible luminance
  float max_lum = 0.0f;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      float lum = img.GetPixel(x, y).Lum();
      if (lum > max_lum) {
        max_lum = lum;
      }
    }
  }

  return max_lum;
}

float ImageMapUtil::MinLuminance(const Image& img) {
  int width = img.Width();
  int height = img.Height();

  // Maximum possible luminance
  float min_lum = INFINITY;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      float lum = img.GetPixel(x, y).Lum();
      if (lum < min_lum) {
        min_lum = lum;
      }
    }
  }

  return min_lum;
}

float ImageMapUtil::DynamicRange(const Image& img) {
  return ImageMapUtil::MaxLuminance(img) / ImageMapUtil::MinLuminance(img);
}

float* ImageMapUtil::Luminances(const Image& img) {
  int width = img.Width();
  int height = img.Height();

  float* lum_array = new float [width * height];

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      lum_array[y * width + x] = img.GetPixel(x, y).Lum();
    }
  }
  return lum_array;
}