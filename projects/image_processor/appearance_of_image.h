#pragma once

#include <vector>
#include "Color.h"


class Image {
    std::vector<std::vector<Color>> store_;
    size_t width_;
    size_t height_;
public:
    Image();
    Image(size_t width, size_t height);
    Image(const Image& image);
    ~Image();

    Color GetColor(size_t x, size_t y);
    void SetColor(size_t x, size_t y, const Color& new_color);

    size_t GetWidth();
    size_t GetHeight();

    void Resize(size_t width, size_t height);

    Image& operator=(Image&& other);
};