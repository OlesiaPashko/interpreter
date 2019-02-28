#pragma once

#include<vector>
#include<string>
#include<fstream>
#include<map>
#include<msclr/marshal_cppstd.h>
using namespace std;
using namespace System;

ref class OthersBehaviour {
	String^ emotion;
	String^ partner = "none";
	String^ curState;
	String^ folder = "othersBehaviour";
public:
	//vector<string> say(string phrase);
	void setEmotion(string newEmotion);
	string convSysStrToStdStr(String^ sysStr);
	string setPartner(string newPartner);
	map<string, double> getAddresses(string state);
	map<string, double> getAddressesByTime(string state, double time);
	map<string, double> getAddressesByAmount(string state, int amount);
	string getCurAddress();
};