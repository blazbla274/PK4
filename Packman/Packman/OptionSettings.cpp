#include "stdafx.h"
#include "OptionSettings.h"


OptionSettings::OptionSettings(Menu *m, Game* g, RenderWindow* w)
{
	name = "Settings";
	yPosition = 350;
	game = g;
	menu = m;
	window = w;
}

void OptionSettings::action()
{
	detection = true;
	OptionBack backInput(menu, game, window);
	OptionMusic musicInput(menu, game, window);
	OptionVolumeUpp volumeUpp(menu, game, window);
	OptionVolumeDown volumeDown(menu, game, window);
	OptionChangeMusic changeMusic(menu, game, window);

	Font font;
	font.loadFromFile("Roboto-Medium.ttf");

	Text textMusic;
	textMusic.setString("Music");
	textMusic.setFont(font);
	textMusic.setCharacterSize(22);
	textMusic.setPosition(290, 220);

	Text textVolume;
	textVolume.setString("Volume");
	textVolume.setFont(font);
	textVolume.setCharacterSize(22);
	textVolume.setPosition(290, 277);

	Text textChangeM;
	textChangeM.setString("Change");
	textChangeM.setFont(font);
	textChangeM.setCharacterSize(22);
	textChangeM.setPosition(290, 347);

	Text textMusicName;
	textMusicName.setFont(font);
	textMusicName.setCharacterSize(22);
	textMusicName.setPosition(445, 347);

	while (true) {

		if (detect(&musicInput)) {
			detection = false;
			Sleep(80);
		}

		if (detect(&volumeUpp)) {
			detection = false;
			Sleep(80);
		}

		if (detect(&volumeDown)) {
			detection = false;
			Sleep(80);
		}

		if (detect(&changeMusic)) {
			detection = false;
			Sleep(150);
		}

		textMusicName.setString(menu->musicName);

		window->clear(menu->background);
		window->draw(menu->logo);
		window->draw(backInput);
		window->draw(musicInput);
		window->draw(textMusic);
		window->draw(textVolume);
		window->draw(textMusicName);
		window->draw(textChangeM);
		window->draw(volumeUpp);
		window->draw(volumeDown);
		window->draw(changeMusic);
		window->display();

		if (detect(&backInput)) {

			detection = false;
			break;
		}
	}
}