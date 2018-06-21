#pragma once
#include "Ghost.h"
#include "Mine.h"

class GhostMineSpreader :public Ghost
{
public:
	friend class Game;
	GhostMineSpreader() = default;
	GhostMineSpreader(float x, float y, Map* m, Game* g, Packman* p);
	~GhostMineSpreader() = default;
	int timeToRespawnSetter{ 120 };
	void update();
protected:
	bool makeMove();
	int direction{ 1 }; //1-top, 2-right, 3-bottom, 4-left
	void exposionDetection(Mine& it);
	void updatePacmanPosition();
	void respawn();
	void dropMine();
	void inspectMine();
	list<Mine> mineList;
	int dropcooldown{ 90 }, dropCounter{ 90 };
	void draw(RenderTarget& target, RenderStates state) const override;
};

