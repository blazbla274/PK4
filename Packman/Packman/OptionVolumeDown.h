#pragma once
#include "MenuOption.h"
class OptionVolumeDown :public MenuOption
{
public:
	OptionVolumeDown(Menu *m, Game* g, RenderWindow* w);
	~OptionVolumeDown() = default;
	void action();
};

