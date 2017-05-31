#pragma once
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template<typename T>
struct Node
{
	Node(T data = T())
		:_data(data)
		, _lChild(NULL)
		, _rChild(NULL)
	{}

	T _data;
	Node* _lChild;
	Node* _rChild;
};

template<typename T>
class BinaryTree
{
public:

	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(const T array[], const size_t size, const T invalue)
		:_root(NULL)
	{
		//CreateBinTreePreOrder(_root);
		size_t i = 0;
		CreateBinTreePreOrder(_root, array, size, i, invalue);
	}

	BinaryTree(const BinaryTree<T>& t)
	{
		Copy(_root, t._root);
	}

	BinaryTree<T>& operator=(const BinaryTree<T>& t)
	{
		if (this == &t)
			return *this;

		Destory(_root);
		Copy(_root, t._root);
		return *this;
	}

	void LevelOrder()
	{
		LevelOrder(_root);
	}

	void PreOder2()
	{
		if (_root)
		{
			stack<Node<T>*> s;
			Node<T>* p = _root;
			s.push(p);
			while (!s.empty())
			{
				p = s.top();
				s.pop();
				cout << p->_data << ' ';
							
				if (p->_rChild)
					s.push(p->_rChild);
				if (p->_lChild)
					s.push(p->_lChild);
			}

			cout << endl;
		}
	}

	void PreOrder1()
	{
		if (_root != NULL)
		{
			stack<Node<T>*> s;
			Node<T>* p = _root;

			s.push(p);
			while (!s.empty())
			{
				p = s.top();
				s.pop();
				cout << p->_data << " ";

				if (NULL != p->_rChild)
				{
					s.push(p->_rChild);
				}

				if (NULL != p->_lChild)
				{
					s.push(p->_lChild);
				}
			}
			cout << endl;
		}
	}

	void PreOrder()
	{
		if (_root != NULL)
		{
			stack<Node<T>*> s;
			Node<T>* p = _root;


			while (p != NULL || !s.empty())
			{
				while (NULL != p)
				{
					cout << p->_data << " ";
					s.push(p);
					p = p->_lChild;
				}

				if (!s.empty())
				{
					p = s.top();
					p = p->_rChild;;
					s.pop();
				}
			}
		}

		cout << endl;
	}

	void PreOrderTraverse()
	{
		PreOrderTraverse(_root);
	}

	void InOrder()
	{
		if (_root != NULL)
		{
			Node<T>* p = _root;
			stack<Node<T>*> s;

			while (p != NULL || !s.empty())
			{
				while (p)
				{
					s.push(p);
					p = p->_lChild;
				}

				if (!s.empty())
				{
					p = s.top();
					cout << p->_data << " ";
					p = p->_rChild;
					s.pop();
				}
			}
			cout << endl;
		}
	}

	void PosOrder()
	{
		if (_root != NULL)
		{
			stack<BinNode*> s;
			Node<T>* p = _root;
			BinNode* tmp;

			while (p != NULL || !s.empty())
			{
				while (NULL != p)
				{
					BinNode* pNewNode = new BinNode(p);
					s.push(pNewNode);
					p = p->_lChild;
				}

				if (!s.empty())
				{
					tmp = s.top();
					s.pop();

					if (tmp->IsFirst)
					{
						tmp->IsFirst = false;
						s.push(tmp);
						p = tmp->root->_rChild;
					}
					else
					{
						cout << tmp->root->_data << " ";
						delete tmp;
						p = NULL;
					}
				}
			}
		}
		cout << endl;
	}

	void PosOrder1()
	{
		if (_root)
		{
			stack<Node<T>*> s;
			Node<T>* pCur = _root;
			Node<T>* pPre = NULL;

			while (pCur || !s.empty())
			{
				while (pCur)
				{
					s.push(pCur);
					pCur = pCur->_lChild;
				}

				pCur = s.top();

				if (pCur->_rChild == NULL || pPre == pCur->_rChild)
				{
					cout << pCur->_data << ' ';
					s.pop();
					pPre = pCur;
					pCur = NULL;
				}
				else
				{
					pCur = pCur->_rChild;
				}
			}
			cout << endl;
		}
	}

	void PosOrderTraverse()
	{
		PosOrderTraverse(_root);
	}

