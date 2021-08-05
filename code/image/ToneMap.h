#ifndef IMAGE_TONE_MAP_H_
#define IMAGE_TONE_MAP_H_

#include "core/Color.h"

  Color ToneMapBasicClamp(const Color& c);

  Color ToneMapAvgLumScale(const Color& c, float avg_lum, float alpha);

#endif
