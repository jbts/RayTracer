#include "light/Material.h"
#include "core/Color.h"

Material::Material() {
    color_amb_ = Color(0, 0, 0);
    color_diff_ = Color(1, 1, 1);
    color_spec_ = Color(0, 0, 0);
    n_phong_ = 5;
    color_trans_ = Color(0, 0, 0);
    ior_ = 1;
}

Material::Material(Color color_ambient, Color color_diffuse, Color color_specular,
                   float phong_power, Color color_transmissive, float index_of_refraction) {
  color_amb_ = color_ambient;
  color_diff_ = color_diffuse;
  color_spec_ = color_specular;
  n_phong_ = phong_power;
  color_trans_ = color_transmissive;
  ior_ = index_of_refraction;
}