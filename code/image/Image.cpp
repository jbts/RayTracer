#include "image/Image.h"

#include <string>

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

void Image::Write(std::string filename) const {
  // Do some sanity checks on the length of filename
  // Shortest filename allowed is something like a.png
  if (filename.length() < 5) {
    Log::Error("output image file name '" + filename + "' is too short - nothing written");
    return;
  }

  uint8_t* data = AsBytes();

  // Infer the format to write in based on the end of the filename
  char lastc = filename.back();

  if (lastc == 'g') { // jpg, jpeg, or png
    char secondlastc = filename.at(filename.length() - 2);
    if (secondlastc == 'n') { // png
      Log::Debug("writing image to file '" + filename + "' in PNG format");
      if (!stbi_write_png(filename.c_str(), width_, height_, 4, data, width_ * 4)) {
          Log::Error("failed to write image to file '" + filename + "'");
      }
    }
    else { // jpg or jpeg
      // Write at 95% quality
      Log::Debug("writing image to file '" + filename +"' in JPG format");
      if (!stbi_write_jpg(filename.c_str(), width_, height_, 4, data, 95)) {
          Log::Error("failed to write image to file '" + filename + "'");
      }
    }
  }
  else if (lastc == 'a') { // tga or targa
    Log::Debug("writing image to file '" + filename + "' in TGA format");
    if (!stbi_write_tga(filename.c_str(), width_, height_, 4, data)) {
        Log::Error("failed to write image to file '" + filename + "'");
    }
  }
  else if (lastc == 'p') { // bmp
    Log::Debug("writing image to file '" + filename + "' in BMP format");
    if (!stbi_write_bmp(filename.c_str(), width_, height_, 4, data)) {
        Log::Error("failed to write image to file '" + filename + "'");
    }
  }
  else { // default to bmp format, write a warning
    Log::Warning("unrecognized extension: defaulting to BMP format for writing image to file '" + filename +"'");
    if (!stbi_write_bmp(filename.c_str(), width_, height_, 4, data)) {
        Log::Error("failed to write image to file '" + filename + "'");
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
      data[4 * (y * width_ + x)] = uint8_t(c.R() * 255 + 0.5);
      data[4 * (y * width_ + x) + 1] = uint8_t(c.G() * 255 + 0.5);
      data[4 * (y * width_ + x) + 2] = uint8_t(c.B() * 255 + 0.5);
      data[4 * (y * width_ + x) + 3] = 255;
    }
  }
  return data;
}