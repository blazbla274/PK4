#pragma once
#include "MenuOption.h"


class OptionPlay :
	public MenuOption
{
public:
	OptionPlay(Menu *m, Game* g, RenderWindow* w);
	~OptionPlay() = default;
	void action();
};

