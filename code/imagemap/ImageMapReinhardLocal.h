#ifndef IMAGEMAP_IMAGEMAPREINHARDLOCAL_H_
#define IMAGEMAP_IMAGEMAPREINHARDLOCAL_H_

#include "imagemap/ImageMap.h"
#include "image/Image.h"

class ImageMapReinhardLocal : public ImageMap {
  private:
    static constexpr float alpha_ = 0.3535534f;

    // The sharpening parameter
    float phi_;
    // The threshold
    float epsilon_;
    // The key value
    float a_;

  public:
    ImageMapReinhardLocal(float a, float phi, float epsilon);

    void ApplyMap(Image& img) const override;

    float ComputeSRaw(int n) const;

    float ComputeGaussian(float dx, float s) const;
    float* ConvolveGaussian(float* luminances, int width, int height, int filter_size) const;
    
    float V(float** convolved_maps, int width, int height, int x, int y, int i, int s) const;
};

#endif
