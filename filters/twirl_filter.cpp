#include "twirl_filter.h"

#include <cmath>

bool TwirlFilter::Apply(const std::vector<double>& parameters) {
    PixelMatrix& image = image_.GetBody();

    uint32_t height = image_.GetHeight();
    uint32_t width = image_.GetWidth();
    PixelMatrix result(height, std::vector<Pixel>(width));

    double twirl_radius = parameters[0];
    double twirl_angle = parameters[1];
    double center_x = width / 2.0;
    double center_y = height / 2.0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double dx = x - center_x;
            double dy = y - center_y;
            double distance = std::sqrt(dx * dx + dy * dy);
            double radius = std::min(distance, twirl_radius);
            double angle = twirl_angle * (radius / twirl_radius);
            double new_theta = std::atan2(dy, dx) + angle;
            int new_x = static_cast<int>(center_x + radius * std::cos(new_theta));
            int new_y = static_cast<int>(center_y + radius * std::sin(new_theta));
            if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
                result[y][x] = image[new_y][new_x];
            }
        }
    }

    image = result;

    return true;
}
