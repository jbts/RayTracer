#ifndef GEOM_SPHERE_H_
#define GEOM_SPHERE_H_

#include "geom/Primitive.h"
#include "geom/Ray.h"
#include "core/Point3.h"
#include "light/Material.h"

/// A 3D sphere
class Sphere : public Primitive {
  private:
    Point3 pos_;
    float r_;
    Material m_;

  public:
    Sphere();
    Sphere(const Point3& pos, float r, const Material& m);

    Point3 Pos() const { return pos_; }
    float Radius() const { return r_; }
    Material GetMaterial() const { return m_; }

    HitInfo FindIntersection(const Ray& ray) const override;
};

#endif
