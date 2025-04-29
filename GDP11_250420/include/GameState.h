#pragma once

#include <memory>
#include "DGDef.h"
#include "View.h"
#include "Player.h"
#include "Enemy.h"



struct GameState
{
// Secret Forbidden Technique: Singleton Pattern
// Anti-pattern that seeps into every part of the codebase (find all references on GetRef() D:)
// Makes testing extremely difficult requiring a dependency injection alternative (DI is the next evolutionary step from singletons)
// The upside is easy brute force solution for small projects
// TODO move view system into a view manager object. one ui view manager per player on a controller object which is what UE prefers.
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
		printf("game state destructor. saving...\n");
	}

	// PREVENT DUPLICATION
	GameState(const GameState& other) = delete; // disable copy constructor
	void operator=(const GameState& other) = delete; // disable assignment
	/* END SINGLETON DEF */


	/* View Management */
public:
	std::vector<View*> ViewStack; // TODO make this private


private:
	EViewContext phase = START_MENU;
public:
	
	int difficulty = 1;
	Enemy Enemies[MAX_ENEMIES];
	Player MainPlayer;
	EAction playerAction = EAction::IDLE; // ideally should be a message queue but seems abit overkill in turned-based. only ever 2 actions, confirm/cancel 
	inline void NewGame()
	{
		difficulty = 1;
		this->MainPlayer.Reset();
		Enemies[0].IncreaseDifficulty(difficulty);
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
	inline EAction PeekPlayerAction()
	{
		return this->playerAction;
	}
	inline EAction ConsumePlayerAction()
	{
		EAction temp = this->playerAction;
		this->playerAction = EAction::IDLE;
		return temp;
	}
	inline void PopView()
	{
		if (!ViewStack.empty())
		{
			ViewStack.back()->SetActive(false);
			ViewStack.back()->Invalidate();
		}
	}
	inline void PushView(View* view)
	{
		if (!ViewStack.empty())
		{
			ViewStack.back()->SetActive(false);
		}
		view->SetActive(true);
		ViewStack.push_back(view);
	}
	inline void ClearViews()
	{
		if (ViewStack.empty())
		{
			return;
		}
		auto it = ViewStack.begin();
		while (it != ViewStack.end())
		{
			(*it)->Invalidate();
			++it;
		}
	}
	inline void UpdateViews()
	{
		for (int i = ViewStack.size() - 1; i >= 0; --i)
		{
			if (ViewStack[i]->IsActive())
			{
				ViewStack[i]->Update();
			}
		}
		PruneViews();
	}
	inline void GUIDrawViews()
	{
		for (int i = 0; i < ViewStack.size(); ++i)
		{
			if (ViewStack[i]->IsValid())
			{
				ViewStack[i]->GuiDraw();
			}
		}
	}
private:
	inline void PruneViews()
	{
		bool pruned = false;
		for (int i = ViewStack.size() - 1; i >= 0; --i)
		{
			if (!ViewStack[i]->IsValid())
			{
				pruned = true;
				delete ViewStack[i];
				ViewStack.erase(ViewStack.begin() + i);
			}
		}
		if (pruned && ViewStack.size())
		{
			ViewStack.back()->SetActive(true);
		}
	}
};
