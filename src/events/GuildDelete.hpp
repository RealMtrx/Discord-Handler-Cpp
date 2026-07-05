#pragma once
#include <dpp/dpp.h>
#include <iostream>

namespace Events {
    inline void onGuildDelete(const dpp::guild_delete_t& event) {
        std::cout << "\033[33m[GuildDelete] Left: " << event.guild_id << "\033[0m" << std::endl;
    }
}
