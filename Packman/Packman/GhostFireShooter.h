#pragma once
#include "GhostMineSpreader.h"
#include "FireBall.h"

class GhostFireShooter :public GhostMineSpreader
{
public:
	GhostFireShooter(float x, float y, Map* m, Game* g, Packman* p);
	~GhostFireShooter() = default;
	list <FireBall> fireBallList;
	void update();
protected:
	void respawn();
	void inspectFireBall();
	void dropFireBall();
	void fireballColision(FireBall & it);
	bool checkFirePosition();
	void draw(RenderTarget& target, RenderStates state) const override;
};

