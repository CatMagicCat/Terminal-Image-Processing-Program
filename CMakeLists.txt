cmake_minimum_required(VERSION 3.11)
project(image_processing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(image_processing_lib STATIC
    src/BMPImage.cpp
    src/BMPImageLoad.cpp
    src/BMPImageSave.cpp
    src/Controller.cpp
    src/Filters.cpp
)

target_include_directories(image_processing_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(image_processing main.cpp)
target_link_libraries(image_processing PRIVATE image_processing_lib)
set_target_properties(image_processing PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(custom_catch STATIC 
    test/catch/catch_main.cpp
)

target_include_directories(custom_catch PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/test/catch/header
)

add_executable(tests EXCLUDE_FROM_ALL test/test.cpp)
target_link_libraries(tests PRIVATE custom_catch image_processing_lib)
set_target_properties(tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test
)

add_custom_target(run_tests
    DEPENDS tests
    COMMAND $<TARGET_FILE:tests>
    COMMENT "Сборка и запуск тестов"
    COMMAND rm ${CMAKE_CURRENT_SOURCE_DIR}/test/temp.bmp
)