#pragma once

#include<vector>
#include<string>
#include<fstream>
#include<map>
#include<msclr/marshal_cppstd.h>
using namespace std;
using namespace System;

ref class SelfBehaviour {
	String^ curState = "stand";
	String^ folder = "selfBehaviour";
public:
	string convSysStrToStdStr(String^ sysStr);
	map<string, double> getAddresses(string state);
	map<string, double> getAddressesByTime(string state, double time);
	map<string, double> getAddressesByAmount(string state, int amount);
	string getCurAddress();
};