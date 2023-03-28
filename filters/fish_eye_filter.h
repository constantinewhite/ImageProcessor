#pragma once

#include "base_filter.h"

//    The FishEyeFilter function applies a fish-eye effect to an image, simulating the
//    distortion caused by a fish-eye lens. The function takes the following parameters:
//    - the fish-eye radius (in pixels)
//    -center_x (0-1, optional)
//    -center_y (0-1, optional)
//
//    The function returns true if the filtering is successful, and false otherwise.
//
//    The fish-eye effect is applied by calculating the new position of each pixel in the image based on its
//    distance from the center (center_x, center_y) and the fish-eye radius. Pixels within the radius are moved
//    towards the center while pixels outside the radius are moved away from the center. The amount of
//    distortion is proportional to the distance from the center.
//
//    Note that the center_x and center_y parameters are optional and have default values of 0.5.

class FishEyeFilter : public BaseFilter {
public:
    explicit FishEyeFilter(Image& image) : BaseFilter(image) {
    }

    bool Apply(const std::vector<double>& parameters) override;

    std::string GetName() const override {
        return "Fish Eye";
    }

    ~FishEyeFilter() override = default;
};