
#include "Dialogue.h"
#include "GameState.h"
#include "raylib.h"



Dialogue::Dialogue(std::string text)
{
	this->text = text;
	OnConfirm([]() {
	});
	OnExit([]() {
		GameState::GetRef().PopView();
	});
}
Dialogue::Dialogue(std::string text, std::function<void()> callback)
{
	this->text = text;
	OnConfirm(callback);
	OnExit([]() {
		GameState::GetRef().PopView();
	});
}
void Dialogue::OnConfirm(std::function<void()> callback)
{
	onConfirm = callback;
}
void Dialogue::OnExit(std::function<void()> callback)
{
	onExit = callback;
}
void Dialogue::Update()
{
	if (GetKeyPressed())
	{
		onConfirm();
		onExit();
	}
}
void Dialogue::GuiDraw()
{
	DrawRectangle(0, WINDOW_HEIGHT - 260, WINDOW_WIDTH, 260, BLACK);
	DrawRectangleLines(30, WINDOW_HEIGHT - 230, WINDOW_WIDTH - 60, 200, WHITE);
	DrawText(this->text.c_str(), 60, WINDOW_HEIGHT - 200, 36, WHITE);
}