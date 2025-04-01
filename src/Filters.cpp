#include "../include/Filters.hpp"

namespace ImageProcessing {
CropFilter::CropFilter(LONG width, LONG height)
    : width(width),
      height(height) {}

void CropFilter::Apply(BMPImage& input) const {
  BMPImage output(input);
  output.SetWidth(std::min(width, input.GetWidth()));
  output.SetHeight(std::min(height, input.GetHeight()));
  for (int y = input.GetHeight() - output.GetHeight(); y < input.GetHeight();
       ++y) {
    for (int x = 0; x < output.GetWidth(); ++x) {
      const Pixel& pixel = input.GetPixel(x, y);
      output.SetPixel(x, y - (input.GetHeight() - output.GetHeight()),
                      {pixel.blue, pixel.green, pixel.red});
    }
  }
  input = output;
}

void MirrorFilter::Apply(BMPImage& input) const {
  BMPImage output(input);
  for (int y = 0; y < output.GetHeight(); ++y) {
    for (int x = output.GetWidth() - 1; x >= 0; --x) {
      const Pixel& pixel = input.GetPixel(x, y);
      output.SetPixel(output.GetWidth() - x, y, {pixel.blue, pixel.green, pixel.red});
    }
  }
  input = output;
}

void GrayscaleFilter::Apply(BMPImage& input) const {
  BMPImage output(input);
  for (int y = 0; y < input.GetHeight(); ++y) {
    for (int x = 0; x < input.GetWidth(); ++x) {
      const Pixel& pixel = input.GetPixel(x, y);
      BYTE gray = 0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue;
      output.SetPixel(x, y, {gray, gray, gray});
    }
  }
  input = output;
}

void NegativeFilter::Apply(BMPImage& input) const {
  BMPImage output(input);
  for (int y = 0; y < input.GetHeight(); ++y) {
    for (int x = 0; x < input.GetWidth(); ++x) {
      const Pixel& pixel = input.GetPixel(x, y);
      output.SetPixel(x, y,
                      {static_cast<BYTE>(255 - pixel.blue),
                       static_cast<BYTE>(255 - pixel.green),
                       static_cast<BYTE>(255 - pixel.red)});
    }
  }
  input = output;
}

SharpFilter::SharpFilter(int max_value, int coef)
    : max_value_(max_value),
      coef_(coef) {}

void SharpFilter::Apply(BMPImage& input) const {
  BMPImage output(input);
  const int filter[3][3] = {{0, -1, 0}, {-1, coef_, -1}, {0, -1, 0}};

  for (int y = 1; y < input.GetHeight() - 1; ++y) {
    for (int x = 1; x < input.GetWidth() - 1; ++x) {
      int red = 0, green = 0, blue = 0;
      for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
          const Pixel& p = input.GetPixel(x + dx, y + dy);
          int weight = filter[dy + 1][dx + 1];
          red += p.red * weight;
          green += p.green * weight;
          blue += p.blue * weight;
        }
      }
      BYTE new_red = std::min(255, std::max(0, red));
      BYTE new_green = std::min(255, std::max(0, green));
      BYTE new_blue = std::min(255, std::max(0, blue));
      if (std::max({new_red, new_blue, new_green}) > max_value_) {
        new_red = 255;
        new_green = 255;
        new_blue = 255;
      } else if (coef_ == 4) {
        new_red = 0;
        new_green = 0;
        new_blue = 0;
      }
      output.SetPixel(x, y, {new_blue, new_green, new_red});
    }
  }
  input = output;
}

EdgeDetectionFilter::EdgeDetectionFilter(int param)
    : SharpFilter(param, 4) {}

GaussianBlurFilter::GaussianBlurFilter(double sigma)
    : sigma_(sigma) {}

std::vector<double> GaussianBlurFilter::GaussianKernel(int size) const {
  std::vector<double> kernel(size);
  double sum = 0.0;
  int half_size = size / 2;

  for (int i = -half_size; i <= half_size; ++i) {
    double value = exp(-(i * i) / (2.0 * sigma_ * sigma_));
    kernel[i + half_size] = value;
    sum += value;
  }

  for (int i = 0; i < size; ++i) {
    kernel[i] /= sum;
  }
  return kernel;
}

