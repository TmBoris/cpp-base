#pragma once

#include <map>
#include <cstdint>
#include <vector>
#include <ostream>

class Poly {
public:
    std::map<int64_t, int64_t> poly_;

public:
    Poly() {
    }
    Poly(const std::vector<int64_t>& coefs);
    Poly(const std::vector<std::pair<int64_t, int64_t>>& m);

    int64_t operator()(int64_t number) const;
    bool operator==(const Poly& other) const;
    bool operator!=(const Poly& m) const;
    Poly operator-(const Poly& poly) const;
    Poly operator+(const Poly& poly) const;
    void operator-=(const Poly& poly);
    void operator+=(const Poly& poly);
    Poly operator*(const Poly& poly) const;
    Poly operator-() const;
    friend std::ostream& operator<<(std::ostream& out, const Poly& poly);
};
