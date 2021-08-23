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

int ImageMapUtil::ReflectIndex(int index, int min, int max) {
  if (index > max) {
    return ImageMapUtil::Clamp(index - 2 * (index - max), min, max);
  }
  if (index < min) {
    return ImageMapUtil::Clamp(index + 2 * (min - index), min, max);
  }
  return index;
}

float* ImageMapUtil::ConvolveFilterHorizontal(const float* const values, int width, int height, const float* const filter, int filter_size) {
  float* values_cpy = new float [width * height];

  for (int i = 0; i < width * height - 1; i++) {
    values_cpy[i] = values[i];
  }
  
  // Horizontal start and end indices for the filter
  int start_index = -filter_size / 2;
  int end_index = width - filter_size / 2;

  for (int y = 0; y < height; y++) {
    for (int x = start_index; x < end_index; x++) {
      float new_value = 0.0f;
      for (int i = 0; i < filter_size; i++) {
        new_value += filter[i] * values[y * width + ImageMapUtil::ReflectIndex(x + i, 0, width - 1)];
      }
      values_cpy[y * width + (x + filter_size / 2)] = new_value;
    }
  }
  return values_cpy;
}

float* ImageMapUtil::ConvolveFilterVertical(const float* const values, int width, int height, const float* const filter, int filter_size) {
  float* values_cpy = new float [width * height];

  for (int i = 0; i < width * height - 1; i++) {
    values_cpy[i] = values[i];
  }
  
  // Vertical start and end indices for the filter
  int start_index = -filter_size / 2;
  int end_index = height - filter_size / 2;

  for (int x = 0; x < width; x++) {
    for (int y = start_index; y < end_index; y++) {
      float new_value = 0.0f;
      for (int i = 0; i < filter_size; i++) {
        new_value += filter[i] * values[ImageMapUtil::ReflectIndex(y + i, 0, height - 1) * width + x];
      }
      values_cpy[(y + filter_size / 2) * width + x] = new_value; 
    }
  }
  return values_cpy;
}