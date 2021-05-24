#include "light/PointLight.h"

#include <vector>

#include "core/Color.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "geom/Primitive.h"
#include "light/Shading.h"
#include "spatial/Scene.h"

Color PointLight::ComputeLighting(const Ray& ray, const HitInfo& hit_info, const Scene& scene, int depth_left) const {
  Point3 intersection_point = ray.AtTime(hit_info.Time());
  // Note: _not_ normalized
  Vector3 to_light = Pos() - intersection_point;
  Vector3 to_light_unit = to_light.Normalized();
  Vector3 normal = hit_info.Normal().Normalized();
  Vector3 dir = ray.Dir().Normalized();
  Intensity i_at_point = IntensityAtDistance(to_light.Mag());
  const Material* mat = hit_info.GetMaterial();

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

  Color reflect_color_adjusted = reflect_color * mat->ColorSpecular();

  Color c = Color(0, 0, 0);
  
  if (!in_shadow) {
    c = c + ComputeDiffuseShading(normal, to_light_unit, i_at_point, mat);
    c = c + ComputeSpecularShadingBlinnPhong(dir, normal, to_light_unit, i_at_point, mat);
  }
  c = c + reflect_color_adjusted;

  return c;
}

Intensity PointLight::IntensityAtDistance(float dist) const {
  // At the exact position of the point light, this explodes to infinity
  // Hopefully this won't be an issue; we'll see
  return i_ * (1.0f / (dist * dist));
}
