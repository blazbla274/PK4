#include "stdafx.h"
#include "OptionBack.h"


OptionBack::OptionBack(Menu *m, Game* g, RenderWindow* w)
{
	name = "Back";
	yPosition = 470;
	game = g;
	menu = m;
	window = w;
}

void OptionBack::action()
{
	detection = true;
}

