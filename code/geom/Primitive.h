#ifndef GEOM_PRIMITIVE_H_
#define GEOM_PRIMITIVE_H_

#include "geom/HitInfo.h"
#include "geom/Ray.h"
#include "spatial/XYZBounds.h"

/// Interface for 3D geometric primitives
/// Primitives must be bounded, so something like a plane or true cone
/// is not a primitive. Triangles, spheres, cubes, circles, and the like
/// are good examples of primitives.
class Primitive {
  public:
    /// Find the first intersection of the given ray with this primitive
    /// A pure virtual function that must be implemented by children
    virtual HitInfo FindIntersection(const Ray& ray) const = 0;

    /// Find bounds for this primitive. They don't need to be exact, but
    /// they should be as close to exact as possible, and the primitive
    /// must be completely contained within the bounds.
    /// Pure virtual function that must be implemented by children
    virtual XYZBounds FindBounds() const = 0;
};

#endif
