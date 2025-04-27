#pragma once

#include "GameState.h"
#include "View.h"



class GameOverView : public View
{
public:
	GameOverView();
	void Update();
	void GuiDraw();
};