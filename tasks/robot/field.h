#pragma once

#include "vector"
#include "point.h"

class Field {
protected:
    std::vector<std::vector<bool>> field_;

public:
    Field(const std::vector<std::vector<bool>>& v);
};