#pragma once

#include "base_filter.h"

class GrayscaleFilter : public BaseFilter {
public:
    explicit GrayscaleFilter(Image& image) : BaseFilter(image) {
    }

    bool Apply(const std::vector<double>& parameters) override;

    std::string GetName() const override {
        return "Grayscale";
    }

    ~GrayscaleFilter() override = default;
};