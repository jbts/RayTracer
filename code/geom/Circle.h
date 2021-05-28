#ifndef GEOM_CIRCLE_H_
#define GEOM_CIRCLE_H_

#include "geom/Primitive.h"
#include "geom/Plane.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "core/Point3.h"
#include "core/Vector3.h"
#include "light/Material.h"
#include "spatial/XYZBounds.h"

/// A 2D circle
/// Can think of it as a circle cut out of a plane
class Circle : public Primitive {
  private:
    Point3 center_;
    float r_;
    // Tells us the orientation of the 2D circle
    Vector3 normal_;
    const Material* m_;
    Plane plane_containing_;

  public:
    Circle(const Point3& center, float r, const Vector3& normal, const Material* const m);

    HitInfo FindIntersection(const Ray& ray) const override;
    XYZBounds FindBounds() const override;

    Point3 Center() const { return center_; }
    float Radius() const { return r_; }
    Vector3 Normal() const { return normal_; }
    const Material* GetMaterial() const { return m_; }
};

#endif
