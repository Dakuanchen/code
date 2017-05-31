#pragma once
#include <iostream>
using namespace std;


template<class K, class V>
struct BSTNode
{
	BSTNode(const K& key, const V& value)
		: _pLeft(NULL)
		, _pRight(NULL)
		, _key(key)
		, _value(value)
	{}

	BSTNode<K, V>* _pLeft;
	BSTNode<K, V>* _pRight;

	K _key;
	V _value;
};

template<class K, class V, class Ref, class Ptr>
class iterator
{
	typedef iterator<K, V, Ref, Ptr> Self;
	typedef BSTNode<K, V> Node;
public:

	Node* operator++()
	{

	}

	Node* operator--()
	{

	}

	bool operator!=(const Self& t)
	{
		return _pNode->_key != t._pNode->_key;
	}

private:
	BSTNode<K, V>* _pNode;
};



template<class K, class V>
class BinarySearchTree
{
	typedef BSTNode<K, V> Node;
	typedef BinarySearchTree<K, V> Self;
public:
	BinarySearchTree()
		: _pRoot(NULL)
	{}

	BinarySearchTree(const Self& bst)
	{
		if (bst._pRoot == NULL)
		{
			_pRoot = NULL;
			return;
		}

		_Copy(_pRoot, bst._pRoot);
	}

	Self& operator=(const Self& bst)
	{

		if (this == &bst)
		{
			return *this;
		}

		if (bst._pRoot == NULL)
		{
			_pRoot = NULL;
			return *this;
		}

		Node* Root = NULL;
		_Copy(Root, bst._pRoot);

		if (Root)
		{
			Destroy(_pRoot);
			_pRoot = Root;
		}

		return *this;
	}

	~BinarySearchTree()
	{
		Destroy(_pRoot);
	}

	// ²éÕÒµÝ¹éºÍ·ÇµÝ¹é
	bool Find_Nor(const K& key)
	{
		if (NULL == _pRoot)
			return false;

		Node* pCur = _pRoot;
		
		while (pCur)
		{
			if (key == pCur->_key)
				return true;
			else if (key > pCur->_key)
				pCur = pCur->_pRight;
			else
				pCur = pCur->_pLeft;
		}

		return false;
	}

	bool Find(const K& key)
	{
		return _Find(_pRoot, key);
	}

	// ²åÈëµÝ¹éºÍ·ÇµÝ¹é
	bool Insert_Nor(const K& key, const V& value)
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

		if (pParent->_key > key)
		{
			pParent->_pLeft = new Node(key, value);
			return true;
		}
		else
		{
			pParent->_pRight = new Node(key, value);
			return true;
		}