	void InsOrderTraverse()
	{
		InsOrderTraverse(_root);
	}

	size_t GetHigh()
	{
		return GetHigh(_root);
	}

	size_t GetLeaf()
	{
		size_t count = 0;
		GetLeaf(_root, count);
		return count;
	}

	size_t GetLeaf1()
	{
		return GetLeaf(_root);
	}

	~BinaryTree()
	{
		Destory(_root);
	}

	Node<T>* GetParent(Node<T>* x)
	{
		return GetParent(_root, x);
	}

	Node<T>* Find(const T& value)
	{
		return Find(_root, value);
	}

	Node<T>* GetLeftChild(const Node<T>* pCur)
	{
		if (NULL == pCur)
		{
			return NULL;
		}

		return pCur->_lChild;
	}

	Node<T>* GetRightChild(const Node<T>* pCur)
	{
		if (NULL == pCur)
		{
			return NULL;
		}

		return pCur->_rChild;
	}

	size_t GetKLevelNode(size_t k)
	{
		if (k <= GetHigh(_root))
		{
			return GetKLevelNode(_root, k);
		}
		return 0;
	}

	Node<T>* GetLatestAnceetorNode(Node<T>* x, Node<T>* y)
	{
		if (NULL == x || NULL == y)
		{
			return NULL;
		}

		if (_root == x || _root == y)
		{
			return _root;
		}

		if (x == y)
		{
			return x;
		}

		Node<T>* xAnceetor = GetParent(_root, x);
		Node<T>* yAnceetor = GetParent(_root, y);

		while (xAnceetor != yAnceetor)
		{
			if (_root != xAnceetor)
			{
				xAnceetor = GetParent(_root, xAnceetor);
			}
			if (_root != yAnceetor)
			{
				yAnceetor = GetParent(_root, yAnceetor);
			}
		}

		return xAnceetor;
	}

	void GetBinaryMirror_Nor()
	{
		if (_root)
		{
			stack<Node<T>*> s;
			Node<T>* pCur = _root;
			Node<T>* pPre = NULL;

			while (pCur || !s.empty())
			{
				while (pCur)
				{
					s.push(pCur);
					pCur = pCur->_lChild;
				}

				pCur = s.top();

				if (pCur->_rChild == NULL || pPre == pCur->_rChild)
				{
					std::swap(pCur->_lChild, pCur->_rChild);
					s.pop();
					pPre = pCur;
					pCur = NULL;
				}
				else
				{
					pCur = pCur->_rChild;
				}
			}
		}
	}

	void GetBinaryMirror()
	{
		GetBinaryMirror(_root);
	}

	bool IsCompleteBinaryTree()
	{
		if (_root)
		{
			queue<Node<T>*> q;
			Node<T>* pCur = _root;
			q.push(pCur);

			while (!q.empty())
			{
				pCur = q.front();
				q.pop();
				if (pCur->_lChild != NULL && pCur->_rChild != NULL)
				{
					q.push(pCur->_lChild);
					q.push(pCur->_rChild);
				}
				else if (pCur->_rChild)
				{
					return false;
				}
				else
				{
					if (pCur->_lChild)
						q.push(pCur->_lChild);

					while (!q.empty())
					{
						pCur = q.top();
						if (NULL == pCur->_lChild && NULL == pCur->_rChild)
							q.pop();
						else
							return false;
					}

					return true;
				}
			}
		}

		return false;
	}

private:

	void Copy(Node<T>*& root, const Node<T>* t)
	{
		if (t == NULL)
			return;
		root = new Node<T>(t->_data);
		Copy(root->_lChild, t->_lChild);
		Copy(root->_rChild, t->_rChild);
	}

	void InsOrderTraverse(const Node<T>* root)
	{
		if (NULL == root)
		{
			return;
		}

		InsOrderTraverse(root->_lChild);
		cout << root->_data << " ";
		InsOrderTraverse(root->_rChild);
	}

	void PosOrderTraverse(const Node<T>* root)
	{
		if (NULL == root)
		{
			return;
		}

		PosOrderTraverse(root->_lChild);
		PosOrderTraverse(root->_rChild);
		cout << root->_data << " ";
	}

