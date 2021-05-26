#ifndef SPATIAL_BVHNODE_H_
#define SPATIAL_BVHNODE_H_

#include <vector>

#include "geom/HitInfo.h"
#include "geom/Ray.h"
#include "geom/Primitive.h"
#include "spatial/XYZBounds.h"

/// An abstract parent class representing nodes in a
/// BVH tree
class BVHNode {
  public:
    virtual HitInfo FindClosestIntersection(const Ray& ray) const = 0;
};

BVHNode* ConstructBVH(std::vector<Primitive*> primitives);

BVHNode* ConstructBVH(std::vector<Primitive*> primitives, std::vector<XYZBounds> bounds);
#endif
