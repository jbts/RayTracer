#include "spatial/BVHNode.h"

#include <vector>

#include "geom/Primitive.h"
#include "spatial/XYZBounds.h"
#include "spatial/BVHLeafNode.h"
#include "spatial/BVHBoundingNode.h"
#include "logging/Log.h"

// Compute bounds and sort primitives by minimum x value, then
// call ConstructBVH(primitives, bounds) to create the BVH
BVHNode* BVHNode::ConstructBVH(std::vector<Primitive*> primitives) {
  Log::Debug("constructing BVH - preprocessing step");
  std::vector<XYZBounds> bounds;

  for (Primitive* primitive : primitives) {
    bounds.push_back(primitive->FindBounds());
  }

  // Sort the primitives by bounds.MinX()
  // Maintain bounds for each primitive in a second parallel list
  // Then call ConstructBVH(primitives, bounds)

  // Sort primitives using bubblesort
  // Good spot for a better algorithm if constructing BVHs takes a long time
  size_t num_primitives = primitives.size();
  size_t min_index = 0;
  float min_value = 1000;
   
  Log::Debug("sorting primitives for BVH");
  for (size_t i = 0; i < num_primitives; i++) {
    min_index = i;
    min_value = bounds.at(i).XMin();
    for (size_t j = i; j < num_primitives; j++) {
      if (bounds.at(j).XMin() < min_value) {
        min_index = j;
        min_value = bounds.at(j).XMin();
      }
    }

    XYZBounds bounds_tmp = bounds.at(i);
    Primitive* primitive_tmp = primitives.at(i);

    bounds.at(i) = bounds.at(min_index);
    primitives.at(i) = primitives.at(min_index);

    bounds.at(min_index) = bounds_tmp;
    primitives.at(min_index) = primitive_tmp;
  }

  Log::Debug("preprocessing done -- recursively constructing BVH");
  return ConstructBVH(primitives, bounds);
}

BVHNode* BVHNode::ConstructBVH(std::vector<Primitive*> primitives, std::vector<XYZBounds> bounds) {
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
