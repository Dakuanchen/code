#define _CRT_SECURE_NO_WARNINGS 1

#include <set>
#include <iostream>
using namespace std;

int main()
{
	int a[10] = { 35, 65, 9, 64, 5, 8, 3, 4, 256, 5 };

	set<int> t(a, a + 10);
	set<int>::iterator it = t.begin();


	cout << t.size() << endl;
	t.insert(35);
	cout << t.size() << endl;
	t.insert(16);
	while (it != t.end())
	{
		cout << *it << ' ';
		++it;
	}
	return 0;
}


// 
// /*#include "stdafx.h"*/
// #include <stdio.h>
// #include<iostream>
// #include<vector>
// #include <assert.h>
// #include <Windows.h>
// #include <fstream>  
// #include <iterator>
// #include <string>
// using namespace std;

 //最长路径长度

/*----------------------------
* 功能 : 递归遍历文件夹，找到其中包含的所有文件
*----------------------------
* 函数 : find
* 访问 : public
*
* 参数 : lpPath [in]      需遍历的文件夹目录
* 参数 : fileList [in]    以文件名称的形式存储遍历后的文件
*/
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
// 	//遍历一次结果的所有文件,获取文件名列表
// 	find("D:\\新建文件夹\\新建文件夹", fileList);//之后可对文件列表中的文件进行相应的操作
// 
// 	//输出文件夹下所有文件的名称
// 	for (size_t i = 0; i < fileList.size(); i++)
// 	{
// 		cout << fileList[i] << endl;
// 	}
// 	cout << "文件数目：" << fileList.size() << endl;
// 	return 0;
// }












// #include <stdio.h>
// 
// 
// int main()
// {
// 	FILE* fp = fopen("D:\新建文件夹\新建文件夹\J2EE3ver1.doc", "r");
// 	if (NULL == fp)
// 	{
// 		return 0;
// 	}
// 
// 	return 0;
// }



//  
//  #include <windows.h>
//  #include <stdio.h>
//  #include <string.h>
//  #define LEN 1024
//  // 深度优先递归遍历目录中所有的文件
// BOOL  DirectoryList(LPCSTR Path, vector<string>& OutPathName)
//  {
//  	WIN32_FIND_DATA FindData;
//  	HANDLE hError;
//  	int FileCount = 0;
//  	char FilePathName[LEN];
//  	// 构造路径
//  	char FullPathName[LEN];
//  	strcpy(FilePathName, Path);
//  	strcat(FilePathName, "\\*.*");
//  	hError = ::FindFirstFile(FilePathName, &FindData);
//  	if (hError == INVALID_HANDLE_VALUE)
//  	{
//  		printf("搜索失败!");
//  		return 0;
//  	}
//  	while (::FindNextFile(hError, &FindData))
//  	{
//  		// 过虑.和..
//  		if (strcmp(FindData.cFileName, ".") == 0
//  			|| strcmp(FindData.cFileName, "..") == 0)
//  		{
//  			continue;
//  		}
//  
//  		// 构造完整路径
//  		wsprintf(FullPathName, "%s\\%s", Path, FindData.cFileName);
//  		FileCount++;
//  		// 输出本级的文件
//  		//printf("\n%d  %s  ", FileCount, FullPathName);
// 		OutPathName.push_back(FullPathName);
//  		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
//  		{
//  			//printf("<Dir>");
//  			DirectoryList(FullPathName,OutPathName);
//  		}
//  	}
//  	return 0;
//  }
//  void main()
//  {
// 
// 	 FILE* fp1 = fopen("Lesson09--04--搜索结构之AVL树.pdf", "rb");
// 	 assert(fp1);
// 
// 	 FILE* fp2 = fopen("Lesson09--04--搜索结构之AVL树.docx", "wb");
// 	 assert(fp2);
// 
// 
// 	 char arr[1024];
// 	 size_t count = fread(arr, 1, 1024, fp1);
// 	 while (count)
// 	 {
// 		 fwrite(arr, 1, count, fp2);
// 		 count = fread(arr, 1, 1024, fp1);
// 	 }


