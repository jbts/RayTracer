#include "geom/NormalTriangle.h"

#include <vector>

#include "core/Vector3.h"
#include "geom/Triangle.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "geom/Plane.h"
#include "light/Material.h"

std::vector<Vector3> NormalTriangle::normals_ = std::vector<Vector3>();

NormalTriangle::NormalTriangle(int v1_index, int v2_index, int v3_index, int n1_index, int n2_index, int n3_index, const Material* const m) : Triangle(v1_index, v2_index, v3_index, m) {
  n1_index_ = n1_index;
  n2_index_ = n2_index;
  n3_index_ = n3_index;
}

void NormalTriangle::AddNormal(const Vector3& normal) {
  normals_.push_back(normal);
}

Vector3 NormalTriangle::Normal1() const {
  return normals_.at(n1_index_);
}

Vector3 NormalTriangle::Normal2() const {
  return normals_.at(n2_index_);
}

Vector3 NormalTriangle::Normal3() const {
  return normals_.at(n3_index_);
}

// Very similar to Triangle::FindIntersection()
// Differs in how we compute the normal at the point of intersection
HitInfo NormalTriangle::FindIntersection(const Ray& ray) const {
  HitInfo hit_info_plane = plane_containing_.FindIntersection(ray);
  // If the ray doesn't hit the plane containing the triangle, then it doesn't hit the triangle
  if (!hit_info_plane.DidIntersect()) {
    return HitInfo::NoHit();
  }

  // Possible optimization: this calls FindBaryCoords(), which we need
  // to call later if the triangle is hit. We could call FindBaryCoords()
  // ourself here and do the point-in-triangle test here
  Point3 intersection_point = ray.AtTime(hit_info_plane.Time());
  bool hit_triangle = Contains(intersection_point);

  if (hit_triangle) {
    // Compute the normal at the intersection by interpolating between the
    // three provided normals using barycentric coordinates
    BaryCoords bc = FindBaryCoords(intersection_point);
    Vector3 normal = (bc.Coord1() * Normal1() + bc.Coord2() * Normal2() + bc.Coord3() * Normal3()).Normalized();
    return HitInfo(true, hit_info_plane.Time(), normal, GetMaterial());
  }

  return HitInfo::NoHit();
}
