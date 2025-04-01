#include <exception>
#include <iostream>

#include "include/Controller.hpp"

signed main(int argc, char* argv[]) {
  try {
    ImageProcessing::Controller(argc, argv).Do();
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}