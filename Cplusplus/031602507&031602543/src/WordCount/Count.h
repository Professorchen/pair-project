#pragma once
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
class Count
{
public:
	int countCharNum(string &charBuf);
	int countLineNum(vector<string> &linesBuf);
	int countWordNum(vector<string> &linesBuf, int weightValue);
	int countPhraseNum(vector<string> &linesBuf, int weightValue, int phraseLen);
	int getpaperCount();
	vector<map<string, int>::iterator>  & countTopXWord(int topX);
	vector<map<string, int>::iterator>  & countTopXPhrase(int topX);
private:
	map<string, int> wordMap;
	map<string, int> phraseMap;
	vector<map<string, int>::iterator> topXWord;
	vector<map<string, int>::iterator> topXPhrase;
	int paperCount;
	inline bool isLetter(string::iterator it);
	inline bool isLetter(const char & ch);
	inline bool isDigit(string::iterator it);
	inline bool isDigit(const char & ch);
	inline bool isWord(const string & str);
};



