#pragma once

#include<vector>
#include<string>
#include<msclr/marshal_cppstd.h>
#include"SelfBehaviour.h"
#include"OthersBehaviour.h"
using namespace System;

ref class Cat {
	String^ furColor;
	String^ eyesColor;
	bool hasPartner = false;
	SelfBehaviour curSelfBehaviour;
	OthersBehaviour curOthersBehaviour;
public:
	vector<string> setFurColor(string newFurColor);
	vector<string> setEyesColor(string newEyesColor);
	string getFurColor();
	string getEyesColor();
	string convSysStrToStdStr(String^ sysStr);
	map<string, double> getAdresses(string action);
	map<string, double> getAdresses(string action, string curPartner);
	map<string, double> getAdressesByAmount(string action, int amount);
	map<string, double> getAdressesByAmount(string action, int amount, string curPartner);
	map<string, double> getAdressesByTime(string action, double time);
	map<string, double> getAdressesByTime(string action, double time, string curPartner);
	map<string, double> getAdressesByPhrase(string phrase);
	map<string, double> getAdressesByPhrase(string phrase, string curPartner);
	int getAmountOfPhrase(string phrase);
};