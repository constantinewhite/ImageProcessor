#pragma once

#include "base_filter.h"

class SepiaFilter : public BaseFilter {
public:
    explicit SepiaFilter(Image& image) : BaseFilter(image) {
    }

    bool Apply(const std::vector<double>& parameters) override;

    ~SepiaFilter() override = default;
};
