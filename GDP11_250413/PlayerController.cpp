
#include "PlayerController.h"
#include <iostream>
#include <conio.h>


void PlayerController::start()
{
    if (running) return;
    
    running = true;
    inputThread = std::thread([this]() {
        while (running)
        {
            if (_kbhit())
            {
                char c = _getch();
                std::lock_guard<std::mutex> lock(i_mutex);
                inputQueue.push(c);
                // mutex lock is released automatically when scope ends
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });
}
void PlayerController::stop()
{
	running = false;
    if (inputThread.joinable())
        inputThread.join();
}
bool PlayerController::hasInput()
{
    std::lock_guard<std::mutex> lock(i_mutex);
    return !inputQueue.empty();
}
char PlayerController::getInput()
{
    std::lock_guard<std::mutex> lock(i_mutex);
    if (inputQueue.empty())
    {
        return '\0';
    }

    char input = inputQueue.front();
    inputQueue.pop();
    return input;
}
