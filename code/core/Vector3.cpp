#include "core/Vector3.h"

#include <cmath>
#include <string>

float Vector3::Mag() const {
  return sqrt(x_*x_ + y_*y_ + z_*z_);
}

float Vector3::MagSqr() const {
  return x_*x_ + y_*y_ + z_*z_;
}

Vector3 Vector3::Normalized() const {
  float mag = Mag();
  return Vector3(x_/mag, y_/mag, z_/mag);
}

float Dot(Vector3 v, Vector3 w) {
  return v.X()*w.X() + v.Y()*w.Y() + v.Z()*w.Z();
}

// Copied over from Dr. Guy's hw3 implementation
Vector3 Cross(Vector3 v, Vector3 w) {
  return Vector3(v.Y()*w.Z() - v.Z()*w.Y(),
                 v.Z()*w.X() - v.X()*w.Z(),
                 v.X()*w.Y() - v.Y()*w.X());
}

Vector3 operator*(float s, Vector3 v) {
  return Vector3(s*v.X(), s*v.Y(), s*v.Z());
}

Vector3 operator*(Vector3 v, float s) {
  return Vector3(v.X()*s, v.Y()*s, v.Z()*s);
}

Vector3 operator+(Vector3 v, Vector3 w) {
  return Vector3(v.X() + w.X(), v.Y() + w.Y(), v.Z() + w.Z());
}

Vector3 operator-(Vector3 v, Vector3 w) {
  return Vector3(v.X() - w.X(), v.Y() - w.Y(), v.Z() - w.Z());
}

std::string ToString(Vector3 v) {
  return "[" + std::to_string(v.X()) + ", " + std::to_string(v.Y()) + ", " + std::to_string(v.Z()) + "]";
}