#include "geom/Circle.h"

#include "geom/Plane.h"
#include "geom/HitInfo.h"
#include "geom/Ray.h"
#include "core/Point3.h"
#include "core/Vector3.h"
#include "spatial/XYZBounds.h"

Circle::Circle(const Point3& center, float r, const Vector3& normal, const Material* const m) {
  center_ = center;
  r_ = r;
  normal_ = normal;
  m_ = m;
  plane_containing_ = Plane(center_, normal_, m_);
}

HitInfo Circle::FindIntersection(const Ray& ray) const {
  HitInfo plane_hit_info = plane_containing_.FindIntersection(ray);

  if (!plane_hit_info.DidIntersect()) {
    return HitInfo::NoHit();
  }

  Point3 intersection_point = ray.AtTime(plane_hit_info.Time());
  
  if ((center_ - intersection_point).Mag() <= r_) {
    return plane_hit_info;
  }

  return HitInfo::NoHit();
}

// These are really loose bounds and could be improved with some
// more work and math
XYZBounds Circle::FindBounds() const {
  float x_min = center_.X() - r_;
  float x_max = center_.X() + r_;
  float y_min = center_.Y() - r_;
  float y_max = center_.Y() + r_;
  float z_min = center_.Z() - r_;
  float z_max = center_.Z() + r_;

  return XYZBounds(x_min, x_max, y_min, y_max, z_min, z_max);
}
