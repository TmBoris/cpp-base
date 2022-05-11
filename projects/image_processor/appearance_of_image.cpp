#include "appearance_of_image.h"

Image::Image(size_t width, size_t height) {
    width_ = width;
    height_ = height;
    store_.resize(height);
    for (size_t i = 0; i < height_; ++i) {
        store_[i].resize(width_);
    }
}
Color Image::GetColor(size_t x, size_t y) {
    return store_[y][x];
}
void Image::SetColor(size_t x, size_t y, const Color& new_color) {
    store_[y][x] = new_color;
}
Image::Image() {
    width_ = 0;
    height_ = 0;
    store_ = {{}};
}
Image::~Image() {
}
size_t Image::GetWidth() {
    return width_;
}
size_t Image::GetHeight() {
    return height_;
}
void Image::Resize(size_t width, size_t height) {
    width_ = width;
    height_ = height;
    store_.erase(store_.begin(), store_.end() - height);
    for (auto& x : store_) {
        x.resize(width);
    }
}
Image::Image(const Image& image) {
    store_ = image.store_;
    width_ = image.width_;
    height_ = image.height_;
}
Image& Image::operator=(Image&& other) {
    std::swap(store_, other.store_);
    width_ = other.width_;
    height_ = other.height_;
    return *this;
}
