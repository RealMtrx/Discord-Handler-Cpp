#pragma once
#include <dpp/dpp.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include "../commands/prefix/Ping.hpp"
#include "../config/Config.hpp"

namespace Events {
    inline std::unordered_map<std::string, decltype(&PrefixCommands::execute)> getPrefixCommands() {
        std::unordered_map<std::string, decltype(&PrefixCommands::execute)> cmds;
        cmds[PrefixCommands::name] = &PrefixCommands::execute;
        for (const auto& alias : PrefixCommands::aliases) {
            cmds[alias] = &PrefixCommands::execute;
        }
        return cmds;
    }

    inline void onMessageCreate(const dpp::message_create_t& event, const Config& config, dpp::cluster& bot) {
        if (event.msg.author.is_bot()) return;
        std::string content = event.msg.content;
        if (content.find(config.prefix) != 0) return;

        std::string withoutPrefix = content.substr(config.prefix.length());
        std::vector<std::string> args;
        std::stringstream ss(withoutPrefix);
        std::string arg;
        while (ss >> arg) {
            args.push_back(arg);
        }
        if (args.empty()) return;

        std::string commandName = args[0];
        std::transform(commandName.begin(), commandName.end(), commandName.begin(), ::tolower);
        args.erase(args.begin());

        static auto prefixCommands = getPrefixCommands();
        auto it = prefixCommands.find(commandName);
        if (it == prefixCommands.end()) return;

        try {
            it->second(event, args);
        } catch (const std::exception& e) {
            std::cerr << "\033[31m[Prefix] Error in " << commandName << ": " << e.what() << "\033[0m" << std::endl;
        }
    }
}
