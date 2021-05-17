#include "geom/Sphere.h"

#include <cmath>

#include "core/Point3.h"
#include "core/Vector3.h"
#include "light/Material.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"

Sphere::Sphere() {
  pos_ = Point3(0, 0, 0);
  r_ = 0;
  m_ = Material();
}

Sphere::Sphere(const Point3& pos, float r, const Material& m) {
  pos_ = pos;
  r_ = r;
  m_ = m;
}

HitInfo Sphere::FindIntersection(const Ray& ray) const {
  Vector3 center_to_start = ray.Start() - pos_;
  Vector3 v = ray.Dir();

  // Coefficients for quadratic equation
  // Possible small optimization: since we know that a ray's direction
  // is always normalized, A is always 1
  float A = Dot(v, v);
  float B = 2 * Dot(v, center_to_start);
  float C = Dot(center_to_start, center_to_start) - r_*r_;

  // The discriminant
  float discrim = B*B - 4*A*C;
  // No intersections possible
  if (discrim < 0) {
    return HitInfo::NoHit();
  }

  // Could be one or two intersections
  float sqrt_discrim = sqrtf(discrim);
  float t1 = (-B + sqrt_discrim) / (2*A);
  float t2 = (-B - sqrt_discrim) / (2*A);

  HitInfo hit_info = HitInfo::NoHit();

  if (t1 > 0) {
    // Compute normal of sphere at intersection
    Vector3 normal = (ray.AtTime(t1) - pos_).Normalized();
    hit_info = HitInfo(true, t1, normal, m_, ID());
  }

  // We know that t2 <= t1 since sqrt_discrim >= 0 and A > 0
  // So if t1 < 0, then t2 is as well
  if (t2 > 0 && t2 < t1) {
    // Compute normal of sphere at intersection
    Vector3 normal = (ray.AtTime(t2) - pos_).Normalized();
    hit_info = HitInfo(true, t2, normal, m_, ID());
  }

  return hit_info;
}
