#pragma once

#include "filter.h"

class GaussFilter : public Filter {
    double sigma_;
public:
    void Apply(Image &image) final;
    GaussFilter(double sigma);
    virtual ~GaussFilter();
};