#pragma once

#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

#define PRECISION 0.00000000001

enum TYPE
{
	INT,
	DOUBLE,
	SYMBOL
};

struct Node
{
	Node(const string& str)
		: _value(str)
		, _type(INT)
		, INT_value(0)
		, DOUBLE_value(0.0)
		, _ch(0)
	{
		int flag = str.find('.');
		if (-1 != flag)
			_type = DOUBLE;

		if (_type == INT)
		{
			_itoa(_value.c_str());
		}
	}

	Node(const char ch, const TYPE& type = SYMBOL)
		: _ch(ch)
		, _type(type)
	{}

	
	string _value;
	TYPE _type;
	int INT_value;
	double DOUBLE_value;
	char _ch;
};

char Compare(char ch1, char ch2)
{
	char Relation[9][9] = { "", " >><<<>>",
		" >><<<>>", " >>>><>>",
		" >>>><>>", " <<<<<= ",
		">>>> >>", " <<<<< =" };
	int x = 0;
	int y = 0;
	switch (ch1)
	{
	case '+':
		x = 1;
		break;
	case '-':
		x = 2;
		break;
	case '*':
		x = 3;
		break;
	case '/':
		x = 4;
		break;
	case '(':
		x = 5;
		break;
	case ')':
		x = 6;
		break;
	case '#':
		x = 7;
		break;
	default:
		exit(1);
		break;
	}

	switch (ch2)
	{
	case '+':
		y = 1;
		break;
	case '-':
		y = 2;
		break;
	case '*':
		y = 3;
		break;
	case '/':
		y = 4;
		break;
	case '(':
		y = 5;
		break;
	case ')':
		y = 6;
		break;
	case '#':
		y = 7;
		break;
	default:
		exit(1);
		break;
	}

	return Relation[x][y];
}

int Operate(int left, Node* OP, int right)
{
	switch (OP->_ch)
	{
	case '-':
		return left - right;
	case '+':
		return left + right;
	case '*':
		return left * right;
	case '/':
		if (left == 0)
		{
			cout << "被除数为0" << endl;
			exit(1);
		}
		return left / right;
	case '%':
		return left % right;
	default:
		cout << "运算符出错" << endl;
		exit(2);
		break;
	}
}

double Operate(double left, Node* OP, int right)
{
	switch (OP->_ch)
	{
	case '-':
		return left - right;
	case '+':
		return left + right;
	case '*':
		return left * right;
	case '/':
		if (left > PRECISION && right < PRECISION)
		{
			cout << "被除数为0" << endl;
			exit(1);
		}
		return left / right;
	case '%':
		cout << "对小数取模出错" << endl;
		exit(3);
	default:
		cout << "运算符出错" << endl;
		exit(2);
		break;
	}
}

double Operate(double left, Node* OP, double right)
{
	switch (OP->_ch)
	{
	case '-':
		return left - right;
	case '+':
		return left + right;
	case '*':
		return left * right;
	case '/':
		if (left > PRECISION && right < PRECISION)
		{
			cout << "被除数为0" << endl;
			exit(1);
		}
		return left / right;
	case '%':
		cout << "对小数取模出错" << endl;
		exit(3);
	default:
		cout << "运算符出错" << endl;
		exit(2);
		break;
	}
}

double Operate(int left, Node* OP, double right)
{
	switch (OP->_ch)
	{
	case '-':
		return left - right;
	case '+':
		return left + right;
	case '*':
		return left * right;
	case '/':
		if (left == 0)
		{
			cout << "被除数为0" << endl;
			exit(1);
		}
		return left / right;
	case '%':
		cout << "对小数取模出错" << endl;
		exit(3);
	default:
		cout << "运算符出错" << endl;
		exit(2);
		break;
	}
}


Node* Operate(Node* left, Node* OP, Node* right)
{
	if (left->_type == INT && right->_type == INT)
	{
		int x = atoi(left->_value.c_str());
		int y = atoi(right->_value.c_str());
		x = Operate(x, OP, y);

		_itoa(x, s, 10);
		string str(s);
		return new Node(str);
	}
	else if (left->_type == INT&&right->_type == DOUBLE)
	{
		int x = atoi(left->_value.c_str());
		double y = atof(right->_value.c_str());
		y = Operate(x, OP, y);

		_
	} 
	else
	{
	}
}


bool IsOperator(char ch)
{
	if ('+' == ch || '-' == ch ||
		'*' == ch || '/' == ch ||
		'(' == ch || ')' == ch ||
		'#' == ch)
	{
		return true;
	}

	if ((ch >= '0' && ch <= '9') || ch == '.')
		return false;

	exit(1);
}

void RNPexpprssion(const string& str)
{
	vector<Node*> v;
	Node* ptmp = NULL;
	size_t pos = 0;
	for (size_t idx = 0; idx < str.size(); ++idx)
	{
		if (IsOperator(str[idx]))
		{
			string s = str.substr(pos, idx - pos);
			if (s.size()>0)
			{
				ptmp = new Node(s);
				v.push_back(ptmp);
			}

			ptmp = new Node(str[idx]);
			v.push_back(ptmp);
			pos = idx + 1;
		}
	}

	v.push_back(new Node('#'));

	stack<Node*> StackOperator;
	stack<Node*> StackNd;
	
	size_t i = 0;
	while (i<v.size() || !StackNd.empty())
	{
		ptmp = v[i];
		if (ptmp->_type != SYMBOL)
		{
			StackNd.push(ptmp);
			i++;
		}
		else
		{
			if (StackOperator.size() == 0)
			{
				StackOperator.push(ptmp);
				i++;
			}
			else
			{
				switch (Compare(StackOperator.top()->_ch,ptmp->_ch))
				{
				case '<':
					StackOperator.push(ptmp);
					i++;
					break;
				case '=':
					StackOperator.pop();
					i++;
					break;
				case '>':

					break;
				}
			}
		}
	}
}


