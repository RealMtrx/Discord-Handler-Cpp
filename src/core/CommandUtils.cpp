#include "CommandUtils.hpp"

std::unordered_map<std::string, std::chrono::steady_clock::time_point> CommandUtils::cooldowns_;
