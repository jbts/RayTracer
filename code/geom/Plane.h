#ifndef GEOM_PLANE_H_
#define GEOM_PLANE_H_

#include "core/Point3.h"
#include "core/Vector3.h"
#include "geom/HitInfo.h"
#include "geom/Ray.h"
#include "light/Material.h"

/// A plane in 3D, defined by a normal and a point lying on the plane
/// A plane is not a Primitive because it's not bounded
class Plane {
  private:
    // A point on the plane
    Point3 p_;
    Vector3 normal_;
    const Material* m_;
  
    // How far a point can be from the plane and still be considered "contained" in it
    float contains_tolerance_ = 0.0001f;

  public:
    Plane() : p_(0, 0, 0), normal_(0, 1, 0), m_(Material::BaseMat()) {}
    Plane(const Point3& p, const Vector3& normal, const Material* const m);

    HitInfo FindIntersection(const Ray& ray) const;

    /// Check whether the plane contains the given point
    bool Contains(const Point3& p) const;
};

#endif
