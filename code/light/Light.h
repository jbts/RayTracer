#ifndef LIGHT_LIGHT_H_
#define LIGHT_LIGHT_H_

#include <vector>

#include "core/Color.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "spatial/Scene.h"

/// An abstract base light class representing a generic light in the scene
class Light {
  private:

  protected:
    // Minimum time of collision to be considered a valid collision for shadow
    // calculations
    const float shadow_tolerance = 0.0001f;

  public:
    Light() {}
    virtual ~Light() {}

    /// Compute the color contribution of this light based on the viewing ray, intersection info, and scene data
    /// A pure virtual function that must be implemented by children
    /// depth_left is a bound on the number of recursive calls allowed. Each recursive call should subtract 1 from depth_left.
    virtual Color ComputeLighting(const Ray& ray, const HitInfo& hit_info, const Scene& scene, int depth_left) const = 0;
};

#endif
