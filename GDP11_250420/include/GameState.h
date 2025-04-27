#pragma once

#include <memory>
#include "DGDef.h"
#include "View.h"
#include "Player.h"
#include "Enemy.h"



struct GameState
{
// Secret Forbidden Technique: Singleton Pattern
private:
	GameState() : difficulty(1), playerAction(EAction::IDLE) {}
public:
	static GameState& GetRef()
	{
		// §6.7[stmt.dcl] p4 If control enters the declaration concurrently while the variable is being initialized,
		// the concurrent execution shall wait for completion of the initialization.
		// meaning thread-safe
		static GameState instance;
		return instance;
	}
	~GameState()
	{
		printf("game state destructor\n");
	}

	// PREVENT DUPLICATION
	GameState(const GameState& other) = delete; // disable copy constructor
	void operator=(const GameState& other) = delete; // disable assignment



public:
	EViewContext phase = START_MENU;
	std::vector<View *> ViewStack;
	int difficulty = 1;
	Enemy Enemy[MAX_ENEMIES];
	Player MainPlayer;
	EAction playerAction = EAction::IDLE; // ideally should be a message queue but seems abit overkill for this
	inline void NewGame()
	{
		difficulty = 1;
		this->MainPlayer.Reset();
		Enemy[0].IncreaseDifficulty(difficulty);
		SetPhase(EViewContext::START_MENU);
	}
	inline void SetPhase(EViewContext phase)
	{
		this->phase = phase;
	}
	inline EViewContext GetPhase()
	{
		return phase;
	}
	inline bool IsRunning() {
		return phase != EViewContext::EXIT;
	}

	inline void SetPlayerAction(EAction playerAction)
	{
		this->playerAction = playerAction;
	}
	inline EAction ConsumePlayerAction()
	{
		EAction temp = this->playerAction;
		this->playerAction = EAction::IDLE;
		return temp;
	}

	inline void PushView(View *view)
	{
		if (!ViewStack.empty())
		{
			ViewStack.back()->SetActive(false);
		}
		view->SetActive(true);
		ViewStack.push_back(view);

	}
	inline void PruneViews()
	{
		for (int i = ViewStack.size() -1; i >= 0; --i)
		{
			if (!ViewStack[i]->IsValid())
			{
				delete ViewStack[i];
				ViewStack.erase(ViewStack.begin() + i);
			}
		}
	}
	inline void UpdateViews()
	{
		// c++ polymorphism check which derived class

		// update with first active top of stack 
		for (int i = ViewStack.size() - 1; i >= 0; --i)
		{
			if (ViewStack[i]->IsActive())
			{
				ViewStack[i]->Update();
				break;
			}
		}
		PruneViews();
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