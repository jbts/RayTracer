#include "image/ToneMapModifyGreen.h"

#include "image/ToneMap.h"
#include "core/Color.h"

Color ToneMapModifyGreen::ApplyMap(const Color& c, const ImageInfo& img_info) const {
  return Color(c.R(), c.G() * s_, c.B());
}