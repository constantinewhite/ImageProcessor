#pragma once

#include "base_filter.h"

//    Image embossing is a computer graphics technique in which each pixel of an image is replaced either by a highlight
//    or a shadow, depending on light/dark boundaries on the original image. The filtered image will represent the rate
//    of color change at each location of the original image. Applying an embossing filter to an image often results in
//    an image resembling a paper or metal embossing of the original image, hence the name.
//    bool EmbossFilter(std::vector<std::vector<Pixel>>& image, const std::vector<double>& parameters)
//
//    The EmbossFilter applies an emboss effect to an image, giving the appearance of a raised or engraved
//    surface. The function takes the following parameter:
//    - double value representing the strength of the emboss effect. The value must be greater than 0,
//    recommended values: 1 - 15.
//
//    The emboss effect is applied by calculating the difference between the color values of adjacent pixels and adding
//    a constant offset. The strength of the effect is determined by the value of the parameter. A parameter value of 0
//    produces no effect.

class EmbossFilter : public BaseFilter {
public:
    explicit EmbossFilter(Image& image) : BaseFilter(image) {
    }

    bool Apply(const std::vector<double>& parameters) override;

    ~EmbossFilter() override = default;
};