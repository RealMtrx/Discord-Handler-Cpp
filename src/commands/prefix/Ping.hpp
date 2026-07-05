#pragma once
#include <dpp/dpp.h>
#include <vector>
#include <string>
#include "../../core/Emojis.hpp"
#include "../../core/CommandUtils.hpp"

namespace PrefixCommands {
    inline const std::string name = "ping";
    inline const std::string description = "Replies with Pong!";
    inline const std::vector<std::string> aliases = {"p"};
    inline const long cooldownMs = 3000;

    inline void execute(const dpp::message_create_t& event, const std::vector<std::string>& args) {
        std::string userId = std::to_string(event.msg.author.id);
        auto cooldown = CommandUtils::checkCooldown(userId, name, cooldownMs);
        if (cooldown.onCooldown) {
            event.reply(dpp::message(Emojis::loading + " Please wait " + std::to_string(cooldown.timeLeft) + " seconds before using this command again."));
            return;
        }
        event.reply(dpp::message(Emojis::success + " Pong!"));
    }
}
