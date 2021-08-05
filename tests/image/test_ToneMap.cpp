#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "core/Color.h"
#include "image/ToneMap.h"

TEST_CASE("Basic clamp tone map") {
  Color c(100.0f, -2.0f, 0.3f);
  c = ToneMapBasicClamp(c);
  REQUIRE(c.R() == Approx(1.0f));
  REQUIRE(c.G() == Approx(0.0f));
  REQUIRE(c.B() == Approx(0.3f));
}

