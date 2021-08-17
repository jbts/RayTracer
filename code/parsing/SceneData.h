#ifndef PARSING_SCENEDATA_H_
#define PARSING_SCENEDATA_H_

#include <vector>
#include <string>

#include "core/Point3.h"
#include "core/Vector3.h"
#include "geom/Triangle.h"
#include "geom/Sphere.h"
#include "light/Light.h"
#include "raygen/ViewFrame.h"
#include "image/ToneMap.h"

/// Holds lots of data about the structure of a scene
/// Includes camera position and orientation, locations
/// and attributes of primitives, lighting information,
/// and picture metadata, among other things
///
/// All members are public for ease of use
class SceneData {
  public:
    // Camera data
    Point3 camera_pos;
    // camera_fwd, camera_up, and camera_right form an orthogonal basis for the
    // 3D space
    Vector3 camera_fwd;
    Vector3 camera_up;
    Vector3 camera_right;
    float camera_fov_ha;

    // Image data
    int film_width;
    int film_height;
    std::string output_image;
    int max_recurse_depth;

    // Geometry data
    std::vector<Primitive*> primitives;
    
    // Lighting data
    Color background_color;
    std::vector<Light*> lights;

    // Ray generation data
    SampleStrategy sample_strat;
    int num_samples_jitter;

    // Tone mapping / post-processing data
    std::vector<ToneMap*> tone_maps;
    
    /// Make a new SceneData object with reasonable default values
    SceneData();
};
#endif
