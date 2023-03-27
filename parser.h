#pragma once

#include <string>
#include <vector>
#include <iostream>

class Parser {
public:
    using Filters = std::vector<std::pair<std::string, std::vector<double>>>;

    Parser(int argc, char** argv);

    [[nodiscard]] std::string GetInputFile() const {
        return input_file_;
    }

    [[nodiscard]] std::string GetOutputFile() const {
        return output_file_;
    }

    Filters& GetFilters() {
        return filters_;
    };

    void Debug() const {
        std::cout << "Input file: " << input_file_ << std::endl;
        std::cout << "Output file: " << output_file_ << std::endl;
        for (const auto& filter : filters_) {
            std::cout << "Filter: " << filter.first << std::endl;
            std::cout << "Parameters:";
            for (const auto& param : filter.second) {
                std::cout << " " << param;
            }
            std::cout << std::endl;
        }
    }

private:
    std::string input_file_;
    std::string output_file_;
    Filters filters_;
};