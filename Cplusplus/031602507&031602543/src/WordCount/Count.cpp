#include "Count.h"

//计算字符数
int Count::countCharNum(string &charBuf)
{
	return int(charBuf.size());
}
//计算行数
int Count::countLineNum(vector<string> &linesBuf)
{
	int lineCount = 0;
	for (int i = 0; i != linesBuf.size(); i++) 
	{
		for (string::iterator it = linesBuf[i].begin(); it != linesBuf[i].end(); it++) 
		{
			if (*it > 32) 
			{
				lineCount++;
				break;
			}
		}
	}
	return lineCount;
}
//计算单词数
int Count::countWordNum(vector<string> &linesBuf,int weightValue)
{
	int wordCount = 0;
	int linesBufSize = int(linesBuf.size());
	string wordBuf;
	int isTitle = 0;
	for (int i = 0; i != linesBufSize; i++) 
	{
		int len = int(linesBuf[i].length());
		for(int j = 0;j < len;j++)
		{
			if (isLetter(linesBuf[i][j]) || isDigit(linesBuf[i][j])) 
			{
				wordBuf += linesBuf[i][j];
			}
			else 
			{
				if (wordBuf == "title" && linesBuf[i][j] == ':')
				{
					isTitle = 1;
					wordBuf = "";
					continue;
				}
				if (wordBuf == "abstract" && linesBuf[i][j] == ':')
				{
					isTitle = 0;
					wordBuf = "";
					continue;
				}
				if (wordBuf.length() >= 4 && isLetter(wordBuf[0]) && isLetter(wordBuf[1]) && isLetter(wordBuf[2]) && isLetter(wordBuf[3])) 
				{
					if (weightValue == 0)
					{
						wordMap[wordBuf]++;
						wordCount++;
					}
					else
					{
						if (isTitle == 1)
						{
							wordMap[wordBuf] += 10;
							wordCount++;
						}
						else
						{
							wordMap[wordBuf]++;
							wordCount++;
						}
					}
				}
				wordBuf = "";
			}
		}
		if (wordBuf.length() >= 4 && isLetter(wordBuf[0]) && isLetter(wordBuf[1]) && isLetter(wordBuf[2]) && isLetter(wordBuf[3]))
		{
			if (weightValue == 0)
			{
				wordMap[wordBuf]++;
				wordCount++;
			}
			else
			{
				if (isTitle == 1)
				{
					wordMap[wordBuf] += 10;
					wordCount++;
				}
				else
				{
					wordMap[wordBuf]++;
					wordCount++;
				}
			}
		}
		wordBuf = "";

	}
	return wordCount;
}
//统计出现频率最高的X个单词
vector<map<string,int>::iterator> & Count::countTopXWord(int topX)
{
	int wordMapSize = int(wordMap.size());
	for (int i = 0; i < wordMapSize && i < topX; i++)
	{
		auto maxFreWord = wordMap.begin();
		for (map<string,int>::iterator it = wordMap.begin(); it != wordMap.end(); it++)
		{
			if (it->second > maxFreWord->second)
			{
				maxFreWord = it;
			}
		}
		topXWord.push_back(maxFreWord);
		maxFreWord->second = -maxFreWord->second;
	}
	return topXWord;
}

//判断是否为字母
inline bool Count::isLetter(string::iterator it) {
	return (*it >= 97 && *it <= 122) ;
}
//判断是否为字母(重载)
inline bool Count::isLetter(const char & ch) {
	return (ch >= 97 && ch <= 122);
}
//判断是否为数字
inline bool Count::isDigit(string::iterator it) {
	return *it >= '0' && *it <= '9';
}
//判断是否为数字(重载)
inline bool Count::isDigit(const char  & ch) {
	return ch >= '0' && ch <= '9';
}