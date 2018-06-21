#include "stdafx.h"
#include <sstream>

using namespace sf;
using namespace std;

atomic<int> timeCounter = 0;
atomic<int> lasCharUse = 0;
atomic<bool> goCounter = true;
atomic<bool> bonusSpeedThread = true;
atomic<bool> bonusMultiplerThread = true;
atomic<bool> bonusAbilityEatThread = true;
atomic<int> gameTime = 0;
atomic<int> gameTimeStatus = false;

bool exitMessegBox(string messeg = "");
void gameTimeF(string action);
void bonusSpeedT(atomic <int> *wsk, String action);
void bonusMultiplerT(atomic <int> *wsk, String action);
void bonusAbilityEatT(atomic <int> *wsk, String action);

void Game::run(Game *game)
{
	RenderWindow window{ VideoMode{ 968, 576 }, "Packman++" }; //768px powie¿chni mapy, 200 menu bocznego
	window.setFramerateLimit(60);

	Event event;
	Map map(game);
	Packman player(107, 47.6, &map, game);
	Ghost ghost(334, 210, &map, game, &player,50);
	Ghost ghost2(312, 225, &map, game, &player, 500);
	GhostMineSpreader ghostMineSpreader(384, 220, &map, game, &player);
	GhostFireShooter ghostFireShooter(454, 205, &map, game, &player);
	Text points;
	Text name;
	Text time;
	Text bonusSpeed;
	Text bonusMultipler;
	Text bonusAbilityEat;
	Text gameOver;

	Text pointsDescription;
	Text nameDescription;
	Text timeDescription;
	Text bonusSpeedDescription;
	Text bonusAbilityEatDescription;
	Text bonusMultiplerDescription;

	Font pointsFont;
	Font nameFont;
	Font timeFont;
	Font descriptionFont;
	Font gameOverFont;

	window.clear(Color::Black);
	window.display();
	setplayerName();
	name.setString(playerName);
	thread t(gameTimeF,"START"); //czas rozgrywki
	thread bSpeed(bonusSpeedT, &bonusSpeedTimer, "START"); //dzia³anie bonusu prêdkoœci
	thread bMultipler(bonusMultiplerT, &bonusMultiplerTimer, "START");
	thread bAbilityEat(bonusAbilityEatT, &bonusAbilityEatTimer, "START");


	setPlayerPointText(&points, &pointsFont);
	setPlayerNameText(&name, &nameFont);
	setGameTimeText(&time, &timeFont);
	setDescriptionPointText(&pointsDescription, &descriptionFont);
	setDescriptionNameText(&nameDescription, &descriptionFont);
	setDescriptionTimeText(&timeDescription, &descriptionFont);
	setDescriptionBonusSpeedText(&bonusSpeedDescription, &descriptionFont);
	setDescriptionBonusMultiplerText(&bonusMultiplerDescription, &descriptionFont);
	setDescriptionBonusAbilityEatText(&bonusAbilityEatDescription, &descriptionFont);
	setDescriptionBonusSpeed(&bonusSpeed, &timeFont);
	setDescriptionBonusMultipler(&bonusMultipler, &timeFont);
	setDescriptionBonusAbilityEat(&bonusAbilityEat, &timeFont);
	setGameOverText(&gameOver, &gameOverFont);

	while (true)
	{
		refreshPlayerPoint(&points);
		updateBonus(&bonusSpeed, &bonusMultipler, &bonusAbilityEat);
		timerUpdate(&time);

		window.clear(Color::Black);
		window.pollEvent(event);

		if (event.type == Event::Closed) {
			if (exitMessegBox("Your score will be saved.")) {
				saveScore();
				window.close();
				break;
			}
		}
		if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			if (exitMessegBox("Your score will be saved.")) {
				saveScore();
				window.close();
				break;
			}
		}
		if (ghostReset) {
			ghost.reset();
			ghost2.reset();
			ghostMineSpreader.reset();
			ghostFireShooter.reset();
			ghostReset = !ghostReset;
		}

		player.update();

		if (!ghost.capture)
			ghost.update();
		else 
			ghost.resetControler(700);

		if (!ghost2.capture) ghost2.update();
		if (!ghostMineSpreader.capture || 
		   (!ghostMineSpreader.mineList.empty() && ghostMineSpreader.capture)) 
		    ghostMineSpreader.update();
		if (!ghostFireShooter.capture ||
				(!ghostFireShooter.fireBallList.empty() && ghostFireShooter.capture))
			ghostFireShooter.update();


		window.draw(map);
		window.draw(player);
		if(!ghost.capture) window.draw(ghost);
		if (!ghost2.capture) window.draw(ghost2);
		window.draw(ghostMineSpreader);
		window.draw(ghostFireShooter);
		window.draw(points);
		window.draw(name);
		window.draw(time);
		window.draw(bonusSpeed);
		window.draw(bonusMultipler);
		window.draw(bonusAbilityEat);
		window.draw(pointsDescription);
		window.draw(nameDescription);
		window.draw(timeDescription);
		window.draw(bonusSpeedDescription);
		window.draw(bonusMultiplerDescription);
		window.draw(bonusAbilityEatDescription);
		if (gameover) window.draw(gameOver);
		window.display();

		if (gameover) {
			while (true) {
				window.pollEvent(event);
				if (event.type != Event::KeyPressed && event.key.code == sf::Keyboard::Return)
					break;
			}
			saveScore();
			window.close();
			break;
		}
	}

	gameTimeF("STOP");
	bonusSpeedT(&bonusSpeedTimer, "STOP");
	bonusMultiplerT(&bonusMultiplerTimer, "STOP");
	bonusAbilityEatT(&bonusAbilityEatTimer, "STOP");

	if (t.joinable()) 
		t.join();
	if (bSpeed.joinable())
		bSpeed.join();
	if (bMultipler.joinable())
		bMultipler.join();
	if (bAbilityEat.joinable())
		bAbilityEat.join();

	gameReset();       //reset przed nastêpn¹ rozgrywki
}

