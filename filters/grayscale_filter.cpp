#include "grayscale_filter.h"

bool GrayscaleFilter::Apply(const std::vector<double>& parameters) {

    if (!parameters.empty()) {
        return false;
    }

    for (Row& row : image_.GetBody()) {
        for (Pixel& pixel : row) {
            auto value = static_cast<uint8_t>(R_COEFFICIENT * static_cast<float>(pixel.r) +
                                                 G_COEFFICIENT * static_cast<float>(pixel.g) +
                                                 B_COEFFICIENT * static_cast<float>(pixel.b));
            pixel.r = value;
            pixel.g = value;
            pixel.b = value;
        }
    }
    return true;
}
