#include "light/Shading.h"

#include <cmath>

#include "core/Color.h"
#include "core/Vector3.h"
#include "light/Intensity.h"
#include "light/Material.h"

Color ComputeDiffuseShading(const Vector3& normal, const Vector3& to_light, const Intensity& intensity, const Material* const mat) {
  // Clamp to nonnegative to prevent negative lighting
  float cosine = std::max(0.0f, Dot(normal, to_light));
  Color col = mat->ColorDiffuse() * intensity;
  return col * cosine;
}

Color ComputeSpecularShadingPhong(const Vector3& dir, const Vector3& light_reflected, const Intensity& intensity, const Material* const mat) {
  float cosine = std::max(0.0f, Dot((-1 * dir), light_reflected));
  Color col = mat->ColorSpecular() * intensity;
  return col * powf(cosine, mat->PhongPower());
}

Color ComputeSpecularShadingBlinnPhong(const Vector3& dir, const Vector3& normal, const Vector3& to_light, const Intensity& intensity, const Material* const mat) {
  // Normalized bisector of dir and to_light
  Vector3 halfway = ((-1 * dir) + to_light).Normalized();
  float cosine = std::max(0.0f, Dot(normal, halfway));
  Color col = mat->ColorSpecular() * intensity;
  return col * powf(cosine, mat->PhongPower());
}
