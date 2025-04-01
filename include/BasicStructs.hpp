#pragma once

#include <cstdint>

namespace ImageProcessing {
using BYTE = uint8_t;
using WORD = uint16_t;
using DWORD = uint32_t;
using LONG = int32_t;

#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER {
  WORD bfType;
  DWORD bfSize;
  WORD bfReserved1;
  WORD bfReserved2;
  DWORD bfOffBits;
} __attribute__((packed)) BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG biWidth;
  LONG biHeight;
  WORD biPlanes;
  WORD biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG biXPelsPerMeter;
  LONG biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} __attribute__((packed)) BITMAPINFOHEADER;
#pragma pack(pop)
} // namespace ImageProcessing