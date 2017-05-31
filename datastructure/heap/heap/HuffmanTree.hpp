#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include "heap.hpp"
#include <string>
#include <stack>
#include <memory>
#include <stdio.h>

template<class T ,class W=long long>
struct Node
{
	Node(const W& weight, const T data = T())
		: _weight(weight)
		, _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
		, _data(data)
	{}

	Node<T>* _pLeft;
	Node<T>* _pRight;
	Node<T>* _pParent;
	W _weight; 
	T _data;
	string coding;
};

template<class T, class W = long long>
class HuffmanTree
{
public:
	HuffmanTree()
		: _pRoot(NULL)
	{}

	HuffmanTree(const W array[], size_t size)
	{
		_array.resize(256);
		_Create(array, size);
	}

	~HuffmanTree()
	{
		Destory(_pRoot);
	}

	void HuffmanCoding()
	{
		for (size_t i = 0; i < 256; i++)
		{
			GetWay(_array[i]);
		}
	}

	size_t CompressedFile(FILE* readfile, FILE* writefile)
	{
		int i = 0;
		long count = 0;
		long count1 = 0;
		unsigned char num = 0;
		unsigned char ch;
		while ((count1 < _pRoot->_weight) && (ch = fgetc(readfile)) != EOF)
		{
			count1++;
			int index = _array[ch]->coding.size();
			while (--index >= 0)
			{
				if (_array[ch]->coding[index] == '0')
				{
					if (i == 8)
					{
						count++;
						fputc(num, writefile);
						i = 0;
						num = 0;
					}
					num <<= 1;
					i++;
				}
				else
				{
					if (i == 8)
					{
						count++;
						fputc(num, writefile);
						i = 0;
						num = 0;
					}

					num <<= 1;
					num |= 1;
					i++;
					
				}
			}
		}

		if (i < 8)
		{
			num <<= (8 - 1);
		}
		fputc(num, writefile);
		count++;
		return count;
	}

	unsigned char* CompressedFile(const T str[],long& count)
	{
		unsigned char* p = new unsigned char[1000];
		int i = 0;
		//long count = 0;
		unsigned char num = 0;
		while (*str)
		{
			int index = _array[*str]->coding.size();
			while (--index >= 0)
			{
				if (_array[*str]->coding[index] == '0')
				{
					if (i == 8 && count < 100)
					{
						p[count++] = num;
						i = 0;
						num = 0;
					}
					num <<= 1;
					i++;
				}
				else
				{
					if (i == 8 && count < 1000)
					{
						p[count++] = num;
						i = 0;
						num = 0;
					}
					num <<= 1;
					num |= 1;
					i++;
				}
			}
			str++;
		}
		if (count < 1000)
		{
			num <<= (8 - i);
			p[count++] = num;
		}
		cout << "count = " << count << endl;
		return p;
	}

	void DecompressedFile(const T* p,size_t size,size_t chcount)
	{
		unsigned char ch;
		size_t count = 0;
		size_t index = 0;
		char str[10] = { 0 };
		ch = p[count++];
		DecToBin(str, ch);
		size_t i = 0;
		do
		{
			Node<T>* root = _pRoot;
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
					ch = p[count++];
					DecToBin(str, ch);
				}
			}

			cout << root->_data ;
			index++;

		} while (count<size || index < chcount);
		cout << endl;
		delete[] p;
	}

	void DecompressedFile(FILE* readfile,size_t readsize, FILE* writefile ,size_t writesize)
	{
		unsigned char ch;
		size_t readcount = 0;
		size_t writecount = 0;
		char str[10] = { 0 };
		ch = fgetc(readfile);
		readcount++;
		DecToBin(str, ch);
		size_t i = 0;
		do 
		{
			Node<T>* root = _pRoot;
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
					if (ch==EOF)
					{
						return;
					} 
					readcount++;
					DecToBin(str, ch);
				}
			}

			fputc(root->_data, writefile);
			writecount++;

		} while (1);
	}

