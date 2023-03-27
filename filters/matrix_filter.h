#pragma once

#include "base_filter.h"

struct IntPixel {
    int b;
    int g;
    int r;

    Pixel ToPixel() const {
        return Pixel{static_cast<uint8_t>(std::max(0, std::min(UINT8_MAX, b))),
                     static_cast<uint8_t>(std::max(0, std::min(UINT8_MAX, g))),
                     static_cast<uint8_t>(std::max(0, std::min(UINT8_MAX, r)))};
    }
};

using IntPixelMatrix = std::vector<std::vector<IntPixel>>;

class MatrixFilter : public BaseFilter {
public:
    explicit MatrixFilter(Image& image) : BaseFilter(image) {
    }

    IntPixelMatrix ApplyMatrix(std::vector<std::vector<int>> matrix);

    ~MatrixFilter() override = default;

protected:
    std::vector<std::vector<int>> matrix_;
};