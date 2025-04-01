#include "../include/BMPImage.hpp"
#include "../include/BMPImageSave.hpp"

constexpr uint32_t COLORS = 3;
namespace ImageProcessing {
Pixel::Pixel(BYTE blue, BYTE green, BYTE red)
    : blue(blue),
      green(green),
      red(red) {}

BMPImage::BMPImage(const BMPImageLoad& load_image)
    : pixels(load_image.GetPixels()),
      width(load_image.GetWidth()),
      height(load_image.GetHeight()),
      row_stride(load_image.GetRowStride()) {}

BMPImage::BMPImage(const BMPImageLoad& load_image, const std::string& out_path)
    : pixels(load_image.GetPixels()),
      width(load_image.GetWidth()),
      height(load_image.GetHeight()),
      row_stride(load_image.GetRowStride()),
      out_path(out_path) {}

const LONG& BMPImage::GetWidth() const noexcept { return width; }

const LONG& BMPImage::GetHeight() const noexcept { return height; }

void BMPImage::SetWidth(LONG new_width) noexcept {
  width = new_width;
  row_stride = (width * COLORS + COLORS) & (~COLORS);
  pixels.resize(row_stride * height);
}

void BMPImage::SetHeight(LONG new_height) noexcept {
  height = new_height;
  pixels.resize(row_stride * height);
}

const size_t& BMPImage::GetRowStride() const { return row_stride; }

const std::vector<BYTE>& BMPImage::GetPixels() const noexcept { return pixels; }

Pixel BMPImage::GetPixel(int x, int y) const {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    throw std::out_of_range("Invalid coordinates");
  }
  const size_t offset = y * row_stride + x * 3;
  return {pixels[offset], pixels[offset + 1], pixels[offset + 2]};
}

void BMPImage::SetPixel(int x, int y, Pixel p) {
  size_t offset = y * row_stride + x * 3;
  pixels[offset] = p.blue;
  pixels[offset + 1] = p.green;
  pixels[offset + 2] = p.red;
}

BMPImage::~BMPImage() {
  if (out_path != "") {
    BMPImageSave image(out_path);
    image.SetHeight(height);
    image.SetWidth(width);
    image.SetPixels(pixels);
    image.Save();
  }
}
} // namespace ImageProcessing