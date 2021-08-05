#include "image/ToneMap.h"

#include "core/Color.h"

Color ToneMapBasicClamp(const Color& c) {
  return Color(ColorCompClamp(c.R()), ColorCompClamp(c.G()), ColorCompClamp(c.B()));
}

Color ToneMapAvgLumScale(const Color& c, float avg_lum, float alpha) {
  return alpha / avg_lum * c;
}
