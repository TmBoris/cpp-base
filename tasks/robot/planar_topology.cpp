#include "planar_topology.h"
PlanarTopology::PlanarTopology(const std::vector<std::vector<bool>>& v) : Topology(v) {
}
std::vector<Point> PlanarTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> ans;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (abs(i) != abs(j) && 0 <= int(point.x) + i && int(point.x) + i < int(field_[0].size()) &&
                0 <= int(point.y) + j && int(point.y) + j < int(field_.size()) && !field_[point.y + j][point.x + i]) {
                Point tmp;
                tmp.x = point.x + i;
                tmp.y = point.y + j;
                ans.push_back(tmp);
            }
        }
    }
    return ans;
}
