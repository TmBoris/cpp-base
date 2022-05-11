#pragma once

#include "matrix_filter.h"

class SharpeningFilter : public MatrixFilter {
public:
    virtual void Apply(Image& image) final;
    SharpeningFilter();
    virtual ~SharpeningFilter();
};;
