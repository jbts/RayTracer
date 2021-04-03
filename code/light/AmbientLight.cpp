#include "light/AmbientLight.h"

#include "core/Color.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "spatial/Scene.h"

Color AmbientLight::ComputeLighting(Ray ray, HitInfo hit_info, Scene scene, int depth_left) const {
  Color mat_ambient = hit_info.GetMaterial().ColorAmbient();
  return i_ * mat_ambient;
}