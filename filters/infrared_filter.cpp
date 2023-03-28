#include "infrared_filter.h"

bool InfraRedFilter::Apply(const std::vector<double>& parameters) {

    if (!parameters.empty()) {
        return false;
    }

    for (Row& row : image_.GetBody()) {
        for (Pixel& pixel : row) {
            uint8_t r = pixel.r;
            uint8_t g = pixel.g;
            uint8_t b = pixel.b;

            // Swap red and blue channels
            pixel.r = b;
            pixel.b = r;

            // Apply brightness and contrast adjustment
            pixel.r = static_cast<uint8_t>((pixel.r * 1.2) + 10);
            pixel.g = static_cast<uint8_t>((pixel.g * 0.8) - 10);
            pixel.b = static_cast<uint8_t>((pixel.b * 1.2) + 10);

            // Clamp the values to [0, 255]
            pixel.r = std::min(pixel.r, static_cast<uint8_t>(255));
            pixel.g = std::min(pixel.g, static_cast<uint8_t>(255));
            pixel.b = std::min(pixel.b, static_cast<uint8_t>(255));
        }
    }
    return true;
}
