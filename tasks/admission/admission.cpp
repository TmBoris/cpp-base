#include "admission.h"
#include <tuple>
#include <iostream>

bool Comp(const Applicant* applicant1, const Applicant* applicant2) {
    if (applicant1->points == applicant2->points) {
        return (std::tie(applicant1->student.birth_date.year, applicant1->student.birth_date.month,
                         applicant1->student.birth_date.day, applicant1->student.name) <
                std::tie(applicant2->student.birth_date.year, applicant2->student.birth_date.month,
                         applicant2->student.birth_date.day, applicant2->student.name));
    } else {
        return applicant1->points > applicant2->points;
    }
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    AdmissionTable ans;
    std::vector<const Applicant*> v;
    for (const auto& it : applicants) {
        v.push_back(&it);
    }
    std::unordered_map<std::string, size_t> free;
    for (auto x : universities) {
        free[x.name] = x.max_students;
    }
    std::sort(v.begin(), v.end(), Comp);
    for (const auto& applicant : v) {
        for (auto university : applicant->wish_list) {
            if (free[university] > 0) {
                free[university]--;
                ans[university].push_back(&applicant->student);
                break;
            }
        }
    }
    return ans;
}