#include "FileCompressed.hpp"
#include <stdio.h>
#include<iostream>
#include<vector>
#include <Windows.h>
#include <fstream>  
#include <iterator>
#include <string>
using namespace std;

// 
// void find(char* lpPath, std::vector<const std::string> &fileList)
// {
// 	char szFind[MAX_PATH];
// 	WIN32_FIND_DATA FindFileData;
// 
// 	strcpy(szFind, lpPath);
// 	strcat(szFind, "\\*.*");
// 
// 	HANDLE hFind = ::FindFirstFile(szFind, &FindFileData);
// 	if (INVALID_HANDLE_VALUE == hFind)    return;
// 
// 	while (true)
// 	{
// 		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
// 		{
// 			if (FindFileData.cFileName[0] != '.')
// 			{
// 				char szFile[MAX_PATH];
// 				strcpy(szFile, lpPath);
// 				strcat(szFile, "\\");
// 				strcat(szFile, (char*)(FindFileData.cFileName));
// 				find(szFile, fileList);
// 			}
// 		}
// 		else
// 		{
// 			//std::cout << FindFileData.cFileName << std::endl;
// 			fileList.push_back(FindFileData.cFileName);
// 		}
// 		if (!FindNextFile(hFind, &FindFileData))    break;
// 	}
// 	FindClose(hFind);
// }
// 
// 
// int main()
// {
// 	std::vector<const std::string> fileList;//定义一个存放结果文件名称的链表
// 
// 	string PathName;
// 
// 	cin >> PathName;
// 	char lPath[MAX_PATH] = { 0 };
// 	for (size_t i = 0; i < PathName.length(); i++)
// 		lPath[i] = PathName[i];
// 	
// 	PathName += '\\';
// 	//遍历一次结果的所有文件,获取文件名列表
// 
// 	find(lPath, fileList);//之后可对文件列表中的文件进行相应的操作
// 
// 	//输出文件夹下所有文件的名称
// 
// 	string ComPath;
// 	cin >> ComPath;
// 
// 	bool iscom = true;
// 
// 	cin >> iscom;
// 
// 	if (iscom)
// 	{
// 		for (size_t i = 0; i < fileList.size(); i++)
// 		{
// 			cout << fileList[i] << endl;
// 			CompressedFile com;
// 			com.Compressed(PathName + fileList[i], ComPath);
// 		}
// 	}
// 	else
// 	{
// 		for (size_t i = 0; i < fileList.size(); i++)
// 		{
// 			cout << fileList[i] << endl;
// 			CompressedFile com;
// 			com.UnCompressed(PathName + fileList[i], ComPath);
// 		}
// 	}
// 	
// 	cout << "文件数目：" << fileList.size() << endl;
// 	return 0;
// }


#define LEN 1024
// 深度优先递归遍历目录中所有的文件
BOOL  DirectoryList(LPCSTR Path, vector<string>& OutPathName)
{
	WIN32_FIND_DATA FindData;
	HANDLE hError;
	int FileCount = 0;
	char FilePathName[LEN];
	// 构造路径
	char FullPathName[LEN];
	strcpy(FilePathName, Path);
	strcat(FilePathName, "\\*.*");
	hError = ::FindFirstFile(FilePathName, &FindData);
	if (hError == INVALID_HANDLE_VALUE)
	{
		printf("搜索失败!");
		return 0;
	}
	while (::FindNextFile(hError, &FindData))
	{
		// 过虑.和..
		if (strcmp(FindData.cFileName, ".") == 0
			|| strcmp(FindData.cFileName, "..") == 0)
		{
			continue;
		}

		// 构造完整路径
		wsprintf(FullPathName, "%s\\%s", Path, FindData.cFileName);
		FileCount++;
		// 输出本级的文件
		//printf("\n%d  %s  ", FileCount, FullPathName);
		OutPathName.push_back(FullPathName);
		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//printf("<Dir>");
			DirectoryList(FullPathName, OutPathName);
		}
	}
	return 0;
}
void main()
{
	vector<string> FullPathName;

	string DesPath;
	string TarPath;
	cin >> DesPath;
	cin >> TarPath;

	TarPath += "\\";
	bool isCom;
	cin >> isCom;

	DirectoryList(DesPath.c_str(), FullPathName);

	for (size_t i = 0; i < FullPathName.size(); ++i)
	{
		//cout << FullPathName[i] << endl;
		size_t pos = FullPathName[i].find_last_of('.');
		bool isFile = true;
		if (pos == -1)
			isFile = false;
		else
		{
			for (size_t j = pos; j < FullPathName[i].size(); ++j)
			{
				if (FullPathName[i][j] == '\\')
				{
					isFile = false;
					break;
				}
			}

		}

		if (isFile)
		{
			cout << FullPathName[i] << endl;
			if (isCom)
			{
				CompressedFile com;
				com.Compressed(FullPathName[i], TarPath);
			}
			else
			{
				CompressedFile com;
				com.UnCompressed(FullPathName[i],TarPath);
			}
		}
	}
}