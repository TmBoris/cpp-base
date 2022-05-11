#include "password.h"

const std::size_t MIN_LENGTH = 8;
const std::size_t MAX_LENGTH = 14;

bool ValidatePassword(const std::string& password) {
    std::size_t n = password.length();
    if (n < MIN_LENGTH || n > MAX_LENGTH) {
        return false;
    }
    bool upper_letters = false;
    bool lower_letters = false;
    bool digits = false;
    bool others = false;
    for (std::size_t i = 0; i < n; i++) {
        if (!std::isgraph(password[i])) {
            return false;
        }
        if (std::isupper(password[i])) {
            upper_letters = true;
        } else if (std::islower(password[i])) {
            lower_letters = true;
        } else if (std::isdigit(password[i])) {
            digits = true;
        } else {
            others = true;
        }
    }
    int counter = 0;
    if (upper_letters) {
        counter++;
    }
    if (lower_letters) {
        counter++;
    }
    if (digits) {
        counter++;
    }
    if (others) {
        counter++;
    }
    if (counter < 3) {
        return false;
    }
    return true;
}