	void PreOrderTraverse(const Node<T>* root)
	{
		if (NULL == root)
		{
			return;
		}

		cout << root->_data << " ";
		PreOrderTraverse(root->_lChild);
		PreOrderTraverse(root->_rChild);
	}

	void CreateBinTreePreOrder(Node<T>*& root)
	{
		T ch;
		cin >> ch;
		if ('#' == ch)
		{
			root = NULL;
		}
		else
		{
			root = new Node<T>(ch);
			CreateBinTreePreOrder(root->_lChild);
			CreateBinTreePreOrder(root->_rChild);
		}
	}

	void CreateBinTreePreOrder(Node<T>*& root, const T array[], const  size_t size, size_t& i, const T invalue)
	{
		if (i < size && array[i] != invalue)
		{
			root = new Node<T>(array[i]);
			CreateBinTreePreOrder(root->_lChild, array, size, ++i, invalue);
			CreateBinTreePreOrder(root->_rChild, array, size, ++i, invalue);
		}
	}

	void LevelOrder(Node<T>* root)
	{
		if (root)
		{
			queue<Node<T>*> q;
			q.push(root);
			while (!q.empty())
			{
				Node<T>* t = q.front();
				q.pop();
				cout << t->_data << " ";
				if (t->_lChild != NULL)
				{
					q.push(t->_lChild);
				}

				if (t->_rChild != NULL)
				{
					q.push(t->_rChild);
				}
			}
			cout << endl;
		}
	}

	void Destory(Node<T>*& root)
	{
		if (NULL == root)
		{
			return;
		}


		Destory(root->_lChild);

		Destory(root->_rChild);

		delete root;
		root = NULL;
	}

	size_t GetHigh(const Node<T>* root)
	{
		if (NULL == root)
		{
			return 0;
		}

		size_t leftcount = GetHigh(root->_lChild);
		size_t rightconnt = GetHigh(root->_rChild);

		return (leftcount > rightconnt) ? leftcount + 1 : rightconnt + 1;
	}

	void GetLeaf(Node<T>* root, size_t& count)
	{
		if (NULL == root)
		{
			return;
		}
		if (root->_lChild == NULL && root->_rChild == NULL)
		{
			count++;
			return;
		}

		GetLeaf(root->_lChild, count);
		GetLeaf(root->_rChild, count);
	}

	size_t GetLeaf(Node<T>* root)
	{
		if (NULL == root)
		{
			return 0;
		}

		if (root->_lChild == NULL && root->_rChild == NULL)
		{
			return 1;
		}

		size_t leftcount = GetLeaf(root->_lChild);
		size_t rightcount = GetLeaf(root->_rChild);
		return rightcount + leftcount;
	}

	Node<T>* GetParent(Node<T>* root, Node<T>* x)
	{
		if (NULL == root || NULL == x || x == _root)
		{
			return NULL;
		}

		if (x == root->_lChild || x == root->_rChild)
		{
			return root;
		}

		Node<T>* ptmp = NULL;
		if (ptmp = GetParent(root->_lChild, x))
		{
			return ptmp;
		}

		return GetParent(root->_rChild, x);
	}

	Node<T>* Find(Node<T>* root, const T& value)
	{
		if (NULL == root)
		{
			return NULL;
		}

		if (root->_data == value)
		{
			return root;
		}

		Node<T>* ptmp = NULL;
		if (ptmp = Find(root->_lChild, value))
		{
			return ptmp;
		}

		return Find(root->_rChild, value);
	}

	size_t GetKLevelNode(Node<T>* root, size_t k)
	{
		if (root == NULL || 0 == k)
		{
			return  0;
		}

		if (1 == k)
		{
			return 1;
		}

		size_t leftcount = GetKLevelNode(root->_lChild, k - 1);
		size_t rightcount = GetKLevelNode(root->_rChild, k - 1);
		return leftcount + rightcount;
	}

	void GetBinaryMirror(Node<T>* root)
	{
		if (root)
		{
			std::swap(root->_lChild, root->_rChild);

			GetBinaryMirror(root->_lChild);
			GetBinaryMirror(root->_rChild);
		}
	}

private:
	struct BinNode
	{
		BinNode(Node<T>* p)
			:root(p)
			, IsFirst(true)
		{}
		Node<T>* root;
		bool IsFirst;
	};
	Node<T>* _root;
};

