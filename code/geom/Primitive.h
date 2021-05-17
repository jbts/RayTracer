#ifndef GEOM_PRIMITIVE_H_
#define GEOM_PRIMITIVE_H_

#include "geom/HitInfo.h"
#include "geom/Ray.h"

/// Interface for 3D geometric primitives
class Primitive {
  private:
    static unsigned long curr_id_;
    unsigned long id_;

  public:
    Primitive();

    /// Find the first intersection of the given ray with this primitive
    /// A pure virtual function that must be implemented by children
    virtual HitInfo FindIntersection(const Ray& ray) const = 0;

    /// Get the id of this primitive
    /// Each primitive has a unique id
    unsigned long ID() const { return id_; }
};

#endif
