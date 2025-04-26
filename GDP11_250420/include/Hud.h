#pragma once

#include "Menu.h"

class Hud : public Menu
{
public:
	Hud(GameState &context);
	void Update();
	void GuiDraw();
private:
	int cursorX;
	int cursorY;
	GameState* context;
};