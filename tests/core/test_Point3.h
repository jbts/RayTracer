#include <catch2/catch_test_macros.hpp>

#include "core/Point3.h"

TEST_CASE("Point accessors") {
  Point3 p(1, 2, 3);

  REQUIRE(0.999f < p.X());
  REQUIRE(p.X() < 1.0001f);
}
