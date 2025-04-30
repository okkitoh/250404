
#include "GameOverView.h"
#include "GameState.h"
#include "StartMenu.h"



GameOverView::GameOverView()
{
	splash = Sprites::GetSprite(GRAVE);
}
void GameOverView::Update()
{
	if (GetKeyPressed())
	{
		GameState::GetRef().PopView();
		GameState::GetRef().PushView(new StartMenu());
	}
}
void GameOverView::GuiDraw()
{
	int scale = 3;
	DrawTextureEx(splash.tex, { (WINDOW_WIDTH / 2.f) - (splash.tex.width * scale / 2.f), -20.f }, 0, scale, WHITE);

	int size = 9 * 32;
	DrawText("Game Over", (WINDOW_WIDTH - (size/2.f)) / 2.f, (WINDOW_HEIGHT / 8.f), 32, RED);
	const char* text = TextFormat("%s falls in battle", GameState::GetRef().MainPlayer.GetName().c_str());
	size = (std::strlen(text) - 1) * 32;
	DrawText(text, (WINDOW_WIDTH - (size / 2.f)) / 2.f, (WINDOW_HEIGHT / 8.f) + 60.f, 32, RAYWHITE);


	const char* text2 = TextFormat("Press [enter] to continue...");
	size = (std::strlen(text2) - 1) * 32;
	DrawText(text2, (WINDOW_WIDTH - (size / 2.f)) / 2.f, (WINDOW_HEIGHT / 6.f) * 5, 32, RAYWHITE);
}