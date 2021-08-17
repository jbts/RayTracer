#include "image/ToneMapBasicClamp.h"

#include "core/Color.h"

Color ToneMapBasicClamp::ApplyMap(const Color& c, const ImageInfo& img_info) const {
  return Color(ColorCompClamp(c.R()), ColorCompClamp(c.G()), ColorCompClamp(c.B()));
}