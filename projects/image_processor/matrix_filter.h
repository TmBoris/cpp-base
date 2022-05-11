#pragma once

#include "filter.h"

class MatrixFilter : public virtual Filter {
public:
    virtual void Apply(Image &image) override;
    MatrixFilter(std::vector<std::vector<double>> v);
    virtual ~MatrixFilter();
protected:
    std::vector<std::vector<double>> FilterMatrix_;
};
