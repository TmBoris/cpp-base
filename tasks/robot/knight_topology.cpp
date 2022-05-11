#include "knight_topology.h"
KnightTopology::KnightTopology(const std::vector<std::vector<bool>>& v) : Topology(v) {
}
std::vector<Point> KnightTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> ans;
    for (int i = -2; i <= 2; i += 4) {
        for (int j = -1; j <= 1; j += 2) {
            if (0 <= int(point.x) + i && int(point.x) + i < int(field_[0].size()) && 0 <= int(point.y) + j &&
                int(point.y) + j < int(field_.size()) && !field_[point.y + j][point.x + i]) {
                Point tmp;
                tmp.x = point.x + i;
                tmp.y = point.y + j;
                ans.push_back(tmp);
            }
        }
    }
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -2; j <= 2; j += 4) {
            if (0 <= int(point.x) + i && int(point.x) + i < int(field_[0].size()) && 0 <= int(point.y) + j &&
                int(point.y) + j < int(field_.size()) && !field_[point.y + j][point.x + i]) {
                Point tmp;
                tmp.x = point.x + i;
                tmp.y = point.y + j;
                ans.push_back(tmp);
            }
        }
    }
    return ans;
}
