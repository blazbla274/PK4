#pragma once
#include "Bonus.h"
class BonusAbilityEat :public sf::Drawable, public virtual Bonus
{
public:
	BonusAbilityEat(float x, float y, Game* g);
	~BonusAbilityEat() = default;
	void action();
	void draw(RenderTarget& target, RenderStates state) const override;
};

