#pragma once

#include <iostream>
using namespace std;

template<class T>
struct Node 
{
	Node(const T& data)
		:_data(data)
		, _lChild(NULL)
		, _rChild(NULL)
		, _leftThread(false)
		, _rightThread(false)
	{}

	T _data;
	Node<T>* _lChild;
	Node<T>* _rChild;
	Node<T>* _Parent;
	bool _leftThread;
	bool _rightThread;
};

template<class T>
class ThreadBinary
{
	typedef Node<T> Node;

public:

	ThreadBinary()
		:_root(NULL)
		, _IsThread(false)
	{}

	ThreadBinary(const T array[], size_t size, const T invalue)
		:_IsThread(false)
	{
		size_t i = 0;
		CreateBinTreePreOrder(_root, array, size, i, invalue);
	}

	void PreThread()
	{
		Node* pPre = NULL;
		_IsThread = true;
		PreThread(_root, pPre);
	}

	void InThread()
	{
		Node* pPre = NULL;
		_IsThread = true;
		InThread(_root, pPre);
	}

	void PosThread()
	{
		Node* pPre = NULL;
		_IsThread = true;
		PosThread(_root, pPre);
	}

	void Preorder()
	{
		Node* pCur = _root;

		while (pCur)
		{
			while (!pCur->_leftThread)
			{
				cout << pCur->_data << ' ';
				pCur = pCur->_lChild;
			}
			cout << pCur->_data << ' ';
			pCur = pCur->_rChild;
		}
	}

	void InOrder()
	{
		Node* pCur = _root;
		Node* pPre = NULL;

		while (pCur)
		{
			if (pPre != pCur->_lChild)
			{
				while (!pCur->_leftThread)
					pCur = pCur->_lChild;
			}

			cout << pCur->_data << ' ';
			pPre = pCur;

			while (pCur->_rChild && !pCur->_rightThread && pCur->_rChild->_leftThread)
			{
				pCur = pCur->_rChild;
				cout << pCur->_data << ' ';
			}

			pCur = pCur->_rChild;
		}
	}

	void PosOrder()
	{
		Node* pCur = _root;
		Node* pPre = NULL;

		while (pCur)
		{
			while (!pCur->_leftThread)
			`	pCur = pCur->_lChild;
			
		}
	}

	~ThreadBinary()
	{
		if (_IsThread)
		{
			Destory1();
		}
		else
		{
			Destory2();
		}
	
	}

private:
	void Destory1()
	{
		if (_root)
		{

		}
	}

	void Destory2()
	{

	}

	void CreateBinTreePreOrder(Node*& root, const T array[], const  size_t size, size_t& i, const T& invalue)
	{
		if (i < size && array[i] != invalue)
		{
			root = new Node(array[i]);
			CreateBinTreePreOrder(root->_lChild, array, size, ++i, invalue);
			if (root->_lChild)
				root->_lChild->_Parent = root;
			
			CreateBinTreePreOrder(root->_rChild, array, size, ++i, invalue);
			if (root->_rChild)
				root->_rChild->_Parent = root;
		}
	}

	void PreThread(Node* root, Node*& pPre)
	{
		if (root)
		{
			if (NULL == root->_lChild)
			{
				root->_leftThread = true;
				root->_lChild = pPre;
			}

			if (pPre && NULL == pPre->_rChild)
			{
				pPre->_rightThread = true;
				pPre->_rChild = root;
			}

			pPre = root;

			if (!root->_leftThread)
			{
				PreThread(root->_lChild, pPre);
			}
			if (!root->_rightThread)
			{
				PreThread(root->_rChild, pPre);
			}
		}
	}

	void InThread(Node* root, Node*& pPre)
	{
		if (root)
		{
			InThread(root->_lChild, pPre);

			if (NULL == root->_lChild)
			{
				root->_leftThread = true;
				root->_lChild = pPre;
			}

			if (pPre && NULL == pPre->_rChild)
			{
				pPre->_rightThread = true;
				pPre->_rChild = root;
			}

			pPre = root;

			if (!root->_rightThread)
			{
				InThread(root->_rChild, pPre);
			}
		}
	}

	void PosThread(Node* root, Node*& pPre)
	{
		if (root)
		{
			PosThread(root->_lChild, pPre);
			PosThread(root->_rChild, pPre);

			if (NULL == root->_lChild)
			{
				root->_leftThread = true;
				root->_lChild = pPre;
			}

			if (pPre && NULL == pPre->_rChild)
			{
				pPre->_rightThread = true;
				pPre->_rChild = root;
			}

			pPre = root;
		}
	}

private:
	Node* _root;
	bool _IsThread;
};