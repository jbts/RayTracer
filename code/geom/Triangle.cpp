#include "geom/Triangle.h"

#include <vector>

#include "core/Point3.h"
#include "core/Vector3.h"
#include "geom/HitInfo.h"
#include "geom/Ray.h"
#include "geom/Plane.h"
#include "light/Material.h"

std::vector<Point3> Triangle::vertices_ = std::vector<Point3>();

Triangle::Triangle(int v1_index, int v2_index, int v3_index, const Material& m) {
  v1_index_ = v1_index;
  v2_index_ = v2_index;
  v3_index_ = v3_index;
  m_ = m;
  plane_containing_ = PlaneContaining(*this);
  area_ = Area();
}

HitInfo Triangle::FindIntersection(const Ray& ray) const {
  HitInfo hit_info_plane = plane_containing_.FindIntersection(ray);
  // If the ray doesn't hit the plane containing the triangle, then it doesn't hit the triangle
  if (!hit_info_plane.DidIntersect()) {
    return HitInfo::NoHit();
  }

  bool hit_triangle = Contains(ray.AtTime(hit_info_plane.Time()));

  if (hit_triangle) {
    // Compute the normal for this triangle
    // Since we don't have any associated normal information (not a NormalTriangle),
    // do a basic normal calculation
    Vector3 normal = Cross(Vertex2() - Vertex1(), Vertex3() - Vertex1()).Normalized();
    // Make sure the triangle's normal is always pointing toward the camera
    // Necessary because triangles don't have a sidedness / orientation in config files
    if (Dot(ray.Dir(), normal) > 0) {
      normal = -1 * normal;
    }
    return HitInfo(true, hit_info_plane.Time(), normal, m_, ID());
  }

  return HitInfo::NoHit();
}

void Triangle::AddVertex(const Point3& vertex) {
  vertices_.push_back(vertex);
}

Point3 Triangle::Vertex1() const {
  return vertices_.at(v1_index_);
}

Point3 Triangle::Vertex2() const {
  return vertices_.at(v2_index_);
}

Point3 Triangle::Vertex3() const {
  return vertices_.at(v3_index_);
}

float Triangle::Area() const {
  return 0.5 * Cross(Vertex2() - Vertex1(), Vertex3() - Vertex1()).Mag();
}

float TriangleArea(const Point3& t1, const Point3& t2, const Point3& t3) {
  return 0.5 * Cross(t2 - t1, t3 - t1).Mag();
}

bool Triangle::Contains(const Point3& p) const {
  BaryCoords bc = FindBaryCoords(p);
  return bc.Coord1() + bc.Coord2() + bc.Coord3() <= 1 + contains_tolerance_;
}

BaryCoords Triangle::FindBaryCoords(const Point3& p) const {
  float coord1 = TriangleArea(Vertex2(), Vertex3(), p) / area_;
  float coord2 = TriangleArea(Vertex3(), Vertex1(), p) / area_;
  float coord3 = TriangleArea(Vertex1(), Vertex2(), p) / area_;
  return BaryCoords(coord1, coord2, coord3);
}

Plane PlaneContaining(const Triangle& tri) {
  Vector3 v1 = tri.Vertex2() - tri.Vertex1();
  Vector3 v2 = tri.Vertex3() - tri.Vertex1();
  Vector3 normal = Cross(v1, v2);
  return Plane(tri.Vertex1(), normal, tri.GetMaterial());
}
