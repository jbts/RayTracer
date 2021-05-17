#include "geom/Ray.h"

#include "core/Point3.h"
#include "core/Vector3.h"

Ray::Ray() {
  start_ = Point3(0, 0, 0);
  dir_ = Vector3(0, 0, 1).Normalized();
}

Ray::Ray(const Point3& start, const Vector3& dir) {
  start_ = start;
  dir_ = dir.Normalized();
}

Point3 Ray::AtTime(float t) const {
  // Dir is normalized
  return start_ + t * dir_;
}
