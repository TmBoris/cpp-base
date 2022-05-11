#include "Grayscale.h"

void GrayscaleFilter::Apply(Image& image) {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Color c = image.GetColor(j, i);
            double red = static_cast<double>(c.red);
            double green = static_cast<double>(c.green);
            double blue = static_cast<double>(c.blue);

            double tmp = 0.299 * red + 0.587 * green + 0.114 * blue;

            unsigned char new_value = static_cast<unsigned char>(std::clamp(tmp, 0.0, 255.0));

            c.red = new_value;
            c.blue = new_value;
            c.green = new_value;
            image.SetColor(j, i, c);
        }
    }
}
GrayscaleFilter::~GrayscaleFilter() {
}
