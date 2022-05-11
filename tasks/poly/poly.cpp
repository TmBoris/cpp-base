#include "poly.h"
#include <cmath>

Poly::Poly(const std::vector<int64_t>& coefs) {
    for (size_t i = 0; i < coefs.size(); ++i) {
        if (coefs[i] != 0) {
            poly_[i] = coefs[i];
        }
    }
}
Poly::Poly(const std::vector<std::pair<int64_t, int64_t>>& m) {
    for (const auto& x : m) {
        poly_[x.first] = x.second;
    }
}
int64_t Poly::operator()(int64_t number) const {
    int64_t result = 0;
    for (auto x : poly_) {
        result += powl(number, x.first) * x.second;
    }
    return result;
}
bool Poly::operator==(const Poly& other) const {
    return poly_ == other.poly_;
}
bool Poly::operator!=(const Poly& m) const {
    return !(*this == m);
}
Poly Poly::operator*(const Poly& poly) const {
    std::map<int64_t, int64_t> tmp;
    for (auto i = poly.poly_.begin(); i != poly.poly_.end(); ++i) {
        for (auto j = poly_.begin(); j != poly_.end(); ++j) {
            tmp[i->first + j->first] += i->second * j->second;
        }
    }
    Poly result;
    for (auto& x : tmp) {
        result.poly_[x.first] = x.second;
    }
    return result;
}
Poly Poly::operator+(const Poly& poly) const {
    Poly result = *this;
    for (auto& x : poly.poly_) {
        result.poly_[x.first] += x.second;
    }
    for (auto it = result.poly_.begin(); it != result.poly_.end();) {
        if (it->second == 0) {
            it = result.poly_.erase(it);
        } else {
            ++it;
        }
    }
    return result;
}
Poly Poly::operator-() const {
    Poly tmp;
    tmp.poly_[0] = -1;
    return *this * tmp;
}
Poly Poly::operator-(const Poly& poly) const {
    return *this + -poly;
}
void Poly::operator-=(const Poly& poly) {
    *this = *this - poly;
}
void Poly::operator+=(const Poly& poly) {
    *this = *this + poly;
}
std::ostream& operator<<(std::ostream& out, const Poly& poly) {
    if (poly.poly_.empty()) {
        out << "y = 0";
    } else {
        std::string for_out;
        size_t counter = 0;
        for (const auto& x : poly.poly_) {
            if (x.first == 0) {
                for_out += std::to_string(x.second);
            } else {
                for_out += std::to_string(x.first) + "^x" + std::to_string(x.second);
            }
            if (counter != poly.poly_.size() - 1) {
                for_out += " + ";
            }
            counter++;
        }
        out << "y = ";
        for (size_t i = for_out.size() - 1; i != 0; --i) {
            out << for_out[i];
        }
        out << for_out[0];
    }
    return out;
}
