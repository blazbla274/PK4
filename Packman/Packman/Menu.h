#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

class Menu 
{
public:
	Menu(Game* g);
	~Menu() = default;
	Game *game;
	Menu *menu;
	void view(Menu *m);
	bool display{ true };
	Color background{ 16, 74, 168 };
	Sprite logo;
	int musicVolume{ 1717986918 };
	String musicName{ "Pac-Man - Intro Theme [Remix]" };
	int musicTt{ 1 };
};

