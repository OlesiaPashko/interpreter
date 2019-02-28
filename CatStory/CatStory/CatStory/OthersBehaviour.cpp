#include"OthersBehaviour.h"

void OthersBehaviour::setEmotion(string newEmotion) {
	emotion = gcnew String(&newEmotion[0]);
}

string OthersBehaviour::convSysStrToStdStr(String^ sysStr) {
	/* Œ—“€À‹, Õ»◊≈ Õ»œ¿Õﬂ“Õ¿*/
	return msclr::interop::marshal_as<string>(sysStr);
}

string OthersBehaviour::setPartner(string newPartner) {
	partner = gcnew String(&newPartner[0]);
	string stFolder = convSysStrToStdStr(folder);
	string stPartner = convSysStrToStdStr(partner);
	return stFolder + "/" + stPartner + ".gif";
}

map<string, double> OthersBehaviour::getAddresses(string state) {
	vector<string> adresses;
	map<string, string> myMap;
	string t = "", a = "";
	vector<string> temp;
	int counter = 0;   //counter of lines 
	map<string, string>::iterator it;

	ifstream file;
	file.open("partsOfSpeech/verbOthersMap.txt");

	while (!file.eof()) {
		getline(file, t); // put whole line into temp
		temp.push_back(t);
		++counter;
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
			}
			else
				t += temp[i][j];
		}

	}

	string stFolder = convSysStrToStdStr(folder);
	string stPartner = convSysStrToStdStr(partner);
	string stEmotion = convSysStrToStdStr(emotion);
	string stCurState = convSysStrToStdStr(curState);

	it = myMap.find(state);
	if (it->second != "both") {
		if (curState != gcnew String(&it->second[0])) {
			if (it->second == "sit") {
				adresses.push_back(stFolder + "/" + stPartner + "/sitdown.gif");
			}
			else if (it->second == "stand") {
				adresses.push_back(stFolder + "/" + stPartner + "/standup.gif");
			}
			adresses.push_back(stFolder + "/" + stPartner + "/" + stEmotion + "/" + it->first + ".gif");
		}
	}
	else {
		adresses.push_back(stFolder + "/" + stPartner + "/" + stEmotion + "/" + stCurState + "/" + it->first + ".gif");
	}

	return adresses;
}

string OthersBehaviour::getCurAddress() {
	string stFolder = convSysStrToStdStr(folder);
	string stPartner = convSysStrToStdStr(partner);
	string stCurState = convSysStrToStdStr(curState);

	return stFolder + "/" + stPartner + "/" + stCurState + ".gif";
}