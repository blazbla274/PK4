#pragma once
#include "Bonus.h"
class BonusMultipler :public sf::Drawable, public virtual Bonus
{
public:
	BonusMultipler(float x, float y, Game* g);
	~BonusMultipler() = default;
	void action();
	void draw(RenderTarget& target, RenderStates state) const override;
};

