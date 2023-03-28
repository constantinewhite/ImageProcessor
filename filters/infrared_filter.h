#pragma once

#include "base_filter.h"

class InfraRedFilter : public BaseFilter {
public:
    explicit InfraRedFilter(Image& image) : BaseFilter(image) {
    }

    bool Apply(const std::vector<double>& parameters) override;

    std::string GetName() const override {
        return "Infrared";
    }

    ~InfraRedFilter() override = default;
};
