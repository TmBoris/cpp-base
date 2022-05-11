#pragma once

#include "matrix_filter.h"
#include "Grayscale.h"

class EdgeDetectionFilter : public MatrixFilter, public GrayscaleFilter {
private:
    double threshold_;
public:
    virtual void Apply(Image& image) final;

    EdgeDetectionFilter(double threshold);
    virtual ~EdgeDetectionFilter();
};