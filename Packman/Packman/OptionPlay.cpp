#include "stdafx.h"
#include "OptionPlay.h"

OptionPlay::OptionPlay(Menu *m, Game* g, RenderWindow* w)
{
	name = "Play";
	yPosition = 230;
	game = g;
	menu = m;
	window = w;
}

void OptionPlay::action()
{
	detection = true;
}