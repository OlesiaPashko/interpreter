#pragma once

#include<vector>
#include<string>
using namespace std;

class Background {
	string background;
	string folder = "background";
public:
	vector<string> setBackground(string newBackground);
	string getBackground();
};