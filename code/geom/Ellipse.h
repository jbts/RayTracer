#ifndef GEOM_ELLIPSE_H_
#define GEOM_ELLIPSE_H_

#include "geom/Primitive.h"
#include "geom/Ray.h"
#include "geom/Plane.h"
#include "geom/HitInfo.h"
#include "core/Point3.h"
#include "core/Vector3.h"
#include "light/Material.h"
#include "spatial/XYZBounds.h"

class Ellipse : public Primitive {
  private:
    Point3 focus1_;
    Point3 focus2_;
    float d_;
    Vector3 normal_;
    const Material* m_;
    Plane plane_containing_;

  public:
    Ellipse(const Point3& focus1, const Point3& focus2, float d, const Vector3& normal, const Material* const m);

    HitInfo FindIntersection(const Ray& ray) const override;
    XYZBounds FindBounds() const override;
};

#endif
