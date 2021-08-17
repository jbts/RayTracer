#ifndef IMAGE_TONEMAPMODIFYBLUE_H_
#define IMAGE_TONEMAPMODIFYBLUE_H_

#include "image/ToneMap.h"
#include "core/Color.h"

class ToneMapModifyBlue : public ToneMap {
  private:
    float s_;
  
  public:
    ToneMapModifyBlue(float s) : s_(s) {}
    Color ApplyMap(const Color& c, const ImageInfo& img_info) const override;
};

#endif