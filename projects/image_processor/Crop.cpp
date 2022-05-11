#include "Crop.h"

void CropFilter::Apply(Image& image) {
    image.Resize(std::min(width_, image.GetWidth()), std::min(height_, image.GetHeight()));
}
CropFilter::CropFilter(size_t width, size_t height) : Filter() {
    width_ = width;
    height_ = height;
}
CropFilter::~CropFilter() {
}
