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

#define MAX_PATH 1024  //�·������  
char * filePath = "D:\\�½��ļ���"; //Ҫ��ȡ���ļ��е�·��
string newname = "a"; //Ҫ��ӵ��ļ������ƺ��������

//ʵ�ֵݹ�ı��ļ�������
void getJustCurrentFile(string path, vector<string>& files)
{
	//�ļ���� 
	long  hFile = 0;
	//�ļ���Ϣ 
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
					//��Ϊ���޸��ļ�������ʱ�����ⲿ��
					stringstream ss;
					ss << newname;
					string new_name = p.assign(path).append("\\") + fileinfo.name + string(ss.str());
					rename(p.assign(path).append("\\").append(fileinfo.name).c_str(), new_name.c_str());
					cout << fileinfo.name << endl;
					//getJustCurrentFile(new_name.c_str(), files);//�ٴε��øó�����Ϊ�˶�ȡ���ļ��У���ͬʱ�޸��ļ��а��������ļ�����ʱ�򿪣�

					//��Ϊ���޸��ļ����ڰ����������ļ����ֵ�ʱ���Ҫ��
					//getJustCurrentFile(p.assign(path).append("\\").append(fileinfo.name).c_str(), files);
				}
			}
			else
			{
				//�����޸������ļ����ڰ������ļ���������
				stringstream ss;
				ss << newname;
				string new_name = p.assign(path).append("\\") + fileinfo.name + string(ss.str());
				string temp = fileinfo.name;
				if(!strcmp(temp.c_str(),"123.bmp"))
					rename(p.assign(path).append("\\").append(fileinfo.name).c_str(), new_name.c_str());

				files.push_back(fileinfo.name);//����ļ���洢�޸ĺ��������֣��ò��ϣ�
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name) ); 
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


int main()
{
	vector<string> files;
	char * distAll = "AllFiles.txt";//����ļ���洢�޸ĺ��������֣��ò��ϣ�
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

