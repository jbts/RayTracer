#ifndef LIGHT_AMBIENTLIGHT_H_
#define LIGHT_AMBIENTLIGHT_H_

#include <vector>

#include "light/Intensity.h"
#include "light/Light.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "spatial/Scene.h"

class AmbientLight : public Light {
  private:
    Intensity i_;
  
  public:
    AmbientLight() : i_(0, 0, 0) {}
    AmbientLight(Intensity intensity) : i_(intensity) {}

    Intensity GetIntensity() const { return i_; }

    /// Compute the color contribution of this light at the intersection point
    /// Since this light is ambient, it affects every point the same amount
    /// based on its intensity
    Color ComputeLighting(Ray ray, HitInfo hit_info, Scene scene, int depth_left) const override;
};

#endif