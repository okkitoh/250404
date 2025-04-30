#pragma once

#include "View.h"
#include "Sprites.h"
#include "raylib.h"


class GameOverView : public View
{
public:
	GameOverView();
	void Update();
	void GuiDraw();
private:
	Sprite splash;
};