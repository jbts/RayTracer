#ifndef GEOM_HITINFO_H_
#define GEOM_HITINFO_H_

#include "core/Vector3.h"
#include "light/Material.h"

/// Holds information about the intersection(s) of a ray and another object
class HitInfo {
  private:
    bool did_intersect_;
    float time_;
    Vector3 normal_;
    const Material* material_;
    unsigned long primitive_id_;

  public:
    HitInfo();
    HitInfo(bool did_intersect, float time, const Vector3& normal, const Material* const material, unsigned long primitive_id);

    /// Whether there was an intersection or not. If this evaluates to false,
    /// then the rest of the data in the HitInfo object aren't meaningful.
    bool DidIntersect() const { return did_intersect_; }

    /// "Time" of intersection in the ray's frame
    /// If there are multiple times of intersection, then this is the smallest
    float Time() const { return time_; }

    /// The normal of the object at the point of intersection
    Vector3 Normal() const { return normal_; }

    /// The material of the object at the point of intersection
    const Material* GetMaterial() const { return material_; }

    /// Return the id of the primitive intersected
    unsigned long PrimitiveID() const { return primitive_id_; }

    /// Creates a HitInfo object indicating that there was no intersection, with
    /// reasonable values. DidIntersect() is guaranteed to return false on the returned
    /// object.
    static HitInfo NoHit();
};

#endif
