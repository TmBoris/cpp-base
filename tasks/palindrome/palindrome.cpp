#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    std::size_t l = 0;
    std::size_t r = str.size();
    while (r > l + 1) {
        if (str[l] != ' ' && str[r - 1] != ' ') {
            if (str[l] == str[r - 1]) {
                l++;
                r--;
            } else {
                return false;
            }
        } else if (str[l] == ' ') {
            l++;
        } else {
            r--;
        }
    }
    return true;
}
