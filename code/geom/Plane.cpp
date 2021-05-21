#include "geom/Plane.h"

#include <cmath>

#include "core/Point3.h"
#include "core/Vector3.h"
#include "geom/HitInfo.h"
#include "geom/Ray.h"
#include "light/Material.h"

Plane::Plane(const Point3& p, const Vector3& normal, const Material& m) {
  p_ = p;
  normal_ = normal.Normalized();
  m_ = m;
}

HitInfo Plane::FindIntersection(const Ray& ray) const {
  Vector3 v = ray.Dir();
  Vector3 start_to_plane = p_ - ray.Start();

  float denom = Dot(normal_, v);
  // If the denom is 0, then the ray is parallel to the plane -- no intersection
  if (denom == 0) {
    return HitInfo::NoHit();
  }

  float t = Dot(normal_, start_to_plane) / denom;

  // No intersection - plane is "behind" the ray
  if (t < 0) {
    return HitInfo::NoHit();
  }

  return HitInfo(true, t, normal_, m_, ID());
}

bool Plane::Contains(const Point3& p) const {
  Vector3 v = p - p_;
  
  return fabs(Dot(v, normal_)) <= contains_tolerance_;
}
