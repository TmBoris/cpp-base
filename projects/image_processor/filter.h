#pragma once

#include "appearance_of_image.h"

class Filter {
public:
    virtual void Apply(Image& image) = 0;
    virtual ~Filter() = default;
};

