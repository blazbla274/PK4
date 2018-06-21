#include "stdafx.h"
#include "OptionVolumeUpp.h"

atomic<int> musicVolume;

OptionVolumeUpp::OptionVolumeUpp(Menu *m, Game* g, RenderWindow* w)
{
	name = "+";
	yPosition = 295;
	xPosition = 475;
	width = 55;
	charakterSize = 33;
	lineHeight = -6;
	game = g;
	menu = m;
	window = w;
}

void OptionVolumeUpp::action()
{
	switch (menu->musicVolume) {
	case 0: menu->musicVolume = 858993459;
		break;
	case 858993459: menu->musicVolume = 1717986918;
		break;
	case 1717986918: menu->musicVolume = -1717986919;
		break;
	case -1717986919: menu->musicVolume = -858993460;
		break;
	case -858993460: menu->musicVolume = -1;
		break;
	case -1:
		break;
	}
	cout << menu->musicVolume << endl;
	waveOutSetVolume(0, menu->musicVolume);
}


