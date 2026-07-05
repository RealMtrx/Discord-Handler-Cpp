#pragma once
#include <string>
#include <unordered_map>
#include <chrono>

struct CooldownResult {
    bool onCooldown;
    long timeLeft;
};

class CommandUtils {
public:
    static CooldownResult checkCooldown(const std::string& userId, const std::string& commandName, long cooldownMs = 3000) {
        std::string key = userId + ":" + commandName;
        auto now = std::chrono::steady_clock::now();
        auto it = cooldowns_.find(key);
        if (it != cooldowns_.end()) {
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - it->second).count();
            if (elapsed < cooldownMs) {
                return {true, (cooldownMs - elapsed) / 1000};
            }
        }
        cooldowns_[key] = now;
        return {false, 0};
    }

private:
    static std::unordered_map<std::string, std::chrono::steady_clock::time_point> cooldowns_;
};
