#include "stdafx.h"
#include "MenuOption.h"

using namespace sf;

void MenuOption::draw(RenderTarget & target, RenderStates state) const
{
	int xWitchOrigin = xPosition - width / 2;
	int yWitchOrigin = yPosition - height / 2;
	RectangleShape *rectangle = new RectangleShape;
	Text *text = new Text;
	Font *font = new Font;
	font->loadFromFile("ObelixPro.ttf");

	text->setString(name);
	text->setCharacterSize(charakterSize);
	text->setFont(*font);
	text->setFillColor(textColor);
	text->setOutlineColor(textOutlineColor);
	text->setOutlineThickness(textThickness);
	float textWidth = text->getLocalBounds().width;
	text->setPosition(xWitchOrigin + width/2 - textWidth/2, yWitchOrigin + height/3 + lineHeight);


	rectangle->setSize(sf::Vector2f(width, height));
	rectangle->setOutlineColor(sf::Color::Red);
	rectangle->setOutlineThickness(outlineThickness);
	rectangle->setFillColor(background);
	rectangle->setPosition(xWitchOrigin, yWitchOrigin);

	target.draw(*rectangle, state);
	target.draw(*text, state);

	delete rectangle;
	delete text;
	delete font;
}

bool detect(MenuOption* menuOption)
{
	int xWitchOrigin = menuOption->xPosition - menuOption->width / 2;
	int yWitchOrigin = menuOption->yPosition - menuOption->height / 2;
	sf::Vector2i mousePos = sf::Mouse::getPosition(*menuOption->window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		if (xWitchOrigin < mousePos.x
			&& xWitchOrigin + menuOption->width > mousePos.x
			&& yWitchOrigin < mousePos.y
			&& yWitchOrigin + menuOption->height > mousePos.y
			) {

			menuOption->action();
			return true;
		}
	}
	if (xWitchOrigin < mousePos.x
		&& xWitchOrigin + menuOption->width > mousePos.x
		&& yWitchOrigin < mousePos.y
		&& yWitchOrigin + menuOption->height > mousePos.y
		) {

		menuOption->background = menuOption->hoverBackground;
	} else {

		menuOption->background = menuOption->unHoverBackground;
	}

	return false;
}

bool exitMessegBox(string messeg)
{
	RenderWindow window{ VideoMode{ 360, 150 }, "Exit" };
	window.setFramerateLimit(60);

	int optionWidth = 110;
	int optionHeight = 27;
	RectangleShape yes(sf::Vector2f(optionWidth, optionHeight)), no(sf::Vector2f(optionWidth, optionHeight));
	Color fillColorButton(209, 209, 209);
	Color fillColorBackgrount(227, 229, 229);
	Color fillColorButtonHover(217, 219, 219);
	Color outlineColor(40, 40, 40);

	yes.setFillColor(fillColorButton);
	no.setFillColor(fillColorButton);

	yes.setOutlineColor(outlineColor);
	no.setOutlineColor(outlineColor);

	yes.setOutlineThickness(1);
	no.setOutlineThickness(1);

	yes.setPosition(sf::Vector2f(35, 100));
	no.setPosition(sf::Vector2f(215, 100));

	Font font;
	font.loadFromFile("Roboto-Medium.ttf");

	Text text;
	Event event;
	Vector2i mousePos;

	while (true) {

		window.pollEvent(event);

		text.setFont(font);
		text.setCharacterSize(17);
		text.setFillColor(outlineColor);

		window.clear(fillColorBackgrount);

		window.draw(yes);
		window.draw(no);

		text.setString("Yes");
		text.setPosition(sf::Vector2f(75, 104));
		window.draw(text);

		text.setString("No");
		text.setPosition(sf::Vector2f(260, 104));
		window.draw(text);

		text.setString("Do you really want to exit?\n" + messeg);
		text.setPosition(sf::Vector2f(30, 40));
		window.draw(text);
		
		mousePos = sf::Mouse::getPosition(window);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			if (yes.getPosition().x < mousePos.x
				&& yes.getPosition().x + optionWidth > mousePos.x
				&& yes.getPosition().y < mousePos.y
				&& yes.getPosition().y + optionHeight > mousePos.y
				) {

				window.close();
				return true;
			}

			if (no.getPosition().x < mousePos.x
				&& no.getPosition().x + optionWidth > mousePos.x
				&& no.getPosition().y < mousePos.y
				&& no.getPosition().y + optionHeight > mousePos.y
				) {

				window.close();
				return false;
			}
		}

		if (event.type == sf::Event::MouseMoved) {

			if (yes.getPosition().x < mousePos.x
				&& yes.getPosition().x + optionWidth > mousePos.x
				&& yes.getPosition().y < mousePos.y
				&& yes.getPosition().y + optionHeight > mousePos.y
				) {

				yes.setFillColor(fillColorButtonHover);
			} else {
				yes.setFillColor(fillColorButton);
			}

			if (no.getPosition().x < mousePos.x
				&& no.getPosition().x + optionWidth > mousePos.x
				&& no.getPosition().y < mousePos.y
				&& no.getPosition().y + optionHeight > mousePos.y
				) {

				no.setFillColor(fillColorButtonHover);
			} else {
				no.setFillColor(fillColorButton);
			}
		}

		if (event.type == Event::Closed) {

			window.close();
			return false;
		}

		window.display();
	}
}