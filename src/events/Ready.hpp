#pragma once
#include <dpp/dpp.h>
#include <iostream>

namespace Events {
    inline void onReady(const dpp::ready_t& event, dpp::cluster& bot, const std::string& botName) {
        bot.set_presence(dpp::presence(dpp::ps_online, dpp::at_game, botName));
        std::cout << "\033[32m[Ready] Logged in as " << bot.me.username << "\033[0m" << std::endl;
    }
}
