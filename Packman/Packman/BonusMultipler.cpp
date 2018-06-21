#include "stdafx.h"
#include "BonusMultipler.h"


BonusMultipler::BonusMultipler(float x, float y, Game* g)
{
	game = g;
	posX = x;
	posY = y;
	width = 22;
	height = 22;;
	origin = 12;
	object.setPosition(x, y);
	texture.loadFromFile("bonusMultipler.png");
	object.setTexture(texture);
	object.setOrigin(origin, origin);
}

void BonusMultipler::action()
{
	if (game->bonusMultipler == 1) {
		game->bonusMultiplerTimer += 6;
		game->bonusMultipler = 2;
	} else {
		game->bonusMultiplerTimer += 6;
	}
}

void BonusMultipler::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(this->object, state);
}
