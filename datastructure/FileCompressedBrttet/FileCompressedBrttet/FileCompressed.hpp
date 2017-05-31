#pragma once
#include "HuffmanTree.hpp"
#include <algorithm>
#include <assert.h>


struct FileInfo
{
	FileInfo(unsigned char ch = char())
		:_ch(ch)
		, _count(0)
	{}

	FileInfo& operator=(const FileInfo& x)
	{
		this->coding = x.coding;
		this->_ch = x._ch;
		this->_count = x._count;
		return *this;
	}

	bool operator==(const FileInfo& x)const
	{
		return !(*this != x);
	}

	bool operator!=(const FileInfo& x)const
	{
		return this->_count != x._count;
	}

	unsigned char _ch;
	long long _count;
	string coding;
};

FileInfo operator+(const FileInfo& left, const FileInfo& right)
{
	FileInfo ret;
	ret._count = left._count + right._count;
	return ret;
}

bool operator<(const FileInfo& left, const FileInfo& right)
{
	return left._count < right._count;
}

class CompressedFile
{
public:
	CompressedFile()
	{
		for (size_t i = 0; i < 256; i++)
		{
			_FileInfo[i]._ch = i;
		}
	}

	void Compressed(string readname, string  CompressedFileName = "")
	{
		FILE* readfile = fopen(readname.c_str(), "rb");
		assert(readfile);

		unsigned char* readstr = new unsigned char[1024 * 32];
		size_t readcount = 0;
		readcount = fread(readstr, 1, 1024 * 32, readfile);
		while (readcount != 0)
		{
			for (size_t i = 0; i < readcount; i++)
			{
				_FileInfo[readstr[i]]._count++;
			}
			readcount = fread(readstr, 1, 1024 * 32, readfile);
		}

		FileInfo invalue;
		HuffmanTree<FileInfo> ht(_FileInfo, 256, invalue);
		Coding(ht);
		fseek(readfile, 0, SEEK_SET);

		string FileHead = GetPost(readname);

		CompressedFileName += readname.substr(CompressedFileName.length(), readname.find_last_of('.'));
		CompressedFileName = CompressedFileName.substr(0, CompressedFileName.find_last_of('.'));
		CompressedFileName += ".huf";

		FileHead += '\n';

		size_t valuecount = 0;
		string strvalue;

		for (size_t i = 0; i < 256; i++)
		{
			if (_FileInfo[i]._count)
			{
				string ptmp;
				char strptmp[20] = { 0 };
				ptmp += _FileInfo[i]._ch;
				ptmp += ',';
				_i64toa(_FileInfo[i]._count, strptmp, 10);
				ptmp += strptmp;
				ptmp += '\n';
				strvalue += ptmp;
				valuecount++;
			}
		}

		char  str[10] = { 0 };
		_itoa(valuecount, str, 10);

		FileHead += str;
		FileHead += '\n';
		FileHead += strvalue;

		FILE* writefile = fopen(CompressedFileName.c_str(), "wb");
		assert(writefile);

		fwrite(FileHead.c_str(),1,FileHead.length(),writefile);
		char* writestr = new char[1024 * 32];
		size_t writecount = 0;
		size_t idx = 0;
		char value = 0;
		readcount = fread(readstr, 1, 1024 * 32, readfile);
		HuffmanNode<FileInfo>* _root = ht.GetRoot();
		long long weight = _root->_weight._count / (1024 * 32);
		long long arv = weight / 100;
		if (arv == 1)
			arv++;
		long long k = 0;
		char __arr[102] = { 0 };
		while (readcount)
		{
			k++;
			if (k == arv)
			{
				cout << '*';
				k = 0;
			}
			for (size_t i = 0; i < readcount; i++)
			{
				string coding = _FileInfo[readstr[i]].coding;

				for (size_t j = 0; j < coding.length(); ++j)
				{
					value <<= 1;
					if (coding[j] == '1')
						value |= 1;

					if (++idx == 8)
					{
						writestr[writecount++] = value;
						if (writecount == (1024 * 32))
						{
							fwrite(writestr, 1, 1024 * 32, writefile);
							fflush(writefile);
							writecount = 0;
						}
						idx = 0;
						value = 0;
					}
				}
			}

			readcount = fread(readstr, 1, 1024 * 32, readfile);
		}

		if (idx)
		{
			value <<= (8 - idx);
			writestr[writecount++] = value;
		}

		if (writecount)
		{
			fwrite(writestr, 1, writecount, writefile);
		}

		cout << endl;
		delete[] readstr;
		delete[] writestr;
		fclose(readfile);
		fclose(writefile);	
	}

