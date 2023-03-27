#pragma once

#include "image.h"
#include "filters/grayscale_filter.h"

#include <iostream>

void Test1() {
    Image img;

    std::cout << img.ReadFile(
                     "/Users/admin/pmi-226-1-Konstantin-Belomestnykh-Constantine/tasks/image_processor/test_script/"
                     "data/lenna.bmp")
              << std::endl;

    GrayscaleFilter filter = GrayscaleFilter(img);

    std::cout << img.WriteFile(
        "/Users/admin/pmi-226-1-Konstantin-Belomestnykh-Constantine/tasks/image_processor/test.bmp");
}