#include <stdio.h>  
#include <iostream>  
#include <vector>  
#include <Windows.h>  
#include <fstream>    
#include <iterator>  
#include <string>  
#include <io.h>
#include <sstream> 
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

char * filePath = "D:\\Data\\2����\\5��������\\highway";           //Ҫ��ȡ���ļ��е�·��
string savePath = "D:\\Data\\2����\\5��������\\1highway";						//Ҫ�洢���ĵط�

void getJustCurrentFile(string path, int *random_array);

#define AllPic 28140					//�ļ��ܵĴ�С
#define OutPic 10000			        //Ҫ��ȡ�����ļ�������
int num = 0;						    //��¼�����ͼƬ����
int index = 0;						    //��¼�������ļ���
int main()
{
	vector<int> temp;
	int random_array[AllPic];
	memset(random_array, 0, sizeof(int)*AllPic);

	for (int i = 0; i < AllPic; ++i)
		temp.push_back(i + 1);
	
	random_shuffle(temp.begin(), temp.end());	

	for (int i = 0; i < OutPic; i++)
		random_array[temp[i]]++;
	//
	getJustCurrentFile(filePath, random_array);
	getchar();
}


//ʵ�ֵݹ�ı��ļ�������
void getJustCurrentFile(string path, int *random_array)
{
	long  hFile = 0;
	struct _finddata_t fileinfo;
	string pathname;
	if ((hFile = _findfirst(pathname.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					//��Ϊ���޸��ļ����ڰ����������ļ����ֵ�ʱ���Ҫ��
					getJustCurrentFile(pathname.assign(path).append("\\").append(fileinfo.name).c_str(), random_array);
				}
			}
			else
			{
				if (random_array[index] == 1)
				{
					//copyfile������ǰ��һ��������ԭ�ļ���·������һ��������Ŀ��·��,true��ʾ���Ŀ������򲻿�����false��ʾ�����򿽱�������
					index++;
					string savefile;
					savefile.assign(fileinfo.name);
					string temp;
					temp = savePath;
					if (savefile.back() == 'g' || savefile.back() == 'G')
					{
						num++;
						cout << num << endl;
						CopyFile(pathname.assign(path).append("\\").append(fileinfo.name).c_str(), savePath.append("\\").append(fileinfo.name).c_str(), TRUE);
						//MoveFile(pathname.assign(path).append("\\").append(fileinfo.name).c_str(), savePath.append("\\").append(fileinfo.name).c_str());
						if (num == OutPic)
							break;
						if (index == AllPic)
							break;
					}
					savePath = temp;
				}
				else
				{
					index++;
					if (index == AllPic)
						break;
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


