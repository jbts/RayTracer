#ifndef CORE_COLOR_H_
#define CORE_COLOR_H_

#include <string>

/// An RGB color with components in the range [0,max_float_value)
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

    /// Compute the luminance of this Color as 0.3r + 0.6g + 0.1b
    float Lum() const;
};

/// Clamp a color component to the range [0,1]
float ColorCompClamp(float comp);

/// Linearly interpolate between two colors
Color ColorLerp(const Color& start, const Color& target, float t);

/// Add two colors in a component-wise fashion
Color operator+(const Color& c, const Color& d);

/// Multiply two colors in a component-wise fashion
Color operator*(const Color& c, const Color& d);

/// Multiply a color by a scalar in a component-wise fashion
Color operator*(const Color& c, float s);

/// Multiply a color by a scalar in a component-wise fashion
Color operator*(float s, const Color& c);

/// Convert a color to a string describing the color
/// Useful for output and debugging
std::string ToString(const Color& c);

#endif
