#include "edge_detection.h"

void EdgeDetectionFilter::Apply(Image& image) {
    GrayscaleFilter::Apply(image);
    MatrixFilter::Apply(image);

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Color ans;

            if ((static_cast<double>(image.GetColor(j, i).red) / 255.0f) > threshold_) {
                ans.red = 255;
                ans.green = 255;
                ans.blue = 255;
            } else {
                ans.red = 0;
                ans.green = 0;
                ans.blue = 0;
            }

            image.SetColor(j, i, ans);
        }
    }
}
EdgeDetectionFilter::EdgeDetectionFilter(double threshold) : MatrixFilter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}), GrayscaleFilter() {
    threshold_ = threshold;
}
EdgeDetectionFilter::~EdgeDetectionFilter() {
}
