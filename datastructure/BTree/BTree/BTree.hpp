#pragma once

#include <iostream>
#include <assert.h>
using namespace std;

template<class K, size_t M>
struct BTreeNode
{
	BTreeNode()
		:_pParent(NULL)
		, _size(0)
	{
		for (size_t i = 0; i < M + 1; ++i)
			_Ptr[i] = NULL;
	}
	
	K _keys[M];
	BTreeNode<K, M>* _Ptr[M + 1];
	BTreeNode<K, M>* _pParent;
	size_t _size;
};

template<class K, size_t M>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:

	BTree()
		:_pRoot(NULL)
	{}

	pair<Node*, int> Find(const K& key)
	{
		Node* pCur = _pRoot;
		Node* pParent = NULL;

		while (pCur)
		{
			size_t idx = 0;
			while (idx < pCur->_size)
			{
				if (key > pCur->_keys[idx])
					idx++;
				else if (key < pCur->_keys[idx])
					break;
				else
					return make_pair(pCur, idx);
			}
			pParent = pCur;
			pCur = pCur->_Ptr[idx];
		}

		return make_pair(pParent, -1);
	}

	bool Insert(const K& key)
	{
		if (NULL == _pRoot)
		{
			_pRoot = new Node;
			_pRoot->_keys[0] = key;
			_pRoot->_size++;
			return true;
		}

		pair<Node*, int> ret = Find(key);
		if (ret.second > 0)
			return false;

		Node* pCur = ret.first;
		Node* pNewNode = NULL;
		K k = key;

		while (true)
		{
			_Insert(pCur, k, pNewNode);

			if (pCur->_size < M)
				return true;

			pNewNode = new Node;
			size_t mid = M / 2;
			size_t idx = mid + 1;
			size_t count = 0;

			while (idx < M)
			{
				pNewNode->_keys[count] = pCur->_keys[idx];
				pNewNode->_Ptr[count] = pCur->_Ptr[idx];
				pCur->_Ptr[idx] = NULL;
				if (pNewNode->_Ptr[count])
					pNewNode->_Ptr[count]->_pParent = pNewNode;
				pNewNode->_size++;
				count++;
				idx++;
			}
			pNewNode->_Ptr[count] = pCur->_Ptr[idx];
			if (pNewNode->_Ptr[count])
				pNewNode->_Ptr[count]->_pParent = pNewNode;

			pCur->_size = pCur->_size - pNewNode->_size - 1;

			if (NULL == pCur->_pParent)
			{
				_pRoot = new Node;
				_pRoot->_keys[0] = pCur->_keys[mid];
				_pRoot->_Ptr[0] = pCur;
				_pRoot->_Ptr[1] = pNewNode;
				_pRoot->_size++;
				pCur->_pParent = _pRoot;
				pNewNode->_pParent = _pRoot;
				return true;
			}
			else
			{
				k = pCur->_keys[mid];
				pCur = pCur->_pParent;
			}
		}	
	}

	bool Remove(const K& key)
	{
		if (NULL == _pRoot)
			return false;
	
		pair<Node*, int> ret = Find(key);
		if (ret.second == -1)
			return false;

		Node* pCur = ret.first;

	}

	void InOrder()
	{
		cout << "InOrder:";
		_InOrder(_pRoot);
		cout << endl;
	}

private:

	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			size_t i = 0;
			for (; i < pRoot->_size; ++i)
			{
				_InOrder(pRoot->_Ptr[i]);
				cout << pRoot->_keys[i] << ' ';
			}
			_InOrder(pRoot->_Ptr[i]);
		}
	}
	
	void _Insert(Node* pCur, K& key,Node* pSub)
	{
		assert(pCur)
		
		int idx = pCur->_size - 1;
		while (idx > -1)
		{
			if (pCur->_keys[idx] > key)
			{
				pCur->_keys[idx + 1] = pCur->_keys[idx];
				pCur->_Ptr[idx + 2] = pCur->_Ptr[idx + 1];
				idx--;
			}
			else
				break;
		}

		pCur->_keys[idx + 1] = key;
		pCur->_Ptr[idx + 2] = pSub;
		pCur->_size++;

		if (pSub)
			pSub->_pParent = pCur;	   
	}

private:
	Node* _pRoot;
};

void test()
{
	BTree<int, 3> t;
	int arr[7] = { 53, 75, 139, 49, 145, 36, 101 };
	
	for (size_t i = 0; i < 7; ++i)
		t.Insert(arr[i]);

	t.InOrder();
}