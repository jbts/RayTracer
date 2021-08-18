#include "imagemap/ImageMapBasicClamp.h"

#include "image/Image.h"
#include "core/Color.h"

void ImageMapBasicClamp::ApplyMap(Image& img) const {
  int width = img.Width();
  int height = img.Height();

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      Color c = img.GetPixel(x, y);
      Color new_c = Color(ColorCompClamp(c.R()), ColorCompClamp(c.G()), ColorCompClamp(c.B()));
      img.SetPixel(x, y, new_c);
    }
  }
}