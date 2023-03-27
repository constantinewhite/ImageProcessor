#include "application.h"

#include <stdexcept>
#include <iostream>

int main(int argc, char** argv) {
    try {
        Application app;
        return app.Run(argc, argv);
    } catch (std::exception& e) {
        std::cout << e.what();
    }
}
