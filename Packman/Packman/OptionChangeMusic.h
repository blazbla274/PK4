#pragma once
#include "MenuOption.h"
class OptionChangeMusic :public MenuOption
{
public:
	OptionChangeMusic(Menu *m, Game* g, RenderWindow* w);
	~OptionChangeMusic() = default;
	void action();
};

