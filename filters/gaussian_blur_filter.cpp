#include "gaussian_blur_filter.h"

#include <cmath>

int const KERNEL_SIZE = 3;
float const OFFSET = 0.5;

bool GaussianBlurFilter::Apply(const std::vector<double>& parameters) {

    if (parameters.size() != 1) {
        return false;
    }

    PixelMatrix& image = image_.GetBody();

    double sigma = parameters[0];

    int size = static_cast<int>(std::round(sigma * KERNEL_SIZE)) | 1;
    int radius = size / 2;
    std::vector<double> kernel(size);
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        int x = i - radius;
        kernel[i] = std::exp(-1 * (x * x) / (2 * sigma * sigma));
        sum += kernel[i];
    }
    for (int i = 0; i < size; i++) {
        kernel[i] /= sum;
    }

    PixelMatrix result(image_.GetHeight(), std::vector<Pixel>(image_.GetWidth()));
    for (int i = 0; i < image_.GetHeight(); i++) {
        for (int j = 0; j < image_.GetWidth(); j++) {
            double sum_r = 0.0;
            double sum_g = 0.0;
            double sum_b = 0.0;
            for (int k1 = -radius; k1 <= radius; k1++) {
                for (int k2 = -radius; k2 <= radius; k2++) {
                    int x = i + k1;
                    int y = j + k2;
                    if (x >= 0 && x < image_.GetHeight() && y >= 0 && y < image_.GetWidth()) {
                        sum_r += kernel[k1 + radius] * kernel[k2 + radius] * image[x][y].r;
                        sum_g += kernel[k1 + radius] * kernel[k2 + radius] * image[x][y].g;
                        sum_b += kernel[k1 + radius] * kernel[k2 + radius] * image[x][y].b;
                    }
                }
            }
            result[i][j].r = static_cast<uint8_t>(sum_r + OFFSET);
            result[i][j].g = static_cast<uint8_t>(sum_g + OFFSET);
            result[i][j].b = static_cast<uint8_t>(sum_b + OFFSET);
        }
    }

    image = result;

    return true;
}
