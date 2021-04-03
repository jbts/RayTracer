#include "core/Color.h"

#include <string>

Color::Color(float r, float g, float b) {
  r_ = ColorCompClamp(r);
  g_ = ColorCompClamp(g);
  b_ = ColorCompClamp(b);
}

float ColorCompClamp(float comp) {
  if (comp < 0) return 0;
  if (comp > 1) return 1;
  return comp;
}

Color ColorLerp(Color start, Color target, float t) {
  float new_r = start.R() * (1 - t) + target.R() * t;
  float new_g = start.G() * (1 - t) + target.G() * t;
  float new_b = start.B() * (1 - t) + target.B() * t;

  return Color(new_r, new_g, new_b);
}

Color operator+(Color c, Color d) {
  return Color(c.R()+d.R(), c.G()+d.G(), c.B()+d.B());
}

Color operator*(Color c, float s) {
  return Color(c.R()*s, c.G()*s, c.B()*s);
}

Color operator*(float s, Color c) {
  return Color(s*c.R(), s*c.G(), s*c.B());
}

std::string ToString(Color c) {
  return "(" + std::to_string(c.R()) + ", " + std::to_string(c.G()) + ", " + std::to_string(c.B()) + ")";
}