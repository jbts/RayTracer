#include "light/SpotLight.h"

#include <vector>

#include "core/Color.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "spatial/Scene.h"

Color SpotLight::ComputeLighting(Ray ray, HitInfo hit_info, Scene scene, int depth_left) const {
  return Color(0, 0, 0);
}