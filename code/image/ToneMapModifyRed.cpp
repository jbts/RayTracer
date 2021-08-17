#include "image/ToneMapModifyRed.h"

#include "image/ToneMap.h"
#include "core/Color.h"

Color ToneMapModifyRed::ApplyMap(const Color& c, const ImageInfo& img_info) const {
  return Color(c.R() * s_, c.G(), c.B());
}