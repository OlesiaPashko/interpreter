#include "Cat.h"

string Cat::convSysStrToStdStr(System::String^ sysStr) {
	/* Œ—“€À‹, Õ»◊≈ Õ»œ¿Õﬂ“Õ¿*/
	return msclr::interop::marshal_as<string>(sysStr);
}

vector<string> Cat::setFurColor(string newFurColor) {
	vector<string> res;
	string curAction;
	if (hasPartner) {
		curOthersBehaviour.getCurAddress();
	}
	else {
		curSelfBehaviour.getCurAddress();
	}

	string stEyesColor = convSysStrToStdStr(eyesColor);

	res.push_back(newFurColor + "/" + stEyesColor + "/" + curAction);
	return res;
}

vector<string> Cat::setEyesColor(string newEyesColor) {
	vector<string> res;
	string curAction;
	if (hasPartner) {
		curOthersBehaviour.getCurAddress();
	}
	else {
		curSelfBehaviour.getCurAddress();
	}

	string stFurColor = convSysStrToStdStr(furColor);

	res.push_back(stFurColor + "/" + newEyesColor + "/" + curAction);
	return res;
}

string Cat::getFurColor() {
	return convSysStrToStdStr(furColor);
}

string Cat::getEyesColor() {
	return convSysStrToStdStr(eyesColor);
}

map<string, double> Cat::getAdresses(string action) {
	return getAdresses(action, "auto");
}

map<string, double> Cat::getAdresses(string action, string curPartner) {
	if (curPartner != "auto") {
		curOthersBehaviour.setPartner(curPartner);
		if (curPartner == "none") {
			hasPartner = false;
		}
		else {
			hasPartner = true;
		}
	}
	if (hasPartner) {
		return curOthersBehaviour.getAddresses(action);
	}
	else {
		return curSelfBehaviour.getAddresses(action);
	}
}

map<string, double> Cat::getAdressesByAmount(string action, int amount) {
	return getAdressesByTime(action, amount, "auto");
}

map<string, double> Cat::getAdressesByAmount(string action, int amount, string curPartner) {
	if (curPartner != "auto") {
		curOthersBehaviour.setPartner(curPartner);
		if (curPartner == "none") {
			hasPartner = false;
		}
		else {
			hasPartner = true;
		}
	}
	if (hasPartner) {
		return curOthersBehaviour.getAddressesByAmount(action, amount);
	}
	else {
		return curSelfBehaviour.getAddressesByAmount(action, amount);
	}
}

map<string, double> Cat::getAdressesByTime(string action, double time) {
	return getAdressesByTime(action, time, "auto");
}

map<string, double> Cat::getAdressesByTime(string action, double time, string curPartner) {
	if (curPartner != "auto") {
		curOthersBehaviour.setPartner(curPartner);
		if (curPartner == "none") {
			hasPartner = false;
		}
		else {
			hasPartner = true;
		}
	}
	if (hasPartner) {
		return curOthersBehaviour.getAddressesByTime(action, time);
	}
	else {
		return curSelfBehaviour.getAddressesByTime(action, time);
	}
}

map<string, double> Cat::getAdressesByPhrase(string phrase) {
	return getAdressesByPhrase(phrase, "auto");
}

map<string, double> Cat::getAdressesByPhrase(string phrase, string curPartner) {
	double amount = getAmountOfPhrase(phrase);
	return getAdressesByAmount("say", amount, "auto");
}

int Cat::getAmountOfPhrase(string phrase) {
	int res;
	string vowels = "eyuioa";
	for (int i = 0; i < phrase.length(); i++) {
		for (int j = 0; j < vowels.length(); j++) {
			if (phrase[i] == vowels[j]) {
				res++;
				break;
			}
		}
	}
	return res;
}