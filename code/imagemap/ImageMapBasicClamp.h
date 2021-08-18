#ifndef IMAGEMAP_IMAGEMAPBASICCLAMP_H_
#define IMAGEMAP_IMAGEMAPBASICCLAMP_H_

#include "imagemap/ImageMap.h"
#include "image/Image.h"

class ImageMapBasicClamp : public ImageMap {
  public:
    ImageMapBasicClamp() {}
    void ApplyMap(Image& img) const override;
};

#endif