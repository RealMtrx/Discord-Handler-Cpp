# Discord Handler Cpp

A modern, feature-rich Discord bot handler built with C++ and DPP (D++), featuring both slash commands and prefix commands with a robust modular architecture.

## Features

- Slash commands and prefix commands
- Modular architecture (commands, events, handlers)
- Anti-crash system with webhook error reporting
- Cooldown system
- Unicode emoji exports
- CMake-based build system

## Prerequisites

- C++20 compatible compiler (GCC 8+, Clang 6+, MSVC 2019+)
- CMake 3.16+
- OpenSSL development libraries
- zlib development libraries
- libcurl development libraries (for webhooks)

## Build & Run

```bash
git clone https://github.com/RealMtrx/Discord-Handler-Cpp.git
cd Discord-Handler-Cpp
cp .env.example .env
# Edit .env with your bot token
cmake -B build
cmake --build build
./build/Discord-Handler-Cpp
```

## Project Structure

```
src/
├── main.cpp                  # Entry point
├── config/Config.hpp         # Configuration loader (.env)
├── commands/slash/Ping.hpp   # Slash ping command
├── commands/prefix/Ping.hpp  # Prefix ping command
├── core/Emojis.hpp           # Unicode emoji exports
├── core/CommandUtils.hpp/cpp # Cooldown utilities
├── core/WebhookUtil.hpp      # Webhook utility
├── database/Mongo.hpp        # MongoDB connection (stub)
├── events/Ready.hpp          # Ready event
├── events/GuildCreate.hpp    # Guild join event
├── events/GuildDelete.hpp    # Guild leave event
├── events/InteractionCreate.hpp # Slash command handler
├── events/MessageCreate.hpp  # Prefix command handler
├── handlers/AntiCrash.hpp/cpp # Error handling
├── handlers/Logger.hpp       # Startup logger
└── models/UserModel.hpp      # User data model
```

## MongoDB

MongoDB support requires the mongocxx driver. By default, the database module is a stub. To enable MongoDB:

1. Install libmongocxx-dev (or build from source)
2. Add to CMakeLists.txt:
   ```cmake
   find_package(libmongocxx REQUIRED)
   target_link_libraries(${PROJECT_NAME} PRIVATE mongocxx::mongocxx)
   ```
3. Update `database/Mongo.hpp` with actual implementation

## License

MIT License - see [LICENSE](LICENSE) for details.
