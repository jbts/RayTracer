#ifndef SPATIAL_XYZBOUNDS_H_
#define SPATIAL_XYZBOUNDS_H_

#include "geom/Sphere.h"
#include "geom/Triangle.h"

/// Represents bounds in x, y, and z for a sphere or triangle
/// They don't need to be exact, the primitive just needs to be completely
/// contained inside the bounds
/// Used for constructing a BVH
class XYZBounds {
  private:
    float x_min_;
    float x_max_;
    float y_min_;
    float y_max_;
    float z_min_;
    float z_max_;
  
  public:
    XYZBounds(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max) : x_min_(x_min), x_max_(x_max), y_min_(y_min), y_max_(y_max), z_min_(z_min), z_max_(z_max) {}

    float XMin() const { return x_min_; }
    float XMax() const { return x_max_; }
    float YMin() const { return y_min_; }
    float YMax() const { return y_max_; }
    float ZMin() const { return z_min_; }
    float ZMax() const { return z_max_; }

    /// Get bounds for a sphere
    /// The bounds returned are very close to exact
    static XYZBounds GetBounds(Sphere* sphere);

    /// Get bounds for a triangle
    /// The bounds returned are very close to exact
    static XYZBounds GetBounds(Triangle* triangle);
};

#endif