	void UnCompressed(const string& readname, string writename = "")
	{
		FILE* readfile = fopen(readname.c_str(), "rb");
		assert(readfile);

		writename += readname.substr(writename.length(), readname.find_last_of('.'));
		writename = writename.substr(0, writename.find_last_of('.'));
		string strptmmp;
		GetLine(readfile, strptmmp);
		if (strptmmp.length())
		{
			writename += strptmmp;
		}

		int num = 0;
		strptmmp = "";
		GetLine(readfile,strptmmp);
		if (strptmmp.length())
		{
			num = atoi(strptmmp.c_str());
		}
 
  		for (int i = 0; i < num; ++i)
  		{

			strptmmp = "";
  			GetLine(readfile,strptmmp);
			unsigned char ch = strptmmp[0];
			_FileInfo[ch]._ch = ch;
			//string ptmp = strptmmp.substr(1, strptmmp.length() - 1);
  			_FileInfo[ch]._count = atoi(strptmmp.c_str()+2);
  		}
 
 		FILE* writefile = fopen(writename.c_str(), "wb");
 		assert(writefile);
 
 		FileInfo invalue;
 		HuffmanTree<FileInfo> ht(_FileInfo, 256, invalue);
 		HuffmanNode<FileInfo>* _root = ht.GetRoot();
 
 		unsigned char* readstr = new unsigned char[1024];
 		unsigned char* writestr = new unsigned char[1024];
 		size_t writecount = 0;
 		unsigned char ch;
 		int pos = 7;
 		long long filesize = _root->_weight._count;
 		HuffmanNode<FileInfo> * root = _root;
 
 		size_t readcount = fread(readstr, 1, 1024, readfile);
 		while (readcount)
 		{
 			for (size_t i = 0; i < readcount;)
 			{
 				ch = readstr[i];
 				
 				while (NULL != root->_pLeft || NULL != root->_pRight)
 				{
 					if (ch & (1 << pos--))
 						root = root->_pRight;
 					else
 						root = root->_pLeft;
 					if (pos < 0)
 					{
 						pos = 7;
 						ch = readstr[++i];
 						break;
 					}
 				}
 
 				if (NULL == root->_pLeft && NULL == root->_pRight)
 				{
 					writestr[writecount++] = root->_weight._ch;
 					filesize--;
 					root = _root;
 					if (0 == filesize)
 					{
 						fwrite(writestr, 1, writecount, writefile);
 						return;
 					}
 
 					if (1024 == writecount)
 					{
 						fwrite(writestr, 1, 1024, writefile);
 						writecount = 0;
 					}
 				}
 			}
 		
 			readcount = fread(readstr, 1, 1024, readfile);
 		}
	}

	

private:

	void GetLine(FILE* fp,string& line)
	{
 		char first;
 		if (!feof(fp))
 		{
 			first = fgetc(fp);
 			line += first;
 		}
		while (!feof(fp))
		{
			char ch = fgetc(fp);
			if (ch != '\n')
			{
				line += ch;
			}
			else
			{
				break;
			}
		}

	}

	string GetPost(const string& str)
	{
		size_t pos = str.find_last_of('.');
		return str.substr(pos, str.length() - pos);
	}


	void Coding(HuffmanTree<FileInfo>& ht)
	{
		HuffmanNode<FileInfo>* root = ht.GetRoot();
		size_t count = 0;
		GetLeaf(root, count);
//		cout << "有效字符个数为count = " << count << endl;
	}

	void GetLeaf(HuffmanNode<FileInfo>* root, size_t& count)
	{
		if (root)
		{
			GetLeaf(root->_pLeft, count);
			GetLeaf(root->_pRight, count);

			if (root->_pLeft == NULL && root->_pRight == NULL)
			{
				count++;
				HuffmanNode<FileInfo>* child = root;
				HuffmanNode<FileInfo>* parent = child->_pParent;
				string& coding = _FileInfo[root->_weight._ch].coding;

				while (parent)
				{
					if (child == parent->_pLeft)
					{
						coding += '0';
					}
					else
					{
						coding += '1';
					}

					child = parent;
					parent = child->_pParent;
				}

				reverse(coding.begin(), coding.end());
			}
		}
	}
private:
	FileInfo _FileInfo[256];
};

void test()
{
	CompressedFile com;
	//string filename("2.huf");
	string filename("新建 Microsoft Word 文档.huf");


	//com.Compressed(filename);

	com.UnCompressed(filename);
}