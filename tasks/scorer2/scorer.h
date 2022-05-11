#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

enum class EventType {
    CheckFailed,
    CheckSuccess,
    MergeRequestOpen,
    MergeRequestClosed,
};

using StudentName = std::string;
using TaskName = std::string;

struct Event {
    StudentName student_name;
    TaskName task_name;
    time_t time;
    EventType event_type;
};

using Events = std::vector<Event>;
using ScoreTable = std::map<StudentName, std::set<TaskName>>;

class Scorer {
public:
    void OnCheckFailed(const StudentName& student_name, const TaskName& task_name);
    void OnCheckSuccess(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name);
    void Reset();

    ScoreTable GetScoreTable() const;

private:
    std::map<StudentName, std::map<TaskName, std::pair<bool, bool>>> student_tasks_;
};
