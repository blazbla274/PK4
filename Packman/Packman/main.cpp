// Packman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace sf;
using namespace std;

int main()
{
	PlaySound(TEXT("Pac-Man - Intro Theme [Remix].wav"), NULL, SND_ASYNC);

	Game game;
	Menu menu(&game);
	waveOutSetVolume(0, menu.musicVolume);

	while (menu.display) {

		menu.view(&menu);
	}

	return 0;
}

