#include "stdafx.h"
#include "ListRankRecord.h"

ListRankRecord::ListRankRecord(string nameT, string scoreT, string dateT, string timeT)
{
	name = nameT;
	score = scoreT;
	date = dateT;
	time = timeT;

	font.loadFromFile("Roboto-Medium.ttf");
	int charSize = 22;

	textName.setString(nameT);
	textName.setFont(font);
	textName.setCharacterSize(charSize);

	textScore.setString(scoreT);
	textScore.setFont(font);
	textScore.setCharacterSize(charSize);

	textDate.setString(dateT);
	textDate.setFont(font);
	textDate.setCharacterSize(charSize);

	textTime.setString(timeT);
	textTime.setFont(font);
	textTime.setCharacterSize(charSize);

	textScore.move(sf::Vector2f(50, 0));
	textDate.move(sf::Vector2f(100, 0));
	textTime.move(sf::Vector2f(150, 0));
}
