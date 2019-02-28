#pragma once

#include<vector>
#include<string>
#include "Error.h"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

class Interface {
	//Cat curCat;
	//Background curBackground;
public:
	vector<string> makeSentences(string text);
	vector<string> makeSentences();
	vector<string> getWordsFromFile(string filename);
	vector<string> wordsInSentence(string sentence);
	//void testSentences(vector<string> sentences);
	bool has(vector<string> rightWords, string word);
	bool isOneSentenceCorrect(vector<string> words);
	//vector<string> getWordsFromFile(string filename);
	pair<string, int> makeComplexWord(vector<string> words, int indexOfWord);
	vector<string> getAuxilary();
	bool isConstruction(vector<string> words, int indexOfWord);
	pair<string, int> findAuxilary(vector<string> words, int indexOfWord);
	bool isPartCorrect(vector<string> words, int indexOfWord, vector<string> verbs, vector<string> nouns);
	bool isPartsCorrect(vector<string> words, int indexOfWord, vector<string> verbs, vector<string> nouns);
	vector<string> getFormsOfVerb(string word);
	bool  isNumber(const string& s);
	bool  isFloatNumber(const string& s);
	vector<string> correctSentences(vector<string> sentences);
	bool isVerbBeforePrepositionCorrect(string complexVerb, string correctVerb);
	bool isVerbBeforeToCorrect(string complexVerb);
	bool isVerbBeforeForCorrect(string complexVerb);
	bool isVerbBeforeTimesCorrect(string complexVerb);
	vector<string> getCorrectFormsOfWord(string word, string fileName);
	string join(vector<string> words, string joiner);
	bool isVerbAboutLocationCorrect(string complexVerb);
	bool isCorrectAuxilaryPart(vector<string> words, int indexOfWord);
	bool isQot(string word);
	string qotToPhrase(string word);
	bool correctForSeconds(vector<string> words, int index);
	bool correctForMinutes(vector<string> words, int index);
	bool correctTimes(vector<string> words, int index);
	bool isCorrectSaying(vector<string> words, int indexOfWordAfterVerb);
	bool correctToPart(vector<string> words, int indexOfWordAfterVerb, pair<string, int> verb, vector<string> nouns, vector<string>verbs);
	bool isConstructionCorrect(vector<string> words, int indexOfWord, pair<string, int> verb, vector<string> nouns, vector<string> verbs);
	vector<vector<string> > devideIntoParts(vector<string> words);
	vector<vector<string>> correctAndBetweenObjects(vector<vector<string>> parts);
	bool correctSetEyes(vector<string> words, int index);
	bool correctSetFur(vector<string> words, int index);
	//bool isSaySmthCOrect();
	//void tellStory();
	//void doGif(string action);
};