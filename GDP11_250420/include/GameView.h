#pragma once

#include "Menu.h"



class GameView : public Menu
{
public:
	GameView();
	void Update();
	void GuiDraw();
private:
	int cursorX;
	int cursorY;
};