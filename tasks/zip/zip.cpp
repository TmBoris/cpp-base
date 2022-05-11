#include "zip.h"

Zipped::Zipped(Iterator begin1, Iterator end1, Iterator begin2, Iterator end2) {
    for_iteration1_ = begin1;
    for_iteration2_ = begin2;
    begin1_ = begin1;
    begin2_ = begin2;
    end1_ = end1;
    end2_= end2;
}
Zipped& Zipped::begin() {
    for_iteration1_ = begin1_;
    for_iteration2_ = begin2_;
    return *this;
}
Zipped& Zipped::end() {
    return *this;
}
bool Zipped::operator!=(Zipped& other) const {
    return for_iteration1_ != end1_ && for_iteration2_ != end2_;
}
Zipped& Zipped::operator++() {
    for_iteration1_++;
    for_iteration2_++;
    return *this;
}

ZippedPair Zipped::operator*() const{
    return {*for_iteration1_, *for_iteration2_};
}
Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end) {
    return Zipped(a_begin, a_end, b_begin, b_end);
}