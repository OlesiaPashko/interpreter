#include"Error.h"


void Error::printError() {
	std::cout << "Error!"<<std::endl;
}

void GrammaticalError::printError() {
	if (partOfSpeech == "") {
		std::cout << "Grammatical error in sentense : "<<"\""<< sentenseWithError <<"\" !" << std::endl;
	}
	else {
		std::cout << "Grammmatical error in part : " << "\"" << partOfSpeech << "\"" <<
			" of sentense "<<"\"" << sentenseWithError << "\" !" <<std::endl;
	}
}

void SyntaxError::printError() {
	std::cout<< "Incorrect data! Error with char : " << "\""<< incorrectChar<<"\"" <<" in sentense "<<"\""<<
		sentenseWithError << "\" !" << std::endl;
}

void LexicographicError::printError() {
	std::cout<< "Incorrect data! Error with word : " << "\"" << incorrectWord<< "\"" << " in sentense " << "\"" <<
		sentenseWithError << "\" !" << std::endl;
}

