/********************************************************************************
* @File name: AuthorRank.cpp
* @Author: ChenYuXin
* @Version: 1.0
* @Date: 2018-10-12
* @Description: additonal function
********************************************************************************/


#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<regex>
#include<map>
#include<algorithm>
#include"Additional.h"
using namespace std;



int main(int argc, char *argv[])
{
	vector<string> linesBuf;
	Additional additional;
	additional.readF("input(2).txt", linesBuf);
	additional.countAuthor(linesBuf);

	system("pause");
	return 0;
}