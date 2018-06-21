#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Game
{
public:
	Game() = default;
	~Game() = default;
	void run(Game *game);
	int playerPoints{ 0 };
	int bonusSpeed{ 0 };
	int bonusMultipler{ 1 };
	bool gameover{ false };
	bool ghostModeRunAway{ false };
	bool ghostReset{ false };
	atomic <int> bonusSpeedTimer{ 0 };
	atomic <int> bonusMultiplerTimer{ 0 };
	atomic <int> bonusAbilityEatTimer{ 0 };
	string playerName;
	string gameTimeText{ "00:0" };
	string bonusSpeedTimerText{ "0" };
	string bonusMultiplerTimerText{ "0" };
	string bonusAbilityEatTimerText{ "0" };
	void addPlayerPoint(int count);
	void setplayerName();
	void saveScore();
private:
	void gameReset();
	void refreshPlayerPoint(sf::Text *text);
	void timerUpdate(sf::Text *time);
	void setPlayerPointText(sf::Text *text, sf::Font *font);
	void setPlayerNameText(sf::Text *text, sf::Font *font);
	void setGameTimeText(sf::Text *text, sf::Font *font);
	void setDescriptionPointText(sf::Text *text, sf::Font *font);
	void setDescriptionNameText(sf::Text *text, sf::Font *font);
	void setDescriptionTimeText(sf::Text *text, sf::Font *font);
	void setDescriptionBonusSpeedText(sf::Text *text, sf::Font *font);
	void setDescriptionBonusMultiplerText(sf::Text *text, sf::Font *font);
	void setDescriptionBonusAbilityEatText(sf::Text *text, sf::Font *font);
	void setDescriptionBonusSpeed(sf::Text *text, sf::Font *font);
	void setDescriptionBonusMultipler(sf::Text *text, sf::Font *font);
	void setDescriptionBonusAbilityEat(sf::Text *text, sf::Font *font);
	void setGameOverText(sf::Text *text, sf::Font *font);
	void updateBonus(sf::Text *bonusSpeedWsk, sf::Text *bonusMultiplerWsk, sf::Text* bonusAbilityEatWsk);
};
