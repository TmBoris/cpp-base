#pragma once

#include "topology.h"

#include <exception>
#include <unordered_map>

class World {
    Point start_;
    Point curr_;
    Point end_;
    std::vector<std::vector<std::unordered_map<Point, Topology::Distance>>> prep_field_;

public:
    class IllegalMoveException : public std::exception {};

    World(const Topology& topology, const Point& start, const Point& end);

    std::unordered_map<Point, Topology::Distance> Lookup() const;

    const Point& GetStart() const;
    const Point& GetEnd() const;
    const Point& GetCurrentPosition() const;

    void Move(const Point& to);
};
