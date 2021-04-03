#include "spatial/BVHNode.h"

#include <vector>

#include "geom/Sphere.h"
#include "geom/Triangle.h"
#include "geom/Primitive.h"
#include "spatial/XYZBounds.h"
#include "spatial/BVHLeafNode.h"
#include "spatial/BVHBoundingNode.h"
#include "logging/Log.h"

// Compute bounds and sort primitives by minimum x value, then
// call ConstructBVH(primitives, bounds) to create the BVH
BVHNode* ConstructBVH(std::vector<Sphere*> spheres, std::vector<Triangle*> triangles) {
  Log::Debug("constructing BVH - preprocessing step");
  std::vector<XYZBounds> sphere_bounds;
  std::vector<XYZBounds> triangle_bounds;

  for (Sphere* sphere : spheres) {
    sphere_bounds.push_back(XYZBounds::GetBounds(sphere));
  }

  for (Triangle* triangle : triangles) {
    triangle_bounds.push_back(XYZBounds::GetBounds(triangle));
  }

  // Sort the spheres and triangles by bounds.MinX(), then merge into one list of primitives
  // Maintain bounds for each primitive in a second parallel list
  // Then call ConstructBVH(primitives, bounds)

  // Sort spheres
  // Good spot for a better algorithm if constructing BVHs takes a long time
  size_t num_spheres = spheres.size();
  size_t min_index = 0;
  float min_value = 1000;
   
  Log::Debug("sorting spheres for BVH");
  for (size_t i = 0; i < num_spheres; i++) {
    min_index = i;
    min_value = sphere_bounds.at(i).XMin();
    for (size_t j = i; j < num_spheres; j++) {
      if (sphere_bounds.at(j).XMin() < min_value) {
        min_index = j;
        min_value = sphere_bounds.at(j).XMin();
      }
    }

    XYZBounds bounds_tmp = sphere_bounds.at(i);
    Sphere* sphere_tmp = spheres.at(i);

    sphere_bounds.at(i) = sphere_bounds.at(min_index);
    spheres.at(i) = spheres.at(min_index);

    sphere_bounds.at(min_index) = bounds_tmp;
    spheres.at(min_index) = sphere_tmp;
  }

  // Now sort triangles
  // Probably even worse than spheres...
  size_t num_triangles = triangles.size();
  min_index = 0;
  min_value = 1000;

  Log::Debug("sorting triangles for BVH");
  for (size_t i = 0; i < num_triangles; i++) {
    min_index = i;
    min_value = triangle_bounds.at(i).XMin();
    for (size_t j = i; j < num_triangles; j++) {
      if (triangle_bounds.at(j).XMin() < min_value) {
        min_index = j;
        min_value = triangle_bounds.at(j).XMin();
      }
    }

    XYZBounds bounds_tmp = triangle_bounds.at(i);
    Triangle* triangle_tmp = triangles.at(i);

    triangle_bounds.at(i) = triangle_bounds.at(min_index);
    triangles.at(i) = triangles.at(min_index);

    triangle_bounds.at(min_index) = bounds_tmp;
    triangles.at(min_index) = triangle_tmp;
  }

  // Merge the two lists into one sorted primitives list
  std::vector<Primitive*> sorted_primitives;
  std::vector<XYZBounds> sorted_bounds;

  size_t sphere_index = 0;
  size_t triangle_index = 0;
  while (sphere_index < num_spheres && triangle_index < num_triangles) {
    if (sphere_bounds.at(sphere_index).XMin() < triangle_bounds.at(triangle_index).XMin()) {
      sorted_primitives.push_back(spheres.at(sphere_index));
      sorted_bounds.push_back(sphere_bounds.at(sphere_index));
      sphere_index++;
    }
    else {
      sorted_primitives.push_back(triangles.at(triangle_index));
      sorted_bounds.push_back(triangle_bounds.at(triangle_index));
      triangle_index++;
    }
  }

  // Now clean up any remaining triangles or spheres
  // At most one list has remaining entries, and they are sorted
  while (sphere_index < num_spheres) {
    sorted_primitives.push_back(spheres.at(sphere_index));
    sorted_bounds.push_back(sphere_bounds.at(sphere_index));
    sphere_index++;
  }

  while (triangle_index < num_triangles) {
    sorted_primitives.push_back(triangles.at(triangle_index));
    sorted_bounds.push_back(triangle_bounds.at(triangle_index));
    triangle_index++;
  }

  Log::Debug("preprocessing done -- recursively constructing BVH");
  return ConstructBVH(sorted_primitives, sorted_bounds);
}

BVHNode* ConstructBVH(std::vector<Primitive*> primitives, std::vector<XYZBounds> bounds) {
  // We can assume that primitives are sorted by bounds.MinX()
  size_t num_primitives = primitives.size();
  if (num_primitives == 1) {
    BVHLeafNode* leaf = new BVHLeafNode(primitives.at(0));
    return leaf;
  }

  std::vector<Primitive*> left_primitives;
  std::vector<XYZBounds> left_bounds;
  std::vector<Primitive*> right_primitives;
  std::vector<XYZBounds> right_bounds;

  for (size_t i = 0; i < num_primitives / 2; i++) {
    left_primitives.push_back(primitives.at(i));
    left_bounds.push_back(bounds.at(i));
  }

  for (size_t i = num_primitives / 2; i < num_primitives; i++) {
    right_primitives.push_back(primitives.at(i));
    right_bounds.push_back(bounds.at(i));
  }

  BVHNode* left_child = ConstructBVH(left_primitives, left_bounds);
  BVHNode* right_child = ConstructBVH(right_primitives, right_bounds);

  float xmin = bounds.at(0).XMin();
  float xmax = bounds.at(0).XMax();
  float ymin = bounds.at(0).YMin();
  float ymax = bounds.at(0).YMax();
  float zmin = bounds.at(0).ZMin();
  float zmax = bounds.at(0).ZMax();

  for (size_t i = 0; i < num_primitives; i++) {
    XYZBounds bound = bounds.at(i);

    if (bound.XMin() < xmin) xmin = bound.XMin();
    if (bound.XMax() > xmax) xmax = bound.XMax();
    if (bound.YMin() < ymin) ymin = bound.YMin();
    if (bound.YMax() > ymax) ymax = bound.YMax();
    if (bound.ZMin() < zmin) zmin = bound.ZMin();
    if (bound.ZMax() > zmax) zmax = bound.ZMax();
  }

  Point3 min_corner = Point3(xmin, ymin, zmin);
  Point3 max_corner = Point3(xmax, ymax, zmax);

  return new BVHBoundingNode(left_child, right_child, min_corner, max_corner);
}
