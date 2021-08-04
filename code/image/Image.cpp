#include "image/Image.h"

#include <string>
#include <cctype> // for tolower()

#include "stb_image/stb_image_write.h"
#include "logging/Log.h"

Image::Image(int width, int height) {
  width_ = width;
  height_ = height;
  pixels_ = new Color[width * height];
}

Image::Image(const Image& cpy) {
  width_ = cpy.width_;
  height_ = cpy.height_;
  pixels_ = new Color[width_ * height_];

  for (int i = 0; i < width_ * height_; i++) {
    pixels_[i] = cpy.pixels_[i];
  }
}

Image::~Image() {
  delete[] pixels_;
  pixels_ = nullptr;
}

Image& Image::operator=(const Image& rhs) {
  if (this != &rhs) {
    width_ = rhs.width_;
    height_ = rhs.height_;
    delete[] pixels_;
    pixels_ = new Color[width_ * height_];

    for (int i = 0; i < width_ * height_; i++) {
        pixels_[i] = rhs.pixels_[i];
    }
  }
  return *this;
}

Image* Image::Copy() const {
  // Call the copy constructor
  return new Image(*this);
}

void Image::Write(const std::string& filename) const {
  // Do some sanity checks on the length of filename
  // Shortest filename allowed is something like a.png
  if (filename.length() < 5) {
    Log::Error("output image file name '" + filename + "' is too short - nothing written");
    return;
  }
  Log::Debug("Average luminance of image is " + std::to_string(AvgLum()));
  uint8_t* data = AsBytes();

  // Infer the format to write in based on the end of the filename
  size_t dot_index = filename.find_last_of('.');

  // No . found, so can't infer extension - default to BMP
  if (dot_index == std::string::npos) {
    Log::Warning("no image extension found: defaulting to BMP format for writing to file " + filename);
    if (!stbi_write_bmp(filename.c_str(), width_, height_, 4, data)) {
        Log::Error("failed to write image to file " + filename);
    }
    return;
  }

  std::string ext = filename.substr(dot_index);
  for (int i = 0; i < ext.length(); i++) {
    ext.at(i) = tolower(ext.at(i));
  }

  if (ext == ".png") {
    Log::Debug("writing image to file " + filename + " in PNG format");
      if (!stbi_write_png(filename.c_str(), width_, height_, 4, data, width_ * 4)) {
        Log::Error("failed to write image to file " + filename);
      }
  }
  else if (ext == ".jpg" || ext == ".jpeg") {
    // Write at 95% quality
    Log::Debug("writing image to file " + filename + " in JPG format");
    if (!stbi_write_jpg(filename.c_str(), width_, height_, 4, data, 95)) {
      Log::Error("failed to write image to file " + filename);
    }
  }
  else if (ext == ".tga" || ext == ".targa") {
    Log::Debug("writing image to file " + filename + " in TGA format");
    if (!stbi_write_tga(filename.c_str(), width_, height_, 4, data)) {
      Log::Error("failed to write image to file " + filename);
    }
  }
  else if (ext == ".bmp") {
    Log::Debug("writing image to file " + filename + " in BMP format");
    if (!stbi_write_bmp(filename.c_str(), width_, height_, 4, data)) {
      Log::Error("failed to write image to file " + filename);
    }
  }
  else { // default to bmp format, write a warning
    Log::Warning("unrecognized extension: defaulting to BMP format for writing image to file " + filename);
    if (!stbi_write_bmp(filename.c_str(), width_, height_, 4, data)) {
      Log::Error("failed to write image to file " + filename);
    }
  }

  delete[] data;
}

Color Image::GetPixel(int x, int y) const {
  return pixels_[y * width_ + x];
}

void Image::SetPixel(int x, int y, const Color& c) {
  pixels_[y * width_ + x] = c;
}

uint8_t* Image::AsBytes() const {
  uint8_t* data = new uint8_t[4 * width_ * height_];
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      Color c = pixels_[y * width_ + x];
      data[4 * (y * width_ + x)] = uint8_t(ColorCompClamp(c.R()) * 255 + 0.5);
      data[4 * (y * width_ + x) + 1] = uint8_t(ColorCompClamp(c.G()) * 255 + 0.5);
      data[4 * (y * width_ + x) + 2] = uint8_t(ColorCompClamp(c.B()) * 255 + 0.5);
      data[4 * (y * width_ + x) + 3] = 255;
    }
  }
  return data;
}

float Image::AvgLum() const {
  float total_lum = 0.0f;
  int num_pixels = width_ * height_;

  // An Image with no pixels has 0 average luminance (I guess)
  if (num_pixels <= 0) {
    return 0.0f;
  }

  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      total_lum += pixels_[y * width_ + x].Lum();
    }
  }

  return total_lum / num_pixels;
}
