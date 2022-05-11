#include "sharpening.h"


void SharpeningFilter::Apply(Image& image) {
    MatrixFilter::Apply(image);
}

SharpeningFilter::~SharpeningFilter() {
}
SharpeningFilter::SharpeningFilter() : MatrixFilter({{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}) {
}
