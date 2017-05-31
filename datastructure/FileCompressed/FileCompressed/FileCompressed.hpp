#pragma once
#include "HuffmanTree.hpp"
#include <algorithm>


struct FileInfo 
{
	FileInfo(unsigned char ch = char())
		:_ch(ch)
		,_count(0)
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
			_array[i]._ch = i;
		}
	}
	
	long long Compressed(long long& _count)
	{
		FILE* readfile = fopen("readfile.txt", "rb");
		if (NULL == readfile)
		{
			perror("fopen fail for:");
			return -1;
		}

		unsigned char arr[1024] = { 0 };
		size_t readcount = 0;
		readcount = fread(arr, 1, 1024, readfile);
		while (readcount != 0)
		{
			for (size_t i = 0; i < readcount; i++)
			{
				_array[arr[i]]._count++;
			}
			readcount = fread(arr, 1, 1024, readfile);
		}

		FileInfo invalue;
		HuffmanTree<FileInfo> ht(_array, 256, invalue);
		Coding(ht);
		fseek(readfile, 0, SEEK_SET);
		FILE* writefile = fopen("Compressed.txt", "wb");
		if (NULL == writefile)
		{
			perror("fopen fail for:");
			return -1;
		}
		size_t count = 0;
		unsigned char _ch = 0;
		size_t idx = 0;
		size_t num = 0;
		long long writecount = 1;
		int ch = 0;
		while ((ch = fgetc(readfile)) != EOF)
		{
			count++;
			_ch = (unsigned char)ch;
			string& coding = _array[_ch].coding;
			size_t i = 0;
		
			while (i < coding.size())
			{
				num <<= 1;
				idx++;
				if (coding[i] == '1')
				{
					num |= 1;
				}

				if (8 == idx)
				{
					fputc(num, writefile);
					writecount++;
					num = 0;
					idx = 0;
				}
				i++;
			}
		}
	

		if (idx != 0)
		{
			num <<= (8 - idx);
			fputc(num, writefile);
			writecount++;
		}

		HuffmanNode<FileInfo>* _root = ht.GetRoot();
		if (count == _root->_weight._count)
		{
			cout << "成功压缩" << count << endl;
			cout << "压缩文件含有" << writecount << "个字符" << endl;
		}

		fclose(readfile);
		fclose(writefile);

		_count = _root->_weight._count;
		return writecount;
	}

	long long UnCompressed(long long count)
	{
		FILE* readfile = fopen("Compressed.txt", "rb");
		if (NULL == readfile)
		{
			perror("fopen fail for:");
			return -1;
		}
		
		FILE* writefile = fopen("UnCompressed.txt", "wb");
		if (NULL == writefile)
		{
			perror("fopen fail for:");
			return -1;
		}

		FileInfo invalue;
		HuffmanTree<FileInfo> ht(_array, 256, invalue);
		HuffmanNode<FileInfo>* _root = ht.GetRoot();

		int ch = 0;
		ch = fgetc(readfile);
		char arr[102] = { 0 };
		
		long long _count = count / 100;
		long long readcount = 1;
		unsigned char _ch = (unsigned char)ch;
		size_t i = 0;
		long long size = _root->_weight._count;
		long long writecount = 0;
		char str[10] = { 0 };
		DecToBin(str, _ch);

		do
		{
			HuffmanNode<FileInfo>* root = _root;
			while (NULL != root->_pLeft || NULL != root->_pRight)
			{
				if (i < 8)
				{
					if (str[i] == 1)
						root = root->_pRight;
					else
						root = root->_pLeft;
					i++;
				}
				else
				{
					i = 0;
					ch = fgetc(readfile);
					readcount++;
// 					int j = (int)readcount / _count;
// 					arr[j] = '*';
					//printf("[%-101s][%d]\r",arr,j);
					if (readcount == count)
					{
						if (writecount == size)
						{
							cout << "成功解压" << endl;
						}
						else
						{
							cout << "解压失败" << endl;
							cout << "输入count个字符" << writecount << endl;
						}
						return writecount;
					}
					_ch = (unsigned char)ch;
					DecToBin(str, _ch);
				}
			}
			if (writecount < size)
			{
				fputc(root->_weight._ch, writefile);
				//cout << root->_weight._ch;
				writecount++;
			}
			else
			{
				cout << "成功解压" << endl;
				return writecount;
			}
		} while (1);
		
	}

	bool IsCorretDecomppressed(long long count1,long long count2)
	{
		if (count2 != count1)
			return false;

		FILE* desfile = fopen("readfile.txt", "rb");
		if (NULL == desfile)
		{
			perror("fopen fail for:");
			return false;
		}
		FILE* decompressedfile = fopen("UnCompressed.txt", "rb");
		if (NULL == decompressedfile)
		{
			perror("fopen fail for:");
			return false;
		}

		int ch1 = fgetc(desfile);
		int ch2 = fgetc(decompressedfile);
		long long read1 = 1;
		long long read2 = 1;

		while (read1 < count1 && read2 < count2)
		{
			if (ch1 != ch2)
				return false;
			ch1 = fgetc(desfile);
			ch2 = fgetc(decompressedfile);
			read1++;
			read2++;
		}
		return true;
	}

private:

	void DecToBin(char str[], unsigned char ch)
	{
		memset(str, 0, 10);

		stack<char> s;
		if (ch == 0)
		{
			return;
		}
		while (ch)
		{
			char n = ch % 2;
			s.push(n);
			ch /= 2;
		}
		int i = 8 - s.size();
		while (!s.empty())
		{
			str[i++] = s.top();
			s.pop();
		}
	}

	void Coding(HuffmanTree<FileInfo>& ht)
	{
		HuffmanNode<FileInfo>* root = ht.GetRoot();
		size_t count = 0;
		GetLeaf(root,count);
		cout << "有效字符个数为count = " << count << endl;
	}

	void GetLeaf(HuffmanNode<FileInfo>* root,size_t& count)
	{
		if (root)
		{
			GetLeaf(root->_pLeft,count);
			GetLeaf(root->_pRight,count);

			if (root->_pLeft == NULL && root->_pRight == NULL)
			{
				count++;
				HuffmanNode<FileInfo>* child = root;
				HuffmanNode<FileInfo>* parent = child->_pParent;
				string& coding = _array[root->_weight._ch].coding;

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
	//HuffmanTree<FileInfo> _ht;
	FileInfo _array[256];
};


void test()
{
	CompressedFile com;
	long long count = 0;
	long long count1 = com.Compressed(count);
	if (count1 < 0)
	{
		cout << "压缩失败" << endl;
		return;
	}
	long long count2 = com.UnCompressed(count1);

	if (com.IsCorretDecomppressed(count,count2))
	{
		cout << "正确解压文件" << endl;
	}
	else
	{
		cout << "解压文件有误" << endl;
	}
}