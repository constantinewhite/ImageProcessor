#pragma once

#include "base_filter.h"

class TwirlFilter : public BaseFilter {
public:
    explicit TwirlFilter(Image& image) : BaseFilter(image) {
    }

    bool Apply(const std::vector<double>& parameters) override;

    ~TwirlFilter() override = default;
};
