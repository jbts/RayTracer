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
#include "parsing/SceneData.h"

char* Parser::NextToken() {
  return strtok(nullptr, delim_.c_str());
}

SceneData Parser::ParseFile(std::string filename) {
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
    Material curr_mat(Color(0, 0, 0), Color(1, 1, 1), Color(0, 0, 0), 5, Color(0, 0, 0), 1);

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
        char* w = NextToken();
        char* h = NextToken();

        if (!w || !h) {
          throw ParseError("missing arg(s) to film_resolution command", lineno);
        }

        // Width and height could be negative here, so just take their absolute values
        try {
          sdata.film_width = abs(std::stoi(w));
          sdata.film_height = abs(std::stoi(h));
        }
        catch (...) {
          throw ParseError("unable to convert film_resolution arg(s) to type int", lineno);
        }

        Log::Debug("parsed new film dimensions " + std::to_string(sdata.film_width) + " by " + std::to_string(sdata.film_height));
      }
      // output_image: filename
      else if (strcmp("output_image:", tok) == 0) {
        char* name = NextToken();

        if (!name) {
          throw ParseError("missing arg to output_image command", lineno);
        }

        sdata.output_image = std::string(name);
        Log::Debug("parsed new output file name " + sdata.output_image);
      }
      // sphere: x y z r
      else if (strcmp("sphere:", tok) == 0) {
        char* x = NextToken();
        char* y = NextToken();
        char* z = NextToken();
        char* r = NextToken();

        if (!x || !y || !z || !r) {
          throw ParseError("missing arg(s) to sphere command", lineno);
        }

        try {
          Point3 pos(std::stof(x), std::stof(y), std::stof(z));
          sdata.spheres.push_back(new Sphere(pos, std::stof(r), curr_mat));
        }
        catch (...) {
          throw ParseError("unable to convert sphere arg(s) to type float", lineno);
        }
      }
      // camera_pos: px py pz
      else if (strcmp("camera_pos:", tok) == 0) {
        char* px = NextToken();
        char* py = NextToken();
        char* pz = NextToken();

        if (!px || !py || !pz) {
          throw ParseError("missing args to camera_pos command", lineno);
        }

        try {
          sdata.camera_pos = Point3(std::stof(px), std::stof(py), std::stof(pz));
        }
        catch (...) {
          throw ParseError("unable to convert camera_pos arg(s) to type float", lineno);
        }

        Log::Debug("parsed new camera position " + ToString(sdata.camera_pos)); 
      }
      // camera_fwd: dx dy dz
      else if (strcmp("camera_fwd:", tok) == 0) {
        char* dx = NextToken();
        char* dy = NextToken();
        char* dz = NextToken();

        if (!dx || !dy || !dz) {
          throw ParseError("missing arg(s) to camera_fwd command", lineno);
        }

        try {
          // Make sure to normalize input vector
          sdata.camera_fwd = Vector3(std::stof(dx), std::stof(dy), std::stof(dz)).Normalized();
        }
        catch (...) {
          throw ParseError("unable to convert camera_fwd arg(s) to type float", lineno);
        }

        Log::Debug("parsed new normalized camera forward direction " + ToString(sdata.camera_fwd));
      }
      // camera_up: ux uy uz
      else if (strcmp("camera_up:", tok) == 0) {
        char* ux = NextToken();
        char* uy = NextToken();
        char* uz = NextToken();

        if (!ux || !uy || !uz) {
          throw ParseError("missing arg(s) to camera_up command", lineno);
        }

        try {
          // Normalize input vector
          sdata.camera_up = Vector3(std::stof(ux), std::stof(uy), std::stof(uz)).Normalized();
        }
        catch (...) {
          throw ParseError("unable to convert camera_up arg(s) to type float", lineno);
        }

        Log::Debug("parsed new normalized camera up direction " + ToString(sdata.camera_up));
      }
      // camera_fov_ha: ha
      else if (strcmp("camera_fov_ha:", tok) == 0) {
        char* ha = NextToken();

        if (!ha) {
          throw ParseError("missing arg to camera_fov_ha command", lineno);
        }

        try {
          sdata.camera_fov_ha = std::stof(ha);
        }
        catch (...) {
          throw ParseError("unable to convert camera_fov_ha arg to type float", lineno);
        }

        Log::Debug("parsed new camera half angle FOV (in degrees) " + std::to_string(sdata.camera_fov_ha));
      }
      // background: r g b
      else if (strcmp("background:", tok) == 0) {
        char* r = NextToken();
        char* g = NextToken();
        char* b = NextToken();

        if (!r || !g || !b) {
          throw ParseError("missing arg(s) to background command", lineno);
        }

        try {
          sdata.background_color = Color(std::stof(r), std::stof(g), std::stof(b));
        }
        catch (...) {
          throw ParseError("unable to convert background arg(s) to type float", lineno);
        }

        Log::Debug("parsed new background color " + ToString(sdata.background_color));
      }
      // material: ar ag ab dr dg db sr sg sb ns tr tg tb ior
      else if (strcmp("material:", tok) == 0) {
        char* ar = NextToken();
        char* ag = NextToken();
        char* ab = NextToken();
        char* dr = NextToken();
        char* dg = NextToken();
        char* db = NextToken();
        char* sr = NextToken();
        char* sg = NextToken();
        char* sb = NextToken();
        char* ns = NextToken();
        char* tr = NextToken();
        char* tg = NextToken();
        char* tb = NextToken();
        char* ior = NextToken();

        if (!ar || !ag || !ab || !dr || !dg || !db || !sr || !sg || !sb || !ns || !tr || !tg || !tb || !ior) {
          throw ParseError("missing arg(s) to material command", lineno);
        }

        // Update the current material state
        try {
          Color ambient(std::stof(ar), std::stof(ag), std::stof(ab));
          Color diffuse(std::stof(dr), std::stof(dg), std::stof(db));
          Color specular(std::stof(sr), std::stof(sg), std::stof(sb));
          Color transmissive(std::stof(tr), std::stof(tg), std::stof(tb));
          curr_mat = Material(ambient, diffuse, specular, std::stof(ns), transmissive, std::stof(ior));
        }
        catch (...) {
          throw ParseError("unable to parse material arg(s) as type float", lineno);
        }
      }
      // ambient_light: r g b
      else if (strcmp("ambient_light:", tok) == 0) {
        char* r = NextToken();
        char* g = NextToken();
        char* b = NextToken();

        if (!r || !g || !b) {
          throw ParseError("missing arg(s) to ambient_light command", lineno);
        }

        try {
          Intensity ambient = Intensity(std::stof(r), std::stof(g), std::stof(b));
          sdata.lights.push_back(new AmbientLight(ambient));
        }
        catch (...) {
          throw ParseError("unable to parse ambient_light arg(s) as type float", lineno);
        }

        Log::Debug("parsed an ambient light to add to the scene");
      }
      // point_light: r g b x y z
      else if (strcmp("point_light:", tok) == 0) {
        char* r = NextToken();
        char* g = NextToken();
        char* b = NextToken();
        char* x = NextToken();
        char* y = NextToken();
        char* z = NextToken();

        if (!r || !g || !b || !x || !y || !z) {
          throw ParseError("missing arg(s) to point_light command", lineno);
        }

        try {
          Point3 pos(std::stof(x), std::stof(y), std::stof(z));
          Intensity intensity(std::stof(r), std::stof(g), std::stof(b));
          sdata.lights.push_back(new PointLight(pos, intensity));
        }
        catch (...) {
          throw ParseError("unable to parse point light arg(s) as type float", lineno);
        }

        Log::Debug("parsed a point light to add to the scene");
      }
      // directional_light: r g b x y z
      else if (strcmp("directional_light:", tok) == 0) {
        char* r = NextToken();
        char* g = NextToken();
        char* b = NextToken();
        char* x = NextToken();
        char* y = NextToken();
        char* z = NextToken();

        if (!r || !g || !b || !x || !y || !z) {
          throw ParseError("missing arg(s) to directional_light command", lineno);
        }

        try {
          Vector3 dir(std::stof(x), std::stof(y), std::stof(z));
          Intensity intensity(std::stof(r), std::stof(g), std::stof(b));
          sdata.lights.push_back(new DirectionalLight(dir, intensity));
        }
        catch (...) {
          throw ParseError("unable to parse directional light arg(s) as type float", lineno);
        }

        Log::Debug("parsed a directional light to add to the scene");
      }
      // spot_light: r g b px py pz dx dy dz angle1 angle2
      else if (strcmp("spot_light:", tok) == 0) {
        char* r = NextToken();
        char* g = NextToken();
        char* b = NextToken();
        char* px = NextToken();
        char* py = NextToken();
        char* pz = NextToken();
        char* dx = NextToken();
        char* dy = NextToken();
        char* dz = NextToken();
        char* angle1 = NextToken();
        char* angle2 = NextToken();

        if (!r || !g  || !b || !px || !py || !pz || !dx || !dy || !dz || !angle1 || !angle2) {
          throw ParseError("missing arg(s) to spot_light command", lineno);
        }

        try {
          Intensity intensity(std::stof(r), std::stof(g), std::stof(b));
          Point3 pos(std::stof(px), std::stof(py), std::stof(pz));
          Vector3 dir(std::stof(dx), std::stof(dy), std::stof(dz));
          sdata.lights.push_back(new SpotLight(pos, dir, intensity, std::stof(angle1), std::stof(angle2)));
        }
        catch (...) {
          throw ParseError("unable to parse spot light arg(s) as type float", lineno);
        }

        Log::Debug("parsed a spot light to add to the scene");
      }
      // max_depth: n
      else if (strcmp("max_depth:", tok) == 0) {
        char* n = NextToken();

        if (!n) {
          throw ParseError("missing arg to max_depth command", lineno);
        }

        try {
          sdata.max_recurse_depth = std::stoi(n);
        }
        catch (...) {
          throw ParseError("unable to parse max depth arg as type int", lineno);
        }

        Log::Debug("parsed new maximum recurse depth " + std::to_string(sdata.max_recurse_depth));
      }
      // vertex: x y z
      else if (strcmp("vertex:", tok) == 0) {
        char* x = NextToken();
        char* y = NextToken();
        char* z = NextToken();

        if (!x || !y || !z) {
          throw ParseError("missing arg(s) to vertex command", lineno);
        }

        try {
          Point3 p(std::stof(x), std::stof(y), std::stof(z));
          // Add this vertex to the triangle vertex pool
          Triangle::AddVertex(p);
        }
        catch (...) {
          throw ParseError("unable to parse vertex arg(s) as type float", lineno);
        }
      }
      // normal: x y z
      else if (strcmp("normal:", tok) == 0) {
        char* x = NextToken();
        char* y = NextToken();
        char* z = NextToken();

        if (!x || !y || !z) {
          throw ParseError("missing arg(s) to normal command", lineno);
        }

        try {
          Vector3 n(std::stof(x), std::stof(y), std::stof(z));
          // Add this normal to the triangle normal pool
          NormalTriangle::AddNormal(n);
        }
        catch (...) {
          throw ParseError("unable to parse normal command arg(s) as type float", lineno);
        }
      }
      // triangle: v1 v2 v3
      else if (strcmp("triangle:", tok) == 0) {
        char* v1 = NextToken();
        char* v2 = NextToken();
        char* v3 = NextToken();

        if (!v1 || !v2 || !v3) {
          throw ParseError("missing arg(s) to triangle command", lineno);
        }

        try {
          // v1, v2, v3 are indices, so type int
          sdata.triangles.push_back(new Triangle(std::stoi(v1), std::stoi(v2), std::stoi(v3), curr_mat));
        }
        catch (...) {
          throw ParseError("unable to parse triangle arg(s) as type int", lineno);
        }
      }
      // normal_triangle: v1 v2 v3 n1 n2 n3
      else if (strcmp("normal_triangle:", tok) == 0) {
        char* v1 = NextToken();
        char* v2 = NextToken();
        char* v3 = NextToken();
        char* n1 = NextToken();
        char* n2 = NextToken();
        char* n3 = NextToken();

        if (!v1 || !v2 || !v3 || !n1 || !n2 || !n3) {
          throw ParseError("missing arg(s) to normal_triangle command", lineno);
        }

        try {
          // v1, v2, v3, n1, n2, n3 are indices, so type int
          Triangle* tri = new NormalTriangle(std::stoi(v1), std::stoi(v2), std::stoi(v3), std::stoi(n1), std::stoi(n2), std::stoi(n3), curr_mat);
          sdata.triangles.push_back(tri);
        }
        catch (...) {
          throw ParseError("unable to parse normal_triangle arg(s) as type int", lineno);
        }
      }
      // Custom command
      // sample_jitter: n
      // Indicate that the program should sample with a jittered supersampling strategy
      // n is an integer that specifies the number of samples to take per cell/pixel
      else if (strcmp("sample_jitter:", tok) == 0) {
        char* n = NextToken();

        if (!n) {
          throw ParseError("missing arg to sample_jitter command", lineno);
        }

        try {
          sdata.sample_strat = SAMPLE_STRATEGY_JITTER;
          // Require at least one sample per pixel for sanity
          sdata.num_samples_jitter = std::max(1, std::stoi(n));
        }
        catch (...) {
          throw ParseError("unable to parse sample jitter arg as type int", lineno);
        }

        Log::Debug("parsed sample strategy jittered with " + std::to_string(sdata.num_samples_jitter) + " samples per pixel");
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