#pragma once

#include "base_filter.h"

class NegativeFilter : public BaseFilter {
public:
    explicit NegativeFilter(Image& image) : BaseFilter(image) {
    }

    bool Apply(const std::vector<double>& parameters) override;

    std::string GetName() const override {
        return "Negative";
    }

    ~NegativeFilter() override = default;
};
