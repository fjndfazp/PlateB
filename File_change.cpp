#include <stdio.h>  
#include<iostream>  
#include<vector>  
#include <Windows.h>  
#include <fstream>    
#include <iterator>  
#include <string>  
#include <io.h>
#include <sstream> 

using namespace std;

#define MAX_PATH 1024  //最长路径长度  
char * filePath = "D:\\新建文件夹"; //要读取的文件夹的路径
string newname = "a"; //要添加到文件夹名称后面的内容

//实现递归改变文件夹名称
void getJustCurrentFile(string path, vector<string>& files)
{
	//文件句柄 
	long  hFile = 0;
	//文件信息 
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					//当为了修改文件夹名字时启用这部分
					stringstream ss;
					ss << newname;
					string new_name = p.assign(path).append("\\") + fileinfo.name + string(ss.str());
					rename(p.assign(path).append("\\").append(fileinfo.name).c_str(), new_name.c_str());
					cout << fileinfo.name << endl;
					//getJustCurrentFile(new_name.c_str(), files);//再次调用该程序是为了读取子文件夹（当同时修改文件夹包含的子文件夹名时打开）

					//当为了修改文件夹内包含的所有文件名字的时这个要打开
					//getJustCurrentFile(p.assign(path).append("\\").append(fileinfo.name).c_str(), files);
				}
			}
			else
			{
				//用来修改所有文件夹内包含的文件名的名字
				stringstream ss;
				ss << newname;
				string new_name = p.assign(path).append("\\") + fileinfo.name + string(ss.str());
				string temp = fileinfo.name;
				if(!strcmp(temp.c_str(),"123.bmp"))
					rename(p.assign(path).append("\\").append(fileinfo.name).c_str(), new_name.c_str());

				files.push_back(fileinfo.name);//这个文件会存储修改后结果的名字（用不上）
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name) ); 
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


int main()
{
	vector<string> files;
	char * distAll = "AllFiles.txt";//这个文件会存储修改后结果的名字（用不上）
	getJustCurrentFile(filePath, files);
	ofstream ofn(distAll);
	int size = files.size();
	ofn << size << endl;
	for (int i = 0; i<size; i++)
	{
		ofn << files[i] << endl;
	}
	ofn.close();
	getchar();
}

