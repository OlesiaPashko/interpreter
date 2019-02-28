#include "Interface.h"
/*write from test.txt texst and make sentences from it*/
vector<string> Interface::makeSentences() {
	vector<string> result;
	ifstream file;
	file.open("test.txt");
	string sentence;
	while (!file.eof()) {
		getline(file, sentence, '.');
		if (sentence[0] == ' ')
			sentence.erase(0, 1);
		result.push_back(sentence);
	}
	result = correctSentences(result);
	return result;
}

/*Join sentences when we use floats*/
vector<string> Interface::correctSentences(vector<string> sentences) {
	for (int i = 1; i < sentences.size(); i++) {
		if (isdigit(sentences[i][0])) {
			sentences[i - 1] = sentences[i - 1] + "." + sentences[i];
			sentences.erase(sentences.begin()+i);
		}
	}
	return sentences;
}


/*Gets a words devided by ' ' and test if characters correct*/
vector<string> Interface::wordsInSentence(string sentence) {
	string word = ""; 
	string repl="";//replica
	bool qot = false;//flag that we have met "
	vector<string> result;
	if(!isalpha(tolower(sentence[0])))//to have opportunity use sentence[i-1]
		throw SyntaxError(sentence, sentence[0]);
	word += tolower(sentence[0]);
	for (int i = 1; i < sentence.length(); i++) {
		if (sentence[i] == ',') {
			result.push_back(word);
			word = ",";
		}
		else if (sentence[i] == '\"') {
			qot = !qot;
			if (repl != "")
				word = "\"" + repl + "\"";
		}
		else if (qot) {
			repl += sentence[i];
		}
		else if (sentence[i] != ' '&&((sentence[i-1]==' '|| sentence[i - 1] == '.' ||isdigit(sentence[i - 1]))&&isdigit(sentence[i]))//errors like ca8t 44t5
			|| (isdigit(sentence[i - 1]) && sentence[i]=='.')
			||((sentence[i - 1] == ' '||isalpha(sentence[i-1]))&&isalpha(tolower(sentence[i])))) {
			word += tolower(sentence[i]);
		}
		else if(sentence[i]!=' ')
			throw SyntaxError(sentence, sentence[i]);
		else {
			while (sentence[i + 1] == ' ')//if there are many ' '-s
				i++;
			result.push_back(word);
			word = "";
		}
	}
	result.push_back(word);
	return result;
}

/*return is word one of the correct words*/
bool Interface::has(vector<string> rightWords, string word) {
	for (int i = 0; i < rightWords.size(); i++) {
		if (rightWords[i] == word)
			return true;
	}
	//throw LexicographicError(join(rightWords, " "), partOfSpeech);
	return false;
}

bool Interface::isConstruction(vector<string> words, int indexOfWord) {//after verb is "for", "x times", "to somebody"
	pair<string, int> verb = makeComplexWord(words,indexOfWord);
	int indexOfWordAfterVerb = verb.second + indexOfWord;
	if (indexOfWordAfterVerb < words.size())//verd is not end of the part
		return true;
	return false;
	
}

/*Can we parse string in integer*/
bool  Interface::isNumber(const std::string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

/*Can we parse string in float*/
bool  Interface::isFloatNumber(const std::string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && (isdigit(*it)||(*it)=='.')) ++it;
	return !s.empty() && it == s.end();
}


/*make from "Cat have jumped, said "bla bla bla" and run away" => {" "Cat have jumped", "said \"bla bla bla\"", "run away"}*/
vector<vector<string> > devideIntoParts(vector<string> words) {
	vector<vector<string> > parts;
	int firstWord = 0;
	for (int i = 0; i < words.size(); i++) {
		if (words[i] == "and" || words[i] == "," ) {
			vector<string> temp;
			for (int j = firstWord; j < i; j++) {
				temp.push_back(words[j]);
			}
			firstWord = i + 1;
			parts.push_back(temp);

		}
	}
	vector<string> temp;
	for (int j = firstWord; j < words.size(); j++) {
		temp.push_back(words[j]);
	}
	parts.push_back(temp);
	return parts;
}

