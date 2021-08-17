#ifndef IMAGE_TONEMAPAVGLUMSCALE_H_
#define IMAGE_TONEMAPAVGLUMSCALE_H_

#include "image/ToneMap.h"

#include "core/Color.h"

class ToneMapAvgLumScale : public ToneMap {
  private:
    float alpha_;
  
  public:
    ToneMapAvgLumScale(float alpha) : alpha_(alpha) {}
    Color ApplyMap(const Color& c, const ImageInfo& img_info) const override;
};

#endif