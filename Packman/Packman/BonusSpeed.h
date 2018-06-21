#pragma once
#include "Bonus.h"
class BonusSpeed :public sf::Drawable, public virtual Bonus
{
public:
	BonusSpeed(float x, float y, Game* g);
	~BonusSpeed() = default;
	void action();
	void draw(RenderTarget& target, RenderStates state) const override;
};

