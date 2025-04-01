#include "../include/Controller.hpp"
#include "../include/Filters.hpp"

#include <iostream>
#include <unordered_map>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

namespace ImageProcessing {
static std::vector<std::string> split(const std::string& s, char del) {
  std::vector<std::string> result;
  size_t start = 0;
  size_t end = s.find(del, start);

  while (end != std::string::npos) {
    result.push_back(s.substr(start, end - start));
    start = end + 1;
    end = s.find(del, start);
  }
  result.push_back(s.substr(start));

  return result;
}

Controller::Controller(int argc, char* argv[]) {
  ParseArgs(argc, argv);
  ValidateFilters(filters);
  treminal_width = TerminalWidth();
}

int Controller::TerminalWidth() {
  int consoleWidth = 0;

#ifdef _WIN32
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hConsole == INVALID_HANDLE_VALUE) {
    std::cerr << "Error receiving the console handle" << std::endl;
    return;
  }
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
    std::cerr << "Error getting information about the console" << std::endl;
    return;
  }
  consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  consoleWidth = w.ws_col;
#endif
  return consoleWidth;
}

void Controller::ParseArgs(int argc, char* argv[]) {
  if (argc < 3) {
    PrintHelp();
    return;
  }
  std::string input_file = argv[1];
  std::string output_file = argv[2];

  Controller::ValidateFilesNames(input_file, output_file);

  input_image = BMPImage(BMPImageLoad(argv[1]), argv[2]);

  for (int i = 3; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg[0] == '-') {
      arg.erase(arg.begin());
      filters.push_back({arg, {}});
    } else {
      if (filters.empty()) {
        throw std::invalid_argument("Unexpected parameter: " + arg);
      }
      filters.back().params.push_back(arg);
    }
  }
}

void Controller::ApplyFilterCrop(int width, int height) {
  CropFilter crop(width, height);
  crop.Apply(input_image);
  std::cout << std::string(treminal_width, '=') << '\n'
            << "Crop Filter was applyed\n"
            << std::string(treminal_width, '=') << '\n';
}

void Controller::ApplyFilterGs() {
  GrayscaleFilter gs;
  gs.Apply(input_image);
  std::cout << std::string(treminal_width, '=') << '\n'
            << "Crayscale Filter was applyed\n"
            << std::string(treminal_width, '=') << '\n';
}

void Controller::ApplyFilterNeg() {
  NegativeFilter neg;
  neg.Apply(input_image);
  std::cout << std::string(treminal_width, '=') << '\n'
            << "Negative Filter was applyed\n"
            << std::string(treminal_width, '=') << '\n';
}

void Controller::ApplyFilterSharp() {
  SharpFilter sharp;
  sharp.Apply(input_image);
  std::cout << std::string(treminal_width, '=') << '\n'
            << "Sharp Filter was applyed\n"
            << std::string(treminal_width, '=') << '\n';
}

void Controller::ApplyFilterEdge(int threshold) {
  EdgeDetectionFilter edge(threshold);
  edge.GrayscaleFilter::Apply(input_image);
  edge.SharpFilter::Apply(input_image);
  std::cout << std::string(treminal_width, '=') << '\n'
            << "Edge Detection Filter with threshold = " << threshold
            << " was applyed\n"
            << std::string(treminal_width, '=') << '\n';
}

void Controller::ApplyFilterBlur(int sigma) {
  GaussianBlurFilter gaus(sigma);
  gaus.Apply(input_image);
  std::cout << std::string(treminal_width, '=') << '\n'
            << "Gaussian Blur Filter with sigma = " << sigma << " was applyed\n"
            << std::string(treminal_width, '=') << '\n';
}

void Controller::ApplyFilterMosaic(int block_size) {
  MosaicFilter mosaic(block_size);
  mosaic.Apply(input_image);
  std::cout << std::string(treminal_width, '=') << '\n'
            << "Mosaic Filter with pixel size = " << block_size
            << " was applyed\n"
            << std::string(treminal_width, '=') << '\n';
}

