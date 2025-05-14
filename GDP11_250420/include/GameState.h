#pragma once

#include <memory>
#include "DGDef.h"
#include "View.h"
#include "Animation.h"
#include "AnimationHandle.h"
#include "Player.h"
#include "Enemy.h"



struct GameState
{
// Secret Forbidden Technique: Singleton Pattern
// Anti-pattern that seeps into every part of the codebase (find all references on GetRef() D:)
// Makes testing extremely difficult requiring a dependency injection alternative (DI is the next evolutionary step from singletons)
// The upside is easy brute force solution for small projects
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



private:
	EViewContext phase = START_MENU;
	std::vector<View*> ViewStack;
	std::vector<Animation*> AnimationStack;
public:
	int difficulty = 1;
	Enemy Enemies[MAX_ENEMIES];
	Player MainPlayer;
	EAction playerAction = EAction::IDLE; // ideally should be a message queue but seems abit overkill in turned-based. only ever 2 actions, confirm/cancel 
	AnimationHandle playerModel = { 0 };



	inline void NewGame()
	{
		difficulty = 1;
		this->MainPlayer.Reset();
		playerModel = RegisterAnimation(new Animation(SpriteID::KNIGHT_IDLE, { WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2 }, true));
		Enemies[0].IncreaseDifficulty(difficulty);
		SetPhase(EViewContext::START_MENU);
	}
	inline void SetPhase(EViewContext phase) { this->phase = phase; }
	inline EViewContext GetPhase() { return phase; }
	inline bool IsRunning() { return phase != EViewContext::EXIT; }

	inline void SetPlayerAction(EAction playerAction) { this->playerAction = playerAction; }
	inline EAction PeekPlayerAction() { return this->playerAction; }
	inline EAction ConsumePlayerAction()
	{
		EAction temp = this->playerAction;
		this->playerAction = EAction::IDLE;
		return temp;
	}

	inline AnimationHandle RegisterAnimation(Animation *animation)
	{
		static unsigned int animid = 0;
		AnimationHandle handle { ++animid, animation };
		AnimationStack.push_back(animation);
		return handle;
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
	inline void DrawAnimations()
	{
		for (int i = 0; i < AnimationStack.size(); ++i)
		{
			if (AnimationStack[i]->IsValid())
			{
				AnimationStack[i]->Draw();
			}
		}
		// prune invalidated animations
		for (int i = AnimationStack.size() - 1; i >= 0; --i)
		{
			if (!AnimationStack[i]->IsValid())
			{
				delete AnimationStack[i];
				// Burden of ownership rests on user
				AnimationStack.erase(AnimationStack.begin() + i);
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