// 	 vector<string> FullPathName;
// 	 DirectoryList("D:\\1", FullPathName);
// 
// 	 for (size_t i = 0; i < FullPathName.size(); ++i)
// 	 {
// 		 //cout << FullPathName[i] << endl;
// 		 size_t pos = FullPathName[i].find_last_of('.');
// 		 bool isFile = true;
// 		 if (pos == -1)
// 			 isFile = false;
// 		 else
// 		 {
// 			 for (size_t j = pos; j < FullPathName[i].size(); ++j)
// 			 {
// 				 if (FullPathName[i][j] == '\\')
// 				 {
// 					 isFile = false;
// 					 break;
// 				 }
// 			 }
// 
// 		 }
// 
// 		 if (isFile)
// 		 {
// 			 cout << FullPathName[i] << endl;
// 		 }
// 	 }
//}

//  #include <windows.h>
//  #include <stdio.h>
//  #include <string.h>
// #include <vector>
// #include <string>
// 
// 
//  typedef std::vector<std::string> ArString;
// 
//  typedef void(*packproess)(const std::string&, DWORD, DWORD, DWORD, DWORD);
// 
//  struct pakFileInfo
//  {
// 	 DWORD m_dwLastWriteTime;        // 最后更改时间
// 	 std::string m_strName;            // 文件名字
// 	 std::string m_strPackFile;        // 文件所在包
// 	 DWORD dwFileOffset;
// 	 DWORD dwFileSize;
// 
// 	 pakFileInfo()
// 		 : m_dwLastWriteTime(0)
// 	 {
// 
// 	 }
// 
// 	 void operator = (const pakFileInfo& v)
// 	 {
// 		 m_dwLastWriteTime = v.m_dwLastWriteTime;
// 		 m_strName = v.m_strName;
// 		 m_strPackFile = v.m_strPackFile;
// 		 dwFileOffset = v.dwFileOffset;
// 		 dwFileSize = v.dwFileSize;
// 	 }
//  };
// 
//  // 文件包的头信息
// #pragma once
// 
// #define CFP_VERSION 11
// #define CFP_EXTNAME ".cfp"
// #define CID_EXTNAME ".ind"
// #define CFP_FLAG "CFPK"
// 
// #pragma pack(push)
// #pragma pack(1)
//  struct CFPHeadItem
//  {
// 	 BOOL    bUsed;
// 	 DWORD    dwStartOffset;
// 	 DWORD    dwEndOffset;
// 	 DWORD    dwDatSize;
// 	 DWORD    dwDeCompSize;
// 	 DWORD    dwLastTime;
// 	 char    strName[256];
//  };
// 
//  struct CFPHead
//  {
// 	 DWORD    dwFlag;
// 	 DWORD    dwFileCount;
// 	 DWORD    dwCompPlugin;
// 	 DWORD    dwPatchTarget;
// 	 DWORD    dwPatchVersion;
// 	 BYTE    byVer;
// 	 BYTE    bComp;
// 	 WORD    wRecv;
//  };
// #pragma pack(pop)
// 
//  bool CCommonFilePack::EnumAllFile(std::string strDir, ArString& arFile, pakFileInfo** pInfo)
//  {
// 	 std::vector<FindItem> hFindStk;
// 	 std::vector<pakFileInfo> arFileInfo;
// 
// 	 if (strDir.at(strDir.size() - 1) == '\\')
// 		 strDir.erase(strDir.size() - 1, 1);
// 
// 	 strlwr((char*)strDir.c_str());
// 
//  begin_find:
// 
// 	 WIN32_FIND_DATA wfd;
// 	 HANDLE hFind = FindFirstFile((strDir + "\\*.*").c_str(), &wfd);
// 	 if (hFind != INVALID_HANDLE_VALUE)
// 	 {
// 		 do
// 		 {
// 			 if (wfd.cFileName[0] == '.')
// 				 continue;
// 
// 			 if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
// 			 {
// 				 hFindStk.push_back(FindItem(hFind, strDir));
// 				 strDir = strDir + "\\" + wfd.cFileName;
// 				 goto begin_find;
// 			 }
// 
// 			{
// 				std::string lstr = strDir + "\\" + wfd.cFileName;
// 				strlwr((char*)lstr.c_str());
// 
// 				if (pInfo)
// 				{
// 					pakFileInfo Info;
// 					Info.m_dwLastWriteTime = ECore::convert_FILETIME_to_DWORD(&(wfd.ftLastWriteTime));
// 
// 					Info.m_strName = lstr;
// 
// 					arFileInfo.push_back(Info);
// 				}
// 
// 				arFile.push_back(lstr);
// 			}
// 
// 
// 		continue_list:;
// 		 } while (FindNextFile(hFind, &wfd));
// 
// 		 FindClose(hFind);
// 	 }
// 	 else
// 	 {
// 		 for (int i = 0; i < hFindStk.size(); ++i)
// 		 {
// 			 FindClose(hFindStk[i].hFindFile);
// 		 }
// 		 return false;
// 	 }
// 
// 	 if (!hFindStk.empty())
// 	 {
// 		 FindItem& item = hFindStk[hFindStk.size() - 1];
// 		 strDir = item.strDir;
// 		 hFind = item.hFindFile;
// 		 hFindStk.pop_back();
// 		 goto continue_list;
// 	 }
// 
// 	 if (pInfo)
// 	 {
// 		 *pInfo = new pakFileInfo[arFileInfo.size()];
// 		 for (int i = 0; i < arFileInfo.size(); ++i)
// 		 {
// 			 (*pInfo)[i] = arFileInfo[i];
// 		 }
// 	 }
// 
// 	 return true;
//  }
// 
//  bool CCommonFilePack::PackDirection(const std::string& strDir, const std::string& strDestPath, packproess func)
//  {
// 	 ArString arFile;
// 	 pakFileInfo* pinfo = NULL;
// 	 if (EnumAllFile(strDir, arFile, &pinfo))
// 	 {
// 		 long n = 0;
// 		 for (int i = 0; i < arFile.size(); ++i)
// 		 {
// 			 n += pinfo[i].dwFileSize;
// 		 }
// 		 SAFE_DELETE_ARY(pinfo);
// 
// 		 if (func)
// 			 func("", 0, n, 0, arFile.size());
// 		 return PackFileList(arFile, strDestPath, strDir, func);
// 	 }
// 	 return false;
//  }
// 
//  bool CCommonFilePack::PackFileList(ArString& arList, const std::string& strDestPath,
// 	 std::string strSubDir, packproess func, DWORD dwVersion, DWORD dwPatchTarget)
//  {
// 	 int filecount = arList.size();
// 	 if (filecount <= 0)
// 		 return false;
// 
// 	 // 打包前排个序，按顺序打包
// 	 std::sort(arList.begin(), arList.end());
// 
// 	 std::vector<CFPHeadItem> arItem;
// 	 DWORD dwItemStrLen = 0;
// 
// 	 // 转换列表中的文件名为相对于某个目录的相对路径
// 	 if (strSubDir.at(strSubDir.size() - 1) != '\\')
// 		 strSubDir += '\\';
// 
// 	 int slen = strSubDir.size();
// 	 for (int i = 0; i < arList.size(); ++i)
// 	 {
// 		 std::string sbuf = arList[i];
// 		 if (slen)
// 		 {
// 			 sbuf.erase(0, slen);
// 		 }
// 
// 		 // 准备文件信息表
// 		 CFPHeadItem item;
// 		 strcpy(item.strName, sbuf.c_str());
// 		 item.bUsed = TRUE;
// 
// 		 arItem.push_back(item);
// 	 }
// 
// 	 // 准备文件头
// 	 CFPHead FileHead;
// 	 memset(&FileHead, 0, sizeof(FileHead));
// 	 FileHead.dwFlag = *(DWORD*)"CFPK";
// 	 FileHead.byVer = CFP_VERSION;
// 	 FileHead.dwFileCount = filecount;
// 	 FileHead.bComp = (m_pCompressFunc != 0);
// 	 FileHead.dwCompPlugin = ECore::ELFHash((char*)m_strCompName.c_str());
// 	 FileHead.dwPatchVersion = dwVersion;
// 	 FileHead.dwPatchTarget = dwPatchTarget;
// 
// 	 FILE* fSave = fopen(strDestPath.c_str(), "wb");
// 	 if (!fSave)
// 		 return false;
// 
// 	 long lOffset = 0;
// 
// 	 BYTE *cbuf = NULL, *rbuf = NULL;
// 	 int maxbufsz = 0;
// 
// 	 for (int i = 0; i < filecount; ++i)
// 	 {
// 		 std::string& strFile = arList[i];
// 		 FILE* fp = fopen(strFile.c_str(), "rb");
// 		 if (fp)
// 		 {
// 			 fseek(fp, 0, SEEK_END);
// 			 int size = ftell(fp);
// 			 fseek(fp, 0, SEEK_SET);
// 
// 			 if (maxbufsz < size)
// 			 {
// 				 maxbufsz = size;
// 				 SAFE_DELETE(rbuf);
// 				 rbuf = new BYTE[size + 1];
// 
// 				 if (m_pCompressFunc)
// 				 {
// 					 SAFE_DELETE(cbuf);
// 					 cbuf = new BYTE[size + 1];
// 				 }
// 			 }
// 
// 			 long n = fread(rbuf, 1, size, fp);
// 
// 			 size_t lR = n;
// 			 if (m_pCompressFunc)
// 			 {
// 				 m_pCompressFunc((void*)rbuf, n, (void*)cbuf, size, lR);
// 				 fwrite(cbuf, 1, lR, fSave);
// 			 }
// 			 else
// 			 {
// 				 fwrite(rbuf, 1, n, fSave);
// 			 }
// 
// 			 arItem[i].dwStartOffset = lOffset;
// 			 arItem[i].dwEndOffset = lOffset + lR;
// 			 arItem[i].dwDatSize = lR;
// 			 arItem[i].dwDeCompSize = n;
// 
// 			 lOffset += lR;
// 
// 			 fclose(fp);
// 
// 			 if (func)
// 				 func(strFile, lOffset, 0, i, filecount);
// 
// 			 arItem[i].dwLastTime = ECore::GetFileTimeVersion(strFile);
// 		 }
// 
// 	 }
// 
// 	 fclose(fSave);
// 
// 	 SAFE_DELETE(rbuf);
// 	 SAFE_DELETE(cbuf);
// 
// 	 std::string stridx = strDestPath;
// 	 ECore::StringReplace(stridx, CFP_EXTNAME, CID_EXTNAME);
// 	 FILE* fidx = fopen(stridx.c_str(), "wb");
// 	 if (!fidx)
// 		 return false;
// 
// 	 fwrite(&FileHead, 1, sizeof(FileHead), fidx);
// 
// 	 // 在文件中更新文件信息表的完整信息
// 	 for (int i = 0; i < filecount; ++i)
// 	 {
// 		 CFPHeadItem& item = arItem[i];
// 		 fwrite(&item, 1, sizeof(CFPHeadItem), fidx);
// 	 }
// 
// 	 fclose(fidx);
// 	 return true;
//  }
// 
//  bool CCommonFilePack::unPack(const std::string& strCFPFile, const std::string& strDestPath)
//  {
// 	 FILE *fpidx = NULL, *fpdat = NULL;
// 	 PluginInfo* pCommpPlug = NULL;
// 	 CFPHead FileHead;
// 
// 	 if (GetFilePoint(strCFPFile, &fpidx, &fpdat, &FileHead, &pCommpPlug))
// 	 {
// 
// 		 BYTE *cbuf = NULL, *rbuf = NULL;
// 		 int maxbufsz = 0, maxcsz = 0;
// 
// 		 for (int i = 0; i < FileHead.dwFileCount; ++i)
// 		 {
// 			 CFPHeadItem item;
// 			 fread(&item, 1, sizeof(CFPHeadItem), fpidx);
// 
// 			 fseek(fpdat, item.dwStartOffset, SEEK_SET);
// 			 size_t size = item.dwEndOffset - item.dwStartOffset;
// 
// 			 if (maxbufsz < size)
// 			 {
// 				 maxbufsz = size;
// 				 SAFE_DELETE(rbuf);
// 				 rbuf = new BYTE[size + 1];
// 			 }
// 
// 			 fread(rbuf, 1, size, fpdat);
// 
// 			 if (FileHead.bComp)
// 			 {
// 				 if (maxcsz < item.dwDeCompSize)
// 				 {
// 					 maxcsz = item.dwDeCompSize;
// 					 SAFE_DELETE(cbuf);
// 					 cbuf = new BYTE[maxcsz];
// 				 }
// 
// 				 size_t realsize = 0;
// 				 if (pCommpPlug->unCompressFunc(rbuf, size, cbuf, maxcsz, realsize))
// 					 ECore::ForceWriteFile(strDestPath + "\\" + item.strName, cbuf, realsize);
// 			 }
// 			 else
// 			 {
// 				 ECore::ForceWriteFile(strDestPath + "\\" + item.strName, rbuf, size);
// 			 }
// 
// 		 }
// 
// 		 SAFE_DELETE(rbuf);
// 		 SAFE_DELETE(cbuf);
// 
// 		 fclose(fpdat);
// 		 fclose(fpidx);
// 		 return true;
// 	 }
// 
// 	 m_strError = ECore::va("无法打开文件(%s)！", strCFPFile.c_str());
// 	 return false;
//  }

