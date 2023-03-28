#include "negative_filter.h"

#include <cstdint>

bool NegativeFilter::Apply(const std::vector<double>& parameters) {

    if (!parameters.empty()) {
        return false;
    }

    for (Row& row : image_.GetBody()) {
        for (Pixel& pixel : row) {
            pixel.r = UINT8_MAX - pixel.r;
            pixel.g = UINT8_MAX - pixel.g;
            pixel.b = UINT8_MAX - pixel.b;
        }
    }
    return true;
}
