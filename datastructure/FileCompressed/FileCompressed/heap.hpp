#pragma once
#include <vector>
#include <assert.h>
#include <iostream>
using namespace std;


template<class T>
struct Less
{
	bool operator()(const T& left, const T& right)
	{
		return left < right;
	}
};

template<class T>
struct Greater
{
	bool operator()(const T& left, const T& ringht)
	{
		return left > ringht;
	}
};

template<class T, class Compare = Less<T>>
class Heap
{
public:

	Heap()
	{}

	Heap(const T array[], size_t size)
	{
		CreateHeap(array, size);
	}

	void FindKBigNumber(const T arr[], size_t size, size_t k)
	{

		if (size <= k)
		{
			CreateHeap(arr, size);
			return;
		}

		CreateHeap(arr, k);
		size_t i = k;
		while (i < size)
		{
			if (_heap[0] < arr[i])
			{
				_heap[0] = arr[i];
				_AdjustDown(0);
			}
			i++;
		}
	}

	size_t Size()const
	{
		return _heap.size();
	}

	T& Top()
	{
		assert(!_heap.empty());
		return _heap[0];
	}

	bool Empty()const
	{
		return _heap.empty();
	}

	void Push(const T& data)
	{
		_heap.push_back(data);
		if (_heap.size() > 1 && Compare()(data, _heap[(_heap.size() - 2) >> 1]))
		{
			_AdjustUp(_heap.size() - 1);
		}
	}

	void Pop()
	{
		assert(!Empty());
		size_t size = _heap.size();
		std::swap(_heap[0], _heap[size - 1]);
		_heap.pop_back();
		_AdjustDown(0);
	}

protected:
	void CreateHeap(const T array[], size_t size)
	{
		if (array != NULL && size != 0)
		{
			_heap.resize(size);
			for (size_t i = 0; i < size; ++i)
			{
				_heap[i] = array[i];
			}

			int root = (size - 2) >> 1;
			for (; root >= 0; root--)
			{
				_AdjustDown(root);
			}
		}

	}

	void _AdjustDown(size_t parent)
	{
		size_t size = _heap.size();

		while (size > 1 && parent <= (size - 2) >> 1)
		{
			size_t child = 2 * parent + 1;
			Compare com;
			if (child + 1 < size)
			{
				//if (_heap[child] < _heap[child + 1])
				if (com(_heap[child + 1], _heap[child]))
					child++;
			}
			//if (_heap[parent] < _heap[child])
			if (com(_heap[child], _heap[parent]))
			{
				std::swap(_heap[parent], _heap[child]);
				parent = child;
			}
			else
				return;
		}
	}


	void _AdjustUp(int child)
	{
		int parent = (child - 1) >> 1;
		while (parent >= 0)
		{
			std::swap(_heap[parent], _heap[child]);
			child = parent;
			parent = (child - 1) >> 1;
			if (parent >= 0 && Compare()(_heap[parent], _heap[child]))
				return;
		}
	}

protected:
	std::vector<T> _heap;
};