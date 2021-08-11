#ifndef RAYGEN_PIXELTRACEDATA_H_
#define RAYGEN_PIXELTRACEDATA_H_

#include <vector>

#include "core/Point3.h"

/// Contains the information needed to trace all the rays for a single pixel
/// The associated pixel has indices (X(), Y())
class PixelTraceData {
  private:
    // Image coordinates
    int x_;
    int y_;
    std::vector<Point3> targets_;
    std::vector<float> weights_;
  
  public:
    PixelTraceData() : x_(0), y_(0), targets_(), weights_() {}
    PixelTraceData(int x, int y, const std::vector<Point3>& targets, const std::vector<float>& weights) : x_(x), y_(y), targets_(targets), weights_(weights) {}

    /// The x index of the associated pixel
    int X() const { return x_; }

    /// The y index of the associated pixel
    int Y() const { return y_; }

    /// A list of target points through which rays should be traced
    /// Each ray should be modified by its weight in the parallel Weights() list
    std::vector<Point3> Targets() { return targets_; }

    /// A list of weights for each of the points in Targets()
    ///
    /// Weights.at(i) is the weight for the ray traced through Targets().at(i),
    /// so Weights.at(i) is a multiplicative multiplier on the Color computed by
    /// tracing the ray
    std::vector<float> Weights() { return weights_; }
};

#endif
