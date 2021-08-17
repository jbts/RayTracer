#include "parsing/SceneData.h"

#include <vector>

#include "core/Point3.h"
#include "core/Vector3.h"
#include "geom/Triangle.h"
#include "geom/Sphere.h"
#include "light/Light.h"
#include "raygen/ViewFrame.h"

SceneData::SceneData() {
  camera_pos = Point3(0, 0, 0);
  camera_fwd = Vector3(0, 0, -1);
  camera_up = Vector3(0, 1, 0);
  camera_right = Vector3(-1, 0, 0);
  camera_fov_ha = 45;

  film_width = 640;
  film_height = 480;
  output_image = "raytraced.bmp";
  max_recurse_depth = 5;
     
  primitives = std::vector<Primitive*>();

  background_color = Color(0, 0, 0);
  lights = std::vector<Light*>();

  sample_strat = SAMPLE_STRATEGY_BASIC;
  num_samples_jitter = 5;

  tone_maps = std::vector<ToneMap*>();
}
