#pragma once
#include <iostream>
using namespace std;

enum COLOR
{
	RED,
	BLACK
};

template<class K,class V>
struct RBTreeNode
{
	RBTreeNode(const K& key, const V& value, COLOR color = RED)
		: _pRight(NULL)
		, _pLeft(NULL)
		, _pParent(NULL)
		, _key(key)
		, _value(value)
		, _color(color)
	{}

	RBTreeNode<K, V>* _pRight;
	RBTreeNode<K, V>* _pLeft;
	RBTreeNode<K, V>* _pParent;
	K _key;
	V _value;
	COLOR _color;
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:

	RBTree()
		:_pRoot(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (NULL == _pRoot)
		{
			_pRoot = new Node(key, value, BLACK);
			return true;
		}

		Node* pCur = _pRoot;
		Node* pParent = NULL;
		while (pCur)
		{
			if (key == pCur->_key)
				return false;
			else if (key > pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
		}

		pCur = new Node(key, value);
		if (pParent->_key > key)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;

		pCur->_pParent = pParent;

		if (BLACK == pParent->_color)
			return true;

		while (RED == pCur->_color && RED == pParent->_color)
		{
			Node* pGar = pParent->_pParent;

			if (pParent == pGar->_pLeft)
			{
				Node* pU = pGar->_pRight;

				if (pU && RED == pU->_color)
				{
					pU->_color = BLACK;
					pParent->_color = BLACK;
					pGar->_color = RED;

					pCur = pGar;
					pParent = pGar->_pParent;
				}
				else
				{
					if (pCur == pParent->_pRight)
					{
						_RotateL(pParent);

						std::swap(pParent, pCur);
					}

					_RotateR(pGar);

					pParent->_color = BLACK;
					pGar->_color = RED;

					pCur = pParent->_pParent;
					pParent = pCur->_pParent;
				}
			}
			else
			{
				Node* pU = pGar->_pLeft;

				if (pU && RED == pU->_color)
				{
					pU->_color = BLACK;
					pParent->_color = BLACK;
					pGar->_color = RED;

					pCur = pGar;
					pParent = pGar->_pParent;
				}
				else
				{
					if (pCur == pParent->_pLeft)
					{
						_RotateR(pParent);

						std::swap(pParent, pCur);
					}

					_RotateL(pGar);

					pParent->_color = BLACK;
					pGar->_color = RED;

					pCur = pParent->_pParent;
					pParent = pCur->_pParent;
				}
			}
		}

		return true;
	}

	size_t Size()
	{
		size_t count = 0;
		_Size(_pRoot,count);
		return count;
	}

	bool CheckRBTree()
	{
		size_t count = 0;

		_blackCount(_pRoot, count);
		return _CheckRBTree(_pRoot, count, 0);
	}

	void InOrder()
	{
		cout << "InOrder: ";
		_InOrder(_pRoot);
		cout << endl;
	}

private:

	void _blackCount(Node* pRoot, size_t &count)
	{
		if (pRoot)
		{
			if (BLACK == pRoot->_color)
				count++;


			_blackCount(pRoot->_pLeft, count);
			_blackCount(pRoot->_pRight, count);
		}
	}

	void _RotateR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		pSubL->_pRight = pParent;
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		if (NULL == pPParent)
			_pRoot = pSubL;
		else
		{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
	}

	void _RotateL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;

		pSubR->_pLeft = pParent;
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubR;
		if (pPParent)
		{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
		else
			_pRoot = pSubR;
	}

	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_key << ' ';
			_InOrder(pRoot->_pRight);
		}
	}

	bool _CheckRBTree(Node* pRoot, const size_t blackCount, size_t k)
	{
		if (pRoot == NULL)
			return true;

		if (pRoot->_color == BLACK)
			k++;

		if (pRoot->_color == RED && pRoot->_pParent->_color == RED)
			return false;

		if (pRoot->_pLeft == NULL && pRoot->_pRight == NULL)
		{
			if (blackCount == k)
				return true;
		}

		return _CheckRBTree(pRoot->_pLeft, blackCount, k) && _CheckRBTree(pRoot->_pRight, blackCount, k);
	}

	void _Size(Node* pRoot,size_t& count)
	{
		if (pRoot)
		{
			count++;
			_Size(pRoot->_pLeft, count);
			_Size(pRoot->_pRight, count);
		}
	}

private:
	Node* _pRoot;
};


void Test()
{
	int arr[] = { 3, 8, 5, 9, 4, 67, 26, 36, 5, 78, 96, 42 };

	RBTree<int, int> t;

	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		t.Insert(arr[i], i);

	t.InOrder();
	cout << t.Size() << endl;
	if (t.CheckRBTree())
	{
		cout << "ÊÇºìºÚÊ÷" << endl;
	}
	else
	{
		cout << "²»ÊÇºìºÚÊ÷" << endl;
	}
}