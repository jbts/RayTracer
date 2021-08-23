#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

// Include all of test files, which are all
// header files using Catch2 test macros
#include "core/test_Point3.h"
#include "core/test_Color.h"

#include "geom/test_Circle.h"
#include "geom/test_Ellipse.h"

#include "imagemap/test_ImageMapUtil.h"
#include "imagemap/test_ImageMapReinhardLocal.h"
