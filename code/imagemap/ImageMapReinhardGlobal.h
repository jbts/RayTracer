#ifndef IMAGEMAP_IMAGEMAPREINHARDGLOBAL_H_
#define IMAGEMAP_IMAGEMAPREINHARDGLOBAL_H_

#include "imagemap/ImageMap.h"
#include "image/Image.h"

/// Implements the global tone mapping operator from the paper "Photographic Tone
/// Reproduction for Digital Images" by Reinhard et al.
///
/// This is the version that takes in a parameter lumwhite which determines what
/// luminance will be considered "white" or the maximum displayable luminance
class ImageMapReinhardGlobal : public ImageMap {
  private:
    float lumwhite_;
  
  public:
    ImageMapReinhardGlobal(float lumwhite) : lumwhite_(lumwhite) {}
    void ApplyMap(Image& img) const override;
};

#endif