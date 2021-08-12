#include "geom/Ellipse.h"

#include "geom/Plane.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "core/Point3.h"
#include "core/Vector3.h"
#include "light/Material.h"

Ellipse::Ellipse(const Point3& focus1, const Point3& focus2, float d, const Vector3& normal, const Material* const m) {
  focus1_ = focus1;
  focus2_ = focus2;
  d_ = d;
  normal_ = normal;
  m_ = m;
  plane_containing_ = Plane(focus1_, normal_, m_);
}

HitInfo Ellipse::FindIntersection(const Ray& ray) const {
  HitInfo plane_hit_info = plane_containing_.FindIntersection(ray);

  if (!plane_hit_info.DidIntersect()) {
    return HitInfo::NoHit();
  }

  Point3 intersection_point = ray.AtTime(plane_hit_info.Time());

  // Check that the ray hits the ellipse
  float d_check = (focus1_ - intersection_point).Mag() + (focus2_ - intersection_point).Mag();
  if (d_check <= d_) {
    // Make sure the normal of the ellipse points opposite the direction
    // of the incoming ray
    if (Dot(ray.Dir(), normal_) > 0) {
      return HitInfo(true, plane_hit_info.Time(), -1 * normal_, m_);
    }
    return HitInfo(true, plane_hit_info.Time(), normal_, m_);
  }
  return HitInfo::NoHit(); 
}

/// Like the circle's bounds, these are not optimal
XYZBounds Ellipse::FindBounds() const {
  Point3 center = focus1_ + 0.5f * (focus2_ - focus1_);
  float x_min = center.X() - d_;
  float x_max = center.X() + d_;
  float y_min = center.Y() - d_;
  float y_max = center.Y() + d_;
  float z_min = center.Z() - d_;
  float z_max = center.Z() + d_;

  return XYZBounds(x_min, x_max, y_min, y_max, z_min, z_max);
}
