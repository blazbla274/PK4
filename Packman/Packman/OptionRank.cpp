#include "stdafx.h"
#include "OptionRank.h"


OptionRank::OptionRank(Menu *m, Game* g, RenderWindow* w)
{
	name = "Rank";
	yPosition = 290;
	game = g;
	menu = m;
	window = w;
}

void OptionRank::action()
{
	detection = true;

	list<ListRankRecord> rank;
	Vector2f tablePosition(130, 195);
	int visibleRecords = 10;
	int i = 0;
	OptionBack backInput(menu, game, window);

	fstream file;
	file.open("rank.txt", ios::in);

	if (file.good() == false) { //oznacza ze plik nie istnieje 

		cout << "W katalogu z programem musi znalezæ siê plik base.blaut" << endl;
	}
	else {

		string line;
		string str = "";
		int moveDistance = 0; //oblicza line record height 
		int lineHeight = 22;
		int i = 0, mode;
		ListRankRecord *recorsWsk{ nullptr };
		bool inject = false;
		string nameR, scoreR, dateR, timeR;

		while (getline(file, line)) {

			mode = 0;
			str = "";
			i = 0;
			while(line[i] != ';') {

				if (line[i] != ',') {
					str += line[i];
				} else {

					switch (mode) {
					case 0:  nameR = str;
						break;
					case 1:  scoreR = str;
						break;
					case 2:  dateR = str;
						break;
					case 3:  timeR = str;
						break;
					default:
						break;
					}

					str = "";
					mode++;
				}
				i++;
			}
			
			recorsWsk = new ListRankRecord(nameR, scoreR, dateR, timeR);

			int x = rank.size();
			inject = false;

			if(rank.size() >= 2)
			for (auto iterator = rank.begin(); iterator != rank.end(); iterator++) {

				if (iterator->name == "Name");
				else if (atoi(iterator->score.c_str()) < atoi(scoreR.c_str())) {

					rank.insert(iterator, *recorsWsk);
					inject = true;
					break;
				}
			}

			if (rank.size() == 1 || rank.begin() == rank.end()) {
				rank.push_back(*recorsWsk);
				inject = true;
			}
			if (!inject) {
				rank.push_back(*recorsWsk);
			}

			//delete recorsWsk;
		}
		
		file.close();

		i = 0;
		for (auto iterator = rank.begin(); iterator != rank.end() , i < visibleRecords; ++iterator, i++) {

			iterator->textName.setPosition(tablePosition);
			iterator->textScore.setPosition(tablePosition.x + 100, tablePosition.y);
			iterator->textDate.setPosition(tablePosition.x + 200, tablePosition.y);
			iterator->textTime.setPosition(tablePosition.x + 400, tablePosition.y);

			iterator->textName.move(sf::Vector2f(0, moveDistance));
			iterator->textScore.move(sf::Vector2f(0, moveDistance));
			iterator->textDate.move(sf::Vector2f(0, moveDistance));
			iterator->textTime.move(sf::Vector2f(0, moveDistance));
			moveDistance += lineHeight;
		}
	}

	while (true) {

		window->clear(menu->background);
		window->draw(menu->logo);
		window->draw(backInput);
		
		i = 0;
		for (auto iterator = rank.begin(); iterator != rank.end(), i < visibleRecords; ++iterator, i++) {

			window->draw(iterator->textName);
 			window->draw(iterator->textScore);
			window->draw(iterator->textDate);
			window->draw(iterator->textTime);
		}

		window->display();
		if (detect(&backInput)) {

			detection = false;
			break;
		}
	}
}
