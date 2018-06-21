#include "stdafx.h"
#include "Menu.h"

using namespace sf;


Menu::Menu(Game * g)
{
	game = g;
}

bool exitMessegBox(string messeg = "");

void Menu::view(Menu *m)
{
	menu = m;

	RenderWindow window{ VideoMode{ 768, 576 }, "Packman++" };
	window.setFramerateLimit(60);
	Event event;

	OptionPlay play(menu, game, &window);
	OptionRank rank(menu, game, &window);
	OptionSettings settings(menu, game, &window);
	OptionExit exit(menu, game, &window);

	Texture texture;
	texture.loadFromFile("logo.png");

	Font font;
	font.loadFromFile("Roboto-Medium.ttf");

	Text author;
	author.setFont(font);
	author.setCharacterSize(12);
	author.setFillColor(sf::Color::White);
	author.setPosition(628, 555);
	author.setString("Created by Blazej Blaut");

	logo.setTexture(texture);
	logo.setOrigin(200, 62);
	logo.setPosition(384, 130);

	while (true) {
		window.clear(background);
		window.draw(logo);
		window.pollEvent(event);

		if (event.type == Event::Closed) {
			if (exitMessegBox()) {
				display = false;
				break;
			}
		}
		if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			if (exitMessegBox()) {
				display = false;
				break;
			}
		}

		if (detect(&play))
			break;
		if (detect(&rank));
		if (detect(&settings));
		if (detect(&exit) && exit.detection == true)
			break;

		window.draw(play);
		window.draw(rank);
		window.draw(settings);
		window.draw(exit);
		window.draw(author);
		window.display();
	}

	window.close();

	if (play.detection) {
		game->run(game);
		play.detection = false;
	}
	    
	if(exit.detection)
		display = false;
}


