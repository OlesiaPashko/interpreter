#include"SelfBehaviour.h"

string SelfBehaviour::convSysStrToStdStr(String^ sysStr) {
	/* Œ—“€À‹, Õ»◊≈ Õ»œ¿Õﬂ“Õ¿*/
	return msclr::interop::marshal_as<string>(sysStr);
}

map<string, double> SelfBehaviour::getAddresses(string state) {
	vector<string> adresses;
	string t = "", a = "";
	map <string, string> myMap;
	vector<string> temp;
	map<string, string>::iterator it;

	ifstream file;
	file.open("partsOfSpeech/verbMap.txt");

	while (!file.eof()) {
		getline(file, t); // put whole line into temp
		temp.push_back(t);
	}

	file.close();
	t = "";

	//write words to the first or second vector
	for (int i = 0; i < temp.size(); i++) {
		for (int j = 0; j < temp[i].size(); j++) {
			if (temp[i][j] == ':') {
				a = t;
				t = "";
			}
			else if (j + 1 == temp[i].size()) {
				t += temp[i][j];
				myMap.insert(pair<string, string>(a, t));
				t = "";
				continue;
			}
			else
				t += temp[i][j];
		}

	}

	string stFolder = convSysStrToStdStr(folder);
	string stCurState = convSysStrToStdStr(curState);

	it = myMap.find(state);
	if (it->second != "both") {
		if (stCurState != it->second) {
			if (it->second == "sit") {
				adresses.push_back(stFolder + "/sitdown.gif");
			}
			else if (it->second == "stand") {
				adresses.push_back(stFolder + "/standup.gif");
			}
			adresses.push_back(stFolder + "/" + it->first + ".gif");
		}
	}
	else { //if both
		adresses.push_back(stFolder + "/" + stCurState + it->first + ".gif");
	}

	return adresses;
}

string SelfBehaviour::getCurAddress() {
	string stFolder = convSysStrToStdStr(folder);
	string stCurState = convSysStrToStdStr(curState);

	return stFolder + "/" + stCurState + ".gif";
}