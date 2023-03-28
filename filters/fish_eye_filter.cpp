#include "fish_eye_filter.h"

#include <cmath>

const double MIDDLE = 2.0;

bool FishEyeFilter::Apply(const std::vector<double>& parameters) {

    if (parameters.size() != 1 && parameters.size() != 3) {
        return false;
    }

    PixelMatrix& image = image_.GetBody();

    uint32_t height = image_.GetHeight();
    uint32_t width = image_.GetWidth();
    PixelMatrix result(height, std::vector<Pixel>(width));

    double fish_eye_radius = parameters[0];
    double center_x = width;
    double center_y = height;
    if (parameters.size() > 1) {
        center_x *= parameters[1];
        center_y *= parameters[2];
    } else {
        center_x /= MIDDLE;
        center_y /= MIDDLE;
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double dx = x - center_x;
            double dy = y - center_y;
            double distance = std::sqrt(dx * dx + dy * dy);
            double theta = std::atan2(dy, dx);
            if (distance < fish_eye_radius) {
                double r = distance / fish_eye_radius;
                double new_distance = r * r * fish_eye_radius;
                int new_x = static_cast<int>(center_x + new_distance * std::cos(theta));
                int new_y = static_cast<int>(center_y + new_distance * std::sin(theta));
                if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
                    result[y][x] = image[new_y][new_x];
                }
            } else {
                double r = fish_eye_radius / distance;
                double new_distance = r * r * distance;
                int new_x = static_cast<int>(center_x + new_distance * std::cos(theta));
                int new_y = static_cast<int>(center_y + new_distance * std::sin(theta));
                if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
                    result[y][x] = image[new_y][new_x];
                }
            }
        }
    }

    image = result;

    return true;
}
