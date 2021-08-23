#ifndef IMAGEMAP_IMAGEMAPUTIL_H_
#define IMAGEMAP_IMAGEMAPUTIL_H_

#include "image/Image.h"

/// A namespace defining functions helpful for various image maps or related
/// math and concepts
namespace ImageMapUtil {
  /// Find the maximum luminance of a pixel in the image
  float MaxLuminance(const Image& img);

  /// Find the minimum luminance of a pixel in the image
  float MinLuminance(const Image& img);

  /// Find the dynamic range of the image, which is the ratio of its maximum luminance
  /// to its minimum luminance
  float DynamicRange(const Image& img);

  /// Get an array holding all of the luminances of pixels in the image
  /// The luminance for pixel (x, y) is stored at index y * img.Width() + x in the image
  ///
  /// The array is dynamically allocated
  float* Luminances(const Image& img);

  /// Reflects an integer index back into the interval [min, max]
  /// Clamps the resulting index so that it always lies in the interval [min, max],
  /// even if the reflection would put it outside the interval
  int ReflectIndex(int index, int min, int max);

  /// Clamp a value of type T to the interval [min, max]
  /// Returns value if min <= value <= max
  /// If value < min, then returns min
  /// If value > max, then returns max
  template <typename T>
  T Clamp(T value, T min, T max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
  }

  /// Returns a dynamically allocated array that is the result of convolving the
  /// given 1D filter horizontally with the 2D array values of dimensions width and height
  /// Edges are handled by reflecting indices with ReflectIndex()
  float* ConvolveFilterHorizontal(const float* const values, int width, int height, const float* const filter, int filter_size);

  /// Returns a dynamically allocated array that is the result of convolving the
  /// given 1D filter vertically with the 2D array values of dimensions width and height
  /// Edges are handled by reflecting indices with ReflectIndex()
  float* ConvolveFilterVertical(const float* const values, int width, int height, const float* const filter, int filter_size);
};

#endif