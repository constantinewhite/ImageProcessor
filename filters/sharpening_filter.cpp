#include "sharpening_filter.h"

bool SharpeningFilter::Apply(const std::vector<double>& parameters) {

    if (!parameters.empty()) {
        throw std::logic_error("Sharpening filter can't be applied: wrong number of arguments");
    }

    IntPixelMatrix int_image = ApplyMatrix(matrix_);
    PixelMatrix& image = image_.GetBody();
    for (int y = 0; y < image_.GetHeight(); ++y) {
        for (int x = 0; x < image_.GetWidth(); ++x) {
            image[y][x] = int_image[y][x].ToPixel();
        }
    }
    return true;
}
