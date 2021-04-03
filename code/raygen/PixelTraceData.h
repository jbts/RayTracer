#ifndef RAYGEN_PIXELTRACEDATA_H_
#define RAYGEN_PIXELTRACEDATA_H_

#include <vector>

#include "core/Point3.h"

class PixelTraceData {
  private:
    // Image coordinates
    int x_;
    int y_;
    std::vector<Point3> targets_;
    std::vector<float> weights_;
  
  public:
    PixelTraceData() : x_(0), y_(0), targets_(), weights_() {}
    PixelTraceData(int x, int y, std::vector<Point3> targets, std::vector<float> weights) : x_(x), y_(y), targets_(targets), weights_(weights) {}

    int X() const { return x_; }
    int Y() const { return y_; }
    std::vector<Point3> Targets() { return targets_; }
    std::vector<float> Weights() { return weights_; }
};

#endif