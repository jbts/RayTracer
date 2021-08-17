#ifndef IMAGE_TONE_MAP_H_
#define IMAGE_TONE_MAP_H_

#include "core/Color.h"

/// Contains information about the image as a whole
struct ImageInfo {
  // The average luminance of the image
  float avg_lum;
};

/// Interface that all tone maps must implement
class ToneMap {
  public:
    virtual ~ToneMap() {}
    virtual Color ApplyMap(const Color& c, const ImageInfo& img_info) const = 0;
};

#endif
