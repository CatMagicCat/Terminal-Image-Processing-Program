#pragma once

#include <fstream>

#include "BasicStructs.hpp"

namespace ImageProcessing {
class BMPImageSave {
public:
  BMPImageSave(const std::string& path);

  void SetFileHeader(const BITMAPFILEHEADER& file_header);

  void SetInfoHeader(const BITMAPINFOHEADER& info_header);

  void SetPixels(const std::vector<BYTE>& pixels);

  void SetWidth(const LONG& width);

  void SetHeight(const LONG& height);

  void SetRowStride(const size_t& row_stride);

  void Save();

private:
  BITMAPFILEHEADER file_header;
  BITMAPINFOHEADER info_header;

  std::ofstream file;

  std::vector<BYTE> pixels;
  LONG width = 0;
  LONG height = 0;
  size_t row_stride = 0;
};
} // namespace ImageProcessing