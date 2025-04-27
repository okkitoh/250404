#pragma once

#include <vector>
#include <queue>
#include <memory>
#include "defines.h"
#include "View.h"
#include "Menu.h"
#include "Hud.h"






// Adhering to rule: Only change view stack from root scope which is main().
// Callbacks are nice and all but events being able to delete their parents is no bueno.
//
// To get around this limitation, pass messages around to move from screen to screen
// which main's update will be responsible for handling the view stack/screen to screen portion.

struct ActionEvent
{
	Action action = Action::IDLE;
	int cursor = -1;
};

// Singleton Pattern
// The dark forbidden technique
class GameContext
{
public:
	static GameContext& GetRef()
	{
		if (instance == nullptr)
		{
			instance.reset(new GameContext());
		}
		return *instance;
	}
	void SetPlayerInput(Action action)
	{
		EventQueue.push(ActionEvent{ action, -1 });
	}
	void SetPlayerInput(Action action, int cursor)
	{
		EventQueue.push(ActionEvent{ action, cursor });
	}
	ActionEvent ConsumePlayerInput()
	{
		if (EventQueue.empty())
		{
			return ActionEvent{ Action::IDLE, -1 };
		}
		ActionEvent temp = EventQueue.front();
		EventQueue.pop();
		return temp;
	}
	void PushView(View *view)
	{
	}
private:
	GameContext()
	{

	}
private:
	static std::unique_ptr<GameContext> instance;
	std::vector<View*> ViewStack;
	std::queue<ActionEvent> EventQueue;
};
