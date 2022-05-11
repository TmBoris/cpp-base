#pragma once

#include <forward_list>
#include <string>
#include <vector>

using Value = std::string;
using Iterator = std::forward_list<std::string>::const_iterator;
using ZippedPair = std::pair<const Value&, const Value&>;

class Zipped {
private:
    Iterator begin1_;
    Iterator begin2_;
    Iterator for_iteration1_;
    Iterator for_iteration2_;
    Iterator end1_;
    Iterator end2_;
public:
    Zipped(Iterator begin1, Iterator end1, Iterator begin2, Iterator end2);
    Zipped& begin();
    Zipped& end();
    bool operator!=(Zipped& other) const;
    Zipped& operator++();
    ZippedPair operator*() const;
};

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);
