
#include "Menu.h"
#include "raylib.h"
#include <vector>



Menu::Menu()
{
	cursor = 0;
	options.clear();
}
void Menu::AddOption(std::string label, std::function<void()> callback)
{
	options[label] = callback;
	optionsOrder.push_back(label);
}
void Menu::Update()
{
	if (IsKeyPressed(KEY_UP))
	{
		cursor = (cursor + 1) % options.size();
	}
	if (IsKeyPressed(KEY_DOWN))
	{
		cursor = (cursor - 1);
		cursor = (cursor < 0 ? options.size() + cursor : cursor);
	}
	if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z)) // Confirm
	{
		std::string key = optionsOrder[cursor];
		std::unordered_map<std::string, std::function<void()>>::iterator it = options.find(key);
		if (it != options.end())
		{
			it->second();
		}
	}
	if (IsKeyPressed(KEY_X)) // Cancel
	{

	}
}




