#pragma once

#include "point.h"
#include "field.h"

#include <vector>
#include "deque"
#include "unordered_set"

namespace std {

template <>
struct hash<Point> {
    std::size_t operator()(const Point& p) const {
        return ((p.x * 1000000007) % 997 + (p.y * 9999999967) % 997) % 997;
    }
};
}  // namespace std

class Topology : public Field {
public:
    Topology(const std::vector<std::vector<bool>>& v);

    using Distance = ssize_t;

    virtual std::vector<Point> GetNeighbours(const Point& point) const = 0;
    Distance MeasureDistance(const Point& from, const Point& to) const;

    static const Distance UNREACHABLE = -1;

    std::vector<std::vector<bool>> GetField() const;
};
