#include "scorer.h"

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    if (student_tasks_.contains(student_name) && student_tasks_[student_name].contains(task_name)) {
        student_tasks_[student_name][task_name].first = false;
    }
}
void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    if (student_tasks_.contains(student_name) && student_tasks_[student_name].contains(task_name)) {
        student_tasks_[student_name][task_name].first = true;
    } else {
        student_tasks_[student_name][task_name] = std::make_pair(true, true);
    }
}
void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    if (student_tasks_.contains(student_name) && student_tasks_[student_name].contains(task_name)) {
        student_tasks_[student_name][task_name].second = false;
    } else {
        student_tasks_[student_name][task_name] = std::make_pair(false, false);
    }
}
void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    if (student_tasks_.contains(student_name) && student_tasks_[student_name].contains(task_name)) {
        student_tasks_[student_name][task_name].second = true;
    }
}
void Scorer::Reset() {
    student_tasks_.clear();
}

ScoreTable Scorer::GetScoreTable() const {
    ScoreTable ans;
    for (auto& student : student_tasks_) {
        for (auto& task : student.second) {
            if (task.second.first && task.second.second) {
                ans[student.first].insert(task.first);
            }
        }
    }
    return ans;
}