/*check is all parts by function isPartCorrect()*/
bool Interface::isPartsCorrect(vector<string> words, int indexOfWord, vector<string> verbs, vector<string> nouns) {
	vector<vector<string> > parts = devideIntoParts(words);
	if (!isPartCorrect(parts[0], indexOfWord, verbs, nouns))
		return false;
	for (int i = 1; i < parts.size(); i++) {
		if (!isPartCorrect(parts[i], 0, verbs, nouns))
			return false;
	}
	return true;
}

bool Interface::isVerbBeforeToCorrect(string complexVerb) {
	string correct[] = { "say hello", "say bye", "give five" };
	bool flag = false;
	for (int i = 0; i < 3; i++) {
		if (isVerbBeforePrepositionCorrect(complexVerb, correct[i]))
			flag = true;
	}
	return flag;
}


bool Interface::isVerbAboutLocationCorrect(string complexVerb) {
	string correct[] = { "run", "go", "come", "run away", "go away" };
	bool flag = false;
	for (int i = 0; i < 5; i++) {
		if (isVerbBeforePrepositionCorrect(complexVerb, correct[i]))
			flag = true;
	}
	return flag;
}

bool Interface::isVerbBeforeForCorrect(string complexVerb) {
	string correct[] = { "sniff","run", "sit", "catch", "purr", "hiss" };
	bool flag = false;
	for (int i = 0; i < 6; i++) {
		if (isVerbBeforePrepositionCorrect(complexVerb, correct[i]))
			flag = true;
	}
	return flag;
}

bool Interface::isVerbBeforeTimesCorrect(string complexVerb) {
	string correctSimple[] = { "jump", "hiss", "purr", "catch", "give five", "sniff", "say hello", "say bye" };
	bool flag = false;
	for (int i = 0; i < 8; i++) {
		if (isVerbBeforePrepositionCorrect(complexVerb, correctSimple[i]))
			flag = true;
	}
	return flag;
}

/*sort out all forms of correct verb and returns is complex verb one of them*/
bool Interface::isVerbBeforePrepositionCorrect(string complexVerb, string correctVerb) {
	vector<string> sayForms = getFormsOfVerb(correctVerb);
	vector<string>::iterator it = find(sayForms.begin(), sayForms.end(), complexVerb);
	if (it != sayForms.end())
		return true;
	return false;
}

/*true when part is like "was in park", "have red fur", "have blue eyes", "was red"*/
bool Interface::isCorrectAuxilaryPart(vector<string> words, int indexOfWord) {
	if (words.size() - indexOfWord - 1 == 0)
		return false;
	pair<string, int> aux = findAuxilary(words, indexOfWord);
	if (words.size() > indexOfWord + 1 + aux.second && words[indexOfWord + aux.second] == "in"&&
		has(getCorrectFormsOfWord("Locations", "nouns"), words[indexOfWord + 2]))
		return true;
	else if (words.size() > indexOfWord+ aux.second&&(has(getCorrectFormsOfWord("fur", "adjectives"), words[indexOfWord + 1])|| words[indexOfWord + 1]=="embarrassed"))
		return true;
	else if (words.size() > indexOfWord + aux.second+1&&has(getCorrectFormsOfWord("have", "verbs"), words[indexOfWord]) &&
		(has(getCorrectFormsOfWord("fur", "adjectives"), words[indexOfWord+aux.second]) && words[indexOfWord+aux.second + 1] == "fur") ||
		(has(getCorrectFormsOfWord("eyes", "adjectives"), words[indexOfWord + aux.second]) && words[indexOfWord + aux.second + 1] == "eyes"))
		return true;
	return false;
}

bool Interface::isQot(string word) {
	return word[0] == '\"'&&word[word.size() - 1] == '\"';
}
string Interface::qotToPhrase(string word) {
	string result;
	for (int i = 1; i < word.size() - 1; i++)
		result += word[i];
	return result;
}

