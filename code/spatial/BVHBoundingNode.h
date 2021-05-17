#ifndef SPATIAL_BVHBOUNDINGNODE_H_
#define SPATIAL_BVHBOUNDINGNODE_H_

#include "spatial/BVHNode.h"
#include "geom/HitInfo.h"
#include "geom/Ray.h"

class BVHBoundingNode : public BVHNode {
  private:
    BVHNode* left_child_;
    BVHNode* right_child_;

    /// These corners represent the bounding box, which
    /// is axis-aligned
    Point3 min_corner_;
    Point3 max_corner_;
  public:
    BVHBoundingNode(BVHNode* left_child, BVHNode* right_child, const Point3& min_corner, const Point3& max_corner) : left_child_(left_child), right_child_(right_child), min_corner_(min_corner), max_corner_(max_corner) {}

    /// Check whether the given ray intersects this node's bounding box
    /// Uses the "slab method", which is an efficient method for checking
    /// ray-box intersections for axis-aligned boxes
    ///
    /// I learned about this method from these three webpages/papers:
    /// https://tavianator.com/2011/ray_box.html
    /// 
    /// www.jcgt.org/published/0007/03/04/paper_lowres.pdf
    ///
    /// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
    ///
    /// I've rephrased the algorithm "in my own words"
    bool RayIntersectsBounds(const Ray& ray) const;
    HitInfo FindClosestIntersection(const Ray& ray) const override;
};

#endif
