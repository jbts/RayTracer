#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "imagemap/ImageMapUtil.h"
#include "core/Color.h"
#include "image/Image.h"

using namespace ImageMapUtil;

TEST_CASE("Clamp on floats") {
  REQUIRE(Clamp(0.0f, -1.0f, 1.0f) == Approx(0.0f));
  REQUIRE(Clamp(-1.0f, 0.0f, 1.0f) == Approx(0.0f));
  REQUIRE(Clamp(1.0f, -1.0f, 0.0f) == Approx(0.0f));
  REQUIRE(Clamp(42.0f, 753.0f, 1000.0f) == Approx(753.0f));
  REQUIRE(Clamp(9.0f, 0.0f, 1.0f) == Approx(1.0f));
}

TEST_CASE("Clamp on ints") {
  REQUIRE(Clamp(0, -1, 1) == 0);
  REQUIRE(Clamp(-1, 0, 1) == 0);
  REQUIRE(Clamp(1, -1, 0) == 0);
  REQUIRE(Clamp(42, 753, 1000) == 753);
  REQUIRE(Clamp(9, 0, 1) == 1);
}

TEST_CASE("ReflectIndex") {
  REQUIRE(ReflectIndex(5, 0, 10) == 5);
  REQUIRE(ReflectIndex(0, 0, 10) == 0);
  REQUIRE(ReflectIndex(10, 0, 10) == 10);
  REQUIRE(ReflectIndex(1, 1, 1) == 1);

  REQUIRE(ReflectIndex(11, 5, 10) == 9);
  REQUIRE(ReflectIndex(13, 5, 10) == 7);
  // Clamp to range even if reflection would end up outside
  REQUIRE(ReflectIndex(20, 5, 10) == 5);

  REQUIRE(ReflectIndex(4, 5, 10) == 6);
  REQUIRE(ReflectIndex(2, 5, 10) == 8);
  // Clamp to range even if reflection would end up outside
  REQUIRE(ReflectIndex(-20, 5, 10) == 10);
}

TEST_CASE("Horizontal filter convolution stress test") {
  float values[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  int width = 2;
  int height = 2;
  float filter[100];

  for (int i = 0; i < 100; i++) {
    filter[i] = (i + 1) / 100.0f;
  }

  float* result = ConvolveFilterHorizontal(values, width, height, filter, 100);
  // Shouldn't get null back from the function
  // This could change if/when error handling is added
  REQUIRE(result);
  delete[] result;
  result = nullptr;
}

TEST_CASE("Vertical filter convolution stress test") {
  float values[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  int width = 2;
  int height = 2;
  float filter[100];

  for (int i = 0; i < 100; i++) {
    filter[i] = (i + 1) / 100.0f;
  }

  float* result = ConvolveFilterVertical(values, width, height, filter, 100);
  // Shouldn't get null back from the function
  // This could change if/when error handling is added
  REQUIRE(result);
  delete[] result;
  result = nullptr;
}

TEST_CASE("Luminances of an image's pixels") {
  Image img(3, 2);
  img.SetPixel(0, 0, Color(0, 0, 0));
  img.SetPixel(1, 0, Color(1, 1, 1));
  img.SetPixel(2, 0, Color(1, 0, 1));
  img.SetPixel(0, 1, Color(1, 1, 1));
  img.SetPixel(1, 1, Color(10, 10, 0));
  img.SetPixel(2, 1, Color(0, 100, 0));

  float* result = Luminances(img);

  REQUIRE(result[0] == Approx(0.0f));
  REQUIRE(result[1] == Approx(1.0f));
  REQUIRE(result[2] == Approx(0.4f));
  REQUIRE(result[3] == Approx(1.0f));
  REQUIRE(result[4] == Approx(9.0f));
  REQUIRE(result[5] == Approx(60.0f));

  delete[] result;
  result = nullptr;
}