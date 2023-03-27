#pragma once

#include "matrix_filter.h"

class EdgeDetectionFilter : public MatrixFilter {
public:
    explicit EdgeDetectionFilter(Image& image) : MatrixFilter(image), matrix_({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}) {
    }

    bool Apply(const std::vector<double>& parameters) override;

    ~EdgeDetectionFilter() override = default;

protected:
    std::vector<std::vector<int>> matrix_;
};