#pragma once
#include "MenuOption.h"
class OptionExit :public MenuOption
{
public:
	OptionExit(Menu *m, Game* g, RenderWindow* w);
	~OptionExit() = default;
	void action();
};

