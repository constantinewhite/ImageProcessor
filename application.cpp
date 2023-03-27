#include "application.h"
#include "parser.h"
#include "image.h"
#include "pipeline.h"

#include <stdexcept>

int Application::Run(int arg_count, char** arguments) {

    Parser parser(arg_count, arguments);

    auto* image_ptr = new Image;
    Image& image = *image_ptr;

    if (!image.ReadFile(parser.GetInputFile())) {
        throw std::logic_error("File can't be opened");
    }

    Pipeline pipeline(image);

    for (auto [name, params] : parser.GetFilters()) {
        try {
            pipeline[name]->Apply(params);
        } catch (std::logic_error& e) {
            std::cout << e.what() << std::endl;
        }
    }

    if (!image.WriteFile(parser.GetOutputFile())) {
        throw std::logic_error("File can't be written");
    }

    delete image_ptr;

    return 0;
}
