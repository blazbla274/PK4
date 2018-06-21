#include "stdafx.h"
#include "BonusSpeed.h"


BonusSpeed::BonusSpeed(float x, float y, Game* g)
{
	game = g;
	posX = x;
	posY = y;
	width = 22;
    height = 22;;
	origin = 12;
	object.setPosition(x, y);
	texture.loadFromFile("bonusSpeed.png");
	object.setTexture(texture);
	object.setOrigin(origin, origin);
}

void BonusSpeed::action()
{
	if (game->bonusSpeed == 0) {
		game->bonusSpeedTimer += 4;
		game->bonusSpeed += 1.8;
	}
	else {
		game->bonusSpeedTimer += 5;
	}
}

void BonusSpeed::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(this->object, state);
}

