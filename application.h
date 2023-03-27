#pragma once

class Application {
public:
    Application() = default;

    static int Run(int arg_count, char** arguments);
};