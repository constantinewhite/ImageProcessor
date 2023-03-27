#include "crop_filter.h"

#include <cmath>

bool CropFilter::Apply(const std::vector<double>& parameters) {

    if (parameters.size() != 2) {
        throw std::logic_error("Crop filter can't be applied: wrong number of arguments");
    }

    uint32_t new_width = static_cast<uint32_t>(parameters[0]) < image_.GetWidth() ? static_cast<uint32_t>(parameters[0])
                                                                                  : image_.GetWidth();
    uint32_t new_height = static_cast<uint32_t>(parameters[1]) < image_.GetHeight()
                              ? static_cast<uint32_t>(parameters[1])
                              : image_.GetHeight();

    std::reverse(image_.GetBody().begin(), image_.GetBody().end());
    image_.GetBody().resize(new_height);
    std::reverse(image_.GetBody().begin(), image_.GetBody().end());
    for (Row& row : image_.GetBody()) {
        row.resize(new_width);
    }
    image_.Resize(new_width, new_height);

    return true;
}
