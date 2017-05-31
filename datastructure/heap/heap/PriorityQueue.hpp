#pragma once

#include "heap.hpp"

template<class T, class Compare = Less<T>>
class PriorityQueue
{
public:
	PriorityQueue()
	{}

	void Push(const T& data)
	{
		_hp.Push(data);
	}

	void Pop()
	{
		_hp.Pop();
	}

	const T& Top()const
	{
		_hp.Top();
	}

	size_t Size()const
	{
		return _hp.Size();
	}

	bool Empty()const
	{
		return _hp.Empty();
	}

protected:
	Heap<T, Compare> _hp;
};
