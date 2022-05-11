#include "word2vec.h"
#include <vector>

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    int64_t maxim = INT64_MIN;
    std::vector<std::string> ans;
    for (size_t i = 1; i < words.size(); i++) {
        int64_t sum = 0;
        for (size_t j = 0; j < vectors[0].size(); j++) {
            sum += vectors[0][j] * vectors[i][j];
        }
        if (sum > maxim) {
            maxim = sum;
            ans.clear();
            ans.push_back(words[i]);
        } else if (sum == maxim) {
            ans.push_back(words[i]);
        }
    }
    return ans;
}
