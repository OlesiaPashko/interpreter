#include "Background.h"

vector<string> Background::setBackground(string newBackground) {
	vector<string> result;
	background = newBackground;
	result.push_back(folder + "/" + newBackground + ".png");
	return result;
}

string Background::getBackground() {
	return background;
}