void Game::gameReset()
{
	playerPoints = 0;
	gameover = false;
	ghostModeRunAway = false;
	bonusSpeedTimer = 0;
	bonusMultiplerTimer = 0;
	bonusAbilityEatTimer = 0;
}

void Game::refreshPlayerPoint(Text * text)
{
	ostringstream ss;
	ss << playerPoints;
	string playerPo = ss.str();

	text->setString(playerPo);
}

void Game::timerUpdate(sf::Text * time)
{
	int x = gameTime;

	ostringstream ss;

	string timeText = "";
	if (x / 60 < 1) {

		ss << x;
		string secPas = ss.str();
		ss.str("");
		ss.clear();

		if (x < 10)
			timeText = "00:0" + secPas;
		else
			timeText = "00:" + secPas;

	} else if (x / 60 >= 1) {

		int min = x / 60;
		int sec = x % 60;

		ss << sec;
		string secPas = ss.str();
		ss.str("");
		ss.clear();

		ss << min;
		string minPas = ss.str();
		ss.str("");
		ss.clear();

		if (min < 10) {
			timeText = "0" + minPas;
		} else {
			timeText = minPas;
		}
		timeText += ":";

		if (sec < 10) {
			timeText += "0" + secPas;
		} else {
			timeText += secPas;
		}
	}
	time->setString(timeText);
	gameTimeText = timeText;
}

void Game::setPlayerPointText(sf::Text * text, sf::Font *font)
{
	if (!font->loadFromFile("ObelixPro.ttf"))
		cout << "Can't find the font file." << endl;
	text->setFont(*font);
	text->setCharacterSize(30);
	text->setStyle(sf::Text::Bold);
	text->setPosition(sf::Vector2f(798, 135));
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness( 1 );
}

void Game::setPlayerNameText(sf::Text * text, sf::Font * font)
{
	if (!font->loadFromFile("ObelixPro.ttf"))
		cout << "Can't find the font file." << endl;
	text->setFont(*font);
	text->setCharacterSize(20);
	text->setStyle(sf::Text::Regular);
	text->setPosition(sf::Vector2f(798, 35));
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(1);
}

