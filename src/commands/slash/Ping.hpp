#pragma once
#include <dpp/dpp.h>
#include "../../core/Emojis.hpp"
#include "../../core/CommandUtils.hpp"

namespace SlashCommands {
    inline const std::string name = "ping";
    inline const std::string description = "Replies with Pong!";
    inline const long cooldownMs = 3000;

    inline void execute(const dpp::slashcommand_t& event) {
        std::string userId = std::to_string(event.command.usr.id);
        auto cooldown = CommandUtils::checkCooldown(userId, name, cooldownMs);
        if (cooldown.onCooldown) {
            event.reply(dpp::message(Emojis::loading + " Please wait " + std::to_string(cooldown.timeLeft) + " seconds before using this command again.").set_flags(dpp::m_ephemeral));
            return;
        }
        event.reply(dpp::message(Emojis::success + " Pong!").set_flags(dpp::m_ephemeral));
    }
}
