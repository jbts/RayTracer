#ifndef GEOM_NORMALTRIANGLE_H_
#define GEOM_NORMALTRIANGLE_H_

#include <vector>

#include "core/Vector3.h"
#include "geom/Triangle.h"
#include "geom/Ray.h"
#include "geom/HitInfo.h"
#include "light/Material.h"

/// A triangle in 3D, with normals specified at each vertex
class NormalTriangle : public Triangle {
  private:
    // Normals, as indices into the normals list
    int n1_index_;
    int n2_index_;
    int n3_index_;

    static std::vector<Vector3> normals_;
  
  public:
    NormalTriangle(int v1_index, int v2_index, int v3_index, int n1_index, int n2_index, int n3_index, const Material* const m);
    
    /// Add a normal to the end of the normal list
    static void AddNormal(const Vector3& normal);

    /// Get the normal corresponding to Vertex1()
    Vector3 Normal1() const;

    /// Get the normal corresponding to Vertex2()
    Vector3 Normal2() const;

    /// Get the normal corresponding to Vertex3()
    Vector3 Normal3() const;

    HitInfo FindIntersection(const Ray& ray) const override;
};

#endif
