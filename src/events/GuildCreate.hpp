#pragma once
#include <dpp/dpp.h>
#include <iostream>

namespace Events {
    inline void onGuildCreate(const dpp::guild_create_t& event) {
        std::cout << "\033[36m[GuildCreate] Joined: " << event.created->name << " (" << event.created->id << ")\033[0m" << std::endl;
    }
}
