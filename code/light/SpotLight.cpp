#include "light/SpotLight.h"

#include <vector>
#include <cmath>

#include "core/Point3.h"
#include "core/Vector3.h"
#include "core/Color.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "spatial/Scene.h"
#include "light/Shading.h"

Color SpotLight::ComputeLighting(const Ray& ray, const HitInfo& hit_info, const Scene& scene, int depth_left) const {
  Point3 intersection_point = ray.AtTime(hit_info.Time());
  // Note: _not_ normalized
  Vector3 to_light = Pos() - intersection_point;
  Vector3 to_light_unit = to_light.Normalized();
  Vector3 normal = hit_info.Normal().Normalized();
  Vector3 dir = ray.Dir().Normalized();
  
  float angle = fabs(acos(Dot(dir_.Normalized(), -1 * to_light_unit)));
  Intensity i_at_point = IntensityAt(to_light.Mag(), angle);

  Material mat = hit_info.GetMaterial();

  // Should this intersection be in shadow?
  Ray shadow_ray = Ray(intersection_point + 0.0001 * normal, to_light_unit);
  HitInfo shadow_hit_info = scene.FindClosestIntersection(shadow_ray);
  bool in_shadow = shadow_hit_info.DidIntersect() && shadow_hit_info.Time() < to_light.Mag();
  
  Color reflect_color = Color(0, 0, 0);
  if (depth_left > 0) {
    Vector3 light_reflected = (dir - 2 * (Dot(dir, normal)) * normal).Normalized();
    Ray reflect_ray = Ray(intersection_point + 0.0001 * normal, light_reflected);
    HitInfo reflect_hit_info = scene.FindClosestIntersection(reflect_ray);

    if (reflect_hit_info.DidIntersect()) {
      reflect_color = ComputeLighting(reflect_ray, reflect_hit_info, scene, depth_left - 1);
    }
    else { // must have hit the background
      reflect_color = scene.BackgroundColor();
    }
  }

  Color reflect_color_adjusted = reflect_color * mat.ColorSpecular();
  Color c = Color(0, 0, 0);

  if (!in_shadow) {
    c = c + ComputeDiffuseShading(normal, to_light_unit, i_at_point, mat);
    c = c + ComputeSpecularShadingBlinnPhong(dir, normal, to_light_unit, i_at_point, mat);
  }
  c = c + reflect_color_adjusted;

  return c;
}

/// Helper function for SpotLight::IntensityAt()
/// Computes the falloff of the light's intensity due to the angle
/// max is the maximum angle of the light, where the intensity becomes 0
/// width is the maximum angle of the light minus its minimum
/// value is the angle to the point of intersection
/// f is a function that takes in the normalized value and computes the falloff
static float Falloff(float max, float width, float value, float (*f)(float)) {
  return f((max - value) / width);
}

Intensity SpotLight::IntensityAt(float dist, float angle) const {
  float mod_dist = 1.0f / (dist * dist);
  float mod_angle = 0.0f;
  if (angle < start_fall_angle_) {
    mod_angle = 1.0f;
  }
  else if (angle < end_fall_angle_) {
    // Could precompute the difference of the two angles since it's an attribute of the light
    mod_angle = Falloff(end_fall_angle_, end_fall_angle_ - start_fall_angle_, angle, sqrtf);
  }
  return i_ * mod_dist * mod_angle;
}
