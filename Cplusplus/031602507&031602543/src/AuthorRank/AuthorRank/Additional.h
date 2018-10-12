#pragma once
#include<iostream>
#include<stdio.h>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
class Additional
{
public:
	bool readF(const char* inputFileName, vector<string> &linesBuf);
	void countAuthor(vector<string> &linesBuf);
};

