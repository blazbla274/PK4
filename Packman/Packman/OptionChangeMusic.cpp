#include "stdafx.h"
#include "OptionChangeMusic.h"


OptionChangeMusic::OptionChangeMusic(Menu *m, Game* g, RenderWindow* w)
{
	name = ":-";
	yPosition = 360;
	xPosition = 407;
	width = 55;
	game = g;
	menu = m;
	window = w;
}

void OptionChangeMusic::action()
{
	menu->musicTt++;

	if (menu->musicTt > 4) {
		menu->musicTt = 1;
	}

	switch (menu->musicTt) {
	case 1: PlaySound(TEXT("Pac-Man - Intro Theme [Remix].wav"), NULL, SND_ASYNC);
		Sleep(150);
		menu->musicName = "Pac-Man - Intro Theme[Remix]";
		break;
	case 2: PlaySound(TEXT("Pacman Dubstep Remix.wav"), NULL, SND_ASYNC);
		Sleep(150);
		menu->musicName = "Pacman Dubstep Remix";
		break;
	case 3: PlaySound(TEXT("PacMan Original Theme.wav"), NULL, SND_ASYNC);
		Sleep(150);
		menu->musicName = "PacMan Original Theme";
		break;
	case 4: PlaySound(TEXT("Pac-Man Fever Universe.wav"), NULL, SND_ASYNC);
		Sleep(150);
		menu->musicName = "Pac-Man Fever Universe";
		break;
	}
}

