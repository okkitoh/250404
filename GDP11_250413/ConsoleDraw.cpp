
#include "ConsoleDraw.h"
#include <Windows.h>
#include <iostream>
#include <chrono>


void ConsoleDraw::start()
{
	if (running) return;

	running = true;
	d_thread = std::thread([this]() {

		while (running)
		{
			std::unique_lock<std::mutex> lock(d_mutex);
			d_cv.wait(lock, [this]() { return drawing; });
			drawing = false;

			system("cls");
			std::lock_guard<std::mutex> b_lock(b_mutex);
			for (int i = 0; i < buffer.size(); ++i)
			{
				std::cout << buffer[i] << "\n";
			}
			std::cout << std::endl;		
			buffer.clear();
			buffer.resize(5, "");
		}
	});
}
void ConsoleDraw::stop()
{
	running = false;
	if (d_thread.joinable())
	{
		buffer.clear();
		this->draw();
		d_thread.join();
	}
}
void ConsoleDraw::draw()
{
	std::lock_guard<std::mutex> lock(d_mutex);
	drawing = true;
	d_cv.notify_one();
}
void ConsoleDraw::addBuffer(std::vector<std::string> todraw)
{
	std::lock_guard<std::mutex> lock(b_mutex);
	if (buffer.size() < todraw.size()) {
		buffer.resize(todraw.size());
	}
	for (int i = 0; i < todraw.size(); ++i) {
		buffer[i] += todraw[i];
	}
}
