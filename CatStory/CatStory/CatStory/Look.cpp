#include "Look.h";
#include <iostream>
string Look::getFurColor() {
	return this->furColor;
}

string Look::getEyesColor() {
	return this->eyesColor;
}

vector<string> Look::setFurColor(string newFurColor) {
	vector<string> result;
	if (newFurColor == "red") {
		this->furColor = newFurColor;
		result.push_back("red");
	}
	else if (newFurColor == "black") {
		this->furColor = newFurColor;
		result.push_back("black");
	}
	else if (newFurColor == "white") {
		this->furColor = newFurColor;
		result.push_back("white");
	}
	else
		cout << "It`s illegal fur`s color";//rewrite in different form error
	return result;
}

vector<string> Look::setEyesColor(string newEyesColor) {
	vector<string> result;
	result.push_back(this->getFurColor());
	if (newEyesColor == "yellow") {
		this->eyesColor = newEyesColor;
		result.push_back("yellow");
	}
	else if (newEyesColor == "blue") {
		this->eyesColor = newEyesColor;
		result.push_back("blue");
	}
	else if (newEyesColor == "green") {
		this->eyesColor = newEyesColor;
		result.push_back("green");
	}
	else if (newEyesColor == "brown") {
		this->eyesColor = newEyesColor;
		result.push_back("brown");
	}
	else
		cout << "It`s illegal color of eyes";//rewrite in different form error
	
	return result;
}
