#include "../include/BMPImageLoad.hpp"

#include <fstream>

constexpr uint32_t COLORS = 3;

namespace ImageProcessing {
BMPImageLoad::BMPImageLoad(const std::string& path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Failed to open file");
  }

  file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
  file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

  if (file_header.bfType != 0x4D42) {
    throw std::runtime_error("File isn't a BMP");
  }
  if (info_header.biBitCount != 24) {
    throw std::runtime_error("Only 24-bit BMP supported");
  }
  if (info_header.biCompression != 0) {
    throw std::runtime_error("Only uncompressed BMP supported");
  }

  width = info_header.biWidth;
  height = std::abs(info_header.biHeight);
  row_stride = (width * COLORS + COLORS) & (~COLORS);

  pixels.resize(row_stride * height);
  file.seekg(file_header.bfOffBits);
  file.read(reinterpret_cast<char*>(pixels.data()), pixels.size());
  file.close();
}

const BITMAPFILEHEADER& BMPImageLoad::GetFileHeader() const {
  return file_header;
}

const BITMAPINFOHEADER& BMPImageLoad::GetInfoHeader() const {
  return info_header;
}

const std::vector<BYTE>& BMPImageLoad::GetPixels() const { return pixels; }

const LONG& BMPImageLoad::GetWidth() const { return width; }

const LONG& BMPImageLoad::GetHeight() const { return height; }

const size_t& BMPImageLoad::GetRowStride() const { return row_stride; }
} // namespace ImageProcessing