#pragma once

#include "Menu.h"

class Character;

class ItemMenu : public Menu
{
public:
	ItemMenu();
	void Update();
	void GuiDraw();
private:
	int maxcols;
};