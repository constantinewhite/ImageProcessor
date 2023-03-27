#pragma once

#include "filters/base_filter.h"
#include "filters/grayscale_filter.h"
#include "filters/negative_filter.h"
#include "filters/crop_filter.h"
#include "filters/sharpening_filter.h"
#include "filters/edge_detection_filter.h"
#include "filters/gaussian_blur_filter.h"
#include "filters/emboss_filter.h"
#include "filters/fish_eye_filter.h"
#include "filters/sepia_filter.h"
#include "filters/infrared_filter.h"
#include "filters/twirl_filter.h"
#include "filters/ripple_filter.h"

#include <map>

class Pipeline {
public:
    explicit Pipeline(Image& image) {
        pipeline_ = {{"-crop", new CropFilter(image)},          {"-gs", new GrayscaleFilter(image)},
                     {"-neg", new NegativeFilter(image)},       {"-sharp", new SharpeningFilter(image)},
                     {"-edge", new EdgeDetectionFilter(image)}, {"-blur", new GaussianBlurFilter(image)},
                     {"-emboss", new EmbossFilter(image)},      {"-fisheye", new FishEyeFilter(image)},
                     {"-sepia", new SepiaFilter(image)},        {"-infrared", new InfraRedFilter(image)},
                     {"-twirl", new TwirlFilter(image)},        {"-ripple", new RippleFilter(image)}};
    }

    BaseFilter* operator[](const std::string& name) {
        return pipeline_[name];
    }

    ~Pipeline() {
        for (auto [name, filter_ptr] : pipeline_) {
            delete filter_ptr;
        }
    }

private:
    std::map<std::string, BaseFilter*> pipeline_;
};