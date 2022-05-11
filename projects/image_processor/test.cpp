#include <catch.hpp>

#include "appearance_of_image.h"
#include "reading_of_bmp.h"
#include "exporting_of_bmp.h"
#include "Grayscale.h"
#include "Crop.h"
#include "Negative.h"
#include "sharpening.h"
#include "edge_detection.h"
#include "gauss_filter.h"
#include "emboss_filter.h"

TEST_CASE("Image") {
    Image im;
    REQUIRE(im.GetWidth() == 0);
    REQUIRE(im.GetHeight() == 0);

    Image image(3, 3);
    Color color;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            color.red = i + j;
            image.SetColor(i, j, color);
        }
    }

    color.red = 0;
    REQUIRE(image.GetColor(0, 0) == color);

    color.red = 4;
    REQUIRE(image.GetColor(2, 2) == color);
}

TEST_CASE("Importing, exporting") {
    Image picture = Import::import("../projects/image_processor/examples/example.bmp");
    Export::exporting("../projects/image_processor/examples/exported_example.bmp", picture);
    Image picture2 = Import::import("../projects/image_processor/examples/exported_example.bmp");
    for (size_t i = 0; i < picture.GetHeight(); ++i) {
        for (size_t j = 0; j < picture.GetWidth(); ++j) {
            REQUIRE(picture.GetColor(j, i) == picture2.GetColor(j, i));
        }
    }
}


TEST_CASE("Mistakes, because of no such file in the directory") {
    bool flag = false;
    try {
        Image picture = Import::import("../projects/image_processor/examples/file.bmp");
    } catch (std::exception&) {
        flag = true;
    }
    REQUIRE(flag);
}

TEST_CASE("Not a BMP file") {
    Image image;
    bool flag = false;
    try {
        Image picture = Import::import("../projects/image_processor/examples/giraffe.jpg");
    } catch (std::exception&) {
        flag = true;
    }
    REQUIRE(flag);
}

TEST_CASE("Crop") {
    Image picture = Import::import("../projects/image_processor/examples/example.bmp");
    Image picture2 = Import::import("../projects/image_processor/examples/penguin.bmp");
    CropFilter filter(100, 100);
    filter.Apply(picture);
    filter.Apply(picture2);
    REQUIRE(picture.GetWidth() == picture2.GetWidth());
    REQUIRE(picture.GetHeight() == picture2.GetHeight());
    Image for_check = Import::import("../projects/image_processor/examples/example.bmp");
    for (size_t i = 0; i < 100; ++i) {
        for (size_t j = 0; j < 100; ++j) {
            REQUIRE(picture.GetColor(j, i).red == for_check.GetColor(j, for_check.GetHeight() - 100 + i).red);
            REQUIRE(picture.GetColor(j, i).green == for_check.GetColor(j, for_check.GetHeight() - 100 + i).green);
            REQUIRE(picture.GetColor(j, i).blue == for_check.GetColor(j, for_check.GetHeight() - 100 + i).blue);
        }
    }
}

TEST_CASE("Grayscale") {
    Image picture = Import::import("../projects/image_processor/examples/example.bmp");
    GrayscaleFilter filter;
    filter.Apply(picture);
    Image for_check = Import::import("../projects/image_processor/examples/ideal_grayscale.bmp");
    for (size_t i = 0; i < picture.GetHeight(); ++i) {
        for (size_t j = 0; j < picture.GetWidth(); ++j) {
            REQUIRE(picture.GetColor(j, i).red - for_check.GetColor(j, i).red < 1);
            REQUIRE(picture.GetColor(j, i).green - for_check.GetColor(j, i).green < 1);
            REQUIRE(picture.GetColor(j, i).blue - for_check.GetColor(j, i).blue < 1);
        }
    }

}

TEST_CASE("Negative") {
    Image picture = Import::import("../projects/image_processor/examples/example.bmp");
    NegativeFilter filter;
    filter.Apply(picture);
    Image for_check = Import::import("../projects/image_processor/examples/ideal_negative.bmp");
    for (size_t i = 0; i < picture.GetHeight(); ++i) {
        for (size_t j = 0; j < picture.GetWidth(); ++j) {
            REQUIRE(picture.GetColor(j, i) == for_check.GetColor(j, i));
        }
    }
}

TEST_CASE("Sharpening") {
    Image picture = Import::import("../projects/image_processor/examples/example.bmp");
    SharpeningFilter filter;
    filter.Apply(picture);
    Image for_check = Import::import("../projects/image_processor/examples/ideal_sharp.bmp");
    for (size_t i = 0; i < picture.GetHeight(); ++i) {
        for (size_t j = 0; j < picture.GetWidth(); ++j) {
            REQUIRE(for_check.GetColor(j, i).red - picture.GetColor(j, i).red < 1);
            REQUIRE(for_check.GetColor(j, i).green - picture.GetColor(j, i).green < 1);
            REQUIRE(for_check.GetColor(j, i).blue - picture.GetColor(j, i).blue < 1);

        }
    }
}

TEST_CASE("Edge_Detection") {
    Image picture = Import::import("../projects/image_processor/examples/example.bmp");
    EdgeDetectionFilter filter(10);
    filter.Apply(picture);
    Color col(0, 0, 0);
    for (size_t i = 0; i < picture.GetHeight(); ++i) {
        for (size_t j = 0; j < picture.GetWidth(); ++j) {
            REQUIRE(picture.GetColor(j, i) == col);
        }
    }

    Image picture2 = Import::import("../projects/image_processor/examples/example.bmp");
    EdgeDetectionFilter filter2(-10);
    filter2.Apply(picture2);
    Color col2(255, 255, 255);
    for (size_t i = 0; i < picture2.GetHeight(); ++i) {
        for (size_t j = 0; j < picture2.GetWidth(); ++j) {
            REQUIRE(picture2.GetColor(j, i) == col2);
        }
    }
}

TEST_CASE("Emboss") {
    Image picture = Import::import("../projects/image_processor/examples/example.bmp");
    EmbossFilter filter;
    filter.Apply(picture);
    Image for_check = Import::import("../projects/image_processor/examples/ideal_emboss.bmp");
    for (size_t i = 0; i < picture.GetHeight(); ++i) {
        for (size_t j = 0; j < picture.GetWidth(); ++j) {
            REQUIRE(for_check.GetColor(j, i).red - picture.GetColor(j, i).red < 1);
            REQUIRE(for_check.GetColor(j, i).green - picture.GetColor(j, i).green < 1);
            REQUIRE(for_check.GetColor(j, i).blue - picture.GetColor(j, i).blue < 1);
        }
    }
}