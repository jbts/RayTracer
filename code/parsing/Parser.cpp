#include <cstring>
#include <fstream>
#include <cmath>

#include "parsing/Parser.h"
#include "logging/Log.h"
#include "light/Material.h"
#include "light/Intensity.h"
#include "light/AmbientLight.h"
#include "light/PointLight.h"
#include "light/DirectionalLight.h"
#include "light/SpotLight.h"
#include "geom/Sphere.h"
#include "geom/Triangle.h"
#include "geom/NormalTriangle.h"
#include "geom/Circle.h"
#include "geom/Ellipse.h"
#include "image/ToneMap.h"
#include "image/ToneMapBasicClamp.h"
#include "image/ToneMapAvgLumScale.h"
#include "image/ToneMapModifyRed.h"
#include "image/ToneMapModifyGreen.h"
#include "image/ToneMapModifyBlue.h"
#include "parsing/SceneData.h"

char* Parser::NextToken() {
  return strtok(nullptr, delim_.c_str());
}

float Parser::NextTokenAsFloat(int lineno) {
  char* tok = NextToken();
  if (!tok) {
    throw ParseError("missing arg(s) to command", lineno);
  }
  try {
    return std::stof(tok);
  }
  catch (...) {
    throw ParseError("unable to convert arg(s) to type float", lineno);
  }
}

int Parser::NextTokenAsInt(int lineno) {
  char* tok = NextToken();
  if (!tok) {
    throw ParseError("missing arg(s) to command", lineno);
  }
  try {
    return std::stoi(tok);
  }
  catch (...) {
    throw ParseError("unable to convert arg(s) to type int", lineno);
  }
}

