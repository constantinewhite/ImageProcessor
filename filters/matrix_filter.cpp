#include "matrix_filter.h"

IntPixelMatrix MatrixFilter::ApplyMatrix(std::vector<std::vector<int>> matrix) {
    uint16_t height = image_.GetHeight();
    uint16_t width = image_.GetWidth();
    IntPixelMatrix result(height, std::vector<IntPixel>(width));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int new_r = 0;
            int new_g = 0;
            int new_b = 0;

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx < 0) {
                        nx = 0;
                    } else if (nx >= width) {
                        nx -= 1;
                    }
                    if (ny < 0) {
                        ny = 0;
                    } else if (ny >= height) {
                        ny -= 1;
                    }

                    new_r += image_.GetBody()[ny][nx].r * matrix[dy + 1][dx + 1];
                    new_g += image_.GetBody()[ny][nx].g * matrix[dy + 1][dx + 1];
                    new_b += image_.GetBody()[ny][nx].b * matrix[dy + 1][dx + 1];
                }
            }
            result[y][x].r = new_r;
            result[y][x].g = new_g;
            result[y][x].b = new_b;
        }
    }

    return result;
}
