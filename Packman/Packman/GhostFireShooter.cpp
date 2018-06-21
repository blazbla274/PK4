#include "stdafx.h"
#include "GhostFireShooter.h"


GhostFireShooter::GhostFireShooter(float x, float y, Map* m, Game* g, Packman* p)
{
	respX = x;
	respY = y;
	name = "Ghost";
	map = m;
	game = g;
	pacman = p;
	width = 23;
	height = 23;
	texture.loadFromFile("ghostYellow.png");
	fearTexture.loadFromFile("ghostFered.png");
	object.setTexture(texture);
	object.setPosition(x, y);
	object.setOrigin(width / 2, height / 2);
	timeToRespawn = 100;
	timeToRespawnSetter = 100;
	dropcooldown = 40;
	dropCounter = 40;

	velocityHunt = pacman->velocity + pacman->velocity / 4;
	velocity = velocityHunt;
	velocityRunOut = pacman->velocity - pacman->velocity / 2;
}

void GhostFireShooter::update()
{
	if (resp) { //respawn moba
		GhostFireShooter::respawn();
		return;
	}

	updatePacmanPosition();
	updateVelocity();
	fearDetection();
	inspectFireBall();

	while (!makeMove()) {
		direction = (std::rand() % 4) + 1;
	}

	if (--dropCounter < 0 
		&& checkFirePosition() 
		&& !game->ghostModeRunAway) {

		dropCounter = dropcooldown;
		dropFireBall();
	}
	colisionDetection();
}

void GhostFireShooter::respawn()
{
	if (--timeToRespawn <= 0) {

		object.move(sf::Vector2f(1, 0));
		if (object.getPosition().x >= 528) {
			resp = false;
		}
	}
}

void GhostFireShooter::inspectFireBall()
{
	for (auto itFireBall = fireBallList.begin(); itFireBall != fireBallList.end(); ++itFireBall) {

		if (itFireBall->explosionTime < 0) {
			fireBallList.erase(itFireBall);
			break;
		}
		itFireBall->update();
		fireballColision(*itFireBall);
	}
}

void GhostFireShooter::dropFireBall()
{
	FireBall fireball(object.getPosition().x, object.getPosition().y, direction, map);
	fireBallList.push_back(fireball);
}

void GhostFireShooter::fireballColision(FireBall & it)
{
	Sprite fireball = it.returnObject();
	float radius{ 0.0f };
	if (it.explosionMode)
		radius = it.radiusExposion;
	else
		radius = it.fireBallRadius;

	if (pacmanPosition.x + pacman->width / 2 > fireball.getPosition().x - radius + 2
		&& pacmanPosition.x - pacman->width / 2  < fireball.getPosition().x + radius -2
		&& pacmanPosition.y + pacman->height  / 2 > fireball.getPosition().y - radius + 2
		&& pacmanPosition.y - pacman->height  / 2 < fireball.getPosition().y + radius - 2
		) {

		game->gameover = true;
	}
}

bool GhostFireShooter::checkFirePosition()
{                                           //1-top, 2-right, 3-bottom, 4-left

	if (direction == 1) {
		if (checkCollision(velocityVectorTop))
			return true;
	}
	else if (direction == 2) {
		if (checkCollision(velocityVectorRight))
			return true;
	}
	else if (direction == 3) {
		if (checkCollision(velocityVectorBottom))
			return true;
	}
	else if (direction == 4) 
		if (checkCollision(velocityVectorLeft)) 
			return true;

	return false;
}

void GhostFireShooter::draw(RenderTarget & target, RenderStates state) const
{
	FireBall fb;
	for (auto itFireBall = fireBallList.begin(); itFireBall != fireBallList.end(); ++itFireBall) {

		fb = *itFireBall;
		target.draw(fb.returnObject(), state);
	}

	if (!this->capture)
		target.draw(this->object, state);
}


