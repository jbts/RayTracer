#ifndef CORE_VECTOR3_H_
#define CORE_VECTOR3_H_

#include <string>

/// A 3D vector
class Vector3 {
  private:
    float x_;
    float y_;
    float z_;

  public:
    Vector3() : x_(0), y_(0), z_(0) {}
    Vector3(float x, float y, float z) : x_(x), y_(y), z_(z) {}
    float X() const { return x_; }
    float Y() const { return y_; }
    float Z() const { return z_; }

    /// Get the vector's magnitude
    float Mag() const;
    /// Get the vector's magnitude squared
    float MagSqr() const;
    /// Get a normalized version of the vector
    Vector3 Normalized() const;
};

/// Compute the dot product of two vectors
float Dot(const Vector3& v, const Vector3& w);

/// Compute the cross product of two vectors
Vector3 Cross(const Vector3& v, const Vector3& w);

/// Multiply a float and a vector
Vector3 operator*(float s, const Vector3& v);
/// Multiply a vector and a float
Vector3 operator*(const Vector3& v, float s);

/// Add two vectors
Vector3 operator+(const Vector3& v, const Vector3& w);
/// Subtract two vectors
Vector3 operator-(const Vector3& v, const Vector3& w);

/// Converts a vector to a string describing the vector
/// Useful for output and debugging
std::string ToString(const Vector3& v);

#endif
