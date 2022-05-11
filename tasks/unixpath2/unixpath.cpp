#include "unixpath.h"

void Parsing(const std::string_view& str, std::vector<std::string>& v) {
    bool flag = false;
    size_t tmp;
    std::string s;
    for (size_t ch = 0; ch < str.size(); ++ch) {
        if (str[ch] != '/' && str[ch] != '.' && !flag) {
            tmp = ch;
            flag = true;
        }
        if (ch < str.size() - 1 && str[ch] == '.' && str[ch + 1] == '.') {
            v.push_back(std::string(str.substr(ch, 2)));
        }
        if (str[ch] == '/' && flag) {
            v.push_back(std::string(str.substr(tmp, ch - tmp)));
            flag = false;
        }
        if (ch == str.size() - 1 && flag && str[ch] != '.' && str[ch] != '/') {
            v.push_back(std::string(str.substr(tmp, ch - tmp + 1)));
        }
    }
}

std::string NormalizeAbsolutePath(const std::vector<std::string>& p) {
    std::string ans;
    if (p.empty()) {
        ans += '/';
    }
    for (auto& x : p) {
        ans += '/';
        ans += x;
    }
    return ans;
}

std::string NormalizeRelativePath(const std::vector<std::string>& curr, const std::vector<std::string>& p) {
    std::string ans;
    std::vector<std::string> prepo_for_ans;
    for (auto& x : curr) {
        prepo_for_ans.push_back(x);
    }
    for (auto& x : p) {
        if (x == "..") {
            if (!prepo_for_ans.empty()) {
                prepo_for_ans.pop_back();
            }
        } else {
            prepo_for_ans.push_back(x);
        }
    }
    if (prepo_for_ans.empty()) {
        ans += '/';
    } else {
        for (auto& x : prepo_for_ans) {
            ans += '/';
            ans += x;
        }
    }
    return ans;
}

UnixPath::UnixPath(std::string_view initial_dir) {
    Parsing(initial_dir, initial_dir_);
    Parsing(initial_dir, curr_abs_dir_);
}

void UnixPath::ChangeDirectory(std::string_view path) {
    path_.clear();
    Parsing(path, path_);
    if (path[0] == '/') {
        curr_abs_dir_.clear();
        Parsing(path, curr_abs_dir_);
    } else {
        std::string tmp = NormalizeRelativePath(curr_abs_dir_, path_);
        curr_abs_dir_.clear();
        Parsing(std::string_view(tmp), curr_abs_dir_);
    }
}

std::string UnixPath::GetAbsolutePath() const {
    return NormalizeAbsolutePath(curr_abs_dir_);
}

std::string UnixPath::GetRelativePath() const {
    size_t n = 0;
    for (; n < curr_abs_dir_.size() && n < initial_dir_.size() && curr_abs_dir_[n] == initial_dir_[n]; ++n) {
    }
    std::string ans;
    if (n == curr_abs_dir_.size() && n == initial_dir_.size()) {
        return ".";
    } else if (n != 0) {
        ans += "./";
    }
    for (size_t i = n; i < initial_dir_.size(); ++i) {
        ans += "../";
    }
    for (size_t i = n; i < curr_abs_dir_.size(); ++i) {
        ans += curr_abs_dir_[i];
    }
    return ans;
}