void Controller::ApllyFilterRetro() {
  RetroFilter retro;
  retro.Apply(input_image);
  std::cout << std::string(treminal_width, '=') << '\n'
            << "Retro Filter was applyed\n"
            << std::string(treminal_width, '=') << '\n';
}

void Controller::ApplyFilterMirror() {
  MirrorFilter mirror;
  mirror.Apply(input_image);
  std::cout << std::string(treminal_width, '=') << '\n'
            << "Mirror Filter was applyed\n"
            << std::string(treminal_width, '=') << '\n';
}

void Controller::ValidateFilesNames(const std::string& input_file,
                                    const std::string& output_file) {
  bool check_validate_input_file =
      (split(input_file, '.').size() != 2 ? false : true);
  bool check_validate_output_file =
      (split(output_file, '.').size() != 2 ? false : true);
  if (!check_validate_input_file && !check_validate_output_file) {
    Controller::PrintHelp();
    throw std::invalid_argument("invalid arguments for input and output files");
  }
  if (!check_validate_input_file) {
    Controller::PrintHelp();
    throw std::invalid_argument("invalid arguments for input file");
  }
  if (!check_validate_output_file) {
    Controller::PrintHelp();
    throw std::invalid_argument("invalid arguments for output file");
  }
}

void Controller::ValidateFilters(const std::vector<FilterInfo>& filters) {
  static const std::unordered_map<std::string, size_t> param_counts = {
      {"crop", 2}, {"gs", 0},     {"neg", 0},   {"sharp", 0}, {"edge", 1},
      {"blur", 1}, {"mosaic", 1}, {"retro", 0}, {"mirror", 0}};

  for (const auto& filter : filters) {
    auto it = param_counts.find(filter.name);
    if (it == param_counts.end()) {
      throw std::invalid_argument("Unknown filter: " + filter.name);
    }
    if (filter.params.size() != it->second) {
      throw std::invalid_argument("Invalid parameters for filter: " +
                                  filter.name);
    }
  }
}

void Controller::PrintHelp() {
  std::cout << "Usage: image_processor <input.bmp> <output.bmp> [filters...]\n"
            << "Available filters:\n"
            << "  -crop   <width> <height> Crop image\n"
            << "  -gs                       Grayscale\n"
            << "  -neg                      Negative\n"
            << "  -sharp                    Sharpening\n"
            << "  -edge   <threshold>       Edge detection\n"
            << "  -blur   <sigma>           Gaussian blur\n"
            << "  -mosaic <pixel size>      Mosaic\n"
            << "  -retro                    Retro\n"
            << "  -mirror                   Mirror\n";
}

void Controller::Do() {
  try {
    for (const auto& filter : filters) {
      if (filter.name == "crop") {
        ApplyFilterCrop(std::stoi(filter.params[0]),
                        std::stoi(filter.params[1]));
      } else if (filter.name == "gs") {
        ApplyFilterGs();
      } else if (filter.name == "neg") {
        ApplyFilterNeg();
      } else if (filter.name == "sharp") {
        ApplyFilterSharp();
      } else if (filter.name == "edge") {
        ApplyFilterEdge(std::stoi(filter.params[0]));
      } else if (filter.name == "blur") {
        ApplyFilterBlur(std::stoi(filter.params[0]));
      } else if (filter.name == "mosaic") {
        if (std::stoi(filter.params[0]) <= 0) {
          throw std::invalid_argument("invalid parameters for filter: " +
                                      filter.name);
        }
        ApplyFilterMosaic(std::stoi(filter.params[0]));
      } else if (filter.name == "retro") {
        ApllyFilterRetro();
      } else if (filter.name == "mirror") {
        ApplyFilterMirror();
      }
    }
  } catch (...) {
    throw;
  }
}
} // namespace ImageProcessing