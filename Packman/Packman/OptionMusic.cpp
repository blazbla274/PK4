#include "stdafx.h"
#include "OptionMusic.h"


OptionMusic::OptionMusic(Menu *m, Game* g, RenderWindow* w)
{
	name = "Off";
	yPosition = 235;
	xPosition = 420;
	width = 80;
	height = 40;
	game = g;
	menu = m;
	window = w;
}

void OptionMusic::action()
{
	detection = true;
	if (status) {
		PlaySound(NULL, 0, 0);
		name = "On";
		status = false;
	} else {

		switch (menu->musicTt) {
		case 1: PlaySound(TEXT("Pac-Man - Intro Theme [Remix].wav"), NULL, SND_ASYNC);
			menu->musicName = "Pac-Man - Intro Theme[Remix]";
			break;
		case 2: PlaySound(TEXT("Pacman Dubstep Remix.wav"), NULL, SND_ASYNC);
			menu->musicName = "Pacman Dubstep Remix";
			break;
		case 3: PlaySound(TEXT("PacMan Original Theme.wav"), NULL, SND_ASYNC);
			menu->musicName = "PacMan Original Theme";
			break;
		case 4: PlaySound(TEXT("Pac-Man Fever Universe.wav"), NULL, SND_ASYNC);
			menu->musicName = "Pac-Man Fever Universe";
			break;
		}
		name = "Off";
		status = true;
	}
	
}


