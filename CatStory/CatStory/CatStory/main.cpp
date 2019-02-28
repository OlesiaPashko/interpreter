#include "Interface.h"
#include "Error.h"
#include <vector>
#include <iostream>
#include <ctime>
using namespace std;
int main() {
	time_t start, end;
	time(&start);
	Interface* a = new Interface();
	/*vector<string> m = a->makeSentences();
	for (int i = 0; i < m.size(); i++)
		cout << m[i] << endl;
	string s1 = m[1];
	vector<string> k = a->wordsInSentence(s1);
	for (int i = 0; i < k.size(); i++)
		cout << k[i] << "-  -";
	/*SelfBehaviour a;
	a.runPreviousEmotion("hello");*/
	try {
		vector<string>text = a->makeSentences();
		vector<string> words = a->wordsInSentence(text[0]);
		cout << a->isOneSentenceCorrect(words);
		time(&end);
		cout << "\n";
		cout << end - start;
	}
	catch (Error &e) {
		e.printError();
	}
	//cout <<(s1==s2) ;
	system("pause");
	return 0;
}