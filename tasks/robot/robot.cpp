#include "robot.h"
#include <limits.h>

namespace robot {

Path FindPath(World& world) {
    Path ans;
    bool flag = false;
    for (auto& x : world.Lookup()) {
        if (x.second != Topology::UNREACHABLE) {
            flag = true;
            break;
        }
    }
    if (flag || world.GetStart() == world.GetEnd()) {
        ans.push_back(world.GetStart());
        while (!(world.GetCurrentPosition() == world.GetEnd())) {
            Point new_point;
            Topology::Distance maxim = SSIZE_MAX;
            for (const auto& [key, value] : world.Lookup()) {
                if (value < maxim) {
                    new_point = key;
                    maxim = value;
                }
            }
            world.Move(new_point);
            ans.push_back(world.GetCurrentPosition());
        }
    }
    return ans;
}

}  // namespace robot
