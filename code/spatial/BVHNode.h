#ifndef SPATIAL_BVHNODE_H_
#define SPATIAL_BVHNODE_H_

#include <vector>

#include "geom/HitInfo.h"
#include "geom/Ray.h"
#include "geom/Primitive.h"
#include "spatial/XYZBounds.h"

/// An abstract parent class representing nodes in a BVH tree
class BVHNode {
  public:
    /// Find the closest intersection of the ray with a primitive in this node,
    /// or find that there is no such intersection
    ///
    /// Pure virtual function that must be implemented by children
    virtual HitInfo FindClosestIntersection(const Ray& ray) const = 0;
};

/// Construct a BVH containing all of the primitives in the given list
/// The list of primitives *must not* be empty
///
/// Preprocess the list of primitives, then call the recursive
/// ConstructBVH(primitives, bounds) to finish construction
BVHNode* ConstructBVH(std::vector<Primitive*> primitives);

/// Recursive helper function for ConstructBVH(primitives)
/// To construct a BVH, call ConstructBVH(primitives) instead of this function
BVHNode* ConstructBVH(std::vector<Primitive*> primitives, std::vector<XYZBounds> bounds);
#endif
