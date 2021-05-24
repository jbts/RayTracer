#include "geom/HitInfo.h"

#include "core/Vector3.h"
#include "light/Material.h"

HitInfo::HitInfo() {
  did_intersect_ = false;
  time_ = -1;
  normal_ = Vector3(0, 1, 0);
  material_ = Material::BaseMat();
  primitive_id_ = -1;
}

HitInfo::HitInfo(bool did_intersect, float time, const Vector3& normal, const Material* const material, unsigned long primitive_id) {
    did_intersect_ = did_intersect;
    time_ = time;
    normal_ = normal;
    material_ = material;
    primitive_id_ = primitive_id;
}

HitInfo HitInfo::NoHit() {
  return HitInfo(false, -1, Vector3(0, 1, 0), Material::BaseMat(), 0);
}
