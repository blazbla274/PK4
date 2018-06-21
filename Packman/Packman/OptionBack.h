#pragma once
#include "MenuOption.h"
class OptionBack :public MenuOption
{
public:
	OptionBack(Menu *m, Game* g, RenderWindow* w);
	~OptionBack() = default;
	void action();
};

