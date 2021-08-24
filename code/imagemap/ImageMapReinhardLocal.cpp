#include "imagemap/ImageMapReinhardLocal.h"

#include <cmath>
#include <iostream>

#include "imagemap/ImageMapUtil.h"
#include "image/Image.h"

// ***************************************************************
// Need to take care of the case where M_PI isn't defined in cmath

ImageMapReinhardLocal::ImageMapReinhardLocal(float a, float phi, float epsilon) {
  a_ = a;
  phi_ = phi;
  epsilon_ = epsilon;
}

void ImageMapReinhardLocal::ApplyMap(Image& img) const {
  int width = img.Width();
  int height = img.Height();

  int max_index = 9;
  float* convolved_maps[max_index];
  int s[max_index];

  float* luminances = ImageMapUtil::Luminances(img);

  for (int i = 0; i < max_index; i++) {
    s[i] = (int)(ComputeSRaw(i) + 0.5f);
    convolved_maps[i] = ConvolveGaussian(luminances, width, height, s[i]);
  }

  // For each pixel, find the largest scale sm with |V(x, y, sm)| < epsilon_
  // Store it as its integer index into the s array
  int* sm_indices = new int [width * height];
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int sm_index = 0;
      
      while (sm_index < max_index - 1 && V(convolved_maps, width, height, x, y, sm_index, s[sm_index]) < epsilon_) {
        sm_index++;
      }

      sm_indices[y * width + x] = sm_index;
    }
  }

  // Now we know how to adjust the luminance of each pixel
  // Actually apply the map to the image
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      Color c = img.GetPixel(x, y);
      int map_index = sm_indices[y * width + x];
      float denom = 1 + convolved_maps[map_index][y * width + x];
      img.SetPixel(x, y, c * (1.0f / denom));
    }
  }

  // Free memory
  delete[] sm_indices;
  sm_indices = nullptr;

  for (int i = 0; i < max_index; i++) {
    delete[] convolved_maps[i];
    convolved_maps[i] = nullptr;
  }

  delete[] luminances;
  luminances = nullptr;
}

float ImageMapReinhardLocal::ComputeSRaw(int n) const {
  return powf(1.6, n);
}

float ImageMapReinhardLocal::ComputeGaussian(float dx, float s) const {
  float alpha_s_sqr = alpha_ * alpha_ * s * s;
  float scalar = 1.0f / (M_PI * alpha_s_sqr);
  return scalar * expf(-dx*dx / alpha_s_sqr);
}

float* ImageMapReinhardLocal::ConvolveGaussian(float* luminances, int width, int height, int filter_size) const {
  float* filter = new float [filter_size];
  float filter_center = (filter_size - 1) / 2.0f;
  float filter_sum = 0.0f;

  for (int i = 0; i < filter_size; i++) {
    filter[i] = ComputeGaussian(fabs(i - filter_center), filter_size);
    filter_sum += filter[i];
  }

  // Normalize the filter so it sums to 1
  for (int i = 0; i < filter_size; i++) {
    filter[i] /= filter_sum;
  }
  
  // The Gaussian filter is separable, so convolve first in the horizontal
  // direction and then in the vertical direction
  float* convolve_horiz = ImageMapUtil::ConvolveFilterHorizontal(luminances, width, height, filter, filter_size);
  float* convolve_vert = ImageMapUtil::ConvolveFilterVertical(convolve_horiz, width, height, filter, filter_size);
  
  delete[] convolve_horiz;
  convolve_horiz = nullptr;
  delete[] filter;
  filter = nullptr;

  return convolve_vert;
}

float ImageMapReinhardLocal::V(float** convolved_maps, int width, int height, int x, int y, int i, int s) const {
  float numer = convolved_maps[i][y * width + x] - convolved_maps[i + 1][y * width + x];
  float denom = powf(2, phi_) * a_ / (s*s) + convolved_maps[i][y * width + x];

  return numer / denom;
}