protected:

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

	void Destory(Node<T>* pRoot)
	{
		for (size_t i = 0; i < 256; i++)
		{
			delete _array[i];
		}
	}

	struct Compare
	{
		bool operator()(const Node<T>* pLeft, const Node<T>* pRight)
		{
			return pLeft->_weight < pRight->_weight;
		}
	};

	void GetWay(Node<T>* child)
	{
		Node<T>* ch = child;
		Node<T>* pParent = ch->_pParent;
		while (NULL != pParent)
		{
			if (ch == pParent->_pLeft)
			{
				child->coding.push_back('0');
			}
			else
			{
				child->coding.push_back('1');
			}

			ch = pParent;
			pParent = ch->_pParent;
		}
	}

	void _Create(const W array[], size_t size)
	{
		Heap<Node<T>*,Compare> hp;
		
		for (size_t i = 0; i < size; i++)
		{
			Node<T>* ptmp = new Node<T>(array[i],i);
			_array[i] = ptmp;
			hp.Push(ptmp);
		}

		while (hp.Size()>1)
		{
			Node<T>* pLeft = hp.Top();
			hp.Pop();
			Node<T>* pRight = hp.Top();;
			hp.Pop();
			Node<T>* pParent = new Node<T>(pRight->_weight + pLeft->_weight);
			pParent->_pLeft = pLeft;
			pParent->_pRight = pRight;
			pLeft->_pParent = pParent;
			pRight->_pParent = pParent;
			hp.Push(pParent);
		}

		_pRoot = hp.Top();
	}

protected:
	vector<Node<T>*> _array;
	Node<T>* _pRoot;
};

#define LONGEST 20

void Test2()
{
	long long array[256] = { 0 };
	char readfilename[LONGEST] = { "readfile.txt" };
	//cout << "输入文件名并且文件名长度小于20" << endl;
	//cin >> readfilename;
	FILE* readfile = fopen(readfilename, "r");
	if (readfile == NULL)
	{
		perror("readfile is:");
		return;
	}
	
	unsigned int ch;
	size_t count1 = 0;
	while ((ch = fgetc(readfile)) != EOF)
	{
		count1++;
		array[ch]++;
	}


	cout << "count1 = " << count1 << endl;
	//fseek(readfile, 0, SEEK_SET);
	fclose(readfile);
	readfile = fopen(readfilename, "r");
	if (NULL == readfile)
	{
		perror("readfile is:");
		return;
	}

	HuffmanTree<unsigned char> ht(array, 256);
	ht.HuffmanCoding();
	
	FILE* writefile = fopen("CompressedFile.txt", "w");
	if (NULL == writefile)
	{
		perror("writefile is :");
		return;
	}

	size_t count = ht.CompressedFile(readfile, writefile);
	fclose(readfile);
	fclose(writefile);

	readfile = fopen("CompressedFile.txt", "r");
	if (NULL == readfile)
	{
		perror("readfile is:");
		return;
	}
	writefile = fopen("DeCompressedFile.txt", "w");
	if (NULL == writefile)
	{
		perror("writefile is :");
		return;
	}

	ht.DecompressedFile(readfile,count,writefile,count1);

	fclose(readfile);
	fclose(writefile);
}

void test1()
{
	long long array[256] = { 0 };
	unsigned char arr[] = { "aabbbccccddjbnaajffdnd\njdkhfkjhjkhfkshfk\nsjfhjkhkshdgkj\nsaghsdakjfhd\nksjfhajdkfsdhfkjkhfkhfkhfkhsjkd\nh捡垃圾分类\nfdsifjsoifj\n ifjiojfddsifjiosjfiosdjfsidjfiojdffd\niofjddif节目标】\n1、基本概念\n	2、HuffmanTree构造算法\n3、Huffman编码\n4、完成文件压缩\n基本概念\n在一棵二叉树中：\n定义从A结点到B结点所经过的分支序列为从A结点到B结点的路径。\n定义从A结点到B结点所经过的分支个数为从A结点到B结点的路径长度。\n从二叉树的根节点到二叉树中所有节点的路径长度之和为该二叉树的路径长度。\n由树的定义可知：从树的根节点到达树中每一结点有且仅有一条路径。 若设树的根节点处\n于第1层，某节点处于第k层，因为从根节点到达该结点的路径上的分支数为k - jddfjdd\njfioddjfddjffkafaf陈文宽" };
	unsigned char*str = arr;

	while (*str)
		array[*str++]++;
	long count = 0;
	HuffmanTree<unsigned char> ht(array, 256);
	ht.HuffmanCoding();
	unsigned char* p = ht.CompressedFile(arr, count);
	ht.DecompressedFile(p,count,sizeof(arr)-1);
}
