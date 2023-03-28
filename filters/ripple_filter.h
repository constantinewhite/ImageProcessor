#pragma once

#include "base_filter.h"

class RippleFilter : public BaseFilter {
public:
    explicit RippleFilter(Image& image) : BaseFilter(image) {
    }

    bool Apply(const std::vector<double>& parameters) override;

    std::string GetName() const override {
        return "Ripple";
    }

    ~RippleFilter() override = default;
};
