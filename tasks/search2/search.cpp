#include "search.h"

bool Comp(std::pair<double, size_t>& one, std::pair<double, size_t>& two) {
    if (one.first == two.first) {
        return one.second < two.second;
    }
    return one.first > two.first;
}

void SearchEngine::Splitting(std::string_view& str, std::vector<std::string>& v) const {
    size_t i = 0;
    std::string new_str;
    for (; i < str.size(); ++i) {
        if (std::isalpha(str[i])) {
            new_str += tolower(str[i]);
        }
        if (!std::isalpha(str[i]) && !new_str.empty()) {
            v.push_back(new_str);
            new_str = "";
        }
    }
    if (!new_str.empty()) {
        v.push_back(new_str);
    }
}

void SearchEngine::RoutinesWithString(std::vector<std::string>& vector_for_strings, size_t start) {
    Splitting(curr_str_, vector_for_strings);
    text_in_vector_.push_back(vector_for_strings);
    beginning_of_strings_.push_back(start);
    counter_of_strings_++;
    std::unordered_map<std::string, double> tf_of_each_query_in_string;
    for (const auto& x : vector_for_strings) {
        tf_of_each_query_in_string[x] += (double(1) / words_in_string_);
    }
    tf_for_each_string_.push_back(tf_of_each_query_in_string);
    vector_for_strings.clear();
    words_in_string_ = 0;
}

void SearchEngine::BuildIndex(std::string_view text) {
    index_ = text;
    size_t start = 0;
    size_t end = 0;
    std::vector<std::string> vector_for_strings;
    if (!text.empty()) {
        if (std::isalpha(text[0])) {
            words_in_string_++;
        }
        size_t i = 1;
        for (; i < text.size(); ++i) {
            if (std::isalpha(text[i]) && !std::isalpha(text[i - 1])) {
                words_in_string_++;
            }
            if (text[i] != '\n' && text[i - 1] == '\n') {
                start = i;
            }
            if (text[i] == '\n') {
                end = i;
                curr_str_ = text.substr(start, end - start);
                if (!curr_str_.empty()) {
                    RoutinesWithString(vector_for_strings, start);
                }
                start = i + 1;
            }
        }
        end = i;
        curr_str_ = text.substr(start, end - start);
        if (!curr_str_.empty()) {
            RoutinesWithString(vector_for_strings, start);
        }
    }
}

std::vector<std::string_view> SearchEngine::Search(std::string_view query, size_t results_count) const {
    if (text_in_vector_.empty()) {
        return {};
    }
    std::vector<std::string_view> ans;
    std::vector<std::string> queries;
    Splitting(query, queries);
    std::unordered_map<std::string, double> idf_of_each_query;
    for (const auto& str : text_in_vector_) {
        for (const auto& q : queries) {
            if (std::count(str.begin(), str.end(), q) > 0) {
                idf_of_each_query[q]++;
            }
        }
    }
    std::vector<std::pair<double, size_t>> for_ans;
    double tf_idf;
    size_t counter = 0;
    for (const auto& str : tf_for_each_string_) {
        for (const auto& word : str) {
            if (std::count(queries.begin(), queries.end(), word.first) > 0) {
                tf_idf += word.second * log10(counter_of_strings_ / idf_of_each_query[word.first]);
            }
        }
        for_ans.push_back(std::make_pair(tf_idf, counter));
        counter++;
        tf_idf = 0;
    }
    std::sort(for_ans.begin(), for_ans.end(), Comp);

    size_t begin_of_str = 0;
    size_t end_of_str = 0;
    for (size_t j = 0; j < for_ans.size() && j < results_count && for_ans[j].first > 0; ++j) {
        begin_of_str = beginning_of_strings_[for_ans[j].second];
        end_of_str = begin_of_str;
        for (; end_of_str < index_.size() && index_[end_of_str] != '\n'; ++end_of_str) {
        }
        ans.push_back(index_.substr(begin_of_str, end_of_str - begin_of_str));
    }
    return ans;
}