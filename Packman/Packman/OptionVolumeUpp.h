#pragma once
#include "MenuOption.h"
class OptionVolumeUpp :public MenuOption
{
public:
	OptionVolumeUpp(Menu *m, Game* g, RenderWindow* w);
	~OptionVolumeUpp() = default;
	void action();
};

