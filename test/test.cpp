#define CATCH_CONFIG_MAIN

#include <string>

#include "../include/BMPImage.hpp"
#include "../include/BMPImageLoad.hpp"
#include "../include/Filters.hpp"
#include "../test/catch/header/catch.hpp"

using namespace ImageProcessing;

TEST_CASE("Blur Filter", "[filters]") {
  BMPImage img(BMPImageLoad("../test/input_images/medved.bmp"), "../test/temp.bmp");
  BMPImage true_output_ing(BMPImageLoad("../test/output_images/filter_blur_4.bmp"));
  GaussianBlurFilter filter(4);

  SECTION("Blur") {
    filter.Apply(img);
    for (LONG x = 0; x < img.GetWidth() / 2; ++x) {
      for (LONG y = 0; y < img.GetHeight() / 2; ++y) {
        Pixel p = img.GetPixel(x, y);
        Pixel expected = true_output_ing.GetPixel(x, y);
        REQUIRE(p.red == expected.red);
        REQUIRE(p.green == expected.green);
        REQUIRE(p.blue == expected.blue);
      }
    }
  }
}

TEST_CASE("Crop Filter", "[filters]") {
  BMPImage img(BMPImageLoad("../test/input_images/medved.bmp"), "../test/temp.bmp");
  BMPImage true_output_ing(
      BMPImageLoad("../test/output_images/filter_crop_width_100_height_100.bmp"));
  CropFilter filter(100, 100);

  SECTION("Crop") {
    filter.Apply(img);
    for (LONG x = 0; x < img.GetWidth() / 2; ++x) {
      for (LONG y = 0; y < img.GetHeight() / 2; ++y) {
        Pixel p = img.GetPixel(x, y);
        Pixel expected = true_output_ing.GetPixel(x, y);
        REQUIRE(p.red == expected.red);
        REQUIRE(p.green == expected.green);
        REQUIRE(p.blue == expected.blue);
      }
    }
  }
}

TEST_CASE("Edge Filter", "[filters]") {
  BMPImage img(BMPImageLoad("../test/input_images/medved.bmp"), "../test/temp.bmp");
  BMPImage true_output_ing(BMPImageLoad("../test/output_images/filter_edge_4.bmp"));
  EdgeDetectionFilter filter(4);

  SECTION("Edge") {
    filter.GrayscaleFilter::Apply(img);
    filter.SharpFilter::Apply(img);
    for (LONG x = 0; x < img.GetWidth() / 2; ++x) {
      for (LONG y = 0; y < img.GetHeight() / 2; ++y) {
        Pixel p = img.GetPixel(x, y);
        Pixel expected = true_output_ing.GetPixel(x, y);
        REQUIRE(p.red == expected.red);
        REQUIRE(p.green == expected.green);
        REQUIRE(p.blue == expected.blue);
      }
    }
  }
}

TEST_CASE("Grayscale Filter", "[filters]") {
  BMPImage img(BMPImageLoad("../test/input_images/medved.bmp"), "../test/temp.bmp");
  BMPImage true_output_ing(BMPImageLoad("../test/output_images/filter_grayscale.bmp"));
  GrayscaleFilter filter;

  SECTION("Grayscale") {
    filter.Apply(img);
    for (LONG x = 0; x < img.GetWidth() / 2; ++x) {
      for (LONG y = 0; y < img.GetHeight() / 2; ++y) {
        Pixel p = img.GetPixel(x, y);
        Pixel expected = true_output_ing.GetPixel(x, y);
        REQUIRE(p.red == expected.red);
        REQUIRE(p.green == expected.green);
        REQUIRE(p.blue == expected.blue);
      }
    }
  }
}

TEST_CASE("Mosaic Filter", "[filters]") {
  BMPImage img(BMPImageLoad("../test/input_images/medved.bmp"), "../test/temp.bmp");
  BMPImage true_output_ing(BMPImageLoad("../test/output_images/filter_mosaic_10.bmp"));
  MosaicFilter filter(10);

  SECTION("Mosaic") {
    filter.Apply(img);
    for (LONG x = 0; x < img.GetWidth() / 2; ++x) {
      for (LONG y = 0; y < img.GetHeight() / 2; ++y) {
        Pixel p = img.GetPixel(x, y);
        Pixel expected = true_output_ing.GetPixel(x, y);
        REQUIRE(p.red == expected.red);
        REQUIRE(p.green == expected.green);
        REQUIRE(p.blue == expected.blue);
      }
    }
  }
}

TEST_CASE("Negative Filter", "[filters]") {
  BMPImage img(BMPImageLoad("../test/input_images/medved.bmp"), "../test/temp.bmp");
  BMPImage true_output_ing(BMPImageLoad("../test/output_images/filter_negative.bmp"));
  NegativeFilter filter;

  SECTION("Negative") {
    filter.Apply(img);
    for (LONG x = 0; x < img.GetWidth() / 2; ++x) {
      for (LONG y = 0; y < img.GetHeight() / 2; ++y) {
        Pixel p = img.GetPixel(x, y);
        Pixel expected = true_output_ing.GetPixel(x, y);
        REQUIRE(p.red == expected.red);
        REQUIRE(p.green == expected.green);
        REQUIRE(p.blue == expected.blue);
      }
    }
  }
}

TEST_CASE("Retro Filter", "[filters]") {
  BMPImage img(BMPImageLoad("../test/input_images/medved.bmp"), "../test/temp.bmp");
  BMPImage true_output_ing(BMPImageLoad("../test/output_images/filter_retro.bmp"));
  RetroFilter filter;

  SECTION("Retro") {
    filter.Apply(img);
    for (LONG x = 0; x < img.GetWidth() / 2; ++x) {
      for (LONG y = 0; y < img.GetHeight() / 2; ++y) {
        Pixel p = img.GetPixel(x, y);
        Pixel expected = true_output_ing.GetPixel(x, y);
        REQUIRE(p.red == expected.red);
        REQUIRE(p.green == expected.green);
        REQUIRE(p.blue == expected.blue);
      }
    }
  }
}

TEST_CASE("Sharp Filter", "[filters]") {
  BMPImage img(BMPImageLoad("../test/input_images/medved.bmp"), "../test/temp.bmp");
  BMPImage true_output_ing(BMPImageLoad("../test/output_images/filter_sharp.bmp"));
  SharpFilter filter;

  SECTION("Sharp") {
    filter.Apply(img);
    for (LONG x = 0; x < img.GetWidth() / 2; ++x) {
      for (LONG y = 0; y < img.GetHeight() / 2; ++y) {
        Pixel p = img.GetPixel(x, y);
        Pixel expected = true_output_ing.GetPixel(x, y);
        REQUIRE(p.red == expected.red);
        REQUIRE(p.green == expected.green);
        REQUIRE(p.blue == expected.blue);
      }
    }
  }
}