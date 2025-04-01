#pragma once

#include <vector>

#include "BMPImage.hpp"

namespace ImageProcessing {
class Filter {
public:
  Filter() = default;

  virtual void Apply(BMPImage& input) const = 0;

  virtual ~Filter() = default;
};

class CropFilter : public Filter {
public:
  CropFilter(LONG width, LONG height);
  void Apply(BMPImage& input) const override;

private:
  LONG width;
  LONG height;
};

class MirrorFilter : public Filter {
public:
  void Apply(BMPImage& input) const override;
};

class GrayscaleFilter : public Filter {
public:
  void Apply(BMPImage& input) const override;
};

class NegativeFilter : public Filter {
public:
  void Apply(BMPImage& input) const override;
};

class SharpFilter : public Filter {
public:
  SharpFilter(int max_value = 255, int coef = 5);

  void Apply(BMPImage& input) const override;

protected:
  int max_value_ = 255;
  int coef_ = 5;
};

class EdgeDetectionFilter : public SharpFilter, public GrayscaleFilter {
public:
  EdgeDetectionFilter(int param);
};

class GaussianBlurFilter : public Filter {
public:
  GaussianBlurFilter(double sigma);

  void Apply(BMPImage& input) const override;

private:
  double sigma_;

  std::vector<double> GaussianKernel(int size) const;
};

class MosaicFilter : public Filter {
public:
  MosaicFilter(int block_size);

  void Apply(BMPImage& input) const override;

private:
  int block_size_;
};

class RetroFilter : public Filter {
public:
  void Apply(BMPImage& input) const override;
};
} // namespace ImageProcessing