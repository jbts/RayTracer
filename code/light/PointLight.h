#ifndef LIGHT_POINTLIGHT_H_
#define LIGHT_POINTLIGHT_H_

#include <vector>

#include "core/Point3.h"
#include "light/Intensity.h"
#include "light/Light.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "spatial/Scene.h"

/// A point light source
class PointLight : public Light {
  private:
    Point3 pos_;
    Intensity i_;

  public:
    PointLight() : pos_(0, 0, 0), i_(0, 0, 0) {}
    PointLight(const Point3& pos, const Intensity& intensity) : pos_(pos), i_(intensity) {}

    Point3 Pos() const { return pos_; }
    Intensity GetIntensity() const { return i_; }

    /// Compute the color contribution of this point light at a point of intersection
    Color ComputeLighting(const Ray& ray, const HitInfo& hit_info, const Scene& scene, int depth_left) const override;

    /// Compute the intensity of this light at the specified distance
    /// In the real world, these lights fall off as 1/(dist^2)
    /// This function computes the fall off as 1/dist instead
    Intensity IntensityAtDistance(float dist) const;
};

#endif
