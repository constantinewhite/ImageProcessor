#pragma once

#include "base_filter.h"

class GaussianBlurFilter : public BaseFilter {
public:
    explicit GaussianBlurFilter(Image& image) : BaseFilter(image) {
    }

    bool Apply(const std::vector<double>& parameters) override;

    std::string GetName() const override {
        return "Gaussian Blur";
    }

    ~GaussianBlurFilter() override = default;
};
