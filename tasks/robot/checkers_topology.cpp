#include "checkers_topology.h"

CheckersTopology::CheckersTopology(const std::vector<std::vector<bool>>& v) : Topology(v) {
}
std::vector<Point> CheckersTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> ans;
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            if (0 <= i + int(point.x) && i + int(point.x) < int(field_[0].size()) && 0 <= int(point.y) + j &&
                int(point.y) + j < int(field_.size()) && !field_[point.y + j][point.x + i]) {
                Point tmp;
                tmp.x = point.x + i;
                tmp.y = point.y + j;
                ans.push_back(tmp);
            }
        }
    }
    std::deque<Point> deque;
    std::unordered_set<Point> s;
    deque.push_back(point);
    while (!deque.empty()) {
        Point p = deque.front();
        deque.pop_front();
        if (!s.contains(p)) {
            for (int i = -1; i <= 1; i += 2) {
                for (int j = -1; j <= 1; j += 2) {
                    if (0 <= 2 * i + int(p.x) && 2 * i + int(p.x) < int(field_[0].size()) && 0 <= int(p.y) + 2 * j &&
                        int(p.y) + 2 * j < int(field_.size()) && field_[p.y + j][p.x + i] &&
                        !field_[p.y + 2 * j][p.x + 2 * i]) {
                        Point tmp;
                        tmp.x = p.x + 2 * i;
                        tmp.y = p.y + 2 * j;
                        if (!s.contains(tmp)) {
                            deque.push_back(tmp);
                            ans.push_back(tmp);
                        }
                    }
                }
            }
            s.insert(p);
        }
    }
    return ans;
}
