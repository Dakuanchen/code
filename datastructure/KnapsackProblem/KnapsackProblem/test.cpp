#include <vector>
#include <assert.h>
#include <iostream>
using namespace std;


template<class T>
class Stack
{
public:
	Stack()
	{}

	void Pop()
	{
		v.pop_back();
	}

	void Push(const T data)
	{
		v.push_back(data);
	}

	size_t Size()
	{
		return v.size();
	}

	T& Top()
	{
		assert(!v.empty());
		return v[v.size() - 1];
	}

	bool Empty()
	{
		return v.empty();
	}

	size_t Sum()
	{
		size_t sum = 0;
		size_t size = v.size();
		size_t i = 0;
		while (i < size)
			sum += v[i++];

		return sum;
	}

private:
	vector<T> v;
};

int main()
{
	Stack<int> s;
	int arr[6] = { 1, 8, 4, 3, 5, 2 };
	int sum = 10;
	int count = 0;
	for (size_t j = 0; j < 6;)
	{
		for (size_t i = j; i < 6; ++i)
		{
			s.Push(arr[i]);
			count = s.Sum();
			if (count == sum)
			{
				while (!s.Empty())
				{
					cout << s.Top() << ' ';
					s.Pop();
				}
				cout << endl;
				break;
			}
			else if (count > sum)
			{
				s.Pop();
			}
		}

		if (!s.Empty())
		{
			s.Pop();
		}

	}
	

	return 0;
}