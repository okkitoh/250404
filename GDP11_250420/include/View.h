#pragma once

class View
{
public:
	~View() = default;
	virtual void Update() = 0;
	virtual void Draw() {};
	virtual void GuiDraw() = 0;
	virtual bool IsActive()
	{
		return valid && active;
	}
	virtual void SetActive(bool isActive)
	{
		active = isActive;
	}
	virtual bool IsValid()
	{
		return valid;
	}
	// 250427 - Command Pattern to manage views
	// The get-it-working iteration has a major design flaw.
	// Callbacks are tasked with deleting the view that owns the callback
	// meaning the views are imploding.
	//
	// Solution: mark object to signal game loop that this view should be
	// cleaned up at a later convenient time.
	virtual void Invalidate()
	{
		valid = false;
	}
protected:
	bool active = true;
	bool valid = true;
};