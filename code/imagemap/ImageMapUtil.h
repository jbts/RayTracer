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
};

#endif