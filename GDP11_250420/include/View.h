#pragma once



class View
{
public:
	~View() = default;
	virtual void Update() = 0;
	virtual void GuiDraw() = 0;
	virtual bool IsActive()
	{
		return active;
	}
protected:
	bool active;
};