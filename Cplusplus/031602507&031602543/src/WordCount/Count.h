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
	int countWordNum(vector<string> &linesBuf, int weightValue);
	int countLineNum(vector<string> &linesBuf);
	vector<map<string,int>::iterator>  & countTopXWord(int topX);
private:
	map<string, int> wordMap;
	vector<map<string, int>::iterator> topXWord;
	int paperCount;
	inline bool isLetter(string::iterator it);
	inline bool isLetter(const char & ch);
	inline bool isDigit(string::iterator it);
	inline bool isDigit(const char & ch);
};