bool Interface::correctForSeconds(vector<string> words, int index) {
	return words.size() > index + 2 && words[index] == "for"&&
		isFloatNumber(words[index + 1]) &&
		words[index + 2] == "seconds";
}

bool Interface::correctForMinutes(vector<string> words, int index) {
	return words.size() > index + 2 && words[index] == "for"&&
		isFloatNumber(words[index + 1]) &&
		words[index + 2] == "minutes";
}

bool Interface::correctTimes(vector<string> words, int index) {
	return words.size() > index + 1 && isNumber(words[index]) && words[index + 1] == "times";
}

bool Interface::isCorrectSaying(vector<string> words, int indexOfWordAfterVerb) {
	if (isQot(words[indexOfWordAfterVerb])) {// say "blabla"
		if (words.size() - 1 == indexOfWordAfterVerb) {
			//resForm->doCat(curCat.getAdressesByPhrase(qotToPhrase(words[indexOfWordAfterVerb])));
			//resForm->printSay(qotToPhrase(words[indexOfWordAfterVerb]));
			return true;
		}
		else if (correctTimes(words, indexOfWordAfterVerb + 1)) {//say "blabla" x times
			//resForm->doCat(curCat.getAdressesByAmountAndPhrase(qotToPhrase(words[indexOfWordAfterVerb]), stoi(words[indexOfWordAfterVerb + 1])));
			//resForm->printSay(qotToPhrase(words[indexOfWordAfterVerb]));
			return true;
		}
		else if (words.size() > indexOfWordAfterVerb + 2 && words[indexOfWordAfterVerb + 1] == "to" &&// say "blabla" to fox
			has(getCorrectFormsOfWord("Persons", "nouns"), words[indexOfWordAfterVerb + 2])) {
			cout << 303;
			//if (!curCat.getHasPartner())
				//resForm->doCat(curCat.getAdresses("run", words[indexOfWordAfterVerb + 2]));
			//else if (curCat.getPartner() != words[indexOfWordAfterVerb + 2]) {
				//тут я еще подумаю
		//	}
			//resForm->doCat(curCat.getAdressesByPhrase(qotToPhrase(words[indexOfWordAfterVerb]), words[indexOfWordAfterVerb + 2]));
			//resForm->printSay(qotToPhrase(words[indexOfWordAfterVerb]));
			cout << " 304";
			return true;
		}
	}
	else if (correctTimes(words, indexOfWordAfterVerb) && isQot(words[indexOfWordAfterVerb + 2])) {//say x times "blabla"
		//resForm->doCat(curCat.getAdressesByAmountAndPhrase(qotToPhrase(words[indexOfWordAfterVerb + 2]), stoi(words[indexOfWordAfterVerb])));
		//resForm->printSay(qotToPhrase(words[indexOfWordAfterVerb + 2]));
		return true;
	}
	return false;
}

bool Interface::correctToPart(vector<string> words, int indexOfWordAfterVerb, pair<string, int> verb, vector<string> nouns, vector<string>verbs) {
	if (has(nouns, words[indexOfWordAfterVerb + 1]) && isVerbAboutLocationCorrect(verb.first)) {//run to park, go away to city
		//curBackground.setBackground(words[indexOfWordAfterVerb + 1]);
		//resForm->doCat(curCat.getAdresses(getNormWord(verb.first)));
		return true;
	}
	else if (indexOfWordAfterVerb + 3 < words.size() && has(getCorrectFormsOfWord("Persons", "nouns"), words[indexOfWordAfterVerb + 1])
		&& correctTimes(words, indexOfWordAfterVerb + 2)) {//say hello to fox 3 times
		//resForm->doCat(curCat.getAdressesByAmount(getNormWord(verb.first), stoi(words[indexOfWordAfterVerb + 2]), words[indexOfWordAfterVerb + 1]));
		return true;
	}
	else if (has(nouns, words[indexOfWordAfterVerb + 1]) && isVerbBeforeToCorrect(verb.first)) {//give five to fox
		cout << 1234;
		//if (!curCat.getHasPartner())
			//resForm->doCat(curCat.getAdresses("run", words[indexOfWordAfterVerb + 1]));
		//else if (curCat.getPartner() != words[indexOfWordAfterVerb + 1]) {
			//тут я еще подумаю
		//}
		//resForm->doCat(curCat.getAdresses("givefive"));
		return true;
	}
	else
		return false;
}

