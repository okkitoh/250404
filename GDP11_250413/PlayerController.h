#pragma once

#include <thread>
#include <atomic>
#include <queue>
#include <mutex>



/*
 * Basic input controller 
 */
class PlayerController
{
public:
	PlayerController() : running(false) {}
	~PlayerController() { stop(); }
	
	void start();
	void stop();
	bool hasInput();
	char getInput();
private:
	std::thread inputThread;
	std::queue<char> inputQueue;
	std::mutex i_mutex; // lock to prevent multiple thread access. In other words, 
					  // a tool to ensure that only 1 thread can access a shared resource at a time
	                  // could be thread that reads and saves user input (producer)
	                  // could be main thread that reads and performs actions using user input (consumer) 
	std::atomic<bool> running;
};