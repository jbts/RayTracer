#ifndef SPATIAL_BVHLEAFNODE_H_
#define SPATIAL_BVHLEAFNODE_H_

#include "spatial/BVHNode.h"
#include "geom/Primitive.h"
#include "geom/HitInfo.h"
#include "geom/Ray.h"

/// Represents a leaf or terminal node in a BVH tree, holding exactly one primitive
class BVHLeafNode : public BVHNode {
  private:
    Primitive* primitive_;

  public:
    BVHLeafNode(Primitive* primitive) : primitive_(primitive) {}

    /// Find the closest intersection within this BVHNode
    /// Since this node holds exactly one primitive, this is the same
    /// as finding the intersection with the primitive
    HitInfo FindClosestIntersection(const Ray& ray) const override;
};

#endif
