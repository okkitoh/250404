
#include "GameView.h"
#include "GameState.h"
#include "Dialogue.h"
#include "raylib.h"
#include "raymath.h"



GameView::GameView() : Menu()
{
	cursorX = 0;
	cursorY = 0;
	AddOption("Attack", []() {
		GameState::GetRef().SetPlayerAction(EAction::ATTACK);
	});
	AddOption("Parry", []() {
		GameState::GetRef().SetPlayerAction(EAction::PARRY);
	});
	AddOption("Defend", []() {
		GameState::GetRef().SetPlayerAction(EAction::DEFEND);
	});
	AddOption("Items", []() {
		printf("Show item menu\n");
	});
}
void GameView::Update()
{
	if (IsKeyPressed(KEY_UP))
	{
		cursorY -= 1;
		if (cursorY < 0)
		{
			cursorY = 2 + cursorY;
		}
		cursor = cursorX * 2 + cursorY;
	}
	if (IsKeyPressed(KEY_DOWN))
	{
		cursorY = (cursorY + 1) % 2;
		cursor = cursorX * 2 + cursorY;
	}
	if (IsKeyPressed(KEY_LEFT))
	{
		cursorX -= 1;
		if (cursorX < 0)
		{
			cursorX = 2 + cursorX;
		}
		cursor = cursorX * 2 + cursorY;
	}
	if (IsKeyPressed(KEY_RIGHT))
	{
		cursorX = (cursorX + 1) % 2;
		cursor = cursorX * 2 + cursorY;
	}
	if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z)) // Confirm
	{
		std::string key = optionsOrder[cursor];
		std::unordered_map<std::string, std::function<void()>>::iterator it = options.find(key);
		if (it != options.end())
		{
			it->second();
		}
	}
}
void GameView::GuiDraw()
{
	DrawText("HP", 18, 18, 18, WHITE);
	float HP_size = 200 / GameState::GetRef().MainPlayer.GetMaxHealth();
	DrawRectangle(60, 18, HP_size * GameState::GetRef().MainPlayer.GetHealth(), 18, RED);
	DrawRectangle(60, 18, HP_size * GameState::GetRef().MainPlayer.GetMaxHealth(), 18, Color{ 230, 41, 55, 56 });
	DrawText(TextFormat("%d / %d", GameState::GetRef().MainPlayer.GetHealth(), GameState::GetRef().MainPlayer.GetMaxHealth()), 128, 18, 18, WHITE);

	const Enemy& enemy = GameState::GetRef().Enemies[0];
	std::string roundNumberLabel = "Round " + std::to_string(GameState::GetRef().difficulty);
	int labelSize = MeasureText(roundNumberLabel.c_str(), 32) / 2;
	DrawText(roundNumberLabel.c_str(), WINDOW_WIDTH / 2 - labelSize, 32, 32, WHITE);

	int namesize = MeasureText(enemy.GetName().c_str(), 32) / 2;
	DrawText(enemy.GetName().c_str(), WINDOW_WIDTH / 2.f - namesize, 72, 32, WHITE);

	float viewY = WINDOW_HEIGHT - 200;
	float viewX = 280;
	float spacingV = 100;
	float spacingH = 600;
	for (int i = 0; i < this->optionsOrder.size(); ++i)
	{
		DrawText(this->optionsOrder[i].c_str(), viewX, viewY, 36, WHITE);
		if (cursor == i)
		{
			DrawTriangle({ viewX - 30, viewY + 8 }, { viewX - 30, viewY + 20 + 8 }, { viewX - 30 + 20, viewY + 16}, RED);
		}
		viewY += spacingV;
		if (i == 1)
		{
			viewY = WINDOW_HEIGHT - 200;
			viewX += spacingH;
		}
	}


}