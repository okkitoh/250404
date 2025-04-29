#pragma once

#include "View.h"
#include <functional>
#include <string>



class Dialogue : public View
{
public:
	Dialogue(std::string text);
	Dialogue(std::string text, std::function<void()> callback);
	void OnConfirm(std::function<void()> callback);
	void OnExit(std::function<void()> callback);
	void Update() override;
	void GuiDraw() override;
private:
	std::string text;
	std::function<void()> onConfirm;
	std::function<void()> onExit;
};