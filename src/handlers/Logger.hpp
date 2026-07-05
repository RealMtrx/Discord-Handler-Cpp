#pragma once
#include <string>
#include <iostream>

struct StartupData {
    std::string name;
    int prefix;
    int slash;
    int events;
    bool anticrash;
    bool mongo;
};

class Logger {
public:
    static void startupReport(const StartupData& data) {
        std::string line = "\033[36m\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\033[0m";
        std::cout << std::endl;
        std::cout << line << std::endl;
        std::cout << "  \033[1;36m" << data.name << "\033[0m" << std::endl;
        std::cout << line << std::endl;
        std::cout << "  " << statusEmoji(data.slash > 0) << " Slash Commands: " << data.slash << std::endl;
        std::cout << "  " << statusEmoji(data.prefix > 0) << " Prefix Commands: " << data.prefix << std::endl;
        std::cout << "  " << statusEmoji(data.events > 0) << " Events Loaded: " << data.events << std::endl;
        std::cout << "  " << statusEmoji(data.anticrash) << " AntiCrash: " << (data.anticrash ? "Active" : "Inactive") << std::endl;
        std::cout << "  " << statusEmoji(data.mongo) << " MongoDB: " << (data.mongo ? "Connected" : "Disconnected") << std::endl;
        std::cout << line << std::endl;
        std::cout << "  \033[35mBot is now online and fully operational.\033[0m" << std::endl;
        std::cout << std::endl;
    }

private:
    static std::string statusEmoji(bool ok) {
        return ok ? "\u2705" : "\u274C";
    }
};
