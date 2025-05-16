
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
Dialogue::Dialogue(std::string text, std::function<void()> onConfirm)
{
	this->text = text;
	OnConfirm(onConfirm);
	OnExit([]() {
		GameState::GetRef().PopView();
	});
}
Dialogue::Dialogue(std::string text, std::function<void()> onEnter, std::function<void()> onConfirm, std::function<void()> onExit)
{
	this->text = text;
	OnEnter(onEnter);
	OnConfirm(onConfirm);
	OnExit([]() {
		GameState::GetRef().PopView();
	});
	OnExit(onExit);
}

void Dialogue::OnEnter(std::function<void()> callback)
{
	onEnter = callback;
}
void Dialogue::OnConfirm(std::function<void()> callback)
{
	onConfirm = callback;
}
void Dialogue::OnExit(std::function<void()> callback)
{
	onExit.push_back(callback);
}
void Dialogue::Update()
{
	if (onEnter != nullptr)
	{
		onEnter();
		onEnter = nullptr;
	}
	if (GetKeyPressed())
	{
		onConfirm();
		while(!onExit.empty())
		{
			onExit.back()();
			onExit.pop_back();
		}
	}
}
void Dialogue::GuiDraw()
{
	DrawRectangle(0, WINDOW_HEIGHT - 260, WINDOW_WIDTH, 260, BLACK);
	DrawRectangleLines(30, WINDOW_HEIGHT - 230, WINDOW_WIDTH - 60, 200, WHITE);
	DrawText(this->text.c_str(), 60, WINDOW_HEIGHT - 200, 36, WHITE);
}