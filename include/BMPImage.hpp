#pragma once

#include "BMPImageLoad.hpp"
#include "BasicStructs.hpp"

#include <vector>

namespace ImageProcessing {
struct Pixel {
  BYTE blue;
  BYTE green;
  BYTE red;

  Pixel(BYTE blue, BYTE green, BYTE red);
};

class BMPImage {
public:
  BMPImage() = default;

  BMPImage(const BMPImageLoad& load_image);

  BMPImage(const BMPImageLoad& load_image, const std::string& out_path);

  const LONG& GetWidth() const noexcept;

  const LONG& GetHeight() const noexcept;

  void SetWidth(LONG new_width) noexcept;

  void SetHeight(LONG new_height) noexcept;

  const std::vector<BYTE>& GetPixels() const noexcept;

  Pixel GetPixel(int x, int y) const;

  void SetPixel(int x, int y, Pixel p);

  const size_t& GetRowStride() const;

  ~BMPImage();

private:
  std::vector<BYTE> pixels;
  LONG width = 0;
  LONG height = 0;
  size_t row_stride = 0;
  std::string out_path = "";
};
} // namespace ImageProcessing