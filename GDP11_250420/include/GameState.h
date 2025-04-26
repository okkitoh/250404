#pragma once

#include "View.h"
#include "Player.h"
#include "Enemy.h"


const float WINDOW_WIDTH = 1280.f;
const float WINDOW_HEIGHT = 720.f;
static const int MAX_DIFFICULTY = 5;
static const bool GOD_MODE = 0;
static const int MAX_ENEMIES = 1;


enum GAMEPHASE
{
	EXIT,
	START_MENU,
	GAME_RUNNING,
	GAME_OVER
};



struct GameState
{
	GAMEPHASE phase = START_MENU;
	std::vector<View *> ViewStack;
	int difficulty = 1;
	Enemy Enemy[MAX_ENEMIES];
	Player MainPlayer;
	Action playerAction = Action::WAIT; // ideally should be a message queue but seems abit overkill for this

	inline void SetPlayerAction(Action playerAction)
	{
		this->playerAction = playerAction;
	}

	inline Action ConsumePlayerAction()
	{
		Action temp = this->playerAction;
		this->playerAction = Action::WAIT;
		return temp;
	}
	inline void ClearViews()
	{
		while (!ViewStack.empty())
		{
			View* temp = ViewStack.back();
			ViewStack.pop_back();
			delete temp;
		}
	}

	inline void UpdateViews()
	{
		// update with first active top of stack 
		for (int i = ViewStack.size() - 1; i >= 0; --i)
		{
			if (ViewStack[i]->IsActive())
			{
				ViewStack[i]->Update();
				break;
			}
		}
	}
	inline void DrawViews()
	{
		for (int i = 0; i < ViewStack.size(); ++i)
		{
			if (ViewStack[i]->IsActive())
			{
				ViewStack[i]->GuiDraw();
			}
		}
	}
};