void Game::setGameTimeText(sf::Text * text, sf::Font * font)
{
	if (!font->loadFromFile("ObelixPro.ttf"))
		cout << "Can't find the font file." << endl;
	text->setFont(*font);
	text->setCharacterSize(23);
	text->setStyle(sf::Text::Regular);
	text->setPosition(sf::Vector2f(798, 235));
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(1);
}

void Game::setDescriptionPointText(sf::Text * text, sf::Font * font)
{
	if (!font->loadFromFile("ObelixPro.ttf"))
		cout << "Can't find the font file." << endl;
	text->setFont(*font);
	text->setString("Points");
	text->setCharacterSize(16);
	text->setStyle(sf::Text::Regular);
	text->setPosition(sf::Vector2f(798, 112));
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(1);
}

void Game::setDescriptionNameText(sf::Text * text, sf::Font * font)
{
	if (!font->loadFromFile("ObelixPro.ttf"))
		cout << "Can't find the font file." << endl;
	text->setFont(*font);
	text->setString("Name");
	text->setCharacterSize(16);
	text->setStyle(sf::Text::Regular);
	text->setPosition(sf::Vector2f(798, 12));
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(1);
}

void Game::setDescriptionTimeText(sf::Text * text, sf::Font * font)
{
	if (!font->loadFromFile("ObelixPro.ttf"))
		cout << "Can't find the font file." << endl;
	text->setFont(*font);
	text->setString("Time");
	text->setCharacterSize(16);
	text->setStyle(sf::Text::Regular);
	text->setPosition(sf::Vector2f(798, 215));
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(1);
}

void Game::setDescriptionBonusSpeedText(sf::Text * text, sf::Font * font)
{
	if (!font->loadFromFile("ObelixPro.ttf"))
		cout << "Can't find the font file." << endl;
	text->setFont(*font);
	text->setString("Speed bonus");
	text->setCharacterSize(16);
	text->setStyle(sf::Text::Regular);
	text->setPosition(sf::Vector2f(798, 327));
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(1);
}

void Game::setDescriptionBonusMultiplerText(sf::Text * text, sf::Font * font)
{
	if (!font->loadFromFile("ObelixPro.ttf"))
		cout << "Can't find the font file." << endl;
	text->setFont(*font);
	text->setString("Multipler");
	text->setCharacterSize(16);
	text->setStyle(sf::Text::Regular);
	text->setPosition(sf::Vector2f(798, 395));
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(1);
}

void Game::setDescriptionBonusAbilityEatText(sf::Text * text, sf::Font * font)
{
	if (!font->loadFromFile("ObelixPro.ttf"))
		cout << "Can't find the font file." << endl;
	text->setFont(*font);
	text->setString("Ability to eat");
	text->setCharacterSize(16);
	text->setStyle(sf::Text::Regular);
	text->setPosition(sf::Vector2f(798, 463));
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(1);
}

void Game::setDescriptionBonusSpeed(sf::Text * text, sf::Font * font)
{
	if (!font->loadFromFile("ObelixPro.ttf"))
		cout << "Can't find the font file." << endl;
	text->setFont(*font);
	text->setCharacterSize(23);
	text->setStyle(sf::Text::Regular);
	text->setPosition(sf::Vector2f(798, 347));
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(1);
}

void Game::setDescriptionBonusMultipler(sf::Text * text, sf::Font * font)
{
	if (!font->loadFromFile("ObelixPro.ttf"))
		cout << "Can't find the font file." << endl;
	text->setFont(*font);
	text->setCharacterSize(23);
	text->setStyle(sf::Text::Regular);
	text->setPosition(sf::Vector2f(798, 417));
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(1);
}

void Game::setDescriptionBonusAbilityEat(sf::Text * text, sf::Font * font)
{
	if (!font->loadFromFile("ObelixPro.ttf"))
		cout << "Can't find the font file." << endl;
	text->setFont(*font);
	text->setCharacterSize(23);
	text->setStyle(sf::Text::Regular);
	text->setPosition(sf::Vector2f(798, 487));
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(1);
}

