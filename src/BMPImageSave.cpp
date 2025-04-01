#include "../include/BMPImageSave.hpp"

namespace ImageProcessing {
BMPImageSave::BMPImageSave(const std::string& path) {
  file = std::ofstream(path, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Failed to create file");
  }
}

void BMPImageSave::SetFileHeader(const BITMAPFILEHEADER& set_file_header) {
  file_header = set_file_header;
}

void BMPImageSave::SetInfoHeader(const BITMAPINFOHEADER& set_info_header) {
  info_header = set_info_header;
}

void BMPImageSave::SetPixels(const std::vector<BYTE>& set_pixels) {
  pixels = set_pixels;
}

void BMPImageSave::SetWidth(const LONG& set_width) { width = set_width; }

void BMPImageSave::SetHeight(const LONG& set_height) { height = set_height; }

void BMPImageSave::SetRowStride(const size_t& set_row_stride) {
  row_stride = set_row_stride;
}

void BMPImageSave::Save() {
  BITMAPFILEHEADER file_header{};
  BITMAPINFOHEADER info_header{};

  // BITMAPFILEHEADER
  file_header.bfType = 0x4D42;
  file_header.bfOffBits = sizeof(file_header) + sizeof(info_header);
  file_header.bfSize = file_header.bfOffBits + pixels.size();
  file_header.bfReserved1 = 0;
  file_header.bfReserved2 = 0;

  // BITMAPINFOHEADER
  info_header.biSize = sizeof(info_header);
  info_header.biWidth = width;
  info_header.biHeight = height;
  info_header.biPlanes = 1;
  info_header.biBitCount = 24;
  info_header.biCompression = 0;
  info_header.biSizeImage = static_cast<DWORD>(pixels.size());
  info_header.biXPelsPerMeter = 0;
  info_header.biYPelsPerMeter = 0;
  info_header.biClrUsed = 0;
  info_header.biClrImportant = 0;

  file.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
  file.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));
  file.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());
  file.close();
}
} // namespace ImageProcessing