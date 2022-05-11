#include "unixpath.h"
#include <vector>
#include "string"

void Parsing(std::string_view str, std::vector<std::string_view>& v) {
    bool flag = false;
    size_t tmp;
    std::string s;
    for (size_t ch = 0; ch < str.size(); ++ch) {
        if (str[ch] != '/' && str[ch] != '.' && !flag) {
            tmp = ch;
            flag = true;
        }
        if (str[ch] == '/' && flag) {
            v.push_back(str.substr(tmp, ch - tmp));
            flag = false;
        }
        if (ch == str.size() - 1 && flag && str[ch] != '.' && str[ch] != '/') {
            v.push_back(str.substr(tmp, ch - tmp + 1));
        }
    }
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string ans;
    std::vector<std::string_view> curr;
    std::vector<std::string_view> p;
    Parsing(current_working_dir, curr);
    Parsing(path, p);
    if (path[0] == '/') {
        if (p.empty()) {
            ans += '/';
        }
        for (auto& x : p) {
            ans += '/';
            ans += x;
        }
    } else {
        for (size_t i = 0; i + 1 < path.size(); i++) {
            if (path[i] == '.' && path[i + 1] == '.' && !curr.empty()) {
                curr.pop_back();
            }
        }
        if (curr.empty() && p.empty()) {
            ans += '/';
        }
        for (auto& x : curr) {
            ans += '/';
            ans += x;
        }
        for (auto& x : p) {
            ans += '/';
            ans += x;
        }
    }
    return ans;
}
