#include <catch2/catch_test_macros.hpp>

#include "geom/Circle.h"
#include "geom/Ray.h"
#include "core/Point3.h"
#include "core/Vector3.h"
#include "light/Material.h"

TEST_CASE("Circle intersections") {
  Circle c(Point3(0, 0, 0), 1.0f, Vector3(1, 0, 0), Material::BaseMat());

  Ray ray(Point3(1, 0, 0), Vector3(-1, 0, 0));
  HitInfo hi = c.FindIntersection(ray);

  REQUIRE(hi.DidIntersect());

  ray = Ray(Point3(1, 0, 0), Vector3(1, 0, 0));
  hi = c.FindIntersection(ray);

  REQUIRE(!hi.DidIntersect());
}
