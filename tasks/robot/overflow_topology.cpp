#include "overflow_topology.h"
OverflowTopology::OverflowTopology(const std::vector<std::vector<bool>>& v) : Topology(v) {
}
std::vector<Point> OverflowTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> ans;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (abs(i) != abs(j)) {
                size_t x = 0;
                size_t y = 0;

                if (i < 0 && point.x == 0) {
                    x = field_[0].size() - 1;
                } else if (i > 0 && point.x == field_[0].size() - 1) {
                    x = 0;
                } else {
                    x = i + point.x;
                }
                if (j < 0 && point.y == 0) {
                    y = field_.size() - 1;
                } else if (j > 0 && point.y == field_.size() - 1) {
                    y = 0;
                } else {
                    y = j + point.y;
                }

                if (!field_[y][x]) {
                    Point new_point;
                    new_point.x = x;
                    new_point.y = y;
                    ans.push_back(new_point);
                }
            }
        }
    }
    return ans;
}
