#ifndef SPATIAL_SCENE_H_
#define SPATIAL_SCENE_H_

#include <vector>

#include "core/Color.h"
#include "geom/Triangle.h"
#include "geom/Sphere.h"
#include "geom/HitInfo.h"
#include "geom/Ray.h"
#include "spatial/BVHNode.h"

/// Organizes a scene in space
/// Provides an interface to intersection code and spatial data structures
class Scene {
  private:
    Color background_color_;
    std::vector<Primitive*> primitives_;
    BVHNode* bvh_root;
    
  public:
    Scene(const Color& background_color, const std::vector<Sphere*>& spheres, const std::vector<Triangle*>& triangles);
    Color BackgroundColor() const { return background_color_; }
    
    /// Find the first intersection between the ray and the group of primitives in the scene
    /// The first intersection is the one with smallest "time" / ray parameter
    /// Returns a HitInfo object with information about the point of collision (and whether it exists)
    HitInfo FindClosestIntersection(const Ray& ray) const;
};

#endif
