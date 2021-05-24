#ifndef GEOM_TRIANGLE_H_
#define GEOM_TRIANGLE_H_

#include <vector>

#include "geom/Primitive.h"
#include "geom/Plane.h"
#include "geom/HitInfo.h"
#include "geom/Ray.h"
#include "light/Material.h"

/// Barycentric coordinates
/// These are an indication of how close a point is to each corner of a triangle
class BaryCoords {
  private:
    float coord1_;
    float coord2_;
    float coord3_;
  
  public:
    BaryCoords(float coord1, float coord2, float coord3) : coord1_(coord1), coord2_(coord2), coord3_(coord3) {}

    float Coord1() const { return coord1_; }
    float Coord2() const { return coord2_; }
    float Coord3() const { return coord3_; }
};

/// A triangle in 3D space
class Triangle : public Primitive {
  private:
    // Vertices, as indices into vertex array
    int v1_index_;
    int v2_index_;
    int v3_index_;

    const Material* m_;

    // How close to 1 a point's barycentric coordinates must be
    // to be considered "contained" in the triangle
    const float contains_tolerance_ = 0.00001f;

    static std::vector<Point3> vertices_;
  
  protected:
    // A plane containing this triangle
    Plane plane_containing_;
    // The area of this triangle
    float area_;

  public:
    Triangle(int v1_index, int v2_index, int v3_index, const Material* const m);

    HitInfo FindIntersection(const Ray& ray) const override;

    /// Add a vertex to the end of the vertex list
    static void AddVertex(const Point3& vertex);

    Point3 Vertex1() const;
    Point3 Vertex2() const;
    Point3 Vertex3() const;

    const Material* GetMaterial() const { return m_; }

    /// Find the area of the triangle
    float Area() const;

    /// Check whether the triangle contains the given point
    bool Contains(const Point3& p) const;

    /// Find the barycentric coordinates of the given point
    /// The returned coordinates line up as you might expect:
    /// Coord1() -> Vertex1(), Coord2() -> Vertex2(), Coord3() -> Vertex3()
    BaryCoords FindBaryCoords(const Point3& p) const;
};

/// Find the area of the triangle spanned by the three given points
float TriangleArea(const Point3& t1, const Point3& t2, const Point3& t3);

/// Get the plane containing all three points of the given triangle
Plane PlaneContaining(const Triangle& tri);

#endif
