#pragma once
class ListRankRecord
{
public:
	ListRankRecord(string nameT, string scoreT, string dateT, string timeT);
	~ListRankRecord() = default;
	string name{ "" };
	string score{ "0" };
	string date{ "2018-01-05" };
	string time{ "0" };
	Font font;
	Text textName;
	Text textScore;
	Text textDate;
	Text textTime;
};

