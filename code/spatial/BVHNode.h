#ifndef SPATIAL_BVHNODE_H_
#define SPATIAL_BVHNODE_H_

#include "geom/HitInfo.h"
#include "geom/Ray.h"
#include "geom/Sphere.h"
#include "geom/Triangle.h"
#include "geom/Primitive.h"
#include "spatial/XYZBounds.h"

/// An abstract parent class representing nodes in a
/// BVH tree
class BVHNode {
  public:
    virtual HitInfo FindClosestIntersection(Ray ray) const = 0;
};

BVHNode* ConstructBVH(std::vector<Sphere*> spheres, std::vector<Triangle*> triangles);

BVHNode* ConstructBVH(std::vector<Primitive*> primitives, std::vector<XYZBounds> bounds);
#endif
