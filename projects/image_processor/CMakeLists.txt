cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        image_processor.cpp
        appearance_of_image.cpp
        exporting_of_bmp.cpp
        reading_of_bmp.cpp
        Color.cpp
        Crop.cpp
        Grayscale.cpp
        Negative.cpp
        matrix_filter.cpp
        sharpening.cpp
        edge_detection.cpp
        gauss_filter.cpp
        emboss_filter.cpp)



add_catch(test_image_processor test.cpp
        appearance_of_image.cpp
        exporting_of_bmp.cpp
        reading_of_bmp.cpp
        Color.cpp
        Crop.cpp
        Grayscale.cpp
        Negative.cpp
        matrix_filter.cpp
        sharpening.cpp
        edge_detection.cpp
        gauss_filter.cpp
        emboss_filter.cpp)