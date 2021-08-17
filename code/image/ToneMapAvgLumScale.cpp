#include "image/ToneMapAvgLumScale.h"

#include "core/Color.h"

Color ToneMapAvgLumScale::ApplyMap(const Color& c, const ImageInfo& img_info) const {
  return alpha_ / img_info.avg_lum * c;
}