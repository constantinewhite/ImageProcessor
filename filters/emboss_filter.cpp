#include "emboss_filter.h"

#include <cmath>

const int OFFSET = 128;
const double COLORS_COUNT = 3.0;

bool EmbossFilter::Apply(const std::vector<double>& parameters) {

    if (parameters.size() != 1) {
        throw std::logic_error("Emboss filter can't be applied: wrong number of arguments");
    }

    PixelMatrix& image = image_.GetBody();

    int height = static_cast<int>(image_.GetHeight());
    int width = static_cast<int>(image_.GetWidth());

    double emboss_strength = parameters[0];

    if (emboss_strength < 1) {
        throw std::logic_error("Emboss filter can't be applied: Emboss strength can't be negative");
    }

    PixelMatrix result(height, std::vector<Pixel>(width));

    for (int y = 1; y < height; y++) {
        for (int x = 1; x < width; x++) {
            double diff_b = image[y][x].b - image[y - 1][x - 1].b;
            double diff_g = image[y][x].g - image[y - 1][x - 1].g;
            double diff_r = image[y][x].r - image[y - 1][x - 1].r;

            double diff = (diff_b + diff_g + diff_r) / COLORS_COUNT;

            uint8_t value = std::max(0, std::min(UINT8_MAX, static_cast<int>(OFFSET + diff * emboss_strength)));

            result[y][x].b = value;
            result[y][x].g = value;
            result[y][x].r = value;
        }
    }

    image = result;

    return true;
}
