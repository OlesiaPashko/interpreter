#pragma once

#include<vector>
#include<string>
#include<iostream>

using namespace std;
class Error {
protected:
	string sentenseWithError;
public:
	virtual void printError();

};

class GrammaticalError : public Error {
private:
	string partOfSpeech;
public:
	virtual void printError();
	
	GrammaticalError(string sentenseWithError,string partOfSpeech) {
		this->sentenseWithError = sentenseWithError;
		this->partOfSpeech = partOfSpeech;
	}
};

class SyntaxError : public Error {
private:
	char incorrectChar;

public:
	virtual void printError();

	SyntaxError(string sentenseWithError, char incorrectChar) {
		this->sentenseWithError = sentenseWithError;
		this->incorrectChar = incorrectChar;
	}
};

class LexicographicError : public Error {
private:
	string incorrectWord;
public:
	virtual void printError();

	LexicographicError(string sentenseWithError, string incorrectWord) {
		this->sentenseWithError = sentenseWithError;
		this->incorrectWord = incorrectWord;

	}

};