bool Interface::isConstructionCorrect(vector<string> words, int indexOfWord, pair<string, int> verb, vector<string> nouns, vector<string> verbs) {
	int indexOfWordAfterVerb = verb.second + indexOfWord;
	if (correctForSeconds(words, indexOfWordAfterVerb) && isVerbBeforeForCorrect(verb.first)) {//verb for somenumber second
		//resForm->doCat(curCat.getAdressesByTime(getNormWord(verb.first), stof(words[indexOfWordAfterVerb + 1])));
		return true;
	}
	if (correctForMinutes(words, indexOfWordAfterVerb) &&
		isVerbBeforeForCorrect(verb.first)) {//verb for somenumber minutes
		float seconds = stof(words[indexOfWordAfterVerb + 1]) * 60;
		//resForm->doCat(curCat.getAdressesByTime(getNormWord(verb.first), seconds));
		return true;
	}
	else if (has(getCorrectFormsOfWord("say", "verbs"), verb.first)) {// say "blabla"
		return isCorrectSaying(words, indexOfWordAfterVerb);
	}
	else if (words[indexOfWordAfterVerb] == "to"&&words.size() > indexOfWordAfterVerb + 1) {
		return correctToPart(words, indexOfWordAfterVerb, verb, nouns, verbs);
	}
	else if (words[indexOfWordAfterVerb] == "into"&&words.size() > indexOfWordAfterVerb + 1 &&
		has(nouns, words[indexOfWordAfterVerb + 1]) && isVerbAboutLocationCorrect(verb.first)) {//run away into park
		//curBackground.setBackground(words[indexOfWordAfterVerb + 1]);
		//resForm->doCat(curCat.getAdresses(getNormWord(verb.first)));
		return true;
	}
	else if (isVerbBeforeTimesCorrect(verb.first) && correctTimes(words, indexOfWordAfterVerb)) {//say hello 2 times
		//resForm->doCat(curCat.getAdressesByAmount(getNormWord(verb.first), stoi(words[indexOfWordAfterVerb])));
		return true;
	}
	else
		throw GrammaticalError(join(words, " "), "");
	return false;

}

bool Interface::isPartCorrect(vector<string> words, int indexOfWord, vector<string> verbs, vector<string> nouns) {
	if (isCorrectAuxilaryPart(words, indexOfWord))
		return true;
	pair<string, int> verb = makeComplexWord(words, indexOfWord);
	if (!isConstruction(words, indexOfWord))//there is only verb without to/in/for...
		if (has(verbs, verb.first)) {
			//resForm->doCat(curCat.getAdresses(getNormWord(verb.first)));
			return true;
		}
		else
			throw GrammaticalError(join(words, " "), verb.first);
	else {
		return isConstructionCorrect(words, indexOfWord, verb, nouns, verbs);
	}

}
/*what this function do? from ({"Cat", "have", "been", "sitting", "down"}, 1) it returns <"have been sitting down", 4> 
input - all sentence and index of verb or auxilary in sentence
output - string of all long verb and how many words does it have
*/
pair<string, int> Interface::makeComplexWord(vector<string> words, int indexOfWord) {
	string firstResult = "";
	int startWord = indexOfWord;
	pair<string, int> aux = findAuxilary(words, indexOfWord);//<"have been", 2> for instance
	if (aux.second == 1) {
		firstResult += aux.first;
		indexOfWord++;
		firstResult = firstResult+' '+ words[indexOfWord];
	}
	else if (aux.second == 2) {
		firstResult += aux.first;
		indexOfWord += 2;
		firstResult = firstResult + ' ' + words[indexOfWord];
	}
	else
		firstResult += words[indexOfWord];
	vector<string> ends = { "down","up","hello","bye","away", "five" };
	indexOfWord++;//to take end like down or up, not a verb like run or sitting
	if (indexOfWord < words.size()) {
		for (int i = 0; i < 6; i++) {
			if (words[indexOfWord] == ends[i]) {
				firstResult = firstResult + " " + ends[i];
				indexOfWord++;
				break;
			}
		}
	}
	return make_pair(firstResult, indexOfWord-startWord);
}
//input ({"Cat", "have", "been", "sitting", "down"}, 1)
//output <"have been", 2> for instance
pair<string, int> Interface::findAuxilary(vector<string> words, int indexOfWord) {//returns auxilary and how many words is it
	vector<string> aux = getAuxilary();
	if (indexOfWord + 1 < words.size()) {//the verb isn`t the last word in sentence
		for (int i = 0; i < aux.size(); i++) {
			if (words[indexOfWord] + " " + words[indexOfWord + 1] == aux[i])
				return make_pair(words[indexOfWord] + " " + words[indexOfWord + 1], 2);
			else if(words[indexOfWord]== aux[i])
				return make_pair(words[indexOfWord], 1);
		}
	}
	return make_pair("", 0);
}

