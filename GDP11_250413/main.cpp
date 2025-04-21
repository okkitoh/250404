
#include <iostream>
#include <vector>
#include <map>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "ConsoleDraw.h"
#include "PlayerController.h"
#include "Phone.h"

const std::chrono::duration<double, std::milli> FRAMEBUDGET_MS(250);

int main()
{
    std::vector<std::string> header = { 
        "E[x]it or ESC to end", 
        "Set an alarm for 3 seconds",
        "",
        "[1] Phone 1        [2] Phone 2",
        ""
    };

    Phone phone1 = Phone("iPhone16", 9391028);
    Phone phone2 = Phone("Galaxy18", 13224273);

    bool running = true;
 
    PlayerController inputThread;
    inputThread.start();
    ConsoleDraw drawThread;
    drawThread.start();

    std::chrono::steady_clock::time_point now;
    std::chrono::steady_clock::time_point prev = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point prev_nosleep = prev;
    while (running)
    {
        while (inputThread.hasInput())
        {
            char input = inputThread.getInput();
            if (input == 'x' || input == 27)
            {
                running = false;
                break;
            }

            if (input == '1')
            {
                phone1.SetTimer(3.0);
            }
            if (input == '2')
            {
                phone2.SetTimer(3.0);
            }
        }
        now = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> sinceLastFrame = now - prev;
        std::chrono::duration<double, std::milli> elapsedTime = now - prev_nosleep;
        phone1.Update((elapsedTime.count()) / 1000.0);
        phone2.Update((elapsedTime.count()) / 1000.0);
        drawThread.addBuffer(header);
        drawThread.addBuffer(phone1.PrintInformation());
        drawThread.addBuffer(phone2.PrintInformation());

        drawThread.draw();

        std::chrono::duration<double, std::milli> sleepAmount(0);
        if (sinceLastFrame < FRAMEBUDGET_MS)
        {
        	sleepAmount = FRAMEBUDGET_MS - sinceLastFrame;
        	std::this_thread::sleep_for(sleepAmount);
        }
        // advance prev by sleep amount
        prev = now + std::chrono::duration_cast<std::chrono::steady_clock::duration>(sleepAmount);
        prev_nosleep = now;
    }
    drawThread.stop();
    inputThread.stop();

    printf("thanks for playing!");
    return 0;
}
