#pragma once

#include <map>
#include <functional>
#include <string>
#include "View.h"




class Menu : public View
{
public:
	Menu();
	void AddOption(std::string label, std::function<void()> callback);
	void Update();
protected:
	int cursor;
	std::vector<std::string> optionsOrder;
	std::unordered_map<std::string, std::function<void()>> options;
};