bool Interface::isOneSentenceCorrect(vector<string> words) {
	vector<string> adj, nouns, verbs, pronouns;
	adj = getWordsFromFile("adjectives");
	nouns = getWordsFromFile("nouns");
	verbs = getWordsFromFile("verbs");
	pronouns = getWordsFromFile("pronouns");
	/*it need`s a rewriting because it`s hardcoding*/
	if (has(getCorrectFormsOfWord("fur", "adjectives"), words[0])) {//the first word is adjactive
		if (words.size() > 5 && (words[1] == "cat" || has(pronouns, words[1])) && words[2] == "with"
			&& has(getCorrectFormsOfWord("eyes", "adjectives"), words[3]) && words[4] == "eyes") {//red cat with blue eyes ...
			//curCat.setEyesColor(words[3]);
			//curCat.setFurColor(words[0]);
			return isPartsCorrect(words, 5, verbs, nouns);
		}
		else if (words.size() > 2 && (words[1] == "cat" || has(pronouns, words[1])))//red cat ...
			//curCat.setFurColor(words[0]);
			return isPartsCorrect(words, 2, verbs, nouns);
	}
	else if (words.size() > 4 && (words[0] == "cat" || has(pronouns, words[0]))//Cat with blue eyes ... 
		&& words[1] == "with" && has(getCorrectFormsOfWord("eyes", "adjectives"), words[2]) && (words[3] == "eyes")) {
		//curCat.setEyesColor(words[2]);
		return isPartsCorrect(words, 4, verbs, nouns);
	}
	else if (words.size() > 4 && (words[0] == "cat" || has(pronouns, words[0]))//Cat with white fur ... 
		&& words[1] == "with" && has(getCorrectFormsOfWord("fur", "adjectives"), words[2]) && words[3] == "fur") {
		//curCat.setFurColor(words[2]);
		return isPartsCorrect(words, 4, verbs, nouns);
	}
	else if (words.size() > 7 && (words[0] == "cat" || has(pronouns, words[0])) && words[1] == "with"
		&& has(getCorrectFormsOfWord("eyes", "adjectives"), words[2]) && words[3] == "eyes" && words[4] == "and"
		&& has(getCorrectFormsOfWord("fur", "adjectives"), words[5]) && words[6] == "fur") {//cat with blue eyes and white fur ...
		//curCat.setEyesColor(words[2]);
		//curCat.setFurColor(words[5]);
		return isPartsCorrect(words, 7, verbs, nouns);
	}
	else if (words.size() > 7 && (words[0] == "cat" || has(pronouns, words[0])) && words[1] == "with"
		&& has(getCorrectFormsOfWord("fur", "adjectives"), words[2]) && words[3] == "fur" && words[4] == "and"
		&& has(getCorrectFormsOfWord("eyes", "adjectives"), words[5]) && words[6] == "eyes") {//cat with white fur and blue eyes ...
		//curCat.setEyesColor(words[5]);
		//curCat.setFurColor(words[2]);
		return isPartsCorrect(words, 7, verbs, nouns);
	}
	else if (words.size() > 1 && (words[0] == "cat" || has(pronouns, words[0])) && isPartsCorrect(words, 1, verbs, nouns)) {//cat ...
		return true;
	}
	else if (words.size() > 2 && has(getCorrectFormsOfWord("Persons", "nouns"), words[0])
		&& has(getCorrectFormsOfWord("give five", "verbs"), makeComplexWord(words, 1).first)) {
		//	if (!curCat.getHasPartner()) {
				//resForm->doCat(curCat.getAdresses("run", words[0]));
			//}
			//else if (curCat.getPartner() != words[0]) {
				//тут я еще подумаю
			//}
			//resForm->doCat(curCat.getAdresses("givefive"));
			//resForm->doPartner(curCat.getAddressesForPartner("givefive"));
			//resForm->doPartner();
		return true;
	}
	/*cout << endl << "-------";
	for(int i = 0; i< getCorrectFormsOfWord("give five", "verbs").size(); i++)
	cout << getCorrectFormsOfWord("give five", "verbs")[i] << endl;*/
	throw GrammaticalError(join(words, " "), "");
}

