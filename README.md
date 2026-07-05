<div align="center">
  <h1>Discord Handler — C++</h1>
  <p><strong>A production-ready Discord bot framework built with DPP (D++) and MongoDB — slash commands, prefix commands, anti-crash, webhook logging via libcurl, and a modular src/ architecture.</strong></p>

  <p>
    <a href="https://github.com/RealMtrx/Discord-Handler-Cpp/blob/main/LICENSE"><img src="https://img.shields.io/badge/license-MIT-blue.svg" alt="License"></a>
    <a href="https://github.com/RealMtrx/Discord-Handler-Cpp/releases"><img src="https://img.shields.io/badge/version-0.9.0--beta-yellow" alt="Version 0.9.0 Beta"></a>
    <a href="https://github.com/RealMtrx/Discord-Handler-Cpp/stargazers"><img src="https://img.shields.io/github/stars/RealMtrx/Discord-Handler-Cpp" alt="Stars"></a>
    <a href="https://github.com/RealMtrx/Discord-Handler-Cpp/issues"><img src="https://img.shields.io/github/issues/RealMtrx/Discord-Handler-Cpp" alt="Issues"></a>
    <a href="https://github.com/RealMtrx/Discord-Handler-Cpp/network"><img src="https://img.shields.io/github/forks/RealMtrx/Discord-Handler-Cpp" alt="Forks"></a>
    <a href="https://github.com/RealMtrx/Discord-Handler/graphs/contributors"><img src="https://img.shields.io/badge/ecosystem-26%20repos-brightgreen" alt="26 Repos"></a>
    <a href="https://discord.gg/0hu2"><img src="https://img.shields.io/badge/discord-0hu2-5865F2" alt="Discord"></a>
  </p>

  <br>

  <p>
    <a href="#-features">Features</a> •
    <a href="#-quick-start">Quick Start</a> •
    <a href="#-project-structure">Structure</a> •
    <a href="#-api-reference">API</a> •
    <a href="#-database-edition">SQL Edition</a> •
    <a href="#-related-repositories">Ecosystem</a>
  </p>
</div>

---

## Overview

Discord Handler C++ is a production-ready bot framework using **DPP (Discord++) 10.1.4** with C++20 and CMake 3.16+. It provides a dual command system (slash + prefix), anti-crash protection, webhook logging via libcurl, MongoDB integration (via mongocxx), and per-command cooldowns — all in a clean header/source layout.

## Features

- **Dual Command System** — Slash and prefix commands with DPP's native interaction API
- **Anti-Crash System** — Signal handlers and exception safety
- **Webhook Logging** — HTTP webhook delivery via libcurl for errors and guild events
- **MongoDB Integration** — mongocxx driver for persistent data storage
- **Cooldown System** — Per-command cooldown enforcement
- **Environment Configuration** — Custom `.env` parser (no external dependency)
- **Event-Driven** — Modular event handlers for all major Discord gateway events
- **FetchContent Build** — DPP auto-downloaded at configure time via CMake FetchContent

## Quick Start

```bash
# Clone the repository
git clone https://github.com/RealMtrx/Discord-Handler-Cpp.git
cd Discord-Handler-Cpp

# Configure and build
cmake -B build
cmake --build build

# Configure environment
cp .env.example .env
# Edit .env with your bot token, MongoDB URI, and webhook URLs

# Run the bot
./build/Discord-Handler-Cpp
```

### Environment Variables

```env
TOKEN=your_bot_token
PREFIX=!
BOT_NAME=Discord Handler
MONGO_URI=mongodb://localhost:27017/discord-handler
ERROR_WEBHOOK=https://discord.com/api/webhooks/...
GUILD_LOG_WEBHOOK=https://discord.com/api/webhooks/...
```

## Project Structure

```
Discord-Handler-Cpp/
├── CMakeLists.txt                   # CMake build (C++20, FetchContent for DPP)
├── src/
│   ├── main.cpp                     # Entry point — boots anti-crash, loads handlers, starts cluster
│   ├── config/Config.hpp            # .env configuration parser
│   ├── Core/
│   │   ├── CommandUtils.hpp         # Cooldown map & utility functions
│   │   ├── CommandUtils.cpp
│   │   ├── Emojis.hpp               # Centralized emoji constants
│   │   └── WebhookUtil.hpp          # Webhook HTTP sender (libcurl)
│   ├── Database/
│   │   └── Mongo.hpp                # MongoDB connection (mongocxx)
│   ├── Events/
│   │   ├── GuildCreate.hpp          # onGuildJoin
│   │   ├── GuildDelete.hpp          # onGuildLeave
│   │   ├── InteractionCreate.hpp    # Slash command dispatcher
│   │   ├── MessageCreate.hpp        # Prefix command dispatcher
│   │   └── Ready.hpp                # onReady
│   ├── Handlers/
│   │   ├── AntiCrash.hpp            # Signal & exception handler
│   │   ├── AntiCrash.cpp
│   │   └── Logger.hpp               # Console logging utilities
│   ├── Models/
│   │   └── UserModel.hpp            # User data model
│   └── Commands/
│       ├── Prefix/
│       │   └── Ping.hpp             # Example prefix command
│       └── Slash/
│           └── Ping.hpp             # Example slash command
```

## API Reference

### Bot Initialization

```cpp
// main.cpp
#include <dpp/dpp.h>
#include "config/Config.hpp"
#include "handlers/AntiCrash.hpp"

int main() {
    Config& config = Config::getInstance();
    AntiCrash::setup();

    dpp::cluster bot(config.token);
    bot.on_log(dpp::utility::cout_logger());

    // Register event handlers
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        // dispatch to command map
    });

    bot.on_message_create([](const dpp::message_create_t& event) {
        // dispatch to prefix command map
    });

    bot.start(dpp::st_wait);
    return 0;
}
```

