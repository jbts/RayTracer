#include <catch2/catch_test_macros.hpp>

#include "geom/Ellipse.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "core/Point3.h"
#include "core/Vector3.h"
#include "light/Material.h"

TEST_CASE("Ellipse intersections") {
  Point3 focus1(1, 0, 0);
  Point3 focus2(3, 0, 0);
  float d = 3;
  Vector3 normal(0, 1, 0);

  Ellipse e(focus1, focus2, d, normal, Material::BaseMat());

  Ray ray(Point3(0, 0, 0), Vector3(0, 1, 0));
  HitInfo hi = e.FindIntersection(ray);
  REQUIRE(!hi.DidIntersect());

  ray = Ray(Point3(1, 1, 0), Vector3(0, -1, 0));
  hi = e.FindIntersection(ray);
  REQUIRE(hi.DidIntersect());

  ray = Ray(Point3(1, 1, 0), Vector3(0, 1, 0));
  hi = e.FindIntersection(ray);
  REQUIRE(!hi.DidIntersect());

  ray = Ray(Point3(1, 1, 0), Vector3(0.3, -1, 0));
  hi = e.FindIntersection(ray);
  REQUIRE(hi.DidIntersect());

  ray = Ray(Point3(3.2, -1, 0), Vector3(0, 1, 0));
  hi = e.FindIntersection(ray);
  REQUIRE(hi.DidIntersect());
}

