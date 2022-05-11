#pragma once

#include "appearance_of_image.h"
#include "filter.h"

class GrayscaleFilter : public virtual Filter {
public:
    virtual void Apply(Image& image) override;
    virtual ~GrayscaleFilter();
};
