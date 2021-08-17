#include "image/ToneMapModifyBlue.h"

#include "image/ToneMap.h"
#include "core/Color.h"

Color ToneMapModifyBlue::ApplyMap(const Color& c, const ImageInfo& img_info) const {
  return Color(c.R(), c.G(), c.B() * s_);
}