#pragma once

#include "appearance_of_image.h"
#include "filter.h"
#include "limits.h"

class NegativeFilter : public Filter {
public:
    void Apply(Image& image) final;
    virtual ~NegativeFilter();
};
