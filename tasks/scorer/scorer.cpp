#include "scorer.h"
#include "iostream"

bool Comp(const Event* first, const Event* second) {
    return std::tie(first->student_name, first->task_name, first->time) <
           std::tie(second->student_name, second->task_name, second->time);
}

std::pair<bool, bool> CondCheck(EventType type, bool check, bool merge) {
    switch (type) {
        case EventType::CheckSuccess:
            check = true;
            break;
        case EventType::CheckFailed:
            check = false;
            break;
        case EventType::MergeRequestOpen:
            merge = false;
            break;
        case EventType::MergeRequestClosed:
            merge = true;
            break;
    }
    return std::make_pair(check, merge);
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable ans;
    std::vector<const Event*> v;
    for (const auto& it : events) {
        if (it.time <= score_time) {
            v.push_back(&it);
        }
    }
    if (v.empty()) {
        return ans;
    }
    std::sort(v.begin(), v.end(), Comp);
    std::pair<bool, bool> check_merge = std::make_pair(false, true);
    for (auto i = v.begin(); i != v.end() - 1; ++i) {
        const Event* event = *i;
        const Event* next_event = *(i + 1);
        check_merge = CondCheck(event->event_type, check_merge.first, check_merge.second);
        if (event->student_name != next_event->student_name || event->task_name != next_event->task_name) {
            if (check_merge.first && check_merge.second) {
                ans[event->student_name].insert(event->task_name);
            }
            check_merge.first = false;
            check_merge.second = true;
        }
    }
    const Event* event = *(v.end() - 1);
    check_merge = CondCheck(event->event_type, check_merge.first, check_merge.second);
    if (check_merge.first && check_merge.second) {
        ans[event->student_name].insert(event->task_name);
    }
    return ans;
}