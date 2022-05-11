#pragma once

#include <iterator>


template <typename begin1, typename begin2>
class Zipped {
private:
    begin1 begin1_;
    begin2 begin2_;
    begin1 for_iteration1_;
    begin2 for_iteration2_;
    begin1 end1_;
    begin2 end2_;
public:
    Zipped(begin1 begin_1, begin1 end_1, begin2 begin_2, begin2 end_2) {
        for_iteration1_ = begin_1;
        for_iteration2_ = begin_2;
        begin1_ = begin_1;
        begin2_ = begin_2;
        end1_ = end_1;
        end2_= end_2;
    }
    Zipped& begin() {
        for_iteration1_ = begin1_;
        for_iteration2_ = begin2_;
        return *this;
    }
    Zipped& end() {
        return *this;
    }
    bool operator!=(Zipped& other) const {
        return for_iteration1_ != end1_ && for_iteration2_ != end2_;
    }
    Zipped& operator++() {
        for_iteration1_++;
        for_iteration2_++;
        return *this;
    }
    auto operator*() const {
        return std::pair(*for_iteration1_, *for_iteration2_);
    }
};


template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    return Zipped(std::begin(sequence1), std::end(sequence1), std::begin(sequence2), std::end(sequence2));
}
