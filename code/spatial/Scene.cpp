#include "spatial/Scene.h"

#include <vector>

#include "core/Color.h"
#include "geom/HitInfo.h"
#include "geom/Ray.h"

Scene::Scene(const Color& background_color, const std::vector<Primitive*>& primitives) {
  background_color_ = background_color;
  primitives_ = primitives;

  bvh_root = ConstructBVH(primitives);
}

/*
HitInfo Scene::FindClosestIntersection(Ray ray) const {
  HitInfo stored_hit_info = HitInfo::NoHit();

  // Prime spot for a more efficient algorithm!
  // Try a BVH
  for (Primitive* primitive : primitives_) {
    HitInfo hit_info = primitive->FindIntersection(ray);

    // If this intersection is either the first found or at a smaller
    // time than the stored intersection, then update the stored hit info
    if (hit_info.DidIntersect() && (!stored_hit_info.DidIntersect() || hit_info.Time() < stored_hit_info.Time())) {
      stored_hit_info = hit_info;
    }
  }

  return stored_hit_info;
}
*/

HitInfo Scene::FindClosestIntersection(const Ray& ray) const {
  return bvh_root->FindClosestIntersection(ray);
}

