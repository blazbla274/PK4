#include "stdafx.h"
#include "Mine.h"


Mine::Mine(float x, float y)
{
	if (!textura.loadFromFile("mine.png"))
		cout << "Failed Load mine.png\n";
	if(!explosion.loadFromFile("explosion.png"))
		cout << "Failed Load explosion.png\n";

	object.setOrigin(radiusMine, radiusMine);
	object.setPosition(x, y);


	setLine(&line1, 1, x, y);
	setLine(&line2, 2, x, y);
	setLine(&line3, 3, x, y);
	setLine(&line4, 4, x, y);
}

void Mine::update()
{
	timeCounter--;
	RectangleShape * lineWsk = nullptr;
	if (timeCounter > 0.8 * time) {

		if(object.getTexture() != &textura)
			object.setTexture(textura, true);

		lineWsk = &line1;
	}
	else if (timeCounter > 0.6 * time) {
		lineWsk = &line2;
	}
	else if (timeCounter > 0.4 * time) {
		lineWsk = &line3;
	}
	else if (timeCounter > 0.2 * time) {
		lineWsk = &line4;
	}
	else if (timeCounter > 0) {

		if (object.getTexture() != &explosion)
			object.setTexture(explosion, true);

		explosionMode = true;
		object.setOrigin(radiusExposion, radiusExposion);
	}

	if(lineWsk != nullptr)
		lineWsk->setFillColor(sf::Color::Red);
}

void Mine::setLine(RectangleShape * wsk, int num, float x, float y)
{
	wsk->setFillColor(sf::Color::Black);
	wsk->setPosition(x, y);
	wsk->setOrigin(0.0, lineBold/2);
	wsk->setRotation(90 * (num - 1));
}
