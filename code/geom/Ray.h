#ifndef GEOM_RAY_H_
#define GEOM_RAY_H_

#include "core/Point3.h"
#include "core/Vector3.h"

/// A 3D ray, sort of like "half a line"
/// Has a starting point and a vector direction
class Ray {
  private:
    Point3 start_;
    // *Unit* vector indicating direction of ray
    Vector3 dir_;
  
  public:
    Ray();
    Ray(const Point3& start, const Vector3& dir);

    Point3 Start() const { return start_; }

    /// Get the *unit* vector indicating the direction of the ray
    Vector3 Dir() const { return dir_; }

    /// Find a point on the ray at time t with the equation start + t * dir,
    /// where dir is a unit vector indicating the direction of the ray
    Point3 AtTime(float t) const;
};

#endif
