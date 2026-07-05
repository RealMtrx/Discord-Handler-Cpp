# Discord Handler C++

A modern, feature-rich Discord bot handler built with **DPP (D++)**, featuring both slash commands and prefix commands with a robust modular architecture designed for scalability and maintainability.

## 🚀 Features

- **Dual Command System**: Support for both slash commands and prefix commands
- **Modular Architecture**: Clean separation of concerns with dedicated handlers
- **Anti-Crash System**: Comprehensive error handling and monitoring
- **Event-Driven**: Fully event-driven architecture with DPP
- **Webhook Logging**: Real-time logging for errors and guild events via libcurl
- **MongoDB Integration**: Persistent data storage (requires mongocxx)
- **Cooldown System**: Per-command cooldown management
- **Environment Configuration**: Secure configuration with custom .env parser

## 📁 Project Structure

```
Discord-Handler-Cpp/
├── CMakeLists.txt                # CMake build configuration with FetchContent
├── src/                          # Source code
│   ├── main.cpp                  # Main bot entry point
│   ├── config/Config.hpp         # Bot configuration from .env
│   ├── Core/                     # Core utilities
│   │   ├── CommandUtils.hpp      # Cooldown and utilities
│   │   ├── Emojis.hpp            # Centralized emoji definitions
│   │   └── WebhookUtil.hpp       # Webhook utility
│   ├── Database/
│   │   └── Mongo.hpp             # MongoDB connection (stub)
│   ├── Events/                   # Discord event handlers
│   │   ├── GuildCreate.hpp       # Handler when bot joins a server
│   │   ├── GuildDelete.hpp       # Handler when bot leaves a server
│   │   ├── InteractionCreate.hpp # Handles slash command interactions
│   │   ├── MessageCreate.hpp     # Handles prefix commands
│   │   └── Ready.hpp             # Bot ready event
│   ├── Handlers/                 # Handlers for modularity
│   │   ├── AntiCrash.hpp         # Crash prevention and error handling
│   │   └── Logger.hpp            # Logger for bot activity
│   ├── Models/
│   │   └── UserModel.hpp         # User data model
│   └── Commands/
│       ├── Prefix/               # Prefix commands
│       │   └── Ping.hpp          # Example prefix ping command
│       └── Slash/                # Slash commands
│           └── Ping.hpp          # Example slash ping command
```

## 🔧 Installation

1. **Clone the repository**

   ```bash
   git clone https://github.com/RealMtrx/Discord-Handler-Cpp.git
   cd Discord-Handler-Cpp
   ```

2. **Build the project**

   ```bash
   cmake -B build
   cmake --build build
   ```

3. **Environment Setup**

   Copy `.env.example` to `.env` and fill in your values:

   ```env
   TOKEN=your_bot_token_here
   PREFIX=!
   BOT_NAME=Discord Handler
   MONGO_URI=mongodb://localhost:27017/discord-handler
   ERROR_WEBHOOK=https://discord.com/api/webhooks/your_webhook
   GUILD_LOG_WEBHOOK=https://discord.com/api/webhooks/your_webhook
   ```

4. **Run the bot**

   ```bash
   ./build/Discord-Handler-Cpp
   ```

## 📋 Dependencies

- **DPP**: v10.1.4 - Discord API wrapper (auto-downloaded via FetchContent)
- **libcurl**: - HTTP client for webhooks
- **OpenSSL**: - TLS support
- **zlib**: - Compression support

## 📝 Command Development

### Creating Slash Commands

Create a new file in `src/Commands/Slash/[name].hpp`:

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

Create a new file in `src/Commands/Prefix/[name].hpp`:

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

---

**Discord Handler** — Built by **Mtrx** — Discord: **0hu2**
