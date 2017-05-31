#include <iostream>
#include <assert.h>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

bool IsBrackets(const char c)
{
	if ('(' == c || '[' == c || '{' == c || ')' == c || ']' == c || '}' == c)
	{
		return true;
	}
	return false;
}

bool MatchBrackets(char arr[], size_t size)
{
	stack<char> s;
	size_t i = 0;
	for (i = 0; i < size; i++)
	{
		if (IsBrackets(arr[i]))
		{
			if ('(' == arr[i] || '[' == arr[i] || '{' == arr[i])
			{
				s.push(arr[i]);
			}

			if (')' == arr[i] || ']' == arr[i] || '}' == arr[i])
			{
				if (s.empty())
				{
					cout << "ÓÒÀ¨ºÅ¶àÓÚ×óÀ¨ºÅ" << endl;
					return false;
				}

				if (')' == arr[i])
				{
					if ('(' == s.top())
					{
						s.pop();
						continue;
					}
				}

				if (']' == arr[i])
				{
					if ('[' == s.top())
					{
						s.pop();
						continue;
					}
				}

				if ('}' == arr[i])
				{
					if ('{' == s.top())
					{
						s.pop();
						continue;
					}
				}
				cout << "×óÓÒÀ¨ºÅ´ÎÐò²»Æ¥Åä" << endl;
				return false;
			}
		}
	}

	if (s.empty())
	{
		return true;
	}

	cout << "×óÀ¨ºÅ¶àÓÚÓÐÀ¨ºÅ" << endl;
	return false;
}

void NumberConvert(int num, int dest)
{
	if (2 == dest)
	{
		stack<int> s;
		while (num)
		{
			int n = num % 2;
			s.push(n);
			num /= 2;
		}

		while (!s.empty())
		{
			cout << s.top();
			s.pop();
		}
		cout << endl;
	}
	else if (8 == dest)
	{
		stack<int> s;
		while (num)
		{
			int n = num % 8;
			s.push(n);
			num /= 8;
		}

		while (!s.empty())
		{
			cout << s.top();
			s.pop();
		}
		cout << endl;
	}
	else
		return;
}

void LineEdit()
{
	stack<char> s;
	stack<char> s1;
	char ch = getchar();

	while (EOF != ch)
	{
		while (EOF != ch && '\n' != ch)
		{
			switch (ch)
			{
			case '#':
				s.pop();
				break;
			case '@':
				while (!s.empty())
				{
					s.pop();
				}
				break;
			default:
				s.push(ch);
				break;
			}
			ch = getchar();
		}

		while (!s.empty())
		{
			s1.push(s.top());
			s.pop();
		}

		while (!s1.empty())
		{
			cout << s1.top();
			s1.pop();
		}
		cout << endl;

		if (ch != EOF)
			ch = getchar();
	}
}


template<typename T>
class Queue
{
public:
	Queue()
	{}

	Queue(const Queue<T>& q)
		:s1(q.s1)
		, s2(q.s2)
	{}

	Queue<T>& operator=(const Queue<T>& q)
	{
		s1 = q.s1;
		s2 = q.s2;
	}

	~Queue()
	{}

public:

	bool Empty()
	{
		return s1.empty();
	}

	size_t Size()
	{
		return s1.size();
	}

