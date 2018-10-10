#include "Additional.h"

//读取文件
bool Additional::readF(const char* inputFileName, vector<string> &linesBuf)
{
	string filename = inputFileName;
	ifstream rf(filename);
	if (!rf) {
		return false;
	}
	else
	{
		string tempLine;
		char c;
		while (1)
		{
			c = rf.get();
			if (c >= '0' && c <= '9')
			{
				while (c != '\n')	//处理论文编号
				{
					c = rf.get();
				}
				int newLineCount = 0;	//换行符个数
				while (1)
				{
					c = rf.get();
					if (c == EOF)	//文件末尾
					{
						if (tempLine.size() > 0)
						{
							transform(tempLine.begin(), tempLine.end(), tempLine.begin(), ::tolower);
							linesBuf.push_back(tempLine);
							tempLine = "";
						}
						break;
					}
					tempLine += c;
					if (c == '\n')
					{
						transform(tempLine.begin(), tempLine.end(), tempLine.begin(), ::tolower);
						linesBuf.push_back(tempLine);
						tempLine = "";
						newLineCount++;
						if (newLineCount == 3)	//一篇论文结束
						{
							break;
						}
					}
				}
			}
			if (c == EOF)	//文件末尾
			{
				if (tempLine.size() > 0)
				{
					transform(tempLine.begin(), tempLine.end(), tempLine.begin(), ::tolower);
					linesBuf.push_back(tempLine);
				}
				break;
			}
		}
		rf.close();
		return true;
	}
}

//作者统计
void Additional::countAuthor(vector<string> &linesBuf)
{
	int wordCount = 0;
	int linesBufSize = int(linesBuf.size());
	string wordBuf;
	vector<string> authorCount;
	map<string,int> authorMap;
	for (int i = 0; i != linesBufSize; i++)
	{
		int lineLen = int(linesBuf[i].length());
		if (linesBuf[i][0] == 'a' && linesBuf[i][1] == 'u' && linesBuf[i][2] == 't' && linesBuf[i][3] == 'h'
			&& linesBuf[i][4] == 'o' && linesBuf[i][5] == 'r' && linesBuf[i][6] == 's' && linesBuf[i][7] == ':')
		{
			for (int j = 9; j < lineLen; j++)
			{
				if (linesBuf[i][j] != ',' && linesBuf[i][j] != '\n')
				{
					wordBuf += linesBuf[i][j];
				}
				else
				{
					authorCount.push_back(wordBuf);
					wordBuf = "";
				}
			}
			if (wordBuf.size() != 0)
			{
				authorCount.push_back(wordBuf);
				wordBuf = "";
			}
		}
		if (linesBuf[i][0] == 'a' && linesBuf[i][1] == 'b' && linesBuf[i][2] == 's' && linesBuf[i][3] == 't'
			&& linesBuf[i][4] == 'r' && linesBuf[i][5] == 'a' && linesBuf[i][6] == 'c' && linesBuf[i][7] == 't'
			&& linesBuf[i][8] == ':')
		{
			int authorCountSize = int(authorCount.size());
			for (int i = 0; i < authorCountSize; i++)
			{
				if (i < 5)
				{
					authorMap[authorCount[i]] += (5 - i);
				}
				else
				{
					authorMap[authorCount[i]]++;
				}
			}
			authorCount.clear();
		}
	}
	ofstream wf("AuthorRank.txt", ios::out);
	wf << "Name/InfluenceFactor" << endl;
	for (int i = 0; i < authorMap.size() && i < 10; i++)
	{
		auto max = authorMap.begin();
		for (auto it = authorMap.begin(); it != authorMap.end(); it++)
		{
			if (it->second > max->second)
			{
				max = it;
			}
		}
		wf << "No" << i << ":";
		wf << max->first << "/" << max->second << endl;
		max->second = -max->second;
	}
}