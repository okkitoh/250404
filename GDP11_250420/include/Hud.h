#pragma once

#include "Menu.h"

class Hud : public Menu
{
public:
	Hud();
	void Update();
	void GuiDraw();
private:
	int cursorX;
	int cursorY;
};