#include "light/DirectionalLight.h"

#include <vector>

#include "core/Color.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "geom/Primitive.h"
#include "light/Shading.h"
#include "spatial/Scene.h"

Color DirectionalLight::ComputeLighting(const Ray& ray, const HitInfo& hit_info, const Scene& scene, int depth_left) const {
  Vector3 normal = hit_info.Normal().Normalized();
  // to_light is the same at every point in space for a directional light
  Vector3 to_light = (-1 * dir_).Normalized();
  Material mat = hit_info.GetMaterial();
  Point3 intersection_point = ray.AtTime(hit_info.Time());
  Vector3 dir = ray.Dir();

  // Should this intersection be in shadow?
  Ray shadow_ray = Ray(intersection_point + 0.001 * normal, to_light);

  HitInfo shadow_hit_info = scene.FindClosestIntersection(shadow_ray);
  bool in_shadow = shadow_hit_info.DidIntersect();

  Color reflect_color = Color(0, 0, 0);
  if (depth_left > 0) {
    Vector3 light_reflected = (dir - 2 * Dot(dir, normal) * normal).Normalized();
    Ray reflect_ray = Ray(intersection_point + 0.001 * normal, light_reflected);
    HitInfo reflect_hit_info = scene.FindClosestIntersection(reflect_ray);

    if (reflect_hit_info.DidIntersect()) {
      reflect_color = ComputeLighting(reflect_ray, reflect_hit_info, scene, depth_left - 1);
    }
    else {
      reflect_color = scene.BackgroundColor();
    }
  }

  Color mat_spec = mat.ColorSpecular();
  Color reflect_color_adjusted = Color(mat_spec.R() * reflect_color.R(), mat_spec.G() * reflect_color.G(), mat_spec.B() * reflect_color.B());
  
  Color c = Color(0, 0, 0);
  
  if (!in_shadow) {
    c = c + ComputeDiffuseShading(normal, to_light, i_, mat);
    c = c + ComputeSpecularShadingBlinnPhong(ray.Dir(), normal, to_light, i_, mat);
  }
  c = c + reflect_color_adjusted;
  
  return c;
}
