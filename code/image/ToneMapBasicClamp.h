#ifndef IMAGE_TONEMAPBASICCLAMP_H_
#define IMAGE_TONEMAPBASICCLAMP_H_

#include "image/ToneMap.h"
#include "core/Color.h"

class ToneMapBasicClamp : ToneMap {
  public:
    Color ApplyMap(const Color& c, const ImageInfo& img_info) const override;
};

#endif