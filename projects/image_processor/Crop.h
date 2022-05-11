#pragma once

#include "filter.h"

class CropFilter : public Filter {
    size_t width_;
    size_t height_;
public:
    void Apply(Image& image) final;
    CropFilter(size_t width, size_t height);
    virtual ~CropFilter();
};
