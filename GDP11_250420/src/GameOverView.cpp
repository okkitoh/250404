
#include "GameOverView.h"
#include "GameState.h"
#include "StartMenu.h"
#include "Sprites.h"
#include "raylib.h"



GameOverView::GameOverView()
{
}
void GameOverView::Update()
{
	if (GetKeyPressed())
	{
		this->Invalidate(); // mark self for deletion later in main loop
		GameState::GetRef().PushView(new StartMenu());
	}
}
void GameOverView::GuiDraw()
{
	Texture2D graveSprite = Sprites::GetSprite(GRAVE);
	DrawTextureEx(graveSprite, { (WINDOW_WIDTH / 2.f) - (256.f * 3.f / 2.f), -20.f }, 0, 3, WHITE);
	int size = 9 * 32;
	DrawText("Game Over", (WINDOW_WIDTH - (size/2.f)) / 2.f, (WINDOW_HEIGHT / 8.f), 32, RED);
	const char* text = TextFormat("%s falls in battle", GameState::GetRef().MainPlayer.GetName().c_str());
	size = (std::strlen(text) - 1) * 32;
	DrawText(text, (WINDOW_WIDTH - (size / 2.f)) / 2.f, (WINDOW_HEIGHT / 8.f) + 60.f, 32, RAYWHITE);


	const char* text2 = TextFormat("Press [enter] to continue...");
	size = (std::strlen(text2) - 1) * 32;
	DrawText(text2, (WINDOW_WIDTH - (size / 2.f)) / 2.f, (WINDOW_HEIGHT / 6.f) * 5, 32, RAYWHITE);
}