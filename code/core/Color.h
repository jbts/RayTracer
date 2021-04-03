#ifndef CORE_COLOR_H_
#define CORE_COLOR_H_

#include <string>

/// An RGB color with components in the range [0,1]
class Color {
  private:
    float r_;
    float g_;
    float b_;

  public:
    Color() : r_(0), g_(0), b_(0) {}
    Color(float r, float g, float b);
    float R() const { return r_; }
    float G() const { return g_; }
    float B() const { return b_; }
};

/// Clamp a color component to the range [0,1]
float ColorCompClamp(float comp);

/// Linearly interpolate between two colors
Color ColorLerp(Color start, Color target, float t);

/// Add two colors in a component-wise fashion
/// Useful for lighting calculations
Color operator+(Color c, Color d);

/// Multiply a color by a scalar in a component-wise fashion
/// Useful for lighting calculations
Color operator*(Color c, float s);

/// Multiply a color by a scalar in a component-wise fashion
/// Useful for lighting calculations
Color operator*(float s, Color c);

/// Convert a color to a string describing the color
/// Useful for output and debugging
std::string ToString(Color c);

#endif
