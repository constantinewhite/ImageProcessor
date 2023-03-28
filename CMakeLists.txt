project(ImageProcessor)

cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)

file(GLOB filters filters/*.cpp)

add_executable(image_processor
        image_processor.cpp
        application.cpp
        parser.cpp
        image.cpp
        ${filters} filters/pinch_filter.cpp)