SceneData Parser::ParseFile(const std::string& filename) {
    SceneData sdata;

    std::ifstream ins;
    ins.open(filename);

    if (!ins.is_open()) {
      throw ParseError("unable to open input file for parsing", 0);
    }

    char* buf = new char[max_line_len_];
    int lineno = 0;

    // Current material, applied to primitives added
    // Default is given in spec file
    Material* curr_mat = new Material(Color(0, 0, 0), Color(1, 1, 1), Color(0, 0, 0), 5, Color(0, 0, 0), 1);

    while (!ins.eof()) {
      lineno++;
      ins.getline(buf, max_line_len_);

      if (strnlen(buf, max_line_len_) == 0) { // empty input line
        continue;
      }

      if (buf[0] == '#') { // comment
        continue;
      }

      char* tok = strtok(buf, delim_.c_str());

      if (!tok) { // line is whitespace
        continue;
      }

      // film_resolution: width height
      if (strcmp("film_resolution:", tok) == 0) {
        int w = NextTokenAsInt(lineno);
        int h = NextTokenAsInt(lineno);

        // Width and height could be negative here, so just take their absolute values
        sdata.film_width = abs(w);
        sdata.film_height = abs(h);

        Log::Debug("parsed new film dimensions " + std::to_string(sdata.film_width) + " by " + std::to_string(sdata.film_height));
      }
      // output_image: filename
      else if (strcmp("output_image:", tok) == 0) {
        char* name = NextToken();

        if (!name) {
          throw ParseError("missing arg to command", lineno);
        }

        sdata.output_image = std::string(name);
        Log::Debug("parsed new output file name " + sdata.output_image);
      }
      // sphere: x y z r
      else if (strcmp("sphere:", tok) == 0) {
        float x = NextTokenAsFloat(lineno);
        float y = NextTokenAsFloat(lineno);
        float z = NextTokenAsFloat(lineno);
        float r = NextTokenAsFloat(lineno);

        Point3 pos(x, y, z);
        sdata.primitives.push_back(new Sphere(pos, r, curr_mat));
      }
      // camera_pos: px py pz
      else if (strcmp("camera_pos:", tok) == 0) {
        float px = NextTokenAsFloat(lineno);
        float py = NextTokenAsFloat(lineno);
        float pz = NextTokenAsFloat(lineno);

        sdata.camera_pos = Point3(px, py, pz);

        Log::Debug("parsed new camera position " + ToString(sdata.camera_pos)); 
      }
      // camera_fwd: dx dy dz
      else if (strcmp("camera_fwd:", tok) == 0) {
        float dx = NextTokenAsFloat(lineno);
        float dy = NextTokenAsFloat(lineno);
        float dz = NextTokenAsFloat(lineno);

        // Normalize input vector
        sdata.camera_fwd = Vector3(dx, dy, dz).Normalized();

        Log::Debug("parsed new normalized camera forward direction " + ToString(sdata.camera_fwd));
      }
      // camera_up: ux uy uz
      else if (strcmp("camera_up:", tok) == 0) {
        float ux = NextTokenAsFloat(lineno);
        float uy = NextTokenAsFloat(lineno);
        float uz = NextTokenAsFloat(lineno);

        // Normalize input vector
        sdata.camera_up = Vector3(ux, uy, uz).Normalized();

        Log::Debug("parsed new normalized camera up direction " + ToString(sdata.camera_up));
      }
      // camera_fov_ha: ha
      else if (strcmp("camera_fov_ha:", tok) == 0) {
        float ha = NextTokenAsFloat(lineno);

        sdata.camera_fov_ha = ha;

        Log::Debug("parsed new camera half angle FOV (in degrees) " + std::to_string(sdata.camera_fov_ha));
      }
      // background: r g b
      else if (strcmp("background:", tok) == 0) {
        float r = NextTokenAsFloat(lineno);
        float g = NextTokenAsFloat(lineno);
        float b = NextTokenAsFloat(lineno);

        sdata.background_color = Color(r, g, b);
        
        Log::Debug("parsed new background color " + ToString(sdata.background_color));
      }
      // material: ar ag ab dr dg db sr sg sb ns tr tg tb ior
      else if (strcmp("material:", tok) == 0) {
        float ar = NextTokenAsFloat(lineno);
        float ag = NextTokenAsFloat(lineno);
        float ab = NextTokenAsFloat(lineno);
        float dr = NextTokenAsFloat(lineno);
        float dg = NextTokenAsFloat(lineno);
        float db = NextTokenAsFloat(lineno);
        float sr = NextTokenAsFloat(lineno);
        float sg = NextTokenAsFloat(lineno);
        float sb = NextTokenAsFloat(lineno);
        float ns = NextTokenAsFloat(lineno);
        float tr = NextTokenAsFloat(lineno);
        float tg = NextTokenAsFloat(lineno);
        float tb = NextTokenAsFloat(lineno);
        float ior = NextTokenAsFloat(lineno);

        // Update the current material state
        Color ambient(ar, ag, ab);
        Color diffuse(dr, dg, db);
        Color specular(sr, sg, sb);
        Color transmissive(tr, tg, tb);
        curr_mat = new Material(ambient, diffuse, specular, ns, transmissive, ior);
      }
      // ambient_light: r g b
      else if (strcmp("ambient_light:", tok) == 0) {
        float r = NextTokenAsFloat(lineno);
        float g = NextTokenAsFloat(lineno);
        float b = NextTokenAsFloat(lineno);

        Intensity ambient = Intensity(r, g, b);
        sdata.lights.push_back(new AmbientLight(ambient));

        Log::Debug("parsed an ambient light to add to the scene");
      }
      // point_light: r g b x y z
      else if (strcmp("point_light:", tok) == 0) {
        float r = NextTokenAsFloat(lineno);
        float g = NextTokenAsFloat(lineno);
        float b = NextTokenAsFloat(lineno);
        float x = NextTokenAsFloat(lineno);
        float y = NextTokenAsFloat(lineno);
        float z = NextTokenAsFloat(lineno);

        Point3 pos(x, y, z);
        Intensity intensity(r, g, b);
        sdata.lights.push_back(new PointLight(pos, intensity));

        Log::Debug("parsed a point light to add to the scene");
      }
      // directional_light: r g b x y z
      else if (strcmp("directional_light:", tok) == 0) {
        float r = NextTokenAsFloat(lineno);
        float g = NextTokenAsFloat(lineno);
        float b = NextTokenAsFloat(lineno);
        float x = NextTokenAsFloat(lineno);
        float y = NextTokenAsFloat(lineno);
        float z = NextTokenAsFloat(lineno);

        Vector3 dir(x, y, z);
        Intensity intensity(r, g, b);
        sdata.lights.push_back(new DirectionalLight(dir, intensity));

        Log::Debug("parsed a directional light to add to the scene");
      }
      // spot_light: r g b px py pz dx dy dz angle1 angle2
      else if (strcmp("spot_light:", tok) == 0) {
        float r = NextTokenAsFloat(lineno);
        float g = NextTokenAsFloat(lineno);
        float b = NextTokenAsFloat(lineno);
        float px = NextTokenAsFloat(lineno);
        float py = NextTokenAsFloat(lineno);
        float pz = NextTokenAsFloat(lineno);
        float dx = NextTokenAsFloat(lineno);
        float dy = NextTokenAsFloat(lineno);
        float dz = NextTokenAsFloat(lineno);
        float angle1 = NextTokenAsFloat(lineno);
        float angle2 = NextTokenAsFloat(lineno);

        Intensity intensity(r, g, b);
        Point3 pos(px, py, pz);
        Vector3 dir(dx, dy, dz);
        sdata.lights.push_back(new SpotLight(pos, dir, intensity, angle1, angle2));

        Log::Debug("parsed a spot light to add to the scene");
      }
      // max_depth: n
      else if (strcmp("max_depth:", tok) == 0) {
        int n = NextTokenAsInt(lineno);

        sdata.max_recurse_depth = n;

        Log::Debug("parsed new maximum recurse depth " + std::to_string(sdata.max_recurse_depth));
      }
      // vertex: x y z
      else if (strcmp("vertex:", tok) == 0) {
        float x = NextTokenAsFloat(lineno);
        float y = NextTokenAsFloat(lineno);
        float z = NextTokenAsFloat(lineno);

        Point3 p(x, y, z);
        // Add this vertex to the triangle vertex pool
        Triangle::AddVertex(p);
      }
      // normal: x y z
      else if (strcmp("normal:", tok) == 0) {
        float x = NextTokenAsFloat(lineno);
        float y = NextTokenAsFloat(lineno);
        float z = NextTokenAsFloat(lineno);

        Vector3 n(x, y, z);
        // Add this normal to the triangle normal pool
        NormalTriangle::AddNormal(n);
      }
      // triangle: v1 v2 v3
      else if (strcmp("triangle:", tok) == 0) {
        // v1, v2, v3 are indices, so type int
        int v1 = NextTokenAsInt(lineno);
        int v2 = NextTokenAsInt(lineno);
        int v3 = NextTokenAsInt(lineno);

        sdata.primitives.push_back(new Triangle(v1, v2, v3, curr_mat));
      }
      // normal_triangle: v1 v2 v3 n1 n2 n3
      else if (strcmp("normal_triangle:", tok) == 0) {
        // v1, v2, v3, n1, n2, n3 are indices, so type int
        int v1 = NextTokenAsInt(lineno);
        int v2 = NextTokenAsInt(lineno);
        int v3 = NextTokenAsInt(lineno);
        int n1 = NextTokenAsInt(lineno);
        int n2 = NextTokenAsInt(lineno);
        int n3 = NextTokenAsInt(lineno);

        Triangle* tri = new NormalTriangle(v1, v2, v3, n1, n2, n3, curr_mat);
        sdata.primitives.push_back(tri);
      }
      // circle: x y z r nx ny nz
      else if (strcmp("circle:", tok) == 0) {
        float x = NextTokenAsFloat(lineno);
        float y = NextTokenAsFloat(lineno);
        float z = NextTokenAsFloat(lineno);
        float r = NextTokenAsFloat(lineno);
        float nx = NextTokenAsFloat(lineno);
        float ny = NextTokenAsFloat(lineno);
        float nz = NextTokenAsFloat(lineno);

        Point3 center(x, y, z);
        float radius = r;
        Vector3 normal(nx, ny, nz);

        sdata.primitives.push_back(new Circle(center, radius, normal, curr_mat));
      }
      // ellipse: x1 y1 z1 x2 y2 z2 d nx ny nz
      else if (strcmp("ellipse:", tok) == 0) {
        float x1 = NextTokenAsFloat(lineno);
        float y1 = NextTokenAsFloat(lineno);
        float z1 = NextTokenAsFloat(lineno);
        float x2 = NextTokenAsFloat(lineno);
        float y2 = NextTokenAsFloat(lineno);
        float z2 = NextTokenAsFloat(lineno);
        float d = NextTokenAsFloat(lineno);
        float nx = NextTokenAsFloat(lineno);
        float ny = NextTokenAsFloat(lineno);
        float nz = NextTokenAsFloat(lineno);

        Point3 f1(x1, y1, z1);
        Point3 f2(x2, y2, z2);
        Vector3 normal(nx, ny, nz);

        sdata.primitives.push_back(new Ellipse(f1, f2, d, normal, curr_mat));
      }
      // sample_jitter: n
      else if (strcmp("sample_jitter:", tok) == 0) {
        int n = NextTokenAsInt(lineno);

        sdata.sample_strat = SAMPLE_STRATEGY_JITTER;
        // Require at least one sample per pixel for sanity
        sdata.num_samples_jitter = std::max(1, n);

        Log::Debug("parsed sample strategy jittered with " + std::to_string(sdata.num_samples_jitter) + " samples per pixel");
      }
      // tm_basic_clamp
      else if (strcmp("tm_basic_clamp", tok) == 0) {
        sdata.tone_maps.push_back(new ToneMapBasicClamp());
        Log::Debug("parsed a basic clamp tone map");
      }
      // tm_avg_lum_scale: alpha
      else if (strcmp("tm_avg_lum_scale:", tok) == 0) {
        float alpha = NextTokenAsFloat(lineno);

        sdata.tone_maps.push_back(new ToneMapAvgLumScale(alpha));
        Log::Debug("parsed an average luminance scale tone map");
      }
      // tm_modify_red: s
      else if (strcmp("tm_modify_red:", tok) == 0) {
        float s = NextTokenAsFloat(lineno);

        sdata.tone_maps.push_back(new ToneMapModifyRed(s));
        Log::Debug("parsed a modify red tone map");
      }
      // tm_modify_green: s
      else if (strcmp("tm_modify_green:", tok) == 0) {
        float s = NextTokenAsFloat(lineno);

        sdata.tone_maps.push_back(new ToneMapModifyGreen(s));
        Log::Debug("parsed a modify green tone map");
      }
      // tm_modify_blue: s
      else if (strcmp("tm_modify_blue:", tok) == 0) {
        float s = NextTokenAsFloat(lineno);

        sdata.tone_maps.push_back(new ToneMapModifyBlue(s));
        Log::Debug("parsed a modify blue tone map");
      }
      // unrecognized command
      else {
        Log::Warning("parsed unrecognized command '" + std::string(tok) + "' on line " + std::to_string(lineno) + " of input file");
      }
    }

    ins.close();
    delete[] buf;
    buf = nullptr;

    // Create an orthogonal camera basis based on camera_up and camera_fwd
    // Copied over from my hw3 code
    sdata.camera_right = (-1 * Cross(sdata.camera_up, sdata.camera_fwd)).Normalized();
    Log::Debug("computed new camera right direction " + ToString(sdata.camera_right));

    // If camera_up and camera_fwd aren't orthogonal, adjust them
    if (fabs(Dot(sdata.camera_up, sdata.camera_fwd)) > 0.0001) {
      // Adjust camera_up to be perpendicular to camera_fwd by rejecting
      // camera_up onto camera_fwd, then normalizing
      Vector3 project = Dot(sdata.camera_up, sdata.camera_fwd) * sdata.camera_fwd;
      sdata.camera_up = (sdata.camera_up - project).Normalized();

      Log::Debug("adjusted camera up direction to " + ToString(sdata.camera_up) + " to make orthogonal basis");
    }

    return sdata;
}
