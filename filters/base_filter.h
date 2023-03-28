#pragma once

#include "../image.h"

#include <stdexcept>

double const R_COEFFICIENT = 0.299;
double const G_COEFFICIENT = 0.587;
double const B_COEFFICIENT = 0.114;

class BaseFilter {
public:
    explicit BaseFilter(Image& image) : image_(image) {
    }

    virtual bool Apply(const std::vector<double>& parameters) = 0;

    virtual std::string GetName() const = 0;

    virtual ~BaseFilter() = default;

protected:
    Image& image_;
};