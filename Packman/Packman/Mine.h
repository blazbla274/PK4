#pragma once

class Mine
{
public:
	Mine() = default;
	Mine(float x, float y);
	~Mine() = default;
	float time{ 200.0f };
	float timeCounter{ 200.0f };
	void update();
	float radiusMine{ 8.0f };
	float radiusExposion{ 11.0f };
	float lineBold{ 2.0f };
	bool explosionMode{ false };
	sf::Sprite object;
	sf::Texture textura;
	sf::Texture explosion;
	sf::RectangleShape line1{ sf::Vector2f(radiusMine, lineBold) };
	sf::RectangleShape line2{ sf::Vector2f(radiusMine, lineBold) };
	sf::RectangleShape line3{ sf::Vector2f(radiusMine, lineBold) };
	sf::RectangleShape line4{ sf::Vector2f(radiusMine, lineBold) };
private:
	void setLine(RectangleShape* wsk, int num, float x, float y);
};

