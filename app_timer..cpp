#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include "app_timer.h"


class app_timer {
public:
    app_timer() : isRunning(false) {}

    // Set the callback event handler
    void setCallback(const std::function<void()>& callback) {
        this->callback = callback;
    }

    // Start the timer with the specified interval in milliseconds
    void start(int interval) {
        if (isRunning) {
            return;
        }

        isRunning = true;
        std::thread timerThread([this, interval]() {
            while (isRunning) {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                if (callback) {
                    callback();
                }
            }
        });
        timerThread.detach();
    }

    // Stop the timer
    void stop() {
        isRunning = false;
    }

private:
    std::function<void()> callback;
    bool isRunning;
};