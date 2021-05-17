#ifndef CORE_POINT3_H_
#define CORE_POINT3_H_

#include <string>

#include "core/Vector3.h"

/// A 3D point
class Point3 {
  private:
    float x_;
    float y_;
    float z_;

  public:
    Point3() : x_(0), y_(0), z_(0) {}
    Point3(float x, float y, float z) : x_(x), y_(y), z_(z) {}
    float X() const { return x_; }
    float Y() const { return y_; }
    float Z() const { return z_; }
};

/// Find the difference between two points; it's a vector
Vector3 operator-(const Point3& p, const Point3& q);

/// Displace a point by a vector to get a new point
Point3 operator+(const Point3& p, const Vector3& v);

/// Converts a point to a string describing the point
/// Useful for output and debugging
std::string ToString(const Point3& p);

#endif
