/********************************************************************************
* @File name: WordCount.cpp
* @Author: ChenYuXin
* @Version: 5.8
* @Date: 2018-10-06
* @Description: code optimization 
********************************************************************************/


#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<regex>
#include<map>
#include<algorithm>
#include"Count.h"	//封装所有的统计相关的功能
#include"FileIO.h"	//封装所有文件读写相关的功能
#include"Additional.h"
using namespace std;



int main(int argc, char *argv[]) 
{
	for (int j = 0; j < 1; j++)
	{
		int lineCount = 0;			//行数
		int characterCount = 0;		//字符数
		int wordCount = 0;			//单词数
		int paperCount = 0;			//论文数
		int invaildChar = 0;		//无效字符数
		const char* inputFileName = "input(2).txt";  //输入文件名
		const char* outputFileName = "output.txt"; //输出文件名
		int weightValue = 0;		//权重
		int phraseLen = -1;         //单词个数
		int topX = 10;				//频率最高的单词(词组),默认为10
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-i") == 0)
			{
				inputFileName = argv[i + 1];
			}
			else if (strcmp(argv[i], "-o") == 0)
			{
				outputFileName = argv[i + 1];
			}
			else if (strcmp(argv[i], "-w") == 0)
			{
				weightValue = atoi(argv[i + 1]);
			}
			else if (strcmp(argv[i], "-m") == 0)
			{
				phraseLen = atoi(argv[i + 1]);
			}
			else if (strcmp(argv[i], "-n") == 0)
			{
				topX = atoi(argv[i + 1]);
			}
		}
		Count count;
		string charBuf;
		vector<string> linesBuf;
		Additional additional;
		additional.readF(inputFileName, linesBuf);
		additional.countAuthor(linesBuf);
		cout << 1;
		if(FileIO::readFile(inputFileName,charBuf,linesBuf))			
		{	
			characterCount = count.countCharNum(charBuf);			//计算字符数
			lineCount = count.countLineNum(linesBuf);				//计算行数
			if (phraseLen == -1)
			{
				wordCount = count.countWordNum(linesBuf, weightValue);	//计算单词数
				paperCount = count.getpaperCount();						//获取论文数
				invaildChar = (paperCount * 17);						//计算无效字符数
				vector<map<string, int>::iterator> topXWord = count.countTopXWord(topX);	//统计出现频率最高的10个单词（有可能单词数没有10个）
				if (!FileIO::outputToFile(characterCount - invaildChar, wordCount, lineCount, outputFileName, topXWord))	//将结果输出到文件
				{
					cout << "output to file fail";
				}
			}
			else
			{
				wordCount = count.countPhraseNum(linesBuf, weightValue,phraseLen);	//计算词组数
				paperCount = count.getpaperCount();									//获取论文数
				invaildChar = (paperCount * 17);									//计算无效字符数
				vector<map<string, int>::iterator> topXPhrase = count.countTopXPhrase(topX);	//统计出现频率最高的10个词组（有可能单词数没有10个）
				if (!FileIO::outputToFile(characterCount - invaildChar, wordCount, lineCount, outputFileName, topXPhrase))	//将结果输出到文件
				{
					cout << "output to file fail";
				}
			}
		}
		else
		{
			cout << "read file fail";
		}
	}

	system("pause");
	return 0;
}