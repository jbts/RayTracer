#ifndef LIGHT_INTENSITY_H_
#define LIGHT_INTENSITY_H_

#include "core/Color.h"

/// Intensity of a light, with red, green, and blue components
/// Different from a color in that the components aren't clamped to any particular values
/// So a really bright light might have components (50, 50, 50), for example
class Intensity {
  private:
    float r_;
    float g_;
    float b_;
  
  public:
    Intensity() : r_(0), g_(0), b_(0) {}
    Intensity(float r, float g, float b) : r_(r), g_(g), b_(b) {}

    float R() const { return r_; }
    float G() const { return g_; }
    float B() const { return b_; }
};

/// Multiply a color by an intensity in a component-wise fashion
/// The result is a color
/// Useful for lighting computations
Color operator*(const Intensity& i, const Color& c);

/// Multiply a color by an intensity in a component-wise fashion
/// The result is a color
/// Useful for lighting computations
Color operator*(const Color& c, const Intensity& i);

/// Multiply an intensity by a scalar in a component-wise fashion
/// Useful for lighting computations
Intensity operator*(const Intensity& i, float s);

/// Multiply an intensity by a scalar in a component-wise fashion
/// Useful for lighting computations
Intensity operator*(float s, const Intensity& i);

#endif
