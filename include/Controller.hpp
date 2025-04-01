#pragma once

#include "BMPImage.hpp"

namespace ImageProcessing {
struct FilterInfo {
  std::string name;
  std::vector<std::string> params;
};

class Controller {
public:
  Controller(int argc, char* argv[]);

  int TerminalWidth();

  void ParseArgs(int argc, char* argv[]);

  void ApplyFilterCrop(int width, int height);

  void ApplyFilterGs();

  void ApplyFilterNeg();

  void ApplyFilterSharp();

  void ApplyFilterEdge(int threshold);

  void ApplyFilterBlur(int sigma);

  void ApplyFilterMosaic(int block_size);

  void ApllyFilterRetro();

  void ApplyFilterMirror();

  static void ValidateFilters(const std::vector<FilterInfo>& filters);

  void ValidateFilesNames(const std::string& input_file,
                          const std::string& output_file);

  void PrintHelp();

  void Do();

private:
  BMPImage input_image;
  std::vector<FilterInfo> filters;
  int treminal_width;
};
} // namespace ImageProcessing