#include "spatial/Scene.h"

#include <vector>

#include "core/Color.h"
#include "geom/HitInfo.h"
#include "geom/Ray.h"
#include "spatial/BVHNode.h"

Scene::Scene(const Color& background_color, const std::vector<Primitive*>& primitives) {
  background_color_ = background_color;
  primitives_ = primitives;

  bvh_root_ = BVHNode::ConstructBVH(primitives);
}

HitInfo Scene::FindClosestIntersection(const Ray& ray) const {
  return bvh_root_->FindClosestIntersection(ray);
}

