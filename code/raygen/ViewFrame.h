#ifndef RAYGEN_VIEWFRAME_H_
#define RAYGEN_VIEWFRAME_H_

#include <vector>

#include "core/Point3.h"
#include "core/Vector3.h"
#include "raygen/PixelTraceData.h"

/// Tells a ViewFrame how to find the points to shoot rays through
enum SampleStrategy {
    // "Normal"/basic sampling
    SAMPLE_STRATEGY_BASIC,
    // Jittered supersampling
    SAMPLE_STRATEGY_JITTER,
    // Adaptive supersampling
    // SAMPLE_STRATEGY_ADAPTIVE,
};

/// Handles the viewing frame for the scene we want to raytrace
/// Does math for generating rays with a given sampling method
/// Useful for generating a list of rays to trace before starting to trace them
class ViewFrame {
  private:
    // Dimensions in pixels
    int width_;
    int height_;

    Point3 eye_pos_;
    Vector3 up_;
    Vector3 forward_;
    Vector3 right_;

    // In degrees
    float half_angle_fov_;
  
    SampleStrategy sample_strat_;

    /// Find the distance from the eye to the frame
    /// Computed from the height and half_angle_fov, assuming that
    /// forward is perpendicular to the plane of the frame
    float EyeToFrameDistance() const;
    Point3 FrameTopLeft() const;

    // Number of samples per pixel for jittered supersampling
    int num_jitter_samples_ = 5;
  public:
    ViewFrame();
    ViewFrame(int width, int height, Point3 eye_pos, Vector3 up, Vector3 forward, Vector3 right, float half_angle_fov);

    /// Set the sampling strategy to be used for sampling points and generating rays
    void SetSampleStrategy(SampleStrategy strat);

    /// Sample the view frame, getting a list of points to shoot rays through
    /// Use the current strategy for sampling
    std::vector<PixelTraceData> SamplePoints() const;

    /// Sample each pixel once, directly in its center
    std::vector<PixelTraceData> SamplePointsBasic() const;

    /// Sample each pixel more than once, with random jittering
    /// within the pixel. Give each pixel an equal weight, so
    /// the resulting colors are averaged.
    ///
    /// Number of samples per pixel is controlled by num_jitter_samples_
    std::vector<PixelTraceData> SamplePointsJittered() const;

    /// Set the number of samples to take per pixel for jittered supersampling
    void SetNumJitterSamples(int num_jitter_samples);
};

#endif