#ifndef IMAGE_IMAGE_H_
#define IMAGE_IMAGE_H_

#include <cstdint>
#include <string>

#include "core/Color.h"
#include "parsing/SceneData.h"
#include "image/ToneMap.h"

/// For holding and manipulating image data
/// Originally based on Dr. Guy's implementation for hw3
class Image {
  private:
    int width_;
    int height_;
    Color* pixels_;

    std::vector<ToneMap*> tone_maps_;

    void ApplyToneMaps();

  public:
    Image(const SceneData& sdata);
    Image(const Image& cpy);
    ~Image();
    Image& operator=(const Image& rhs);

    /// Get a new image that is a copy of this one
    /// Returns a pointer to a dynamically allocated Image object
    Image* Copy() const;

    /// Write the image to a file, using the stb_image_write library
    /// The format to write the image in is inferred from its extension
    /// Supported extensions: .jpeg/.jpg, .png, .tga/.targa, .bmp
    void Write(const std::string& filename);

    int Width() const { return width_; }
    int Height() const { return height_; }

    Color GetPixel(int x, int y) const;
    void SetPixel(int x, int y, const Color& c);

    /// Get the image as a list of bytes
    /// Each pixel is represented as 4 consecutive uint8_t's
    /// in the range [0, 255], for RGBA
    /// Returns a pointer to a dynamically allocated list of bytes
    uint8_t* AsBytes();

    /// Get the average luminance of the samples in this image
    float AvgLum() const;
};

#endif
