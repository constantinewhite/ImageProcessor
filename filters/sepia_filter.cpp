#include "sepia_filter.h"

bool SepiaFilter::Apply(const std::vector<double>& parameters) {
    if (!parameters.empty()) {
        throw std::logic_error("Sepia filter can't be applied: wrong number of arguments");
    }

    for (Row& row : image_.GetBody()) {
        for (Pixel& pixel : row) {
            auto new_r = static_cast<uint8_t>(pixel.r * .393 + pixel.g * .769 + pixel.b * .189);
            auto new_g = static_cast<uint8_t>(pixel.r * .349 + pixel.g * .686 + pixel.b * .168);
            auto new_b = static_cast<uint8_t>(pixel.r * .272 + pixel.g * .534 + pixel.b * .131);

            pixel.r = std::min(255, std::max(0, static_cast<int>(new_r)));
            pixel.g = std::min(255, std::max(0, static_cast<int>(new_g)));
            pixel.b = std::min(255, std::max(0, static_cast<int>(new_b)));

        }
    }
    return true;
}
