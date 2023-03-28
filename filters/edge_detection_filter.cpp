#include "edge_detection_filter.h"

bool EdgeDetectionFilter::Apply(const std::vector<double>& parameters) {

    if (parameters.size() != 1) {
        return false;
    }

    IntPixelMatrix int_image = ApplyMatrix(matrix_);

    uint32_t height = image_.GetHeight();
    uint32_t width = image_.GetWidth();
    PixelMatrix result(height, std::vector<Pixel>(width));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double grayscale = R_COEFFICIENT * int_image[y][x].r + G_COEFFICIENT * int_image[y][x].g +
                               B_COEFFICIENT * int_image[y][x].b;
            result[y][x] =
                grayscale > parameters[0] * UINT8_MAX ? Pixel{UINT8_MAX, UINT8_MAX, UINT8_MAX} : Pixel{0, 0, 0};
        }
    }

    image_.GetBody() = result;

    return true;
}