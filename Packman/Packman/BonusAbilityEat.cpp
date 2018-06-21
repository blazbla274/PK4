#include "stdafx.h"
#include "BonusAbilityEat.h"


BonusAbilityEat::BonusAbilityEat(float x, float y, Game* g)
{
	game = g;
	posX = x;
	posY = y;
	width = 22;
	height = 22;;
	origin = 12;
	object.setPosition(x, y);
	texture.loadFromFile("bonusAbilityEat.png");
	object.setTexture(texture);
	object.setOrigin(origin, origin);
}

void BonusAbilityEat::action()
{
	game->ghostModeRunAway = true;
	game->bonusAbilityEatTimer = 10;
}

void BonusAbilityEat::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(this->object, state);
}