/*void Interface::testSentences(vector<string> sentences) {
	

}*/

/*get all words from file without words before ":"*/
vector<string> Interface::getWordsFromFile(string filename){
	ifstream file;
	file.open("partsOfSpeech/" + filename + ".txt");
	vector<string> result;
	string temp;
	while (!file.eof()) {
		getline(file, temp);
		string word;
		string subst = temp.substr(temp.find(':')+1);
		for (int i = 0; i < subst.length(); i++) {
			if (subst[i] == ',') {
				result.push_back(word);
				word = "";
			}
			else
				word += subst[i];
		}
		result.push_back(word);
	}
	return result;
}

/*returns all words like have, have been, had...*/
vector<string> Interface::getAuxilary() {
	ifstream file;
	file.open("partsOfSpeech/verbs.txt");
	vector<string> result;
	string temp;
		getline(file, temp);
		string word;
		string subst = temp.substr(temp.find(':') + 1);
		for (int i = 0; i < subst.length(); i++) {
			if (subst[i] == ',') {
				result.push_back(word);
				word = "";
			}
			else
				word += subst[i];
		}
		result.push_back(word);
	return result;
}


vector<string> Interface::getFormsOfVerb(string verb) {
	ifstream file;
	string path = "partsOfSpeech/verbs.txt";
	file.open(path);
	vector<string> result;
	string temp;
	while (!file.eof()) {
		getline(file, temp);
		string word;
		string firstWord = temp.substr(0, temp.find(':'));
		if (firstWord == verb) {
			string subst = temp.substr(temp.find(':') + 1);
			for (int i = 0; i < subst.length(); i++) {
				if (subst[i] == ',') {
					result.push_back(word);
					word = "";
				}
				else
					word += subst[i];
			}
			result.push_back(word);
		}
	}
	return result;
}

/*get all words after: in file*/
vector<string> Interface::getCorrectFormsOfWord(string inputWord, string fileName) {
	ifstream file;
	string path = "partsOfSpeech/" + fileName + ".txt";
	file.open(path);
	vector<string> result;
	string temp;
	while (!file.eof()) {
		getline(file, temp);
		string word;
		string firstWord = temp.substr(0, temp.find(':'));
		if (firstWord == inputWord) {
			string subst = temp.substr(temp.find(':') + 1);
			for (int i = 0; i < subst.length(); i++) {
				if (subst[i] == ',') {
					result.push_back(word);
					word = "";
				}
				else
					word += subst[i];
			}
			result.push_back(word);
		}
	}
	return result;
}

/*convert vector into string*/
string Interface::join(vector<string> words, string joiner) {
	string result=words[0];
	for (int i = 1; i < words.size(); i++) {
		result = result + " " + words[i];
	}
	return result;
}
