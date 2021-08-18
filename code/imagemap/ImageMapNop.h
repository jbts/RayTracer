#ifndef IMAGEMAP_IMAGEMAPNOP_H_
#define IMAGEMAP_IMAGEMAPNOP_H_

#include "imagemap/ImageMap.h"
#include "image/Image.h"

// An image map that does nothing
class ImageMapNop : public ImageMap {
  public:
    ImageMapNop() {}
    void ApplyMap(Image& img) const override {}
};

#endif