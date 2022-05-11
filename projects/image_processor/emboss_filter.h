#pragma once

#include "matrix_filter.h"

class EmbossFilter : public MatrixFilter {
public:
    virtual void Apply(Image& image) final;
    EmbossFilter();
    virtual ~EmbossFilter();
};
