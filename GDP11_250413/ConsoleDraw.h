#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>


#include "Phone.h"

class ConsoleDraw
{
public:
	ConsoleDraw() : running(false), drawing(false) {
		buffer.resize(5, "");
	};
	~ConsoleDraw() { stop(); };
	void start();
	void stop();
	void draw();
	void addBuffer(std::vector<std::string> todraw);
private:
	std::thread d_thread;
	std::mutex d_mutex;
	std::condition_variable d_cv;
	bool drawing;

	std::vector<std::string> buffer;
	std::mutex b_mutex;

	std::atomic<bool> running;
};