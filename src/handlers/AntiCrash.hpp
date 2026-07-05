#pragma once
#include <string>
#include <iostream>
#include <csignal>
#include "../core/WebhookUtil.hpp"

class AntiCrash {
public:
    static void init(const std::string& webhookUrl) {
        webhookUrl_ = webhookUrl;
        std::signal(SIGABRT, signalHandler);
        std::signal(SIGFPE, signalHandler);
        std::signal(SIGILL, signalHandler);
        std::signal(SIGSEGV, signalHandler);
        std::signal(SIGTERM, signalHandler);
        std::set_terminate(terminateHandler);
        std::cout << "\033[32m[AntiCrash] Active\033[0m" << std::endl;
    }

    static void reportError(const std::string& title, const std::string& message) {
        std::cerr << "\033[31m[AntiCrash] " << title << ": " << message << "\033[0m" << std::endl;
        if (!webhookUrl_.empty()) {
            WebhookUtil::sendWebhook(webhookUrl_, "**" + title + "**\n```\n" + message + "\n```");
        }
    }

private:
    static std::string webhookUrl_;

    static void signalHandler(int sig) {
        std::cerr << "\033[31m[AntiCrash] Signal caught: " << sig << "\033[0m" << std::endl;
        if (!webhookUrl_.empty()) {
            WebhookUtil::sendWebhook(webhookUrl_, "**Signal Caught**\n```\nSignal: " + std::to_string(sig) + "\n```");
        }
        std::exit(sig);
    }

    static void terminateHandler() {
        std::cerr << "\033[31m[AntiCrash] terminate() called\033[0m" << std::endl;
        if (!webhookUrl_.empty()) {
            WebhookUtil::sendWebhook(webhookUrl_, "**Terminate Called**\n```\nstd::terminate() was invoked\n```");
        }
        std::abort();
    }
};
