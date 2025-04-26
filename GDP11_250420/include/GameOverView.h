#pragma once

#include "GameState.h"
#include "View.h"



class GameOverView : public View
{
public:
	GameOverView(GameState &context);
	void Update();
	void GuiDraw();
private:
	GameState *context;
};