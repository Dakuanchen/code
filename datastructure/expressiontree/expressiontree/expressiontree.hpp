#pragma once

#include <iostream>
#include <stack>
#include <string>
using namespace std;

enum TYPE
{
	INT,
	DOUBLE,
	SYMBOL
};

struct ExpressionTreeNode
{
	ExpressionTreeNode(const string& str, const TYPE& type = INT)
		: _value(str)
		, _type(type)
		, _pLeft(NULL)
		, _pRight(NULL)
	{}

	ExpressionTreeNode(const char ch, const TYPE& type = SYMBOL)
		: _ch(ch)
		, _type(type)
		, _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
	{}

	ExpressionTreeNode* _pLeft;
	ExpressionTreeNode* _pRight;
	ExpressionTreeNode* _pParent;
	string _value;
	TYPE _type;
	char _ch;
};

class ExpressionTree
{
	typedef ExpressionTreeNode Node;

public:

	ExpressionTree(const string& data)
		:_pRoot(NULL)
	{
		_pRoot = _CreateTree(data);
	}

	void PosOrder(stack<Node*>& s)
	{
		_PosOrder(_pRoot, s);
	}

private:

	void _PosOrder(Node* pRoot, stack<Node*>& s)
	{
		if (pRoot)
		{
			_PosOrder(pRoot->_pLeft, s);
			_PosOrder(pRoot->_pRight, s);
			s.push(pRoot);
			if (pRoot->_type == SYMBOL)
				cout << pRoot->_ch;
			else
				cout << pRoot->_value;
		}
	}

	Node* _CreateTree(const string& data)
	{
		size_t pos = 0;
		int count = 0;
		Node* pRoot = NULL;
		Node* ptmp = NULL;
		for (size_t idx = 0; idx < data.size(); idx++)
		{
			if (data[idx] == '(')
			{
				count++;

				string str1;
				while (count && idx<data.size())
				{
					if (data[++idx] == ')')
						count--;
					else if (data[idx] == '(')
						count++;
					
					str1 += data[idx];
				}
				if (count)
				{
					cout << "À¨ºÅ²»Æ¥Åä" << endl;
					exit(1);
				}
				str1 = str1.substr(0, str1.size() - 1);
				ptmp = _CreateTree(str1);
				pos = idx + 1;
			}
			else if (data[idx] == '%' || data[idx] == '+' || data[idx] == '-' || data[idx] == '-' || data[idx] == '*')
			{
				if (NULL == ptmp)
				{
					string str = data.substr(pos, idx - pos);
					int flag = str.find('.');
					if (-1 != flag)
						_GetNode(pRoot, data[idx], str, count, DOUBLE);
					else
						_GetNode(pRoot, data[idx], str, count);
				}
				else
				{
					if (pRoot == NULL)
					{
						pRoot = new Node(data[idx]);
						pRoot->_pLeft = ptmp;
						ptmp->_pParent = pRoot;
						ptmp = NULL;
					}
					else
					{
						Node* root = pRoot;

						while (root->_pRight)
							root = root->_pRight;

						root->_pRight = new Node(data[idx]);
						root->_pRight->_pParent = root;
						root->_pRight->_pLeft = ptmp;
						ptmp->_pParent = root->_pRight;
						ptmp = NULL;
					}
				}
				
				pos = idx + 1;
			}
		}

		if (pos != 0)
		{
			if (ptmp == NULL)
			{
				string str = data.substr(pos, data.size() - pos);
				int flag = str.find('.');
				if (-1 != flag)
					ptmp = new Node(str, DOUBLE);
				else
					ptmp = new Node(str);
			}
			Node* root = pRoot;
			while (root->_pRight)
				root = root->_pRight;

			root->_pRight = ptmp;
			ptmp->_pParent = root;
		}

		return pRoot;
	}

	void _GetNode(Node*& pRoot, const char ch, const string& str, const int count, const TYPE& type = INT)
	{
		if (pRoot == NULL)
			pRoot = new Node(ch);
		
		Node* root = pRoot;
		while (root->_pRight)
			root = root->_pRight;

		if (root->_pLeft != NULL)
		{
			root->_pRight = new Node(ch);
			root->_pRight->_pParent = root;
			root = root->_pRight;
		}

		root->_pLeft = new Node(str, type);
		root->_pLeft->_pParent = root;

		Node* pParent = root->_pParent;
		if (pParent && _Taller(root))
			_RoatreL(root);
	}

	void _RoatreL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		Node* pGrandpa = pParent->_pParent;

		pSubR->_pLeft = pParent;
		pParent->_pParent = pSubR;
		pParent->_pRight = pSubRL;
		pSubRL->_pParent = pParent;
		pSubR->_pParent = pGrandpa;

		if (pGrandpa)
		{
			if (pGrandpa->_pLeft == pParent)
				pGrandpa->_pLeft = pSubR;
			else
				pGrandpa->_pRight = pSubR;
		}
		else
			_pRoot = pSubR;
	}

	bool _Taller(Node* pCur)
	{

		return false;
	}

private:
	Node* _pRoot;
};

// void Calculator(stack<ExpressionTreeNode*>& s)
// {
// 	stack<ExpressionTreeNode*> s2;
// 	ExpressionTreeNode* left;
// 	ExpressionTreeNode* right;
// 
// 	while (s.size())
// 	{
// 		left = s.top();
// 		if (left->_type==SYMBOL)
// 		{
// 			s2.push(left);
// 			s.pop();
// 		}
// 		else
// 		{
// 
// 		}
// 	}
// }

void Test()
{
	string str("((1+3)*(3+4))-(5+5)-3*6");
	stack<ExpressionTreeNode*> s;
	//cin >> str;
	ExpressionTree t(str);
	t.PosOrder(s);

}