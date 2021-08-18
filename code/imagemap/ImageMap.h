#ifndef IMAGEMAP_IMAGEMAP_H_
#define IMAGEMAP_IMAGEMAP_H_

#include "image/Image.h"

class ImageMap {
  public:
    virtual ~ImageMap() {}
    virtual void ApplyMap(Image& img) const = 0;
};

#endif
