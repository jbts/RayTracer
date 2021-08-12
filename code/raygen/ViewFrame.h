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
};

/// A view frame which computes ray targets based on scene information
/// like eye position, distance to the view frame, and camera parameters
///
/// Use SetSampleStrategy() to specify a sample strategy for the view frame
/// to use when sampling
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
    ViewFrame(int width, int height, const Point3& eye_pos, const Vector3& up, const Vector3& forward, const Vector3& right, float half_angle_fov);

    void SetSampleStrategy(SampleStrategy strat);

    /// Sample the view frame, getting a list of PixelTraceData objects
    /// Use the appropriate sampling strategy
    ///
    /// Each PixelTraceData object has information needed to trace the rays for
    /// a single pixel. See the PixelTraceData class for more information.
    std::vector<PixelTraceData> SamplePoints() const;

    /// Sample each pixel once, directly in its center
    std::vector<PixelTraceData> SamplePointsBasic() const;

    /// Sample each pixel num_sample_jitters_ times, with random jittering
    /// within the pixel. Give each pixel an equal weight, so
    /// the resulting colors are averaged.
    ///
    /// Number of samples per pixel is controlled by num_jitter_samples_
    std::vector<PixelTraceData> SamplePointsJittered() const;

    /// Set the number of samples to make per pixel during jittered supersampling
    void SetNumJitterSamples(int num_jitter_samples);
};

#endif
