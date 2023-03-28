#pragma once

#include "matrix_filter.h"

const int CENTER = 5;

class SharpeningFilter : public MatrixFilter {
public:
    explicit SharpeningFilter(Image& image) : MatrixFilter(image), matrix_({{0, -1, 0}, {-1, CENTER, -1}, {0, -1, 0}}) {
    }

    bool Apply(const std::vector<double>& parameters) override;

    std::string GetName() const override {
        return "Sharpening";
    }

    ~SharpeningFilter() override = default;

private:
    std::vector<std::vector<int>> matrix_;
};