void Game::setGameOverText(sf::Text * text, sf::Font * font)
{
	if (!font->loadFromFile("Roboto-Medium.ttf"))
		cout << "Can't find the font file." << endl;
	text->setFont(*font);
	text->setString("GAME OVER");
	text->setCharacterSize(130);
	text->setStyle(sf::Text::Bold);
	text->setPosition(sf::Vector2f(20, 150));
	text->setOutlineColor(sf::Color::Black);
	text->setFillColor(sf::Color::Red);
	text->setOutlineThickness(2);
}

void Game::updateBonus(sf::Text *bonusSpeedWsk, sf::Text *bonusMultiplerWsk, sf::Text* bonusAbilityEatWsk)
{
	if (bonusSpeedTimer == 0) {
		bonusSpeed = 0;
	}
	if (bonusMultiplerTimer == 0) {
		bonusMultipler = 1;
	}
	if (bonusAbilityEatTimer == 0) {
		ghostModeRunAway = false;
	}

	ostringstream ss;
	ss << bonusSpeedTimer;
	bonusSpeedTimerText = ss.str();
	bonusSpeedWsk->setString(bonusSpeedTimerText);
	ss.str("");
	ss.clear();

	ss << bonusMultiplerTimer;
	bonusMultiplerTimerText = ss.str();
	bonusMultiplerWsk->setString(bonusMultiplerTimerText);
	ss.str("");
	ss.clear();

	ss << bonusAbilityEatTimer;
	bonusAbilityEatTimerText = ss.str();
	bonusAbilityEatWsk->setString(bonusAbilityEatTimerText);
	ss.str("");
	ss.clear();
}

void Game::addPlayerPoint(int count)
{
	playerPoints += count * bonusMultipler;
}

void bonusSpeedT(atomic <int> *wsk, String action) 
{
	if (action == "STOP")
	    bonusSpeedThread = false;
	else if (action == "START") 
		bonusSpeedThread = true;

	if(bonusSpeedThread)
		while (bonusSpeedThread) {
			if (*wsk > 0) {
				Sleep(1000);
				*wsk -= 1;
			} else {
				Sleep(50);
			}
		}
}

void bonusMultiplerT(atomic <int> *wsk, String action)
{
	if (action == "STOP")
		bonusMultiplerThread = false;
	else if (action == "START")
		bonusMultiplerThread = true;

	while (bonusMultiplerThread) {
		if (*wsk > 0) {
			Sleep(1000);
			*wsk -= 1;
		} else {
			Sleep(50);
		}
	}
}

void bonusAbilityEatT(atomic <int> *wsk, String action)
{
	if (action == "STOP")
		bonusAbilityEatThread = false;
	else if (action == "START")
		bonusAbilityEatThread = true;

	while (bonusAbilityEatThread) {
		if (*wsk > 0) {
			Sleep(1000);
			*wsk -= 1;
		}
		else {
			Sleep(50);
		}
	}
}

void countMilisec()
{
	while (goCounter) {
		Sleep(1);
		timeCounter++;
	}
}

int timerStatus() {

	return timeCounter;
}

void gameTimeF(string action)
{
	if (action == "START") {

		gameTimeStatus = true;
		while (gameTimeStatus) {

			Sleep(1000);
			gameTime++;
		}
	}
	else if (action == "STOP") {

		gameTimeStatus = false;
		gameTime = 0;
	}
}

