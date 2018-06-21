#pragma once
#include "MenuOption.h"
class OptionSettings :public MenuOption
{
public:
	OptionSettings(Menu *m, Game* g, RenderWindow* w);
	~OptionSettings() = default;
	void action();
};

