#ifndef GEOM_PLANE_H_
#define GEOM_PLANE_H_

#include "core/Point3.h"
#include "core/Vector3.h"
#include "geom/Primitive.h"
#include "geom/HitInfo.h"
#include "geom/Ray.h"
#include "geom/Triangle.h"
#include "light/Material.h"

/// A plane in 3D, defined by a normal and a point lying on the plane
class Plane : public Primitive {
  private:
    // A point on the plane
    Point3 p_;
    Vector3 normal_;
    Material m_;
  
    // How far a point can be from the plane and still be considered "contained" in it
    float contains_tolerance_ = 0.00001f;

  public:
    Plane() : p_(0, 0, 0), normal_(0, 1, 0), m_() {}
    Plane(Point3 p, Vector3 normal, Material m);

    HitInfo FindIntersection(Ray ray) const override;

    /// Check whether the plane contains the given point
    bool Contains(Point3 p) const;
};

/// Get the plane containing all three points of the given triangle
Plane PlaneContaining(Triangle tri);

#endif
