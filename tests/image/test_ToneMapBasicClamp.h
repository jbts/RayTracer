#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "image/ToneMap.h"
#include "image/ToneMapBasicClamp.h"
#include "core/Color.h"

TEST_CASE("Tone map basic clamp") {
  ImageInfo img_info;
  img_info.avg_lum = 0.5f;

  ToneMapBasicClamp tone_map;

  Color c1(0.0f, 0.5f, 1.0f);
  Color c2(-1.0f, 0.0f, 1.5f);
  Color c3(1.2f, -0.2f, 0.3f);
  Color c4(0.3f, 1.7f, -2.0f);

  Color c1m = tone_map.ApplyMap(c1, img_info);
  Color c2m = tone_map.ApplyMap(c2, img_info);
  Color c3m = tone_map.ApplyMap(c3, img_info);
  Color c4m = tone_map.ApplyMap(c4, img_info);

  REQUIRE(c1m.R() == Approx(0.0f));
  REQUIRE(c1m.G() == Approx(0.5f));
  REQUIRE(c1m.B() == Approx(1.0f));

  REQUIRE(c2m.R() == Approx(0.0f));
  REQUIRE(c2m.G() == Approx(0.0f));
  REQUIRE(c2m.B() == Approx(1.0f));
  
  REQUIRE(c3m.R() == Approx(1.0f));
  REQUIRE(c3m.G() == Approx(0.0f));
  REQUIRE(c3m.B() == Approx(0.3f));
  
  REQUIRE(c4m.R() == Approx(0.3f));
  REQUIRE(c4m.G() == Approx(1.0f));
  REQUIRE(c4m.B() == Approx(0.0f));
}