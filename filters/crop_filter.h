#pragma once

#include "base_filter.h"

class CropFilter : public BaseFilter {
public:
    explicit CropFilter(Image& image) : BaseFilter(image) {
    }

    bool Apply(const std::vector<double>& parameters) override;

    std::string GetName() const override {
        return "Crop";
    }

    ~CropFilter() override = default;
};