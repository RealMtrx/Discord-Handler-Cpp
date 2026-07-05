#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

struct Config {
    std::string token;
    std::string clientId;
    std::string botName = "Discord Handler";
    std::string prefix = "$";
    std::vector<std::string> ownerIds;
    std::string mongoUri;
    std::string errorWebhook;
    std::string slashCommandWebhook;
    std::string prefixCommandWebhook;
    std::string joinGuildWebhook;
    std::string leaveGuildWebhook;
    std::string readyWebhook;

    static Config load() {
        Config cfg;
        auto env = loadEnv(".env");
        cfg.token = getOr(env, "TOKEN", "#");
        cfg.clientId = getOr(env, "CLIENT_ID", "#");
        cfg.botName = getOr(env, "BOT_NAME", "Discord Handler");
        cfg.prefix = getOr(env, "PREFIX", "$");
        std::string ids = getOr(env, "OWNER_IDS", "#");
        std::stringstream ss(ids);
        std::string item;
        while (std::getline(ss, item, ',')) {
            cfg.ownerIds.push_back(item);
        }
        cfg.mongoUri = getOr(env, "MONGODB_URI", "#");
        cfg.errorWebhook = getOr(env, "ERROR_WEBHOOK", "");
        cfg.slashCommandWebhook = getOr(env, "SLASH_COMMAND_WEBHOOK", "");
        cfg.prefixCommandWebhook = getOr(env, "PREFIX_COMMAND_WEBHOOK", "");
        cfg.joinGuildWebhook = getOr(env, "JOIN_GUILD_WEBHOOK", "");
        cfg.leaveGuildWebhook = getOr(env, "LEAVE_GUILD_WEBHOOK", "");
        cfg.readyWebhook = getOr(env, "READY_WEBHOOK", "");
        return cfg;
    }

private:
    static std::unordered_map<std::string, std::string> loadEnv(const std::string& path) {
        std::unordered_map<std::string, std::string> env;
        std::ifstream file(path);
        if (!file.is_open()) return env;
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;
            auto eq = line.find('=');
            if (eq == std::string::npos) continue;
            std::string key = line.substr(0, eq);
            std::string val = line.substr(eq + 1);
            env[key] = val;
        }
        return env;
    }

    static std::string getOr(const std::unordered_map<std::string, std::string>& env, const std::string& key, const std::string& def) {
        auto it = env.find(key);
        return it != env.end() && !it->second.empty() ? it->second : def;
    }
};
