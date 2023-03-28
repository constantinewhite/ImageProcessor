#pragma once

#include "base_filter.h"

class SepiaFilter : public BaseFilter {
public:
    explicit SepiaFilter(Image& image) : BaseFilter(image) {
    }

    bool Apply(const std::vector<double>& parameters) override;

    std::string GetName() const override {
        return "Sepia";
    }

    ~SepiaFilter() override = default;
};
