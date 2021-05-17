#ifndef LIGHT_DIRECTIONALLIGHT_H_
#define LIGHT_DIRECTIONALLIGHT_H_

#include <vector>

#include "core/Vector3.h"
#include "light/Intensity.h"
#include "light/Light.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "spatial/Scene.h"

/// A directional light source
/// Models a very far away light source, like the sun
class DirectionalLight : public Light {
  private:
    // Direction of light
    Vector3 dir_;
    Intensity i_;
  
  public:
    DirectionalLight() : dir_(1, 0, 0), i_(0, 0, 0) {}
    DirectionalLight(const Vector3& dir, const Intensity& intensity) : dir_(dir), i_(intensity) {}

    Vector3 Dir() const { return dir_; }
    Intensity GetIntensity() const { return i_; }

    /// Compute the color contribution of this directional light at a point of intersection
    Color ComputeLighting(const Ray& ray, const HitInfo& hit_info, const Scene& scene, int depth_left) const override;
};

#endif
