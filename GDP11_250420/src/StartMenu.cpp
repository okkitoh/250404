
#include "StartMenu.h"
#include "raylib.h"
#include "GameState.h"
#include "Hud.h"

//Testing only
#include "GameOverView.h"


StartMenu::StartMenu() : Menu()
{
	AddOption("Start Game", [this]() {
		GameState::GetRef().NewGame();
		GameState::GetRef().SetPhase(EViewContext::GAME_RUNNING);
		GameState::GetRef().PushView(new GameOverView());
		this->Invalidate();
		/*
		context.ClearViews();
		context.ViewStack.push_back(new Hud(context));
		context.difficulty = 1;
		context.MainPlayer = Player();
		context.Enemy[0] = Enemy();
		context.Enemy[0].IncreaseDifficulty(context.difficulty);
		context.phase = EViewContext::GAME_RUNNING;
		*/
	});
	AddOption("Exit", []() {
		GameState::GetRef().SetPhase(EViewContext::EXIT);
	});
}

void StartMenu::GuiDraw()
{
	int xpos = 60;
	int ypos = WINDOW_HEIGHT - 140;
	for (int i = 0; i < optionsOrder.size(); ++i)
	{
		if (cursor == i)
		{
			DrawTriangle({ xpos + 18.f, (float)ypos }, { xpos + 18.f, (float)ypos + 20 }, { xpos + 38.f, (float)ypos + 10 }, RED);
		}
		DrawText(optionsOrder[i].c_str(), xpos + 60, ypos, 18, WHITE);
		ypos += 40;
	}
}