### Creating Slash Commands

Create a file in `src/Commands/Slash/<Name>.hpp`:

```cpp
#pragma once
#include <dpp/dpp.h>

namespace slash {

struct Ping {
    static constexpr auto name = "ping";
    static constexpr auto description = "Replies with Pong!";

    static void execute(const dpp::slashcommand_t& event) {
        event.reply("Pong! 🏓");
    }
};

}
```

### Creating Prefix Commands

Create a file in `src/Commands/Prefix/<Name>.hpp`:

```cpp
#pragma once
#include <dpp/dpp.h>

namespace prefix {

struct Ping {
    static constexpr auto name = "ping";

    static void execute(const dpp::message_create_t& event, const std::vector<std::string>& args) {
        event.reply("Pong! 🏓");
    }
};

}
```

## Adding Commands

Commands are discovered at compile time through header inclusion — add a new header in the correct `Commands/Slash/` or `Commands/Prefix/` directory and register it in the command dispatcher. No runtime reflection needed.

## Database Edition

This repository uses **MongoDB** (mongocxx). If you prefer a relational database, check out the **SQL Edition**:

[![Discord-Handler-Cpp-Sequelize](https://img.shields.io/badge/Discord--Handler--Cpp--Sequelize-sqlpp11%20ORM-blue)](https://github.com/RealMtrx/Discord-Handler-Cpp-Sequelize)

The SQL edition replaces `Mongo.hpp` with **sqlpp11** ORM and uses SQLite as the default backend.

## Related Repositories

The Discord Handler ecosystem spans **26 repositories** across 13 programming languages — each with a MongoDB edition and a SQL (Sequelize) edition.

### Core Framework (MongoDB)

| Language | Repository |
|---|---|
| TypeScript | [Discord-Handler-Ts](https://github.com/RealMtrx/Discord-Handler-Ts) |
| JavaScript | [Discord-Handler-Js](https://github.com/RealMtrx/Discord-Handler-Js) |
| Python | [Discord-Handler-Py](https://github.com/RealMtrx/Discord-Handler-Py) |
| Java | [Discord-Handler-Java](https://github.com/RealMtrx/Discord-Handler-Java) |
| Kotlin | [Discord-Handler-Kt](https://github.com/RealMtrx/Discord-Handler-Kt) |
| C++ | [Discord-Handler-Cpp](https://github.com/RealMtrx/Discord-Handler-Cpp) |
| C# | [Discord-Handler-Cs](https://github.com/RealMtrx/Discord-Handler-Cs) |
| Go | [Discord-Handler-Go](https://github.com/RealMtrx/Discord-Handler-Go) |
| Rust | [Discord-Handler-Rs](https://github.com/RealMtrx/Discord-Handler-Rs) |
| Dart | [Discord-Handler-Dart](https://github.com/RealMtrx/Discord-Handler-Dart) |
| PHP | [Discord-Handler-Php](https://github.com/RealMtrx/Discord-Handler-Php) |
| Ruby | [Discord-Handler-Rb](https://github.com/RealMtrx/Discord-Handler-Rb) |
| Lua | [Discord-Handler-Lua](https://github.com/RealMtrx/Discord-Handler-Lua) |

### Database Editions (SQL)

| Language | Repository |
|---|---|
| TypeScript | [Discord-Handler-Ts-Sequelize](https://github.com/RealMtrx/Discord-Handler-Ts-Sequelize) |
| JavaScript | [Discord-Handler-Js-Sequelize](https://github.com/RealMtrx/Discord-Handler-Js-Sequelize) |
| Python | [Discord-Handler-Py-Sequelize](https://github.com/RealMtrx/Discord-Handler-Py-Sequelize) |
| Java | [Discord-Handler-Java-Sequelize](https://github.com/RealMtrx/Discord-Handler-Java-Sequelize) |
| Kotlin | [Discord-Handler-Kt-Sequelize](https://github.com/RealMtrx/Discord-Handler-Kt-Sequelize) |
| C++ | [Discord-Handler-Cpp-Sequelize](https://github.com/RealMtrx/Discord-Handler-Cpp-Sequelize) |
| C# | [Discord-Handler-Cs-Sequelize](https://github.com/RealMtrx/Discord-Handler-Cs-Sequelize) |
| Go | [Discord-Handler-Go-Sequelize](https://github.com/RealMtrx/Discord-Handler-Go-Sequelize) |
| Rust | [Discord-Handler-Rs-Sequelize](https://github.com/RealMtrx/Discord-Handler-Rs-Sequelize) |
| Dart | [Discord-Handler-Dart-Sequelize](https://github.com/RealMtrx/Discord-Handler-Dart-Sequelize) |
| PHP | [Discord-Handler-Php-Sequelize](https://github.com/RealMtrx/Discord-Handler-Php-Sequelize) |
| Ruby | [Discord-Handler-Rb-Sequelize](https://github.com/RealMtrx/Discord-Handler-Rb-Sequelize) |
| Lua | [Discord-Handler-Lua-Sequelize](https://github.com/RealMtrx/Discord-Handler-Lua-Sequelize) |

> **Hub repository:** [Discord-Handler](https://github.com/RealMtrx/Discord-Handler) — the multi-language overview and documentation hub.

## License

This project is licensed under the MIT License — see the [LICENSE](https://github.com/RealMtrx/Discord-Handler-Cpp/blob/main/LICENSE) file for details.

---

Built by **Mtrx** — Discord: **0hu2**

[![Discord-Handler](https://img.shields.io/badge/Discord--Handler-Ecosystem%20Hub-5865F2)](https://github.com/RealMtrx/Discord-Handler)
