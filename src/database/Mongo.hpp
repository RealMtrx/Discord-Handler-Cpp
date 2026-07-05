#pragma once
#include <string>
#include <iostream>
#include "../config/Config.hpp"

class Mongo {
public:
    static bool connect(const Config& config) {
        std::cout << "\033[34m[System] MongoDB support requires mongocxx driver.\033[0m" << std::endl;
        std::cout << "\033[33m[MongoDB] Skipping - not available without libmongocxx.\033[0m" << std::endl;
        return false;
    }

    static bool isConnected() {
        return false;
    }

    static void disconnect() {}
};
