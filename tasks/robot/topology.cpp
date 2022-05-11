#include "topology.h"

Topology::Topology(const std::vector<std::vector<bool>>& v) : Field(v) {
}
Topology::Distance Topology::MeasureDistance(const Point& from, const Point& to) const {
    if (from == to) {
        return 0;
    }
    Topology::Distance res = UNREACHABLE;
    std::deque<std::pair<Point, Topology::Distance>> deque;
    std::unordered_set<Point> s;
    deque.push_back(std::make_pair(from, 0));
    while (!deque.empty()) {
        Point p = deque.front().first;
        Topology::Distance len = deque.front().second;
        deque.pop_front();
        std::vector<Point> v = GetNeighbours(p);
        for (auto& x : v) {
            if (!s.contains(x)) {
                if (x == to) {
                    return len + 1;
                }
                deque.push_back(std::make_pair(x, len + 1));
                s.insert(x);
            }
        }
    }
    return res;
}
std::vector<std::vector<bool>> Topology::GetField() const {
    return field_;
}
const Topology::Distance Topology::UNREACHABLE;
