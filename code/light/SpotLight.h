#ifndef LIGHT_SPOTLIGHT_H_
#define LIGHT_SPOTLIGHT_H_

#include <vector>

#include "core/Point3.h"
#include "core/Vector3.h"
#include "light/Intensity.h"
#include "light/Light.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "spatial/Scene.h"

class SpotLight : public Light {
  private:
    Point3 pos_;
    Vector3 dir_;
    Intensity i_;
    // Angle where light intensity starts to fall off
    float start_fall_angle_;
    // Angle where light intensity has fallen off completely
    float end_fall_angle_;
  
  public:
    SpotLight() : pos_(0, 0, 0), dir_(1, 0, 0), i_(0, 0, 0), start_fall_angle_(0), end_fall_angle_(0) {}
    SpotLight(Point3 pos, Vector3 dir, Intensity intensity, float start_fall_angle, float end_fall_angle) :
              pos_(pos), dir_(dir), i_(intensity), start_fall_angle_(start_fall_angle), end_fall_angle_(end_fall_angle) {}

    Point3 Pos() const { return pos_; }
    Vector3 Dir() const { return dir_; }
    Intensity GetIntensity() const { return i_; }
    float StartFallAngle() const { return start_fall_angle_; }
    float EndFallAngle() const { return end_fall_angle_; }

    /// ======= Unimplemented =======
    /// Right now this is a placeholder function always returning black
    Color ComputeLighting(Ray ray, HitInfo hit_info, Scene scene, int depth_left) const override;
};

#endif