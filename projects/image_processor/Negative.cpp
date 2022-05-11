#include "Negative.h"

void NegativeFilter::Apply(Image& image) {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Color c = image.GetColor(j, i);
            c.red = UCHAR_MAX - c.red;
            c.green = UCHAR_MAX - c.green;
            c.blue = UCHAR_MAX - c.blue;

            image.SetColor(j, i, c);
        }
    }
}
NegativeFilter::~NegativeFilter() {
}
