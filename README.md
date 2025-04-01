# Image Processing Project

Этот проект предоставляет инструменты для обработки изображений. Ниже приведены инструкции для сборки и запуска проекта.

## Сборка проекта

### 1. Клонирование репозитория
Выполните команду, чтобы склонировать репозиторий:
```bash
git clone https://github.com/CatMagicCat/Terminal-Image-Processing-Program.git
cd Terminal-Image-Processing-Program
```

### 2. Компиляция с использованием CMake
Для запуска без тестов выполните команды:
```bash
cmake -S . -B build
cmake --build build
```
Для запуска тестов выполните команды:
```bash
cmake -S . -B build
cmake --build build --target run_tests
```

### 3. Запуск проекта
После успешной сборки исполняемый файл image_processing будет находиться в корневой директории проекта. Для его запуска необходимо выполнить команду:
```bash
./image_processing [flags...]
```
Запуск выполняется с определённым набором флагов. Доступные флаги:
```bash
Usage: image_processor <input.bmp> <output.bmp> [filters...]
Available filters:
  -crop   <width> <height> Crop image
  -gs                       Grayscale
  -neg                      Negative
  -sharp                    Sharpening
  -edge   <threshold>       Edge detection
  -blur   <sigma>           Gaussian blur
  -mosaic <pixel size>      Mosaic
  -retro                    Retro
  -mirror                   Mirror
```
