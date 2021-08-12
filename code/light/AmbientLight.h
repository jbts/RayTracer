#ifndef LIGHT_AMBIENTLIGHT_H_
#define LIGHT_AMBIENTLIGHT_H_

#include <vector>

#include "light/Intensity.h"
#include "light/Light.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "spatial/Scene.h"

/// An ambient light source
/// Shines equally in all places
class AmbientLight : public Light {
  private:
    Intensity i_;
  
  public:
    AmbientLight() : i_(0, 0, 0) {}
    AmbientLight(const Intensity& intensity) : i_(intensity) {}

    Intensity GetIntensity() const { return i_; }

    Color ComputeLighting(const Ray& ray, const HitInfo& hit_info, const Scene& scene, int depth_left) const override;
};

#endif
