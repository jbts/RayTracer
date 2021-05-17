#include "spatial/BVHBoundingNode.h"

#include "geom/HitInfo.h"
#include "geom/Ray.h"

bool BVHBoundingNode::RayIntersectsBounds(const Ray& ray) const {
  Point3 start = ray.Start();
  Vector3 dir = ray.Dir();

  // What about divide by zero here?
  // We can probably factor this out and just do the computation once
  // for the entire tree, since the ray is constant as we move down the tree
  float recip_dir_x = 1 / dir.X();
  float recip_dir_y = 1 / dir.Y();
  float recip_dir_z = 1 / dir.Z();

  // There are 6 planes, one of which is x = min_corner_.X(), which define
  // the bounding box. We can solve for the intersection of the ray with
  // this plane and get t = (min_corner_.X() - start.X()) * recip_dir_x.
  // Do this for each of the 6 planes
  float t1x = (min_corner_.X() - start.X()) * recip_dir_x;
  float t2x = (max_corner_.X() - start.X()) * recip_dir_x;
  float t1y = (min_corner_.Y() - start.Y()) * recip_dir_y;
  float t2y = (max_corner_.Y() - start.Y()) * recip_dir_y;
  float t1z = (min_corner_.Z() - start.Z()) * recip_dir_z;
  float t2z = (max_corner_.Z() - start.Z()) * recip_dir_z;

  // Find the minimum and maximum times in each direction
  float tminx = std::min(t1x, t2x);
  float tmaxx = std::max(t1x, t2x);
  float tminy = std::min(t1y, t2y);
  float tmaxy = std::max(t1y, t2y);
  float tminz = std::min(t1z, t2z);
  float tmaxz = std::max(t1z, t2z);

  // Test that all of the minimum values are less than all of the maximum values
  // If they are, then the ray hits the box. Otherwise, it doesn't
  return std::max(std::max(tminx, tminy), tminz) <= std::min(std::min(tmaxx, tmaxy), tmaxz);
}

HitInfo BVHBoundingNode::FindClosestIntersection(const Ray& ray) const {
  if (!RayIntersectsBounds(ray)) {
    return HitInfo::NoHit();
  }

  // The ray must hit this volume
  // Assuming the node is created correctly and always has 2 non-null children...
  HitInfo left_hit_info = left_child_->FindClosestIntersection(ray);
  HitInfo right_hit_info = right_child_->FindClosestIntersection(ray);

  if (right_hit_info.DidIntersect() && (!left_hit_info.DidIntersect() || right_hit_info.Time() < left_hit_info.Time())) {
    return right_hit_info;
  }
  
  return left_hit_info;
}
