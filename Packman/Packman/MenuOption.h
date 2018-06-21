#pragma once
#include "Menu.h"
#include "Game.h"

using namespace sf;

class MenuOption :public sf::Drawable 
{
public:
	MenuOption() = default;
	~MenuOption() = default;
	friend bool detect(MenuOption* menuOption);
	bool detection{ false };
protected:
	int width{ 250 };
	int height{ 50 };
	Color background{ 255, 131, 4 };
	Color unHoverBackground{ 255, 131, 4 };
	Color hoverBackground{ 255, 150, 4 };
	Color outlineColor{ 255, 21, 31 };
	const Color textColor{ 255, 204 ,0 };
	Color textOutlineColor{ 0, 0, 0};
	int textThickness{ 1 };
	int outlineThickness{ 3 };
	int charakterSize{ 20 };
	int lineHeight{ 0 };
	string name;
	int xPosition{ 384 }; //center, witch origin for x and y
	int yPosition; 
	Game* game;
	Menu* menu;
	RenderWindow* window;
	virtual void action() = 0;
	void draw(RenderTarget& target, RenderStates state) const override;
};

