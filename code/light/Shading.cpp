#include "light/Shading.h"

#include <cmath>

#include "core/Color.h"
#include "core/Vector3.h"
#include "light/Intensity.h"
#include "light/Material.h"

Color ComputeDiffuseShading(Vector3 normal, Vector3 to_light, Intensity intensity, Material mat) {
  // Clamp to nonnegative to prevent negative lighting
  float cosine = std::max(0.0f, Dot(normal, to_light));
  Color col = mat.ColorDiffuse() * intensity;
  return col * cosine;
}

Color ComputeSpecularShadingPhong(Vector3 dir, Vector3 light_reflected, Intensity intensity, Material mat) {
  float cosine = std::max(0.0f, Dot((-1 * dir), light_reflected));
  Color col = mat.ColorSpecular() * intensity;
  return col * powf(cosine, mat.PhongPower());
}

Color ComputeSpecularShadingBlinnPhong(Vector3 dir, Vector3 normal, Vector3 to_light, Intensity intensity, Material mat) {
  // Normalized bisector of dir and to_light
  Vector3 halfway = ((-1 * dir) + to_light).Normalized();
  float cosine = std::max(0.0f, Dot(normal, halfway));
  Color col = mat.ColorSpecular() * intensity;
  return col * powf(cosine, mat.PhongPower());
}