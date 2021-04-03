#include "spatial/XYZBounds.h"

#include <cstdlib>

#include "geom/Sphere.h"
#include "geom/Triangle.h"

XYZBounds XYZBounds::GetBounds(Sphere* sphere) {
  Point3 pos = sphere->Pos();
  float r = sphere->Radius();

  float x_min = pos.X() - r;
  float x_max = pos.X() + r;
  float y_min = pos.Y() - r;
  float y_max = pos.Y() + r;
  float z_min = pos.Z() - r;
  float z_max = pos.Z() + r;

  return XYZBounds(x_min, x_max, y_min, y_max, z_min, z_max);
}

XYZBounds XYZBounds::GetBounds(Triangle* triangle) {
  Point3 v1 = triangle->Vertex1();
  Point3 v2 = triangle->Vertex2();
  Point3 v3 = triangle->Vertex3();

  float x_min = std::min(std::min(v1.X(), v2.X()), v3.X());
  float x_max = std::max(std::max(v1.X(), v2.X()), v3.X());
  float y_min = std::min(std::min(v1.Y(), v2.Y()), v3.Y());
  float y_max = std::max(std::max(v1.Y(), v2.Y()), v3.Y());
  float z_min = std::min(std::min(v1.Z(), v2.Z()), v3.Z());
  float z_max = std::max(std::max(v1.Z(), v2.Z()), v3.Z());

  return XYZBounds(x_min, x_max, y_min, y_max, z_min, z_max);
}