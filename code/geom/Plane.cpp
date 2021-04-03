#include "geom/Plane.h"

#include <cmath>

#include "core/Point3.h"
#include "core/Vector3.h"
#include "geom/HitInfo.h"
#include "geom/Ray.h"
#include "light/Material.h"

Plane::Plane(Point3 p, Vector3 normal, Material m) {
  p_ = p;
  normal_ = normal.Normalized();
  m_ = m;
}

HitInfo Plane::FindIntersection(Ray ray) const {
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

bool Plane::Contains(Point3 p) const {
  Vector3 v = p - p_;
  
  return fabs(Dot(v, normal_)) <= contains_tolerance_;
}

Plane PlaneContaining(Triangle tri) {
  Vector3 v1 = tri.Vertex2() - tri.Vertex1();
  Vector3 v2 = tri.Vertex3() - tri.Vertex1();
  Vector3 normal = Cross(v1, v2).Normalized();
  return Plane(tri.Vertex1(), normal, tri.GetMaterial());
}