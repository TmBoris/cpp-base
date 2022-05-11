#pragma once

#include <string_view>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>

class SearchEngine {
public:
    void BuildIndex(std::string_view text);
    std::vector<std::string_view> Search(std::string_view query, size_t results_count) const;

private:
    void RoutinesWithString(std::vector<std::string>& vector_for_strings, size_t start);
    void Splitting(std::string_view& str, std::vector<std::string>& v) const;

    std::vector<std::vector<std::string>> text_in_vector_;
    std::vector<size_t> beginning_of_strings_;
    std::vector<std::unordered_map<std::string, double>> tf_for_each_string_;

    size_t counter_of_strings_ = 0;
    std::string_view curr_str_;
    size_t words_in_string_ = 0;

    std::string_view index_;
};
