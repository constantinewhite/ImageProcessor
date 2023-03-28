#pragma once

#include "base_filter.h"

class PinchFilter : public BaseFilter {
public:
    explicit PinchFilter(Image& image) : BaseFilter(image) {
    }

    bool Apply(const std::vector<double>& parameters) override;

    ~PinchFilter() override = default;
};
