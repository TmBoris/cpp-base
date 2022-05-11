#include "tests_checking.h"
#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::vector<std::string> ans;
    ans.reserve(queries.size());
    std::deque<std::string> order;
    for (const auto& student : student_actions) {
        switch (student.side) {
            case Side::Top:
                order.push_front(student.name);
                break;
            case Side::Bottom:
                order.push_back(student.name);
                break;
        }
    }
    for (const auto& j : queries) {
        ans.push_back(order[j - 1]);
    }
    return ans;
}
