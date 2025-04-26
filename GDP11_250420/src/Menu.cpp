
#include "Menu.h"
#include "Hud.h"
#include "raylib.h"
#include <vector>



Menu::Menu()
{
	cursor = 0;
	active = true;
	options.clear();
}
Menu::Menu(GameState& context)
{
	cursor = 0;
	active = true;
	options.clear();
	AddOption("Start Game", [&context]() {
		context.ViewStack.clear();
		context.ViewStack.push_back(new Hud(context));
		context.phase = GAMEPHASE::GAME_RUNNING;
	});
	AddOption("Exit", [&context]() {
		context.phase = GAMEPHASE::EXIT;
	});
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
void Menu::GuiDraw()
{
	int xpos = 60;
	int ypos = WINDOW_HEIGHT - 140;
	for (int i = 0; i < optionsOrder.size(); ++i)
	{
		if (cursor == i)
		{
			DrawTriangle({ xpos + 18.f, (float)ypos }, { xpos + 18.f, (float)ypos + 20 }, { xpos + 38.f, (float)ypos + 10 }, RED);
		}
		DrawText(optionsOrder[i].c_str(), xpos + 60, ypos, 18, WHITE);
		ypos += 40;
	}
}



