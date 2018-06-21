#include "stdafx.h"
#include "Point.h"


Point::Point(float x, float y)
{
	object.setFillColor(color);
	object.setRadius(radius);
	object.setOrigin(radius, radius);
	object.setPosition(x, y);
	positionX = x;
	positionY = y;
}

void Point::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(this->object, state);
}

