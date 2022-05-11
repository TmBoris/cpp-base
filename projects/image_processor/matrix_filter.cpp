#include "matrix_filter.h"

MatrixFilter::MatrixFilter(std::vector<std::vector<double>> v) : Filter() {
    FilterMatrix_ = v;
}
MatrixFilter::~MatrixFilter() {
}
void MatrixFilter::Apply(Image& image) {
    Image image_copy(image.GetWidth() + 2, image.GetHeight() + 2);
    for (size_t i = 1; i < image.GetHeight() + 1; ++i) {
        for (size_t j = 1; j < image.GetWidth() + 1; ++j) {
            image_copy.SetColor(j, i, image.GetColor(j - 1, i - 1));
        }
    }
    for (size_t i = 1; i < image.GetWidth() + 1; ++i) {
        image_copy.SetColor(i, 0, image.GetColor(i - 1, 1));
        image_copy.SetColor(i, image.GetHeight() + 1, image.GetColor(i - 1, image.GetHeight() - 2));
    }
    for (size_t j = 1; j < image.GetHeight() + 1; ++j) {
        image_copy.SetColor(0, j, image.GetColor(1, j - 1));
        image_copy.SetColor(image.GetWidth() + 1, j, image.GetColor(image.GetWidth() - 2, j - 1));
    }
    image_copy.SetColor(0, 0, image.GetColor(1, 1));
    image_copy.SetColor(image.GetWidth() + 1, 0, image.GetColor(image.GetWidth() - 2, 1));
    image_copy.SetColor(0, image.GetHeight() + 1, image.GetColor(1, image.GetHeight() - 2));
    image_copy.SetColor(image.GetWidth() + 1, image.GetHeight() + 1, image.GetColor(image.GetWidth() - 2, image.GetHeight() - 2));

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Color result;
            double red_res = 0;
            double green_res = 0;
            double blue_res = 0;

            for (size_t q = 0; q < 3; ++q) {
                for (size_t w = 0; w < 3; ++w) {
                    Color tmp = image_copy .GetColor(j + w, i + q);
                    red_res += (static_cast<double>(tmp.red) / 255.0f) * FilterMatrix_[q][w];
                    green_res += (static_cast<double>(tmp.green) / 255.0f) * FilterMatrix_[q][w];
                    blue_res += (static_cast<double>(tmp.blue) / 255.0f) * FilterMatrix_[q][w];
                }
            }

            result.red = static_cast<unsigned char>(std::min(1.0, std::max(0.0, red_res)) * 255.0f);
            result.green = static_cast<unsigned char>(std::min(1.0, std::max(0.0, green_res)) * 255.0f);
            result.blue = static_cast<unsigned char>(std::min(1.0, std::max(0.0, blue_res)) * 255.0f);

            image.SetColor(j, i, result);
        }
    }
}
