#include "stdafx.h"
#include "OptionVolumeDown.h"


OptionVolumeDown::OptionVolumeDown(Menu *m, Game* g, RenderWindow* w)
{
	name = "-";
	yPosition = 295;
	xPosition = 407;
	width = 55;
	charakterSize = 33;
	lineHeight = -6;
	game = g;
	menu = m;
	window = w;
}

void OptionVolumeDown::action()
{
	switch (menu->musicVolume) {
	case 0:
		break;
	case 858993459: menu->musicVolume = 0;
		break;
	case 1717986918: menu->musicVolume = 858993459;
		break;
	case -1717986919: menu->musicVolume = 1717986918;
		break;
	case -858993460: menu->musicVolume = -1717986919;
		break;
	case -1: menu->musicVolume = -858993460;
		break;
	}

	cout << menu->musicVolume << endl;
	waveOutSetVolume(0, menu->musicVolume);
}