void Game::setplayerName()
{
	RenderWindow window{ VideoMode{ 258, 150 }, "Exit" };
	window.setFramerateLimit(60);

	int optionWidth = 45;
	int optionHeight = 27;
	RectangleShape go(sf::Vector2f(optionWidth, optionHeight));
	RectangleShape input(sf::Vector2f(150, 27));
	Color fillColorButton(209, 209, 209);
	Color fillColorBackgrount(227, 229, 229);
	Color fillColorButtonHover(217, 219, 219);
	Color outlineColor(40, 40, 40);

	go.setFillColor(fillColorButton);
	go.setOutlineColor(outlineColor);
	go.setOutlineThickness(1);
	go.setPosition(sf::Vector2f(188, 80));

	input.setFillColor(sf::Color(200, 190, 200));
	input.setPosition(sf::Vector2f(27, 80));
	input.setOutlineThickness( 1 );
	input.setOutlineColor(sf::Color::Black);

	Font font;
	font.loadFromFile("Roboto-Medium.ttf");

	Text text;
	text.setFont(font);
	text.setCharacterSize(19);
	text.setFillColor(outlineColor);

	Text textGo = text;
	textGo.setCharacterSize(17);
	Text textName = text;
	Text textTitle = text;
	string strName = "";

	textGo.setString("Go");
	textGo.setPosition(sf::Vector2f(200, 82));
	textName.setPosition(sf::Vector2f(30, 80));
	textTitle.setString("Set your name:");
	textTitle.setPosition(sf::Vector2f(30, 40));
	text.setString("Max 9 characters");
	text.setPosition(sf::Vector2f(30, 108));
	text.setCharacterSize(12);

	Event event;
	Vector2i mousePos;
	int strNameLength = 0;
	int lastCharNumber = 0;
	thread counter(countMilisec);
	regex playerNameRegex("^\\w+[\\s*\\w*]*");

	while (true) {

		window.pollEvent(event);

		window.clear(fillColorBackgrount);

		textName.setString(strName);
		window.draw(go);
		window.draw(textGo);
		window.draw(input);
		window.draw(textName);
		window.draw(text);
		window.draw(textTitle);

		mousePos = sf::Mouse::getPosition(window);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			if (go.getPosition().x < mousePos.x
				&& go.getPosition().x + optionWidth > mousePos.x
				&& go.getPosition().y < mousePos.y
				&& go.getPosition().y + optionHeight > mousePos.y
				) {

				if (regex_match(strName, playerNameRegex)) {

					window.close();
					break;
				} else {

					strName = "";
				}

			}
		}

		if (event.type == sf::Event::MouseMoved) {

			if (go.getPosition().x < mousePos.x
				&& go.getPosition().x + optionWidth > mousePos.x
				&& go.getPosition().y < mousePos.y
				&& go.getPosition().y + optionHeight > mousePos.y
				) {

				go.setFillColor(fillColorButtonHover);
			}
			else {
				go.setFillColor(fillColorButton);
			}
		}

		if (event.type == sf::Event::TextEntered) {

			if (event.text.unicode < 128 && (event.text.unicode != lastCharNumber || lasCharUse + 120 < timerStatus()) ) {

				strNameLength = strName.length();
				if ((event.text.unicode == 8) && (strNameLength - 1 >= 0)) { //usuniêcie znaku

					strName.erase(strNameLength - 1, 1);
					Sleep(80);
				} else if(event.text.unicode != 8 && strNameLength < 9){

					lastCharNumber = event.text.unicode;
					lasCharUse = timerStatus();
					strName += static_cast<char>(event.text.unicode);
				}
			}
		}
		window.display();
	}

	playerName = strName;

	goCounter = false;
	if (counter.joinable())
		counter.join();
}

void Game::saveScore()
{
	fstream file;
	file.open("rank.txt", ios::out | ios::app);

	if (file.good() == false) { //oznacza ze plik nie istnieje 

		cout << "W katalogu z programem musi znalezæ siê plik base.blaut" << endl;
	}
	else {

		file << playerName << "," << playerPoints << ",";

		SYSTEMTIME st;
		GetLocalTime(&st);

		int day = st.wDay;
		int month = st.wMonth;
		int year = st.wYear;

		file << year;
		file << "-";
		if (month < 10) {

			file << "0" << month;
		} else {

			file << month;
		}
		file << "-";

		if (day < 10) {

			file << "0" << day;
		} else {

			file << day;
		}

		file << "," << gameTimeText << ",;" << endl;

		file.close();
	}
}
