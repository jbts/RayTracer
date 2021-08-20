#ifndef IMAGEMAP_IMAGEMAPAVGLUMSCALE_H_
#define IMAGEMAP_IMAGEMAPAVGLUMSCALE_H_

#include "imagemap/ImageMap.h"
#include "image/Image.h"

class ImageMapAvgLumScale : public ImageMap {
  private:
    float factor_;
  
  public:
    ImageMapAvgLumScale(float factor) : factor_(factor) {}
    void ApplyMap(Image& img) const override;
};

#endif