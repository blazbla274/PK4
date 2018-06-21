#pragma once
#include "MenuOption.h"

class OptionRank :public MenuOption
{
public:
	OptionRank(Menu *m, Game* g, RenderWindow* w);
	~OptionRank() = default;
	void action();
};

