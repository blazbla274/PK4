#include "stdafx.h"
#include "OptionExit.h"

bool exitMessegBox(string messeg = "");

OptionExit::OptionExit(Menu *m, Game* g, RenderWindow* w)
{
	name = "Exit";
	yPosition = 410;
	game = g;
	menu = m;
	window = w;
}

void OptionExit::action()
{
	if (exitMessegBox()) {
		detection = true;
	}
}
