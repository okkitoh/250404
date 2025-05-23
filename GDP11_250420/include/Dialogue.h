#pragma once

#include "View.h"
#include <functional>
#include <string>
#include <vector>



class Dialogue : public View
{
public:
	Dialogue(std::string text);
	Dialogue(std::string text, std::function<void()> onConfirm);
	Dialogue(std::string text, std::function<void()> onEnter, std::function<void()> onConfirm, std::function<void()> onExit);
	void OnEnter(std::function<void()> callback);
	void OnConfirm(std::function<void()> callback);
	void OnExit(std::function<void()> callback);
	void Update() override;
	void GuiDraw() override;
private:
	std::string text;
	std::function<void()> onEnter;
	std::function<void()> onConfirm;
	std::vector<std::function<void()>> onExit;
};