void GaussianBlurFilter::Apply(BMPImage& input) const {
  BMPImage output(input);
  int width = input.GetWidth();
  int height = input.GetHeight();
  int kernel_size = static_cast<int>(ceil(3 * sigma_)) * 2 + 1;
  std::vector<double> kernel = GaussianBlurFilter::GaussianKernel(kernel_size);
  int half_kernel_size = kernel_size / 2;

  std::vector<std::vector<double>> temp(height, std::vector<double>(width * 3));

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      double red = 0.0, green = 0.0, blue = 0.0;
      for (int kx = -half_kernel_size; kx <= half_kernel_size; ++kx) {
        int pixelX = std::min(std::max(x + kx, 0), width - 1);
        Pixel p = input.GetPixel(pixelX, y);
        double weight = kernel[kx + half_kernel_size];
        red += p.red * weight;
        green += p.green * weight;
        blue += p.blue * weight;
      }
      temp[y][x * 3] = blue;
      temp[y][x * 3 + 1] = green;
      temp[y][x * 3 + 2] = red;
    }
  }

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      double red = 0.0, green = 0.0, blue = 0.0;
      for (int ky = -half_kernel_size; ky <= half_kernel_size; ++ky) {
        int pixelY = std::min(std::max(y + ky, 0), height - 1);
        double weight = kernel[ky + half_kernel_size];
        blue += temp[pixelY][x * 3] * weight;
        green += temp[pixelY][x * 3 + 1] * weight;
        red += temp[pixelY][x * 3 + 2] * weight;
      }
      output.SetPixel(x, y,
                      {static_cast<BYTE>(blue), static_cast<BYTE>(green),
                       static_cast<BYTE>(red)});
    }
  }
  input = output;
}

MosaicFilter::MosaicFilter(int block_size)
    : block_size_(block_size) {}

void MosaicFilter::Apply(BMPImage& input) const {
  BMPImage output(input);
  int height = input.GetHeight();
  int width = input.GetWidth();

  for (int y = 0; y < height; y += block_size_) {
    int block_height = std::min(block_size_, height - y);
    for (int x = 0; x < width; x += block_size_) {
      int block_width = std::min(block_size_, width - x);

      double red = 0, green = 0, blue = 0;
      for (int dy = 0; dy < block_height; ++dy) {
        for (int dx = 0; dx < block_width; ++dx) {
          const Pixel& p = input.GetPixel(x + dx, y + dy);
          red += p.red;
          green += p.green;
          blue += p.blue;
        }
      }

      int num_pixels = block_width * block_height;
      BYTE avg_red = static_cast<BYTE>(std::round(red / num_pixels));
      BYTE avg_green = static_cast<BYTE>(std::round(green / num_pixels));
      BYTE avg_blue = static_cast<BYTE>(std::round(blue / num_pixels));

      for (int dy = 0; dy < block_height; ++dy) {
        for (int dx = 0; dx < block_width; ++dx) {
          output.SetPixel(x + dx, y + dy, {avg_blue, avg_green, avg_red});
        }
      }
    }
  }
  input = output;
}

void RetroFilter::Apply(BMPImage& input) const {
  BMPImage output(input);
  for (int y = 0; y < input.GetHeight(); ++y) {
    for (int x = 0; x < input.GetWidth(); ++x) {
      const Pixel& p = input.GetPixel(x, y);
      double red = p.red;
      double green = p.green;
      double blue = p.blue;
      BYTE new_red = static_cast<BYTE>(
          std::min(255.0, red * 0.393 + green * 0.769 + blue * 0.189));
      BYTE new_green = static_cast<BYTE>(
          std::min(255.0, red * 0.349 + green * 0.686 + blue * 0.168));
      BYTE new_blue = static_cast<BYTE>(
          std::min(255.0, red * 0.272 + green * 0.534 + blue * 0.131));
      output.SetPixel(x, y, {new_blue, new_green, new_red});
    }
  }
  input = output;
}
} // namespace ImageProcessing