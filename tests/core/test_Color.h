#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "core/Color.h"

using Catch::Approx;

TEST_CASE("Color luminance") {
  Color red(1, 0, 0);
  Color green(0, 1, 0);
  Color blue(0, 0, 1);
  Color black(0, 0, 0);
  Color white(1, 1, 1);

  REQUIRE(red.Lum() == Approx(0.3f));
  REQUIRE(green.Lum() == Approx(0.6f));
  REQUIRE(blue.Lum() == Approx(0.1f));
  REQUIRE(black.Lum() == Approx(0.0f));
  REQUIRE(white.Lum() == Approx(1.0f));
}
