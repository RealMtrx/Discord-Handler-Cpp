#pragma once
#include <dpp/dpp.h>
#include <iostream>
#include "../commands/slash/Ping.hpp"
#include "../core/WebhookUtil.hpp"

namespace Events {
    inline void onInteractionCreate(const dpp::slashcommand_t& event) {
        std::string cmd = event.command.get_command_name();

        try {
            if (cmd == SlashCommands::name) {
                SlashCommands::execute(event);
            } else {
                event.reply(dpp::message("\u274C Unknown command.").set_flags(dpp::m_ephemeral));
            }
        } catch (const std::exception& e) {
            std::cerr << "\033[31m[InteractionCreate] Error in /" << cmd << ": " << e.what() << "\033[0m" << std::endl;
            if (!event.replied) {
                event.reply(dpp::message("\u274C Error executing command!").set_flags(dpp::m_ephemeral));
            }
        }
    }
}
