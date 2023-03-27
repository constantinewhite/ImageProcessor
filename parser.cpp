#include "parser.h"

Parser::Parser(int argc, char** argv) : input_file_(argv[1]), output_file_(argv[2]) {

    for (int i = 3; i < argc; ++i) {
        std::string filter_name(argv[i]);
        std::vector<double> filter_params;

        if (filter_name[0] == '-') {
            if (i + 1 >= argc || argv[i + 1][0] == '-') {
                filters_.emplace_back(filter_name, std::vector<double>{});
                continue;
            }
            while (i + 1 < argc && argv[i + 1][0] != '-') {
                filter_params.push_back(std::stod(argv[++i]));
            }
        }

        filters_.emplace_back(filter_name, filter_params);
    }
}
