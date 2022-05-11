#include "world.h"

World::World(const Topology& topology, const Point& start, const Point& end) {
    start_ = start;
    curr_ = start;
    end_ = end;
    prep_field_.resize(topology.GetField().size());
    for (size_t i = 0; i < topology.GetField().size(); ++i) {
        prep_field_[i].resize(topology.GetField()[0].size());
        for (size_t j = 0; j < topology.GetField()[0].size(); ++j) {
            if (!topology.GetField()[i][j]) {
                std::unordered_map<Point, Topology::Distance> tmp;
                Point p;
                p.x = j;
                p.y = i;
                for (const auto& x : topology.GetNeighbours(p)) {
                    tmp[x] = topology.MeasureDistance(x, end_);
                }
                prep_field_[i][j] = tmp;
            }
        }
    }
}
const Point& World::GetStart() const {
    return start_;
}
const Point& World::GetEnd() const {
    return end_;
}
const Point& World::GetCurrentPosition() const {
    return curr_;
}
void World::Move(const Point& to) {
    bool flag = true;
    for (const auto& [key, value] : prep_field_[curr_.y][curr_.x]) {
        if (key == to) {
            curr_.x = to.x;
            curr_.y = to.y;
            flag = false;
            break;
        }
    }
    if (flag) {
        throw IllegalMoveException();
    }
}
std::unordered_map<Point, Topology::Distance> World::Lookup() const {
    return prep_field_[curr_.y][curr_.x];
}
