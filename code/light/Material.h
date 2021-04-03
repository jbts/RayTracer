#ifndef LIGHT_MATERIAL_H_
#define LIGHT_MATERIAL_H_

#include "core/Color.h"

/// Models a material that interacts with lighting
class Material {
  private:
    Color color_amb_;
    Color color_diff_;
    Color color_spec_;
    float n_phong_;
    Color color_trans_;
    float ior_;
  
  public:
    Material();
    Material(Color color_ambient, Color color_diffuse, Color color_specular,
             float phong_power, Color color_transmissive, float index_of_refraction);
    
    Color ColorAmbient() const { return color_amb_; }
    Color ColorDiffuse() const { return color_diff_; }
    Color ColorSpecular() const { return color_spec_; }
    float PhongPower() const { return n_phong_; }
    Color ColorTransmissive() const { return color_trans_; }
    /// Get the index of refraction of the material
    float IOR() const { return ior_; }
};

#endif