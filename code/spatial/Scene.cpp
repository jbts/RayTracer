#include "spatial/Scene.h"

#include <vector>

#include "core/Color.h"
#include "geom/Triangle.h"
#include "geom/Sphere.h"
#include "geom/HitInfo.h"
#include "geom/Ray.h"

Scene::Scene(const Color& background_color, const std::vector<Sphere*>& spheres, const std::vector<Triangle*>& triangles) {
  background_color_ = background_color;
  for (Sphere* sphere : spheres) {
    primitives_.push_back(sphere);
  }
  for (Triangle* triangle : triangles) {
    primitives_.push_back(triangle);
  }

  bvh_root = ConstructBVH(spheres, triangles);
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

HitInfo Scene::FindClosestIntersection(const Ray& ray, const std::vector<unsigned long>& exclude_ids) {
  HitInfo stored_hit_info = HitInfo::NoHit();

  for (Primitive* primitive : primitives_) {
    HitInfo hit_info = primitive->FindIntersection(ray);

    for (unsigned long id : exclude_ids) {
      // Ignore this primitive
      if (id == hit_info.PrimitiveID()) {
        continue;
      }
    }

    if (hit_info.DidIntersect() && (!stored_hit_info.DidIntersect() || hit_info.Time() < stored_hit_info.Time())) {
      stored_hit_info = hit_info;
    }
  }

  return stored_hit_info;
}
