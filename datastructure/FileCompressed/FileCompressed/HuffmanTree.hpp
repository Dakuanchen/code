#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include "heap.hpp"
#include <string>
#include <stack>
#include <memory>
#include <stdio.h>

template<class T>
struct HuffmanNode
{
	HuffmanNode(const T& weight)
		: _weight(weight)
		, _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
	{}

	HuffmanNode<T>* _pLeft;
	HuffmanNode<T>* _pRight;
	HuffmanNode<T>* _pParent;
	T _weight;
	T _data;
};

template<class T>
class HuffmanTree
{
public:
	HuffmanTree()
		: _pRoot(NULL)
	{}

	HuffmanTree(const T array[], size_t size,const T& invalue)
	{
		_Create(array, size, invalue);
	}

	HuffmanNode<T>* GetRoot()
	{
		return _pRoot;
	}

// 	~HuffmanTree()
// 	{
// 		Destory(_pRoot);
// 	}

private:
	void Destory(HuffmanNode<T>* pRoot)
	{
		Destory(pRoot->_pLeft);
		Destory(pRoot->_pRight);
		delete pRoot;
	}

	struct Compare
	{
		bool operator()(const HuffmanNode<T>* pLeft, const HuffmanNode<T>* pRight)
		{
			return pLeft->_weight < pRight->_weight;
		}
	};
	void _Create(const T array[], size_t size ,const T& invalue)
	{
		assert(array);

		Heap<HuffmanNode<T>*, Compare> hp;

		for (size_t i = 0; i < size; i++)
		{
			if (array[i] != invalue)
			{
				HuffmanNode<T>* ptmp = new HuffmanNode<T>(array[i]);
				hp.Push(ptmp);
			}
		}

		while (hp.Size()>1)
		{
			HuffmanNode<T>* pLeft = hp.Top();
			hp.Pop();
			HuffmanNode<T>* pRight = hp.Top();;
			hp.Pop();
			HuffmanNode<T>* pParent = new HuffmanNode<T>(pRight->_weight + pLeft->_weight);
			pParent->_pLeft = pLeft;
			pParent->_pRight = pRight;
			pLeft->_pParent = pParent;
			pRight->_pParent = pParent;
			hp.Push(pParent);
		}

		_pRoot = hp.Top();
	}

protected:
	HuffmanNode<T>* _pRoot;
};