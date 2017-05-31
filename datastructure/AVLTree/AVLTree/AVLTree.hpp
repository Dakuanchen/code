#pragma once
#include <iostream>
using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode(const K& key,const V& value)
		: _pParent(NULL)
		, _pLeft(NULL)
		, _pRight(NULL)
		, _key(key)
		, _value(value)
		, _bf(0)
	{}

	AVLTreeNode<K, V>* _pParent;
	AVLTreeNode<K, V>* _pLeft;
	AVLTreeNode<K, V>* _pRight;
	K _key;
	V _value;
	int _bf;
};



template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_pRoot(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (NULL == _pRoot)
		{
			_pRoot = new Node(key, value);
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


		while (pParent)
		{
			if (pCur == pParent->_pLeft)
				pParent->_bf--;
			else
				pParent->_bf++;

			if (0 == pParent->_bf)
				break;
			else if (1 == pParent->_bf || -1 == pParent->_bf)
			{
				pCur = pParent;
				pParent = pParent->_pParent;
			}
			else
			{
				if (2 == pParent->_bf)
				{
					if (1 == pCur->_bf)
						_RotateL(pParent);
					else
						_RotateRL(pParent);
				}
				else
				{
					if (1 == pCur->_bf)
						_RotateLR(pParent);
					else
						_RotateR(pParent);
				}
				return true;
			}
		}
		return true;
	}

	bool IsBalanceTree()
	{
		return _IsBalanceTree(_pRoot);
	}

	void InOrder()
	{
		cout << "InOrder:";
		_InOrder(_pRoot);
		cout << endl;
	}

private:

	bool _IsBalanceTree(Node* pRoot)
	{
		int RightHight = _Hight(pRoot->_pRight);
		int LeftHight = _Hight(pRoot->_pLeft);

		if (pRoot->_bf == (RightHight - LeftHight))
			return _Hight(pRoot->_pLeft) && _Hight(pRoot->_pRight);
		
		return false;
	}

	int _Hight(Node* pRoot)
	{
		if (pRoot)
		{
			if (NULL == pRoot->_pRight && NULL == pRoot->_pLeft)
				return 1;

			int RightHight = _Hight(pRoot->_pRight);
			int LeftHight = _Hight(pRoot->_pLeft);
			return (RightHight > LeftHight) ? RightHight + 1 : LeftHight + 1;
		}

		return 0;
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

	void _RotateL(Node* parent)
	{
		Node* pSubR = parent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		
		parent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = parent;

		pSubR->_pLeft = parent;
		Node* pParent = parent->_pParent;
		parent->_pParent = pSubR;
		if (NULL ==  pParent)
		{
			_pRoot = pSubR;
			pSubR->_pParent = NULL;
		}
		else
		{
			pSubR->_pParent = pParent;
			if (pParent->_pLeft == parent)
				pParent->_pLeft = pSubR;
			else
				pParent->_pRight = pSubR;
		}

		parent->_bf = 0;
		pSubR->_bf = 0;
	}

	void _RotateR(Node* parent)
	{
		Node* pSubL = parent->_pLeft;
		Node* pSubLR = pSubL->_pRight;

		parent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = parent;

		pSubL->_pRight = parent;
		Node* pParent = parent->_pParent;
		parent->_pParent = pSubL;
		if (NULL == pParent)
		{
			_pRoot = pSubL;
			pSubL->_pParent = NULL;
		}
		else
		{
			pSubL->_pParent = pParent;
			if (parent == pParent->_pLeft)
				pParent->_pLeft = pSubL;
			else
				pParent->_pRight = pSubL;
		}

		parent->_bf = 0;
		pSubL->_bf = 0;
	}

	void _RotateRL(Node* parent)
	{
		Node* pSubR = parent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		int bf = pSubRL->_bf;

		_RotateR(parent->_pRight);
		_RotateL(parent);
		if (1 == bf)
		{
			pSubRL->_bf = 0;
			parent->_bf = -1;
		}
		else if (-1 == bf)
		{
			pSubRL->_bf = 0;
			pSubR->_bf = 1;
		}
	}

	void _RotateLR(Node* parent)
	{
		Node* pSubL = parent->_pLeft;
		Node* pSubLR = pSubL->_pRight;

		int bf = pSubLR->_bf;

		_RotateL(parent->_pLeft);
		_RotateR(parent);
		
		if (1 == bf)
		{
			pSubLR->_bf = 0;
			pSubL->_bf = -1;
		}
		else if (-1 == bf)
		{
			pSubLR->_bf = 0;
			parent->_bf = 1;
		}
	}

private:
	Node* _pRoot;
};

void Test()
{
	AVLTree<int, int>  t;
	int arr[10] = { 3, 2, 1, 4, 5, 6, 7, 10, 9, 8 };

	for (size_t i = 0; i < 10; i++)
		t.Insert(arr[i], i);

	t.InOrder();

	if (t.IsBalanceTree())
	{
		cout << "ÊÇAVLÊ÷" << endl;
	}
	else
	{
		cout << "²»ÊÇAVLÊ÷" << endl;
	}
}