#ifndef IMAGE_TONEMAPMODIFYGREEN_H_
#define IMAGE_TONEMAPMODIFYGREEN_H_

#include "image/ToneMap.h"
#include "core/Color.h"

class ToneMapModifyGreen : public ToneMap {
  private:
    float s_;
  
  public:
    ToneMapModifyGreen(float s) : s_(s) {}
    Color ApplyMap(const Color& c, const ImageInfo& img_info) const override;
};

#endif