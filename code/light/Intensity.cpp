#include "light/Intensity.h"

Color operator*(Intensity i, Color c) {
  return Color(i.R()*c.R(), i.G()*c.G(), i.B()*c.B());
}

Color operator*(Color c, Intensity i) {
  return Color(c.R()*i.R(), c.G()*i.G(), c.B()*i.B());
}

Intensity operator*(Intensity i, float s) {
  return Intensity(i.R()*s, i.G()*s, i.B()*s);
}

Intensity operator*(float s, Intensity i) {
  return Intensity(s*i.R(), s*i.G(), s*i.B());
}