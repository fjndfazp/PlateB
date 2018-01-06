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

char * filePath = "D:\\Data\\2整车\\5高速数据\\highway";           //要读取的文件夹的路径
string savePath = "D:\\Data\\2整车\\5高速数据\\1highway";						//要存储到的地方

void getJustCurrentFile(string path, int *random_array);

#define AllPic 28140					//文件总的大小
#define OutPic 10000			        //要提取出的文件的数量
int num = 0;						    //记录保存的图片个数
int index = 0;						    //记录遍历的文件数
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


//实现递归改变文件夹名称
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
					//当为了修改文件夹内包含的所有文件名字的时这个要打开
					getJustCurrentFile(pathname.assign(path).append("\\").append(fileinfo.name).c_str(), random_array);
				}
			}
			else
			{
				if (random_array[index] == 1)
				{
					//copyfile函数的前面一个参数是原文件的路径，后一个参数是目的路径,true表示如果目标存在则不拷贝，false表示存在则拷贝并覆盖
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


