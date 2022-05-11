#include "gauss_filter.h"
#include "cmath"
#include "math.h"
#include "corecrt.h"

void GaussFilter::Apply(Image& image) {
    Image image_copy(image.GetWidth() + 6 * sigma_, image.GetHeight() + 6 * sigma_);
    for (size_t i = 3 * sigma_; i < image.GetHeight() + 3 * sigma_; ++i) {
        for (size_t j = 3 * sigma_; j < image.GetWidth() + 3 * sigma_; ++j) {
            image_copy.SetColor(j, i, image.GetColor(j - 3 * sigma_, i - 3 * sigma_));
        }
    }
    for (size_t i = 3 * sigma_; i < image.GetHeight() + 3 * sigma_; ++i) {
        for (size_t j = 0; j < 3 * sigma_; ++j) {
            image_copy.SetColor(j, i, image.GetColor(3 * sigma_ - 1 - j, i - 3 * sigma_));
        }
        for (size_t j = image.GetWidth() + 3 * sigma_; j < image.GetWidth() + 6 * sigma_; ++j) {
            image_copy.SetColor(
                j, i, image.GetColor(image.GetWidth() + 3 * sigma_ + image.GetWidth() - 1 - j, i - 3 * sigma_));
        }
    }

    for (ssize_t y0 = 0; y0 < static_cast<ssize_t>(image.GetHeight()); ++y0) {
        for (ssize_t x0 = 0; x0 < static_cast<ssize_t>(image.GetWidth()); ++x0) {
            Color new_color;
            double red = 0;
            double green = 0;
            double blue = 0;

            for (ssize_t x = 0; x < image.GetWidth() + 6 * sigma_; ++x) {
                Color col = image_copy.GetColor(x, y0 + 3 * sigma_);
                red += (static_cast<double>(col.red)) * exp(-(double(abs(x - x0 - 3 * sigma_) * abs(x - x0 - 3 * sigma_)) / (2 * sigma_ * sigma_)));
                green += (static_cast<double>(col.green)) * exp(-(double(abs(x - x0 - 3 * sigma_) * abs(x - x0 - 3 * sigma_)) / (2 * sigma_ * sigma_)));
                blue += (static_cast<double>(col.blue)) * exp(-(double(abs(x - x0 - 3 * sigma_) * abs(x - x0 - 3 * sigma_)) / (2 * sigma_ * sigma_)));
            }
            red /= sqrt(2 * M_PI * sigma_ * sigma_);
            green /= sqrt(2 * M_PI * sigma_ * sigma_);
            blue /= sqrt(2 * M_PI * sigma_ * sigma_);

            new_color.red = static_cast<unsigned char>(std::round(std::clamp(red, 0.0, 255.0)));
            new_color.green = static_cast<unsigned char>(std::round(std::clamp(green, 0.0, 255.0)));
            new_color.blue = static_cast<unsigned char>(std::round(std::clamp(blue, 0.0, 255.0)));

            image.SetColor(x0, y0, new_color);
        }
    }

    for (size_t i = 3 * sigma_; i < image.GetHeight() + 3 * sigma_; ++i) {
        for (size_t j = 3 * sigma_; j < image.GetWidth() + 3 * sigma_; ++j) {
            image_copy.SetColor(j, i, image.GetColor(j - 3 * sigma_, i - 3 * sigma_));
        }
    }

    for (size_t i = 3 * sigma_; i < image.GetWidth() + 3 * sigma_; ++i) {
        for (size_t j = 0; j < 3 * sigma_; ++j) {
            image_copy.SetColor(i, j, image.GetColor(i - 3 * sigma_, 3 * sigma_ - 1 - j));
        }
        for (size_t j = image.GetHeight() + 3 * sigma_; j < image.GetHeight() + 6 * sigma_; ++j) {
            image_copy.SetColor(i, j, image.GetColor(i - 3 * sigma_, image.GetHeight() + 3 * sigma_ +
            image.GetHeight() - 1 - j));
        }
    }

    for (ssize_t y0 = 0; y0 < static_cast<ssize_t>(image.GetHeight()); ++y0) {
        for (ssize_t x0 = 0; x0 < static_cast<ssize_t>(image.GetWidth()); ++x0) {
            Color new_color;
            double red = 0;
            double green = 0;
            double blue = 0;

            for (ssize_t y = 0; y < image.GetHeight() + 6 * sigma_; ++y) {
                Color col = image_copy.GetColor(x0 + 3 * sigma_, y);

                red += (static_cast<double>(col.red)) *
                       exp(-(double((y - y0 - 3 * sigma_) * (y - y0 - 3 * sigma_)) / (2 * sigma_ * sigma_)));
                green += (static_cast<double>(col.green)) *
                         exp(-(double((y - y0 - 3 * sigma_) * (y - y0 - 3 * sigma_)) / (2 * sigma_ * sigma_)));
                blue += (static_cast<double>(col.blue)) *
                        exp(-(double((y - y0 - 3 * sigma_) * (y - y0 - 3 * sigma_)) / (2 * sigma_ * sigma_)));
            }
            red /= sqrt(2 * M_PI * sigma_ * sigma_);
            green /= sqrt(2 * M_PI * sigma_ * sigma_);
            blue /= sqrt(2 * M_PI * sigma_ * sigma_);

            new_color.red = static_cast<unsigned char>(std::round(std::clamp(red, 0.0, 255.0)));
            new_color.green = static_cast<unsigned char>(std::round(std::clamp(green, 0.0, 255.0)));
            new_color.blue = static_cast<unsigned char>(std::round(std::clamp(blue, 0.0, 255.0)));

            image.SetColor(x0, y0, new_color);
        }
    }
}
GaussFilter::GaussFilter(double sigma) {
    sigma_ = sigma;
}
GaussFilter::~GaussFilter() {
}