	T Front()
	{
		if (!Empty())
		{
			while (!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
			T tmp = s2.top();

			while (!s2.empty())
			{
				s1.push(s2.top());
				s2.pop();
			}
			return tmp;
		}
		return s1.top();
	}

	T Back()
	{
		return s1.top();
	}

	void Push(T t)
	{
		s1.push(t);
	}

	void Pop()
	{
		while (!s1.empty())
		{
			while (!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
			s2.pop();

			while (!s2.empty())
			{
				s1.push(s2.top());
				s2.pop();
			}
		}
	}

private:
	stack<T> s1;
	stack<T> s2;
};

template<class T>
class Stack
{
public:
	Stack()
	{}

	~Stack()
	{}
public:

	bool Empty()
	{
		return q1.empty();
	}

	size_t Size()
	{
		return q1.size();
	}

	T Top()
	{
		return q1.back();
	}

	void Push(T t)
	{
		q1.push(t);
	}

	void Pop()
	{
		while (1 != q1.size())
		{
			q2.push(q1.front());
			q1.pop();
		}
		q1.pop();
		while (!q2.empty())
		{
			q1.push(q2.front());
			q2.pop();
		}
	}


private:
	queue<T> q1;
	queue<T> q2;
};

template<class T>
class Stack1
{
public:
	Stack1()
	{}

	size_t Size()
	{
		return s1.size();
	}

	bool Empty()
	{
		return s1.empty();
	}

	void Push(T data)
	{
		s1.push(data);
		if (s2.empty())
		{
			s2.push(data);
			//s1.push(data);
			return;
		}
		if (data <= s2.top())
		{
			s2.push(data);
		}
	}

	T& Min()
	{
		assert(s1.size() > 0 && s2.size() > 0);
		return s2.top();
	}

	void Pop()
	{
		assert(s1.size() > 0 && s2.size() > 0);

		if (s2.top() == s1.top())
			s2.pop();
		s1.pop();
	}

private:
	stack<T> s1;
	stack<T> s2;
};

template<class T>
class Stack2
{
public:
	Stack2(size_t cap)
		: _cap(cap)
		, _s2(cap - 1)
		, _s1_size(0)
		, _s2_size(0)
		, _pData(new T[cap])
	{}

	void s1_pop()
	{
		_s1_size--;
		_size--;
	}

	void s2_pop()
	{
		_s2++;
		_size--;
		_s2_size--;
	}

	void s1_push(T data)
	{
		if (_size == _cap)
		{
			cout << "¿Õ¼ä²»×ã" << endl;
			return;
		}
		_pData[_s1_size++] = data;
		_size++;
	}

	void s2_push(T data)
	{
		if (_size == _cap)
		{
			cout << "¿Õ¼ä²»×ã" << endl;
			return;
		}
		_pData[_s2--] = data;
		_s2_size++;
		_size++;
	}

	T& s2_top()
	{
		assert(_s2_size);

		return _pData[_s2];
	}

	T& s1_top()
	{

	}

	~Stack2()
	{
		if (_pDtat)
		{
			delete[] _pData;
			_pData = NULL;
		}
	}

private:
	void Getmemory()
	{
		T* pData = new T[_cap * 2];
		memcpy(pData, _pData, _s1_size * sizeof(T));
		memcpy(pData + _s2 + _cap, _pData + _s2, _s2_size * sizeof(T));
		_s2 += _cap;
		_cap *= 2;
	}

private:
	size_t _size;
	size_t _cap;
	size_t _s2;
	size_t _s1_size;
	size_t _s2_size;
	T*  _pData;
};

bool IsPopOrder(const int* pPush, const int* pPop, int nLength)
{
	if (pPush != NULL && pPop != NULL && nLength > 0)
	{
		const int* pNextPush = pPush;
		const int* pNextPop = pPop;

		stack<int> StackData;

		while (pNextPop - pPop < nLength)
		{
			while (StackData.empty() || StackData.top() != *pNextPop)
			{
				if (pNextPush - pPush == nLength)
				{
					break;
				}

				StackData.push(*pNextPush);
				pNextPush++;
			}

			if (StackData.top() != *pNextPop)
			{
				break;
			}

			StackData.pop();
			pNextPop++;
		}

		if (StackData.empty() && pNextPop - pPop == nLength)
			return true;
	}

	return false;
}

void KnapsackProblem(size_t t, size_t arr[], size_t size)
{
	if (0 == t || size == 0)
	{
		return;
	}

	stack<size_t> s1;
	stack<size_t> s2;
	size_t i = 0;
	while (i < size)
	{
		if (arr[i] < t)
		{

		}
	}
}

int main()
{
	return 0;
}