		return false;
	}

	bool Insert(const K& key, const V& value)
	{
		return _Insert(_pRoot, key, value);
	}

	// É¾³ýµÝ¹éºÍ·ÇµÝ¹é
	bool Remove_Nor(const K& key)
	{
		if (_pRoot == NULL)
		{
			return false;
		}

		if (_pRoot->_pLeft == NULL && _pRoot->_pRight == NULL && _pRoot->_key == key)
		{
			delete _pRoot;
			_pRoot = NULL;
			return true;
		}

		Node* pCur = _pRoot;
		Node* pParent = NULL;
	    while (pCur)
		{
			if (key > pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else if (key < pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else
				break;
		}
		
		if (pCur)
		{
			if (pCur->_pLeft ==  NULL)
			{
				if (_pRoot == pCur)
				{
					_pRoot = pCur->_pRight;
					delete pCur;
					pCur = NULL;
					return true;
				}
				else
				{
					if (pCur == pParent->_pLeft)
					{
						pParent->_pLeft = pCur->_pRight;
						delete pCur;
						pCur = NULL;
						return true;
					}
					else
					{
						pParent->_pRight = pCur->_pRight;
						delete pCur;
						pCur = NULL;
						return true;
					}
				}
			}
			else  if (pCur->_pRight == NULL)
			{
				if (_pRoot == pCur)
				{
					_pRoot = pCur->_pLeft;
					delete pCur;
					pCur = NULL;
					return true;
				}
				else if (pParent->_pLeft == pCur)
				{
					pParent->_pLeft = pCur->_pLeft;
					delete pCur;
					pCur = NULL;
					return true;
				}
				else
				{
					pParent->_pRight = pCur->_pLeft;
					delete pCur;
					pCur = NULL;
					return true;
				}
			}
			else
			{
				Node* firstInOrder = pCur->_pRight;
				pParent = pCur;

				while (firstInOrder->_pLeft)
				{
					pParent = firstInOrder;
					firstInOrder = firstInOrder->_pLeft;
				}

				pCur->_key = firstInOrder->_key;
				pCur->_value = firstInOrder->_value;

				if (pParent ==  pCur)
				{	
					pCur->_pRight = firstInOrder->_pRight;
					delete firstInOrder;
					return true;
				}
				else
				{
					pParent->_pLeft = firstInOrder->_pRight;
					delete firstInOrder;
					return true;
				}
			}
		}

		return false;
	}

	bool Remove(const K& key)
	{
		return _Remove(_pRoot, key);
	}

	void InOrder()
	{
		cout << "InOrder:";
		_InOrder(_pRoot);
		cout << endl;
	}

private:
	bool _Find(Node* pRoot, const K& key)
	{
		if (NULL == pRoot)
			return false;

		if (key == pRoot->_key)
			return true;

		if (pRoot->_key < key)
			return _Find(pRoot->_pRight, key);
		else
			return _Find(pRoot->_pLeft, key);		
	}

	bool _Insert(Node* &pRoot, const K& key, const V& value)
	{
		if (NULL == pRoot)
		{
			pRoot = new Node(key, value);
			return true;
		}

		if (key == pRoot->_key)
		{
			return false;
		}

		if (pRoot->_key < key)
			return _Insert(pRoot->_pRight, key, value);
		else
			return _Insert(pRoot->_pLeft, key, value);
	}

	bool _Remove(Node*& pRoot, const K& key)
	{
		if (pRoot == NULL)
		{
			return false;
		}

		if (pRoot->_key == key)
		{
			if (pRoot->_pLeft == NULL)
			{
				Node* pCur = pRoot;
				pRoot = pRoot->_pRight;
				delete pCur;
				return true;
			}
			else if (pRoot->_pRight == NULL)
			{
				Node* pCur = pRoot;
				pRoot = pRoot->_pLeft;
				delete  pCur;
				return true;
			}
			else
			{
				Node* firstInOrder = pRoot->_pRight;

				while (firstInOrder->_pLeft)
					firstInOrder = firstInOrder->_pLeft;

				pRoot->_key = firstInOrder->_key;
				pRoot->_value = firstInOrder->_value;

				return _Remove(pRoot->_pRight, firstInOrder->_key);
			}
		}

		if (key > pRoot->_key)
			return  _Remove(pRoot->_pRight, key);
		else
			return _Remove(pRoot->_pLeft, key);
	}

	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_key << " ";
			_InOrder(pRoot->_pRight);
		}
	}

	void Destroy(Node*& pRoot)
	{
		if (NULL == pRoot)
		{
			return;
		}

		Destroy(pRoot->_pLeft);
		Destroy(pRoot->_pRight);

		delete pRoot;
		pRoot = NULL;
	}

	void _Copy(Node*& pRoot, const Node* pDes)
	{
		if (pDes)
		{
			pRoot = new Node(pDes->_key, pDes->_value);
			_Copy(pRoot->_pLeft, pDes->_pLeft);
			_Copy(pRoot->_pRight, pDes->_pRight);
		}
	}
private:
	Node* _pRoot;
};


void test()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };

	BinarySearchTree<int, int> t;


	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		t.Insert_Nor(a[i], a[i]);
	}

	BinarySearchTree<int, int> t1(t);
	BinarySearchTree<int, int> t2;
	t2 = t;

	t1.InOrder();
	t2.InOrder();

	t.InOrder();

	cout << t.Find_Nor(4) << endl;
	t.Remove_Nor(4);
	t.InOrder();
	cout << t.Find_Nor(8) << endl;
	t.Remove_Nor(8);
	t.InOrder();
	cout << t.Find_Nor(3) << endl;
	t.Remove_Nor(3);
	t.InOrder();
	cout << t.Find_Nor(5) << endl;
	t.Remove_Nor(5);
	t.InOrder();

}