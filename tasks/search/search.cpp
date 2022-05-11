#include "search.h"
#include "unordered_map"
#include "string"
#include "iostream"
#include "cmath"

void Splitting(std::string_view& str, std::vector<std::string>& v) {
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
        new_str = "";
    }
}

void RoutinesWithString(
    std::vector<std::string>& vector_for_strings, std::vector<std::string>& queries,
    std::unordered_map<std::string, double>& tf_of_each_query_in_string, size_t& words_in_string,
    std::unordered_map<std::string, double>& number_of_lines_with_each_query,
    std::vector<std::pair<std::string, std::pair<double, std::pair<size_t, size_t>>>>& for_multipliing_tf_idf,
    size_t start, size_t& counter_of_strings) {
    for (const auto& x : vector_for_strings) {
        for (const auto& q : queries) {
            if (q == x) {
                tf_of_each_query_in_string[q] += (double(1) / words_in_string);
            }
        }
    }
    for (const auto& q : queries) {
        if (tf_of_each_query_in_string.contains(q)) {
            number_of_lines_with_each_query[q]++;
            for_multipliing_tf_idf.push_back(std::make_pair(
                q, std::make_pair(tf_of_each_query_in_string[q], std::make_pair(counter_of_strings, start))));
        }
    }
    counter_of_strings++;
    vector_for_strings.clear();
    tf_of_each_query_in_string.clear();
    words_in_string = 0;
}

bool Comp(std::pair<double, std::pair<size_t, size_t>>& one, std::pair<double, std::pair<size_t, size_t>>& two) {
    if (one.first == two.first) {
        return one.second.first < two.second.first;
    }
    return one.first > two.first;
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::vector<std::string_view> ans;
    std::vector<std::pair<std::string, std::pair<double, std::pair<size_t, size_t>>>> for_multipliing_tf_idf;
    std::vector<std::string> queries;
    Splitting(query, queries);
    std::unordered_map<std::string, double> number_of_lines_with_each_query;
    size_t counter_of_strings = 0;
    std::string_view curr_str;
    if (text.empty()) {
        return {};
    }
    size_t words_in_string = 0;
    if (std::isalpha(text[0])) {
        words_in_string++;
    }
    std::vector<std::string> vector_for_strings;
    std::unordered_map<std::string, double> tf_of_each_query_in_string;
    size_t start = 0;
    size_t end = 0;
    size_t i = 1;
    for (; i < text.size(); ++i) {
        if (std::isalpha(text[i]) && !std::isalpha(text[i - 1])) {
            words_in_string++;
        }
        if (text[i] != '\n' && text[i - 1] == '\n') {
            start = i;
        }
        if (text[i] == '\n') {
            end = i;
            curr_str = text.substr(start, end - start);
            if (!curr_str.empty()) {
                Splitting(curr_str, vector_for_strings);
                RoutinesWithString(vector_for_strings, queries, tf_of_each_query_in_string, words_in_string,
                                   number_of_lines_with_each_query, for_multipliing_tf_idf, start, counter_of_strings);
            }
            start = i + 1;
        }
    }
    end = i;
    curr_str = text.substr(start, end - start);
    if (!curr_str.empty()) {
        Splitting(curr_str, vector_for_strings);
        RoutinesWithString(vector_for_strings, queries, tf_of_each_query_in_string, words_in_string,
                           number_of_lines_with_each_query, for_multipliing_tf_idf, start, counter_of_strings);
    }
    for (auto& x : number_of_lines_with_each_query) {
        x.second = log10(counter_of_strings / x.second);
    }
    std::vector<std::pair<double, std::pair<size_t, size_t>>> for_ans(counter_of_strings + 1,
                                                                      std::make_pair(0, std::make_pair(0, 0)));
    for (auto& x : for_multipliing_tf_idf) {
        for_ans[x.second.second.first].first += (x.second.first * number_of_lines_with_each_query[x.first]);
        for_ans[x.second.second.first].second = x.second.second;
    }
    std::sort(for_ans.begin(), for_ans.end(), Comp);
    size_t begin_of_str = 0;
    for (size_t j = 0; j < for_ans.size() && j < results_count && for_ans[j].first > 0; ++j) {
        begin_of_str = for_ans[j].second.second;
        for (; for_ans[j].second.second < text.size() && text[for_ans[j].second.second] != '\n';
             ++for_ans[j].second.second) {
        }
        ans.push_back(text.substr(begin_of_str, for_ans[j].second.second - begin_of_str));
    }
    return ans;
}
