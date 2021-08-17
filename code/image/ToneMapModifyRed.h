#ifndef IMAGE_TONEMAPMODIFYRED_H_
#define IMAGE_TONEMAPMODIFYRED_H_

#include "image/ToneMap.h"
#include "core/Color.h"

class ToneMapModifyRed : public ToneMap {
  private:
    float s_;
  
  public:
    ToneMapModifyRed(float s) : s_(s) {}
    Color ApplyMap(const Color& c, const ImageInfo& img_info) const override;
};

#endif