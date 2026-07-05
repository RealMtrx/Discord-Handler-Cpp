#include <dpp/dpp.h>
#include <iostream>
#include "config/Config.hpp"
#include "events/Ready.hpp"
#include "events/GuildCreate.hpp"
#include "events/GuildDelete.hpp"
#include "events/InteractionCreate.hpp"
#include "events/MessageCreate.hpp"
#include "handlers/AntiCrash.hpp"
#include "handlers/Logger.hpp"
#include "database/Mongo.hpp"

int main() {
    std::cout << "\033[36m" << "\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557" << "\033[0m" << std::endl;
    std::cout << "\033[36m" << "\u2551     Starting Discord Handler     \u2551" << "\033[0m" << std::endl;
    std::cout << "\033[36m" << "\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D" << "\033[0m" << std::endl;
    std::cout << std::endl;

    auto config = Config::load();

    std::cout << "\033[34m[System] Initializing AntiCrash...\033[0m" << std::endl;
    AntiCrash::init(config.errorWebhook);

    std::cout << "\033[34m[System] Connecting to MongoDB...\033[0m" << std::endl;
    bool mongoConnected = Mongo::connect(config);

    std::cout << "\033[34m[System] Creating Discord bot...\033[0m" << std::endl;
    dpp::cluster bot(config.token);

    bot.on_log([](const dpp::log_t& event) {
        if (event.severity >= dpp::ll_warning) {
            std::cerr << "[Log] " << event.message << std::endl;
        }
    });

    bot.on_ready([&bot, &config](const dpp::ready_t& event) {
        Events::onReady(event, bot, config.botName);

        bot.global_command_create(dpp::slashcommand("ping", "Replies with Pong!", bot.me.id), [](const dpp::confirmation_callback_t& cb) {
            if (cb.is_error()) {
                std::cerr << "\033[31m[Commands] Failed to register ping: " << cb.get_error().message << "\033[0m" << std::endl;
            } else {
                std::cout << "\033[32m[Commands] Slash command 'ping' registered\033[0m" << std::endl;
            }
        });

        Logger::startupReport({
            config.botName,
            1,
            1,
            5,
            true,
            Mongo::isConnected()
        });
    });

    bot.on_guild_create([](const dpp::guild_create_t& event) {
        Events::onGuildCreate(event);
    });

    bot.on_guild_delete([](const dpp::guild_delete_t& event) {
        Events::onGuildDelete(event);
    });

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        Events::onInteractionCreate(event);
    });

    bot.on_message_create([&bot, &config](const dpp::message_create_t& event) {
        Events::onMessageCreate(event, config, bot);
    });

    bot.start(dpp::st_wait);

    return 0;
}
