#pragma once

#include <string>
#include <vector>

#include "BasicStructs.hpp"

namespace ImageProcessing {
class BMPImageLoad {
public:
  BMPImageLoad(const std::string& path);

  const BITMAPFILEHEADER& GetFileHeader() const;

  const BITMAPINFOHEADER& GetInfoHeader() const;

  const std::vector<BYTE>& GetPixels() const;

  const LONG& GetWidth() const;

  const LONG& GetHeight() const;

  const size_t& GetRowStride() const;

private:
  BITMAPFILEHEADER file_header;
  BITMAPINFOHEADER info_header;

  std::vector<BYTE> pixels;
  LONG width = 0;
  LONG height = 0;
  size_t row_stride = 0;
};
} // namespace ImageProcessing