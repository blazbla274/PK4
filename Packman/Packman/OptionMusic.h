#pragma once
#include "MenuOption.h"
class OptionMusic :public MenuOption
{
public:
	OptionMusic(Menu* m, Game* g, RenderWindow* w);
	~OptionMusic() = default;
	void action();
	bool status{ true };
};

