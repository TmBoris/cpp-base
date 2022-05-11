#include "emboss_filter.h"

void EmbossFilter::Apply(Image& image) {
    MatrixFilter::Apply(image);
}
EmbossFilter::EmbossFilter() : MatrixFilter({{-4, -2, 0}, {-2, 1, 2}, {0, 2, 4}}){
}
EmbossFilter::~EmbossFilter() {
}
