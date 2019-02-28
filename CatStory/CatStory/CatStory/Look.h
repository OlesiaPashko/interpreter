#pragma once

#include<vector>
#include<string>
using namespace std;

class Look {
	string furColor, eyesColor;
public:
	vector<string> setFurColor(string newFurColor);
	vector<string> setEyesColor(string newEyesColor);
	string getFurColor();
	string getEyesColor();

};