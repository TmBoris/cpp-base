#pragma once

#include "topology.h"

class PlanarTopology : public Topology {
public:
    PlanarTopology(const std::vector<std::vector<bool>>& v);
    virtual std::vector<Point> GetNeighbours(const Point& point) const final;
};
