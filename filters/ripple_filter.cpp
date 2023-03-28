#include "ripple_filter.h"

#include <cmath>

bool RippleFilter::Apply(const std::vector<double>& parameters) {

    if (parameters.size() != 2) {
        return false;
    }

    PixelMatrix& image = image_.GetBody();

    uint32_t height = image_.GetHeight();
    uint32_t width = image_.GetWidth();
    PixelMatrix result(height, std::vector<Pixel>(width));

    double ripple_amplitude = parameters[0];
    double ripple_frequency = parameters[1];
    double center_x = width / 2.0;
    double center_y = height / 2.0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double dx = x - center_x;
            double dy = y - center_y;
            double distance = std::sqrt(dx * dx + dy * dy);
            double theta = std::atan2(dy, dx);
            double ripple_factor = ripple_amplitude * std::sin(distance / ripple_frequency);
            double new_x = x + ripple_factor * std::cos(theta);
            double new_y = y + ripple_factor * std::sin(theta);
            if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
                result[y][x] = image[static_cast<int>(new_y)][static_cast<int>(new_x)];
            }
        }
    }

    image = result;

    return true;
}
